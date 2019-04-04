/* Engine.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: VMakeList 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/Engine.h>

#include <CCore/inc/MakeFileName.h>
#include <CCore/inc/FileSystem.h>
#include <CCore/inc/ScanRange.h>

#include <CCore/inc/Exception.h>

namespace App {

/* class FindFiles */

class FindFiles::Proc : NoCopy
 {
   FindFiles &obj;

  private:

   static bool SkipDir(StrLen name)
    {
     return name.len && name[0]=='.' ;
    }

   static bool SkipFile(StrLen name)
    {
     return name.len && name[0]=='.' ;
    }

  public:

   explicit Proc(FindFiles &obj_) : obj(obj_) {}

   using DataType = void ;

   DataType * dir(StrLen root)
    {
     Used(root);

     return this;
    }

   DataType * dir(StrLen path,StrLen name,DataType *parent_data)
    {
     Used(path);

     if( !parent_data || SkipDir(name) ) return 0;

     return this;
    }

   void file(StrLen path,StrLen name,DataType *parent_data)
    {
     if( !parent_data || SkipFile(name) ) return;

     obj.appendFile(path,name);
    }

   void enddir(StrLen path,StrLen name,DataType *data)
    {
     Used(path);
     Used(name);
     Used(data);
    }
 };

void FindFiles::appendFile(StrLen path,StrLen name)
 {
  if( path.hasSuffix("/."_c) )
    {
     path.len-=2;
    }

  if( path.hasPrefix("././"_c) )
    {
     path+=2;
    }

  if( name.hasSuffix(".cpp"_c) )
    {
     cpp_list.append_fill(pool.cat(path,"/"_c,name),name.len);
    }
  else if( name.hasSuffix(".s"_c) )
    {
     asm_list.append_fill(pool.cat(path,"/"_c,name),name.len);
    }
 }

void FindFiles::append(StrLen dir)
 {
  DirTreeRun dev(dir);
  Proc proc(*this);

  dev.apply(proc);
 }

FindFiles::FindFiles(PtrLen<DDL::MapText> dir_list)
 {
  for(StrLen dir : dir_list ) append(dir);
 }

/* class Engine */

template <class Func>
bool Engine::Walk(StrLen path,Func func)
 {
  SplitPath split(path);

  SplitPathName split1(split.path);

  while( split1.path.len )
    {
     if( !func(path.prefix(split.dev.len+split1.path.len)) ) return false;

     split1=SplitPathName(split1.path);
    }

  if( !split1.no_path )
    {
     if( !func(path.prefix(split.dev.len+1)) ) return false;
    }

  return true;
 }

void Engine::prepareRoot()
 {
  if( !root )
    {
     FileSystem fs;

     char temp[MaxPathLen+1];

     ulen count = 0 ;

     auto func = [&] (StrLen dir)
                     {
                      //Printf(Con,"try #.q;\n",dir);

                      MakeFileName file(dir,"host.vm.ddl"_c);

                      if( fs.getFileType(file.get())==FileType_file ) return false;

                      count++;

                      return true;

                     } ;

     if( Walk(fs.pathOf(src_file_name,temp),func) )
       {
        Printf(Exception,"App : CCORE not found");
       }

     if( count )
       {
        PrintString out;

        Putobj(out,".."_c);

        for(count--; count ;count--) Putobj(out,"/.."_c);

        auto_root=out.close();
       }
     else
       {
        auto_root="."_c;
       }

     root=Range(auto_root);

     Printf(Con,"Use auto root #.q;\n",root);
    }
 }

void Engine::prepareTarget()
 {
  if( !target )
    {
     MakeFileName file(root,"host.vm.ddl"_c);

     TargetFile data(file.get());

     def_target=data.getTarget();

     target=Range(def_target);

     if( !target )
       {
        Printf(Exception,"App : empty default target");
       }

     Printf(Con,"Use default target #.q;\n",target);
    }
 }

