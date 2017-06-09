/* LangDataMap.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: Applied CondLangLR1
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/lang/LangDataMap.h>

#include <CCore/inc/Print.h>
#include <CCore/inc/FileName.h>
#include <CCore/inc/FileToMem.h>
#include <CCore/inc/MemAllocGuard.h>

#include <CCore/inc/ddl/DDLEngine.h>
#include <CCore/inc/ddl/DDLTypeSet.h>

#include <CCore/inc/Exception.h>

namespace CCore {
namespace Lang {

/* TypeSet */

#include <CCore/src/lang/LangData.TypeSet.gen.h>

/* class DataMap */

StrLen DataMap::Pretext()
 {
  return
"  type AtomIndex = uint32 ;"
"  type SyntIndex = uint32 ;"
"  type KindIndex = uint32 ;"
"  type ElementIndex = uint32 ;"
"  type RuleIndex = uint32 ;"
"  type StateIndex = uint32 ;"
"  type FinalIndex = uint32 ;"

"  struct Lang"
"   {"
"    Atom[] atoms;"
"    Synt[] synts;"
"    Synt * [] lang;"
"    Element[] elements;"
"    Rule[] rules;"
"    TopRule[] top_rules;"
"    State[] states;"
"    Final[] finals;"
"   };"

"  struct Atom"
"   {"
"    AtomIndex index;"
"    text name;"

"    Element *element;"
"   };"

"  struct Synt"
"   {"
"    SyntIndex index;"
"    text name;"

"    Kind[] kinds;"
"    Rule * [] rules;"
"   };"

"  struct Kind"
"   {"
"    KindIndex kindex;"
"    KindIndex index;"
"    text name;"

"    Synt *synt;"

"    Element *element;"

"    TopRule * [] rules;"
"   };"

"  struct Element"
"   {"
"    ElementIndex index;"

"    {Atom,Kind} * elem;"
"   };"

"  struct Rule"
"   {"
"    RuleIndex index;"
"    text name;"

"    Kind *result;"

"    type Arg = {Atom,Synt} * ;"

"    Arg[] args;"
"   };"

"  struct TopRule"
"   {"
"    RuleIndex index;"
"    text name;"

"    Rule *bottom;"

"    Kind *result;"

"    type Arg = {Atom,Kind} * ;"

"    Arg[] args;"
"   };"

"  struct State"
"   {"
"    StateIndex index;"
"    Final *final;"

"    struct Transition"
"     {"
"      Element *element;"
"      State *state;"
"     };"

"    Transition[] transitions;"
"   };"

"  struct Final"
"   {"
"    FinalIndex index;"

"    struct Action"
"     {"
"      Atom *atom;"
"      Rule *rule;"
"     };"

"    Action[] actions;"
"   };"_c;
 }

template <class T>
bool DataMap::Checkin(T *ptr,PtrLen<T> range)
 {
  if( ptr==0 ) return false;

  ulen index=ptr->index;

  return index<range.len && ptr==range.ptr+index ;
 }

template <class T>
bool DataMap::Checkin_null(T *ptr,PtrLen<T> range)
 {
  if( ptr==0 ) return true;

  ulen index=ptr->index;

  return index<range.len && ptr==range.ptr+index ;
 }

void DataMap::load(StrLen file_name,PrintBase &eout)
 {
  DDL::FileEngine<FileName,FileToMem> engine(eout);

  auto result=engine.process(file_name,Pretext());

  eout.flush();

  if( !result )
    {
     Printf(Exception,"CCore::Lang::DataMap::DataMap(...) : input file processing error");
    }
  else
    {
     DDL::TypedMap<TypeSet> map(result);
     MemAllocGuard guard(map.getLen());

     map(guard);

     lang=map.takeConst<TypeDef::Lang>("lang");

     mem=guard.disarm();
    }
 }

DataMap::DataMap(StrLen file_name)
 {
  PrintCon eout;

  load(file_name,eout);
 }

