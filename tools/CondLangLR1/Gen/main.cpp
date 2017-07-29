/* main.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: ParserGen 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/Print.h>
#include <CCore/inc/Exception.h>
#include <CCore/inc/PrintStem.h>

#include <CCore/inc/lang/LangDataMap.h>

using namespace CCore;
using namespace CCore::Lang;

/* Main() */

void Main(StrLen ddl_file_name,StrLen class_name,StrLen h_file_name,StrLen cpp_file_name)
 {
  DataMap map(ddl_file_name);

  map.sanity();

  PrintFile outh(h_file_name);
  PrintFile outc(cpp_file_name);

  // 1

  {
   Printf(outh,"/* enum AtomClass */\n\n");

   Printf(outh,"enum AtomClass\n");
   Printf(outh," {\n");
   Printf(outh,"  AtomNull = 0,\n\n");

   map.atoms( [&] (auto atom_index,StrLen name)
                  {
                   Printf(outh,"  Atom_XXX_#; = #;,  /*  #;  */\n",atom_index,atom_index,name);
                  } );

   Printf(outh," };\n\n");

   Printf(outh,"const char * GetTextDesc(AtomClass ac);\n\n");

   Printf(outh,"/* struct #; */\n\n",class_name);

   Printf(outh,"struct #;\n",class_name);
   Printf(outh," {\n");

   Printf(outh,"  using Rule = int ;\n\n");

   Printf(outh,"  static const Rule NoRule = -1 ;\n\n");
   Printf(outh,"  static const Rule ShiftRule = 0 ;\n\n");

   Printf(outh,"  using ElementIndex = int ;\n\n");

   Printf(outh,"  using Property = Rule (*)(AtomClass) ;\n\n");

   Printf(outh,"  struct State;\n\n");

   Printf(outh,"  using Transition = const State * (*)(ElementIndex) ;\n\n");

   Printf(outh,"  static ElementIndex RuleOutput(Rule rule);\n\n");

   Printf(outh,"  static ElementIndex AtomToElement(AtomClass ac) { return ac; }\n\n");

   Printf(outh,"  struct State\n");
   Printf(outh,"   {\n");
   Printf(outh,"    Property prop;\n");
   Printf(outh,"    Transition trans;\n");
   Printf(outh,"   };\n\n");

   Printf(outh,"  static const State *const Start;\n\n");

   Printf(outh,"  struct Element;\n\n");

   Printf(outh,"  struct ElementAtom;\n\n");

   map.synts( [&] (StrLen name,auto rule_list)
                  {
                   Used(rule_list);

                   Printf(outh,"  struct Element_#;;\n",name);
                  } );

   Printf(outh,"\n  static auto Apply(Rule rule,auto func);\n");

   Printf(outh," };\n\n");

   Printf(outh,"struct #;::Element // TODO\n",class_name);
   Printf(outh," {\n");
   Printf(outh,"  using RetType = void ;\n\n");
   Printf(outh,"  using ContextType = int ;\n\n");
   Printf(outh," };\n\n");

   Printf(outh,"struct #;::ElementAtom : Element // TODO\n",class_name);
   Printf(outh," {\n");
   Printf(outh,"  // TODO\n");
   Printf(outh," };\n\n");

   map.synts( [&] (StrLen synt_name,auto rule_list)
                  {
                   Printf(outh,"struct #;::Element_#; : Element\n",class_name,synt_name);
                   Printf(outh," {\n");
                   Printf(outh,"  // TODO\n\n");

                   rule_list( [&] (StrLen rule_name,auto arg_list)
                                  {
                                   Printf(outh,"  RetType #;(ContextType",rule_name);

                                   arg_list( [&] (bool is_atom,StrLen name)
                                                 {
                                                  if( is_atom )
                                                   {
                                                    Printf(outh,",ElementAtom *");
                                                   }
                                                  else
                                                   {
                                                    Printf(outh,",Element_#; *",name);
                                                   }

                                                 } );

                                   Printf(outh,");\n\n");
                                  } );

                   Printf(outh," };\n\n");
                  } );

   Printf(outh,"auto #;::Apply(Rule rule,auto func)\n",class_name);
   Printf(outh," {\n");
   Printf(outh,"  switch( rule )\n");
   Printf(outh,"    {\n");

   map.rules( [&] (auto rule_index,StrLen synt_name,StrLen rule_name,auto element_index)
                  {
                   Printf(outh,"     case #; : return func(&Element_#;::#;,ElementIndex(#;));\n",rule_index,synt_name,rule_name,element_index);
                  } );

   Printf(outh,"\n     default: return func();\n");

   Printf(outh,"    }\n");

   Printf(outh," };\n\n");
  }

  // 2

  {
   Printf(outc,"/* enum AtomClass */\n\n");

   Printf(outc,"const char * GetTextDesc(AtomClass ac)\n");
   Printf(outc," {\n");
   Printf(outc,"  switch( ac )\n");
   Printf(outc,"    {\n");
   Printf(outc,"     case 0 : return \"(Null)\";\n");

   map.atoms( [&] (auto atom_index,StrLen name)
                  {
                   Printf(outc,"     case #; : return \"#;\";\n",atom_index,name);
                  } );

   Printf(outc,"\n     default: return \"???\";\n");
   Printf(outc,"    }\n");
   Printf(outc," }\n\n");
  }

  // 3

  {
   Printf(outc,"/* struct #; */\n\n",class_name);

   Printf(outc,"auto #;::RuleOutput(Rule rule) -> ElementIndex\n",class_name);
   Printf(outc," {\n");
   Printf(outc,"  switch( rule )\n");
   Printf(outc,"    {\n");

   map.rules( [&] (auto rule_index,StrLen synt_name,StrLen rule_name,auto element_index)
                  {
                   Used(synt_name);
                   Used(rule_name);

                   Printf(outc,"     case #; : return #;;\n",rule_index,element_index);
                  } );

   Printf(outc,"\n     default: return 0;\n");
   Printf(outc,"    }\n");
   Printf(outc," }\n\n");
  }

  // 4

  ulen state_count=map.getStatesCount();

  {
   map.finals( [&] (auto final_index,auto action_list)
                   {
                    Printf(outc,"static #;::Rule Prop#;(AtomClass ac)\n",class_name,final_index);
                    Printf(outc," {\n");
                    Printf(outc,"  switch( ac )\n");
                    Printf(outc,"    {\n");

                    action_list( [&] (auto atom_index,auto rule_index)
                                     {
                                      Printf(outc,"     case #; : return #;;\n",atom_index,rule_index);
                                     } );

                    Printf(outc,"\n     default: return -1;\n");
                    Printf(outc,"    }\n");
                    Printf(outc," }\n\n");
                   } );

   Printf(outc,"static const #;::State * TransNone(#;::ElementIndex)\n",class_name,class_name);
   Printf(outc," {\n");
   Printf(outc,"  return 0;\n");
   Printf(outc," }\n\n");

   map.states( [&] (auto state_index,auto final_index,auto trans_list)
                   {
                    Used(final_index);

                    if( !trans_list ) return;

                    Printf(outc,"static const #;::State * Trans#;(#;::ElementIndex ei)\n",class_name,state_index,class_name);
                    Printf(outc," {\n");
                    Printf(outc,"  switch( ei )\n");
                    Printf(outc,"    {\n");

                    trans_list( [&] (auto element_index,auto state_index)
                                    {
                                     Printf(outc,"     case #; : return #;::Start+#;;\n",element_index,class_name,state_index);
                                    } );

                    Printf(outc,"\n     default: return 0;\n");
                    Printf(outc,"    }\n");
                    Printf(outc," }\n\n");
                   } );

   Printf(outc,"static const #;::State StateList[#;]=\n",class_name,state_count);
   Printf(outc," {");

   PrintFirst stem("\n  ",",\n  ");

   map.states( [&] (auto state_index,auto final_index,auto trans_list)
                   {
                    if( +trans_list )
                      Printf(outc,"#;{Prop#;,Trans#;}",stem,final_index,state_index);
                    else
                      Printf(outc,"#;{Prop#;,TransNone}",stem,final_index);
                   } );

   Printf(outc,"\n };\n\n");

   Printf(outc,"const #;::State *const #;::Start=StateList;\n\n",class_name,class_name);
  }
 }

/* main() */

int main(int argc,const char *argv[])
 {
  try
    {
     ReportException report;

     {
      Printf(Con,"--- ParserGen 1.00 ---\n--- Copyright (c) 2017 Sergey Strukov. All rights reserved. ---\n\n");

      if( argc!=5 )
        {
         Printf(Con,"Usage: CCore-ParserGen <Lang.ddl> <ClassName> <Lang.gen.h> <Lang.gen.cpp>\n");

         return 1;
        }

      Main(argv[1],argv[2],argv[3],argv[4]);
     }

     report.guard();

     return 0;
    }
  catch(CatchType)
    {
     return 1;
    }
 }