void Engine::prepareTools()
 {
  if( !tools )
    {
     MakeString<MaxPathLen> temp;

     temp.add("Target"_c,'/',target,'/',"tools.vm.ddl"_c);

     MakeFileName file(root,temp.get());

     def_tools.create(file.get());

     tools=def_tools->getTools();
    }
 }

bool Engine::TestSingle(StrLen str)
 {
  if( !str ) return false;

  if( str[0]!='#' || str.back(1)!=';' ) return false;

  for(char ch : str.inner(1,1) ) if( ch==';' ) return false;

  return true;
 }

template <class Func>
void Engine::printBy(PrinterType &,Func)
 {
  Printf(Exception,"App : incompatible variable value");
 }

template <FuncArgType<PrintBase &> Func>
void Engine::printBy(PrinterType &out,Func func)
 {
  func(out);
 }

void Engine::printVarExt(PrinterType &,StrLen str)
 {
  Printf(Exception,"App : unknown variable #.q;",str);
 }

template <class FuncSrc,class FuncDst>
void Engine::printVarExt(PrinterType &out,StrLen str,FuncSrc psrc,FuncDst pdst)
 {
  if( str.equal("SRC"_c) )
    {
     printBy(out,psrc);

     return;
    }

  if( str.equal("DST"_c) )
    {
     printBy(out,pdst);

     return;
    }

  Printf(Exception,"App : unknown variable #.q;",str);
 }

template <class FuncSrc,class FuncDst,class FuncObj>
void Engine::printVarExt(PrinterType &out,StrLen str,FuncSrc psrc,FuncDst pdst,FuncObj pobj)
 {
  if( str.equal("SRC"_c) )
    {
     printBy(out,psrc);

     return;
    }

  if( str.equal("DST"_c) )
    {
     printBy(out,pdst);

     return;
    }

  if( str.equal("OBJ"_c) )
    {
     printBy(out,pobj);

     return;
    }

  Printf(Exception,"App : unknown variable #.q;",str);
 }

template <class ... TT>
void Engine::printVar(PrinterType &out,StrLen str,TT ... tt)
 {
  LockUse lock(level);

  auto printFrame = [&] (StrLen str) { Printf(out,"\"#;\"",DDLString(str)); } ;

  if( str.equal("CCORE_ROOT"_c) )
    {
     printText(out,root,tt...);

     return;
    }

  if( str.equal("CCORE_TARGET"_c) )
    {
     printText(out,target,tt...);

     return;
    }

  if( str.equal("CORELIB"_c) )
    {
     printText(out,tools->CORELIB,tt...);

     return;
    }

  if( str.equal("ROOT"_c) )
    {
     printFrame(root_dir.get());

     return;
    }

  if( str.equal("HOME"_c) )
    {
     printFrame(home_dir.get());

     return;
    }

  printVarExt(out,str,tt...);
 }

template <class ... TT>
void Engine::printText(PrinterType &out,StrLen str,TT ... tt)
 {
  if( !str )
    {
     Putobj(out,"''");

     return;
    }

  PrintFirst stem(""_c,"+"_c);

  auto printFrame = [&] (StrLen str) { Printf(out,"#;\"#;\"",stem,DDLString(str)); } ;

  while( +str )
    {
     ScanStr scan(str,'#');

     if( +scan.next )
       {
        if( +scan.before ) printFrame(scan.before);

        str=scan.next;

        if( str.len>=2 && str[1]=='#' )
          {
           printFrame("#"_c);

           str+=2;
          }
        else
          {
           ScanStr scan(str,';');

           if( +scan.next )
             {
              Putobj(out,stem);

              printVar(out,scan.before.part(1),tt...);

              str=scan.next.part(1);
             }
           else
             {
              printFrame(str);

              return;
             }
          }
       }
     else
       {
        printFrame(str);

        return;
       }
    }
 }