DataMap::DataMap(StrLen file_name,PrintBase &eout)
 {
  load(file_name,eout);
 }

DataMap::~DataMap()
 {
  MemFree(mem);
 }

 // sanity

void DataMap::sanity_atoms()
 {
  auto atoms=lang.atoms.getRange();
  auto elements=lang.elements.getRange();

  if( !atoms )
    {
     Printf(Exception,"CCore::Lang::DataMap::sanity_atoms(...) : no atoms");
    }

  for(ulen i=0; i<atoms.len ;i++)
    {
     auto &atom=atoms[i];

     if( atom.index!=i )
       {
        Printf(Exception,"CCore::Lang::DataMap::sanity_atoms(...) : bad atom #; index",i);
       }

     auto *element=atom.element.getPtr();

     if( !Checkin(element,elements) || element->index!=i || element->elem.getPtr().castPtr<TypeDef::Atom>()!=&atom )
       {
        Printf(Exception,"CCore::Lang::DataMap::sanity_atoms(...) : bad atom #; element",i);
       }
    }
 }

void DataMap::sanity_synts()
 {
  auto synts=lang.synts.getRange();
  auto elements=lang.elements.getRange();
  auto top_rules=lang.top_rules.getRange();
  auto rules=lang.rules.getRange();

  ulen eindex=lang.atoms.len;
  ulen kindex=0;

  if( !synts )
    {
     Printf(Exception,"CCore::Lang::DataMap::sanity_synts(...) : no synts");
    }

  for(ulen i=0; i<synts.len ;i++)
    {
     auto &synt=synts[i];

     if( synt.index!=i )
       {
        Printf(Exception,"CCore::Lang::DataMap::sanity_synts(...) : bad synt #; index",i);
       }

     auto kinds=synt.kinds.getRange();

     if( !kinds )
       {
        Printf(Exception,"CCore::Lang::DataMap::sanity_synts(...) : bad synt #; , no kinds",i);
       }

     for(ulen j=0; j<kinds.len ;j++,eindex++)
       {
        auto &kind=kinds[j];

        if( kind.kindex!=kindex )
          {
           Printf(Exception,"CCore::Lang::DataMap::sanity_synts(...) : bad synt #; , bad kind #; kindex",i,j);
          }

        kindex++;

        if( kind.index!=j )
          {
           Printf(Exception,"CCore::Lang::DataMap::sanity_synts(...) : bad synt #; , bad kind #; index",i,j);
          }

        if( kind.synt.getPtr()!=&synt )
          {
           Printf(Exception,"CCore::Lang::DataMap::sanity_synts(...) : bad synt #; , bad kind #; synt",i,j);
          }

        auto *element=kind.element.getPtr();

        if( !Checkin(element,elements) || element->index!=eindex || element->elem.getPtr().castPtr<TypeDef::Kind>()!=&kind )
          {
           Printf(Exception,"CCore::Lang::DataMap::sanity_synts(...) : bad synt #; , bad kind #; element",i,j);
          }

        if( !kind.rules.getRange() )
          {
           Printf(Exception,"CCore::Lang::DataMap::sanity_synts(...) : bad synt #; , bad kind #; , no rules",i,j);
          }

        for(auto rule : kind.rules.getRange() )
          if( !Checkin(rule.getPtr(),top_rules) || rule->result.getPtr()!=&kind )
            {
             Printf(Exception,"CCore::Lang::DataMap::sanity_synts(...) : bad synt #; , bad kind #; rules",i,j);
            }
       }

     if( !synt.rules.getRange() )
       {
        Printf(Exception,"CCore::Lang::DataMap::sanity_synts(...) : bad synt #; , no rules",i);
       }

     for(auto rule : synt.rules.getRange() )
       if( !Checkin(rule.getPtr(),rules) || !rule->result.getPtr() || rule->result->synt.getPtr()!=&synt )
         {
          Printf(Exception,"CCore::Lang::DataMap::sanity_synts(...) : bad synt #; , bad rules",i);
         }
    }

  if( eindex!=elements.len )
    {
     Printf(Exception,"CCore::Lang::DataMap::sanity_synts(...) : extra elements");
    }
 }