void Engine::printDefText(PrinterType &out,StrLen name,StrLen str)
 {
  auto func = [&] (auto &out) { printText(out,str); } ;

  Printf(out,"text #; = #; ;\n\n",name,PrintBy(func));
 }

template <class List,class ... TT>
void Engine::printSubList(PrinterType &out,PrintFirst &stem,List list,TT ... tt)
 {
  LockUse lock(level);

  for(StrLen str : list )
    {
     if( !printSub(out,stem,str,tt...) )
       {
        Putobj(out,stem);

        printText(out,str,tt...);
       }
    }
 }

template <class Func>
void Engine::printBy(PrinterType &out,PrintFirst &stem,Func func)
 {
  func(out,stem);
 }

template <FuncArgType<PrintBase &> Func>
void Engine::printBy(PrinterType &out,PrintFirst &stem,Func func)
 {
  Putobj(out,stem);

  func(out);
 }

template <class FuncSrc,class FuncDst>
bool Engine::printSubExt(PrinterType &out,PrintFirst &stem,StrLen str,FuncSrc psrc,FuncDst pdst)
 {
  if( str.equal("SRC"_c) )
    {
     printBy(out,stem,psrc);

     return true;
    }

  if( str.equal("DST"_c) )
    {
     printBy(out,stem,pdst);

     return true;
    }

  return false;
 }

template <class FuncSrc,class FuncDst,class FuncObj>
bool Engine::printSubExt(PrinterType &out,PrintFirst &stem,StrLen str,FuncSrc psrc,FuncDst pdst,FuncObj pobj)
 {
  if( str.equal("SRC"_c) )
    {
     printBy(out,stem,psrc);

     return true;
    }

  if( str.equal("DST"_c) )
    {
     printBy(out,stem,pdst);

     return true;
    }

  if( str.equal("OBJ"_c) )
    {
     printBy(out,stem,pobj);

     return true;
    }

  return false;
 }

template <class ... TT>
bool Engine::printSub(PrinterType &out,PrintFirst &stem,StrLen str,TT ... tt)
 {
  if( !TestSingle(str) ) return false;

  str=str.inner(1,1);

  if( str.equal("CCINC"_c) )
    {
     printSubList(out,stem,tools->CCINC.getRange(),tt...);

     return true;
    }

  if( str.equal("CCOPT_EXTRA"_c) )
    {
     printSubList(out,stem,param->CCOPT_EXTRA.getRange(),tt...);

     return true;
    }

  if( str.equal("LDOPT_EXTRA"_c) )
    {
     printSubList(out,stem,param->LDOPT_EXTRA.getRange(),tt...);

     return true;
    }

  if( str.equal("ASOPT_EXTRA"_c) )
    {
     printSubList(out,stem,param->ASOPT_EXTRA.getRange(),tt...);

     return true;
    }

  if( str.equal("LDOPT_DESKTOP"_c) )
    {
     if( param->target==TargetDesktop )
       printSubList(out,stem,tools->LDOPT_DESKTOP.getRange(),tt...);

     return true;
    }

  return printSubExt(out,stem,str,tt...);
 }

template <class List,class ... TT>
void Engine::printList(PrinterType &out,List list,TT ... tt)
 {
  out.put('{');

  PrintFirst stem("\n  "_c,"\n ,"_c);

  printSubList(out,stem,list,tt...);

  out.put('\n');
  out.put('}');
 }

void Engine::genProj(PrinterType &out,FileList &cpp_list,FileList &asm_list)
 {
  printDefText(out,"OBJ_PATH"_c,param->OBJ_PATH);

  printDefText(out,"CC"_c,tools->CC);

  printDefText(out,"AS"_c,tools->AS);

  printDefText(out,"LD"_c,tools->LD);

  printDefText(out,"AR"_c,tools->AR);

  if( param->target==TargetCCore )
    {
     printDefText(out,"TARGET"_c,"CCore.a"_c);
    }
  else
    {
     printDefText(out,"TARGET"_c,param->TARGET);
    }

  // cpp

  {
   cpp_list.apply( [&] (ulen ind,FileName fn)
                       {
                        Printf(out,"Target cpp#; = { \"#;\" , \"#;\" } ;\n",ind,DDLString(fn.name),DDLString(fn.path));

                        StrLen cutname=fn.name.inner(0,4);

                        Printf(out,"Target ocpp#; = { \"#;.o\" , OBJ_PATH+\"/#;.o\" } ;\n",ind,DDLString(cutname),DDLString(cutname));

                        Printf(out,"Rule rcpp#; = { {&cpp#;} , {&ocpp#;} , {&execpp#;} } ;\n",ind,ind,ind,ind);

                        auto psrc = [&] (auto &out) { Printf(out,"\"#;\"",DDLString(fn.path)); } ;

                        auto pdst = [&] (auto &out) { Printf(out,"OBJ_PATH+\"/#;.o\"",DDLString(cutname)); } ;

                        auto func = [&] (auto &out) { printList(out,tools->CCOPT.getRange(),psrc,pdst); } ;

                        Printf(out,"Exe execpp#; = { \"CC #;\" , CC , #; } ;\n\n",ind,DDLString(fn.name),PrintBy(func));

                       } );
  }

  // asm

  {
   asm_list.apply( [&] (ulen ind,FileName fn)
                       {
                        Printf(out,"Target asm#; = { \"#;\" , \"#;\" } ;\n",ind,DDLString(fn.name),DDLString(fn.path));

                        StrLen cutname=fn.name;

                        Printf(out,"Target oasm#; = { \"#;.o\" , OBJ_PATH+\"/#;.o\" } ;\n",ind,DDLString(cutname),DDLString(cutname));

                        Printf(out,"Rule rasm#; = { {&asm#;} , {&oasm#;} , {&exeasm#;} } ;\n",ind,ind,ind,ind);

                        auto psrc = [&] (auto &out) { Printf(out,"\"#;\"",DDLString(fn.path)); } ;

                        auto pdst = [&] (auto &out) { Printf(out,"OBJ_PATH+\"/#;.o\"",DDLString(cutname)); } ;

                        auto func = [&] (auto &out) { printList(out,tools->ASOPT.getRange(),psrc,pdst); } ;

                        Printf(out,"Exe exeasm#; = { \"AS #;\" , AS , #; } ;\n\n",ind,DDLString(fn.name),PrintBy(func));

                       } );
  }

  // target

  {
   Putobj(out,"Target main = { 'main' , TARGET } ;\n\n"_c);

   auto func = [&] (auto &out)
                   {
                    out.put('{');

                    PrintFirst stem("\n  "_c,"\n ,"_c);

                    cpp_list.apply( [&] (ulen ind,FileName)
                                        {
                                         Printf(out,"#;&ocpp#;",stem,ind);

                                        } );

                    asm_list.apply( [&] (ulen ind,FileName)
                                        {
                                         Printf(out,"#;&oasm#;",stem,ind);

                                        } );

                    out.put('\n');
                    out.put('}');

                   } ;

   Printf(out,"Rule rmain = { #; , {&main} , ",PrintBy(func));
  }

  // ld

  if( param->target==TargetConsole || param->target==TargetDesktop )
    {
     Putobj(out,"{&exemain} } ;\n\n"_c);

     auto func = [&] (auto &out)
                     {
                      auto psrc = [&] (auto &out,PrintFirst &stem)
                                      {
                                       cpp_list.apply( [&] (ulen ind,FileName)
                                                           {
                                                            Printf(out,"#;ocpp#;.file",stem,ind);

                                                           } );

                                       asm_list.apply( [&] (ulen ind,FileName)
                                                           {
                                                            Printf(out,"#;oasm#;.file",stem,ind);

                                                           } );
                                      } ;

                      auto pdst = [&] (auto &out) { Putobj(out,"TARGET"_c); } ;

                      printList(out,tools->LDOPT.getRange(),psrc,pdst);

                     } ;

     Printf(out,"Exe exemain = { 'LD '+TARGET , LD , #; } ;\n\n",PrintBy(func));
    }

  // ar

  if( param->target==TargetLib || param->target==TargetCCore )
    {
     Putobj(out,"{&intmain1,&exemain2} } ;\n\n"_c);

     Putobj(out,"IntCmd intmain1 = { 'RM' , &rm1 } ;\n\n"_c);

     Putobj(out,"Rm rm1 = { { TARGET } } ;\n\n"_c);

     auto func = [&] (auto &out)
                     {
                      auto psrc = [&] (auto &out,PrintFirst &stem)
                                      {
                                       cpp_list.apply( [&] (ulen ind,FileName)
                                                           {
                                                            Printf(out,"#;ocpp#;.file",stem,ind);

                                                           } );

                                       asm_list.apply( [&] (ulen ind,FileName)
                                                           {
                                                            Printf(out,"#;oasm#;.file",stem,ind);

                                                           } );
                                      } ;

                      auto pdst = [&] (auto &out) { Putobj(out,"TARGET"_c); } ;

                      StrLen temp[]={"r"_c,"#DST;"_c,"#SRC;"_c};

                      printList(out,Range(temp),psrc,pdst);

                     } ;

     Printf(out,"Exe exemain2 = { 'AR '+TARGET , AR , #; } ;\n\n",PrintBy(func));
    }

  // inc dep

  {
   Printf(out,"include <#;/deps.vm.ddl>\n",StrLen(param->OBJ_PATH));
  }
 }