void DataMap::sanity_lang()
 {
  auto synts=lang.synts.getRange();
  auto langs=lang.lang.getRange();

  if( !langs )
    {
     Printf(Exception,"CCore::Lang::DataMap::sanity_lang(...) : no lang synts");
    }

  for(auto synt : langs )
    if( !Checkin(synt.getPtr(),synts) )
      {
       Printf(Exception,"CCore::Lang::DataMap::sanity_lang(...) : bad lang synt");
      }
 }

void DataMap::sanity_rules()
 {
  auto rules=lang.rules.getRange();
  auto synts=lang.synts.getRange();
  auto atoms=lang.atoms.getRange();

  for(ulen i=0; i<rules.len ;i++)
    {
     auto &rule=rules[i];

     if( rule.index!=i )
       {
        Printf(Exception,"CCore::Lang::DataMap::sanity_rules(...) : bad rule #; index",i);
       }

     auto *result=rule.result.getPtr();

     if( !result || !Checkin(result->synt.getPtr(),synts) || !Checkin(result,result->synt->kinds.getRange()) )
       {
        Printf(Exception,"CCore::Lang::DataMap::sanity_rules(...) : bad rule #; result",i);
       }

     for(auto arg : rule.args.getRange() )
       {
        using AtomsType = decltype(atoms) ;
        using SyntsType = decltype(synts) ;

        struct Func
         {
          AtomsType atoms;
          SyntsType synts;
          ulen i;

          Func(AtomsType atoms_,SyntsType synts_,ulen i_) : atoms(atoms_),synts(synts_),i(i_) {}

          void operator () (TypeDef::Atom *atom)
           {
            if( !Checkin(atom,atoms) )
              {
               Printf(Exception,"CCore::Lang::DataMap::sanity_rules(...) : bad rule #; args",i);
              }
           }

          void operator () (TypeDef::Synt *synt)
           {
            if( !Checkin(synt,synts) )
              {
               Printf(Exception,"CCore::Lang::DataMap::sanity_rules(...) : bad rule #; args",i);
              }
           }
         };

        if( !arg.getPtr() )
          {
           Printf(Exception,"CCore::Lang::DataMap::sanity_rules(...) : bad rule #; args",i);
          }

        arg.getPtr().apply(Func(atoms,synts,i));
       }
    }
 }

void DataMap::sanity_top_rules()
 {
  auto top_rules=lang.top_rules.getRange();
  auto rules=lang.rules.getRange();

  for(ulen i=0; i<top_rules.len ;i++)
    {
     auto &rule=top_rules[i];

     if( rule.index!=i )
       {
        Printf(Exception,"CCore::Lang::DataMap::sanity_top_rules(...) : bad top rule #; index",i);
       }

     auto *bottom=rule.bottom.getPtr();

     if( !Checkin(bottom,rules) )
       {
        Printf(Exception,"CCore::Lang::DataMap::sanity_top_rules(...) : bad top rule #; bottom",i);
       }

     if( rule.result.getPtr()!=bottom->result.getPtr() )
       {
        Printf(Exception,"CCore::Lang::DataMap::sanity_top_rules(...) : bad top rule #; result",i);
       }

     auto args=rule.args.getRange();
     auto bottom_args=bottom->args.getRange();

     if( args.len!=bottom_args.len )
       {
        Printf(Exception,"CCore::Lang::DataMap::sanity_top_rules(...) : bad top rule #; args",i);
       }

     for(ulen j=0; j<args.len ;j++)
       {
        using Type = decltype(bottom_args) ;

        struct Func
         {
          Type bottom_args;
          ulen i;
          ulen j;

          Func(Type bottom_args_,ulen i_,ulen j_) : bottom_args(bottom_args_),i(i_),j(j_) {}

          void operator () (TypeDef::Atom *atom)
           {
            if( bottom_args[j].getPtr().castPtr<TypeDef::Atom>()!=atom )
              {
               Printf(Exception,"CCore::Lang::DataMap::sanity_top_rules(...) : bad top rule #; args",i);
              }
           }

          void operator () (TypeDef::Kind *kind)
           {
            auto *synt=bottom_args[j].getPtr().castPtr<TypeDef::Synt>();

            if( !synt || !Checkin(kind,synt->kinds.getRange()) )
              {
               Printf(Exception,"CCore::Lang::DataMap::sanity_top_rules(...) : bad top rule #; args",i);
              }
           }
         };

        if( !args[j].getPtr() )
          {
           Printf(Exception,"CCore::Lang::DataMap::sanity_top_rules(...) : bad top rule #; args",i);
          }

        args[j].getPtr().apply(Func(bottom_args,i,j));
       }
    }
 }

void DataMap::sanity_states()
 {
  auto states=lang.states.getRange();
  auto finals=lang.finals.getRange();
  auto elements=lang.elements.getRange();

  if( !states )
    {
     Printf(Exception,"CCore::Lang::DataMap::sanity_states(...) : no states");
    }

  for(ulen i=0; i<states.len ;i++)
    {
     auto &state=states[i];

     if( state.index!=i )
       {
        Printf(Exception,"CCore::Lang::DataMap::sanity_states(...) : bad state #; index",i);
       }

     if( !Checkin(state.final.getPtr(),finals) )
       {
        Printf(Exception,"CCore::Lang::DataMap::sanity_states(...) : bad state #; final",i);
       }

     for(auto p=state.transitions.getRange(); +p ;++p)
       {
        if( !Checkin(p->element.getPtr(),elements) || !Checkin(p->state.getPtr(),states) )
          {
           Printf(Exception,"CCore::Lang::DataMap::sanity_states(...) : bad state #; transitions",i);
          }
       }

     for(auto p=state.transitions.getRange(); p.len>1 ;++p)
       if( p[0].element->index>=p[1].element->index )
         {
          Printf(Exception,"CCore::Lang::DataMap::sanity_states(...) : bad state #; transitions",i);
         }
    }
 }

void DataMap::sanity_finals()
 {
  auto finals=lang.finals.getRange();
  auto atoms=lang.atoms.getRange();
  auto rules=lang.rules.getRange();

  for(ulen i=0; i<finals.len ;i++)
    {
     auto &final=finals[i];

     if( final.index!=i )
       {
        Printf(Exception,"CCore::Lang::DataMap::sanity_finals(...) : bad final #; index",i);
       }

     for(auto action : final.actions.getRange() )
       {
        if( !Checkin_null(action.atom.getPtr(),atoms) || !Checkin_null(action.rule.getPtr(),rules) )
          {
           Printf(Exception,"CCore::Lang::DataMap::sanity_finals(...) : bad final #; actions",i);
          }
       }

     {
      auto actions=final.actions.getRange();

      if( +actions && !actions->atom ) ++actions;

      for(auto p=actions; +p ;++p)
        if( !p->atom )
          {
           Printf(Exception,"CCore::Lang::DataMap::sanity_finals(...) : bad final #; actions",i);
          }

      for(auto p=actions; p.len>1 ;++p)
        if( p[0].atom->index>=p[1].atom->index )
          {
           Printf(Exception,"CCore::Lang::DataMap::sanity_finals(...) : bad final #; actions",i);
          }
     }
    }
 }

void DataMap::sanity()
 {
  sanity_atoms();
  sanity_synts();
  sanity_lang();
  sanity_rules();
  sanity_top_rules();
  sanity_states();
  sanity_finals();
 }

} // namespace Lang
} // namespace CCore