void Engine::genPrep(PrinterType &out,FileList &cpp_list,FileList &)
 {
  printDefText(out,"CC"_c,tools->CC);

  printDefText(out,"VMDEP"_c,tools->VMDEP);

  printDefText(out,"OBJ_PATH"_c,param->OBJ_PATH);

  printDefText(out,"TARGET"_c,param->TARGET);

  // obj

  {
   Putobj(out,"Target obj = { 'obj' , OBJ_PATH+'/empty' } ;\n\n"_c);

   Putobj(out,"Rule robj = { {} , {&obj} , {&intobj1,&intobj2} } ;\n\n"_c);

   Putobj(out,"IntCmd intobj1 = { 'MKDIR' , &mkdir1 } ;\n\n"_c);

   Putobj(out,"Mkdir mkdir1 = { OBJ_PATH } ;\n\n"_c);

   Putobj(out,"IntCmd intobj2 = { 'ECHO' , &echo1 } ;\n\n"_c);

   Putobj(out,"Echo echo1 = { 'empty' , OBJ_PATH+'/empty' } ;\n\n"_c);
  }

  // clean

  {
   Putobj(out,"Target clean = { 'clean' } ;\n\n"_c);

   Putobj(out,"Rule rclean = { {} , {&clean} , {&intclean} } ;\n\n"_c);

   Putobj(out,"IntCmd intclean = { 'CLEAN' , &rm1 } ;\n\n"_c);

   Putobj(out,"Rm rm1 = { { TARGET , OBJ_PATH+\"/*\" } } ;\n\n"_c);
  }

  // dep

  {
   Putobj(out,"text DEP = OBJ_PATH+'/deps.vm.ddl' ;\n\n"_c);

   cpp_list.apply( [&] (ulen ind,FileName fn)
                       {
                        Printf(out,"Target cpp#; = { \"#;\" , \"#;\" } ;\n",ind,DDLString(fn.name),DDLString(fn.path));

                        StrLen cutname=fn.name.inner(0,4);

                        Printf(out,"Target dcpp#; = { \"#;.dep\" , OBJ_PATH+\"/#;.dep\" } ;\n",ind,DDLString(cutname),DDLString(cutname));

                        Printf(out,"Rule rdcpp#; = { {&cpp#;,&obj} , {&dcpp#;} , {&execpp#;} } ;\n",ind,ind,ind,ind);

                        auto psrc = [&] (auto &out) { Printf(out,"\"#;\"",DDLString(fn.path)); } ;

                        auto pdst = [&] (auto &out) { Printf(out,"OBJ_PATH+\"/#;.dep\"",DDLString(cutname)); } ;

                        auto pobj = [&] (auto &out) { Printf(out,"OBJ_PATH+\"/#;.o\"",DDLString(cutname)); } ;

                        auto func = [&] (auto &out) { printList(out,tools->DEPOPT.getRange(),psrc,pdst,pobj); } ;

                        Printf(out,"Exe execpp#; = { \"CC-DEP #;\" , CC , #; } ;\n\n",ind,DDLString(fn.name),PrintBy(func));

                        Printf(out,"Target vdcpp#; = { \"#;.vm.dep\" , OBJ_PATH+\"/#;.vm.dep\" } ;\n",ind,DDLString(cutname),DDLString(cutname));

                        Printf(out,"Rule rvdcpp#; = { {&dcpp#;} , {&vdcpp#;} , {&exedcpp#;} } ;\n",ind,ind,ind,ind);

                        Printf(out,"Exe exedcpp#; = { \"CC-VM-DEP #;\" , VMDEP , { OBJ_PATH+\"/#;.dep\" , OBJ_PATH+\"/#;.vm.dep\" , \"#;\" } } ;\n\n"
                          ,ind,DDLString(fn.name),DDLString(cutname),DDLString(cutname),ind);

                       } );
  }

  // cat

  {
   Putobj(out,"Target make_dep = { 'make_dep' , DEP } ;\n\n"_c);

   auto func1 = [&] (auto &out)
                    {
                     cpp_list.apply( [&] (ulen ind,FileName)
                                         {
                                          Printf(out,"\n,&vdcpp#;",ind);

                                         } );

                    } ;

   Printf(out,"Rule rmkdep = { {&obj#;} , {&make_dep} , {&intmkdep} } ; \n\n",PrintBy(func1));

   Putobj(out,"IntCmd intmkdep = { 'CAT' , &cat1 } ;\n\n"_c);

   auto func2 = [&] (auto &out)
                    {
                     cpp_list.apply( [&] (ulen ind,FileName)
                                         {
                                          if( ind==1 ) Putobj(out,"\n "_c); else Putobj(out,"\n,"_c);

                                          Printf(out,"vdcpp#;.file",ind);

                                         } );

                    } ;

   Printf(out,"Cat cat1 = { { #; } , DEP } ;\n\n",PrintBy(func2));
  }
 }

Engine::Engine(TypeDef::Param *param_,StrLen src_file_name_,StrLen proj_file_name_,StrLen prep_file_name_)
 : param(param_),
   src_file_name(src_file_name_),
   proj_file_name(proj_file_name_),
   prep_file_name(prep_file_name_)
 {
  root=param->CCORE_ROOT;
  target=param->CCORE_TARGET;
  tools=param->tools;
 }

Engine::~Engine()
 {
 }

int Engine::run()
 {
  if( param->target==0 )
    {
     Printf(Exception,"App : target type is not set");
    }

  prepareRoot();
  prepareTarget();
  prepareTools();

  FindFiles find(param->SRC_PATH_LIST);

  FileList cpp_list(find.cpp_list);
  FileList asm_list(find.asm_list);

  cpp_list.process();
  asm_list.process();

  PrintFile proj(proj_file_name);

  genProj(proj,cpp_list,asm_list);

  PrintFile prep(prep_file_name);

  genPrep(prep,cpp_list,asm_list);

  return 0;
 }

} // namespace App

