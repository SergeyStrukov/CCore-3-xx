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
     Putobj(out,root_dir.get());

     return;
    }

  if( str.equal("HOME"_c) )
    {
     Putobj(out,home_dir.get());

     return;
    }

  printVarExt(out,str,tt...);
 }

template <class ... TT>
void Engine::printText(PrinterType &out,StrLen str,TT ... tt)
 {
  while( +str )
    {
     ScanStr scan(str,'#');

     if( +scan.next )
       {
        if( +scan.before ) Putobj(out,scan.before);

        str=scan.next;

        if( str.len>=2 && str[1]=='#' )
          {
           Putobj(out,"#"_c);

           str+=2;
          }
        else
          {
           ScanStr scan(str,';');

           if( +scan.next )
             {
              printVar(out,scan.before.part(1),tt...);

              str=scan.next.part(1);
             }
           else
             {
              Putobj(out,str);

              return;
             }
          }
       }
     else
       {
        Putobj(out,str);

        return;
       }
    }
 }

template <class ... TT>
void Engine::printDDLString(PrinterType &out,StrLen str,TT ... tt)
 {
  if( !str )
    {
     Putobj(out,"''");

     return;
    }

  Putobj(out, PrintDDLString( [&] (auto &out) { printText(out,str,tt...); } ) );
 }

void Engine::printDefText(PrinterType &out,StrLen name,StrLen str)
 {
  auto func = [&] (auto &out) { printDDLString(out,str); } ;

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

        printDDLString(out,str,tt...);
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

struct Engine::CppItem
 {
  ulen ind;
  FileName fn;

  StrLen name;

  CppItem(ulen ind_,const FileName &fn_) : ind(ind_),fn(fn_) { name=fn.name.inner(0,4); }

  auto getCppName() const { return DDLString(fn.name); }

  auto getCppPath() const { return DDLString(fn.path); }

  auto getObjName() const { return DDLString(name,".o"_c); }

  auto getObjPath() const { return DDLString("/"_c,name,".o"_c); } // rel to OBJ_PATH

  auto getDepName() const { return DDLString(name,".dep"_c); }

  auto getDepPath() const { return DDLString("/"_c,name,".dep"_c); } // rel to OBJ_PATH

  auto getVDepName() const { return DDLString(name,".vm.dep"_c); }

  auto getVDepPath() const { return DDLString("/"_c,name,".vm.dep"_c); } // rel to OBJ_PATH
 };

struct Engine::AsmItem
 {
  ulen ind;
  FileName fn;

  StrLen name;

  AsmItem(ulen ind_,const FileName &fn_) : ind(ind_),fn(fn_) { name=fn.name; }

  auto getAsmName() const { return DDLString(fn.name); }

  auto getAsmPath() const { return DDLString(fn.path); }

  auto getObjName() const { return DDLString(name,".o"_c); }

  auto getObjPath() const { return DDLString("/"_c,name,".o"_c); } // rel to OBJ_PATH
 };

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
   cpp_list.apply( [&] (ulen ind,const FileName &fn)
                       {
                        CppItem item(ind,fn);

                        auto cpp_name=item.getCppName();

                        auto cpp_path=item.getCppPath();

                        auto obj_name=item.getObjName();

                        auto obj_path=item.getObjPath();

                        auto dep_path=item.getDepPath();

                        Printf(out,"Target cpp#; = { #; , #; } ;\n",ind,cpp_name,cpp_path);

                        Printf(out,"Target ocpp#; = { #; , OBJ_PATH+#; } ;\n",ind,obj_name,obj_path);

                        Printf(out,"Rule rcpp#; = { {&cpp#;} , {&ocpp#;} , {&intdep#;,&execpp#;} } ;\n",ind,ind,ind,ind,ind);

                        auto psrc = [&] (auto &out) { Printf(out,"#;",cpp_path); } ;

                        auto pdst = [&] (auto &out) { Printf(out,"OBJ_PATH+#;",obj_path); } ;

                        auto func = [&] (auto &out) { printList(out,tools->CCOPT.getRange(),psrc,pdst); } ;

                        Printf(out,"Exe execpp#; = { #; , CC , #; } ;\n\n",ind,DDLString("CC "_c,fn.name),PrintBy(func));

                        Printf(out,"IntCmd intdep#; = { 'RM DEP' , &rmdep#; } ;\n\n",ind,ind);

                        Printf(out,"Rm rmdep#; = { { OBJ_PATH+#; } } ;\n\n",ind,dep_path);

                       } );
  }

  // asm

  {
   asm_list.apply( [&] (ulen ind,const FileName &fn)
                       {
                        AsmItem item(ind,fn);

                        auto asm_name=item.getAsmName();

                        auto asm_path=item.getAsmPath();

                        auto obj_name=item.getObjName();

                        auto obj_path=item.getObjPath();

                        Printf(out,"Target asm#; = { #; , #; } ;\n",ind,asm_name,asm_path);

                        Printf(out,"Target oasm#; = { #; , OBJ_PATH+#; } ;\n",ind,obj_name,obj_path);

                        Printf(out,"Rule rasm#; = { {&asm#;} , {&oasm#;} , {&exeasm#;} } ;\n",ind,ind,ind,ind);

                        auto psrc = [&] (auto &out) { Printf(out,"#;",asm_path); } ;

                        auto pdst = [&] (auto &out) { Printf(out,"OBJ_PATH+#;",obj_path); } ;

                        auto func = [&] (auto &out) { printList(out,tools->ASOPT.getRange(),psrc,pdst); } ;

                        Printf(out,"Exe exeasm#; = { #; , AS , #; } ;\n\n",ind,DDLString("AS "_c,fn.name),PrintBy(func));

                       } );
  }

  // target

  {
   Putobj(out,"text ARGS = '@'+OBJ_PATH+'/target.args' ;\n\n"_c);

   auto func1 = [&] (auto &out)
                    {
                     PrintFirst stem("\n "_c,"\n,"_c);

                     auto tail=DDLString("\"\n"_c);

                     cpp_list.apply( [&] (ulen ind,const FileName &)
                                         {
                                          Printf(out,"#;'\"'+ocpp#;.file+#;",stem,ind,tail);

                                         } );

                     asm_list.apply( [&] (ulen ind,const FileName &)
                                         {
                                          Printf(out,"#;'\"'+oasm#;.file+#;",stem,ind,tail);

                                         } );
                    } ;

   Putobj(out,"IntCmd intargs = { 'ARGS' , &echoargs } ;\n\n"_c);

   Printf(out,"Echo echoargs = { { #; } , OBJ_PATH+'/target.args' } ;\n\n",PrintBy(func1));

   Putobj(out,"Target main = { 'main' , TARGET } ;\n\n"_c);

   auto func2 = [&] (auto &out)
                    {
                     cpp_list.apply( [&] (ulen ind,const FileName &)
                                         {
                                          Printf(out,"\n,&ocpp#;",ind);

                                         } );

                     asm_list.apply( [&] (ulen ind,const FileName &)
                                         {
                                          Printf(out,"\n,&oasm#;",ind);

                                         } );

                    } ;

   Printf(out,"Rule rmain = { { core_ptr #; } , {&main} , ",PrintBy(func2));
  }

  // ld

  if( param->target==TargetConsole || param->target==TargetDesktop )
    {
     Putobj(out,"{&intargs,&exemain} } ;\n\n"_c);

     auto psrc = [&] (auto &out) { Putobj(out,"ARGS"_c); } ;

     auto pdst = [&] (auto &out) { Putobj(out,"TARGET"_c); } ;

     auto func = [&] (auto &out) { printList(out,tools->LDOPT.getRange(),psrc,pdst); } ;

     Printf(out,"Exe exemain = { 'LD '+TARGET , LD , #; } ;\n\n",PrintBy(func));

     auto corefunc = [&] (auto &out) { printDDLString(out,"#CCORE_ROOT;/Target/#CCORE_TARGET;/CCore.a"_c); } ;

     Printf(out,"Target core = { 'CCore' , #; } ;\n\n",PrintBy(corefunc));

     Putobj(out,"Target *core_ptr = &core ;\n\n"_c);
    }

  // ar

  if( param->target==TargetLib || param->target==TargetCCore )
    {
     Putobj(out,"{&intargs,&intmain1,&exemain2} } ;\n\n"_c);

     Putobj(out,"IntCmd intmain1 = { 'RM' , &rm1 } ;\n\n"_c);

     Putobj(out,"Rm rm1 = { { TARGET } } ;\n\n"_c);

     Printf(out,"Exe exemain2 = { 'AR '+TARGET , AR , { 'r' , TARGET , ARGS } } ;\n\n");

     Putobj(out,"Target *core_ptr = null ;\n\n"_c);
    }

  // inc dep

  {
   auto func = [&] (auto &out) { printText(out,StrLen(param->OBJ_PATH)); } ;

   Printf(out,"include <#;/deps.vm.ddl>\n",PrintBy(func));
  }
 }

void Engine::genPrep(PrinterType &out,FileList &cpp_list,FileList &)
 {
  printDefText(out,"CC"_c,tools->CC);

  printDefText(out,"VMDEP"_c,tools->VMDEP);

  printDefText(out,"OBJ_PATH"_c,param->OBJ_PATH);

  printDefText(out,"TARGET"_c,param->TARGET);

  Putobj(out,"text DEP = OBJ_PATH+'/deps.vm.ddl' ;\n\n"_c);

  // obj

  {
   Putobj(out,"Target obj = { 'obj' , OBJ_PATH+'/empty' } ;\n\n"_c);

   Putobj(out,"Rule robj = { {} , {&obj} , {&intobj1,&intobj2} } ;\n\n"_c);

   Putobj(out,"IntCmd intobj1 = { 'MKDIR' , &mkdir1 } ;\n\n"_c);

   Putobj(out,"Mkdir mkdir1 = { { OBJ_PATH } } ;\n\n"_c);

   Putobj(out,"IntCmd intobj2 = { 'ECHO' , &echo1 } ;\n\n"_c);

   Putobj(out,"Echo echo1 = { { 'empty' } , OBJ_PATH+'/empty' } ;\n\n"_c);
  }

  // clean

  {
   Putobj(out,"Target clean = { 'clean' } ;\n\n"_c);

   Putobj(out,"Rule rclean = { {} , {&clean} , {&intclean} } ;\n\n"_c);

   Putobj(out,"IntCmd intclean = { 'CLEAN' , &rm1 } ;\n\n"_c);

   Putobj(out,"Rm rm1 = { { TARGET , OBJ_PATH+'/*' } } ;\n\n"_c);
  }

  // clean dep

  {
   Putobj(out,"Target clean_dep = { 'clean dep' } ;\n\n"_c);

   Putobj(out,"Rule rclean_dep = { {} , {&clean_dep} , {&intclean_dep} } ;\n\n"_c);

   Putobj(out,"IntCmd intclean_dep = { 'CLEAN DEP' , &rm2 } ;\n\n"_c);

   Putobj(out,"Rm rm2 = { { DEP , OBJ_PATH+'/*.dep' } } ;\n\n"_c);
  }

  // dep

  {
   cpp_list.apply( [&] (ulen ind,const FileName &fn)
                       {
                        CppItem item(ind,fn);

                        auto cpp_name=item.getCppName();

                        auto cpp_path=item.getCppPath();

                        auto obj_path=item.getObjPath();

                        auto dep_name=item.getDepName();

                        auto dep_path=item.getDepPath();

                        auto vdep_name=item.getVDepName();

                        auto vdep_path=item.getVDepPath();

                        Printf(out,"Target cpp#; = { #; , #; } ;\n",ind,cpp_name,cpp_path);

                        Printf(out,"Target dcpp#; = { #; , OBJ_PATH+#; } ;\n",ind,dep_name,dep_path);

                        Printf(out,"Rule rdcpp#; = { {&cpp#;,&obj} , {&dcpp#;} , {&execpp#;} } ;\n",ind,ind,ind,ind);

                        auto psrc = [&] (auto &out) { Printf(out,"#;",cpp_path); } ;

                        auto pdst = [&] (auto &out) { Printf(out,"OBJ_PATH+#;",dep_path); } ;

                        auto pobj = [&] (auto &out) { Printf(out,"OBJ_PATH+#;",obj_path); } ;

                        auto func = [&] (auto &out) { printList(out,tools->DEPOPT.getRange(),psrc,pdst,pobj); } ;

                        Printf(out,"Exe execpp#; = { #; , CC , #; } ;\n\n",ind,DDLString("CC-DEP "_c,fn.name),PrintBy(func));

                        Printf(out,"Target vdcpp#; = { #; , OBJ_PATH+#; } ;\n",ind,vdep_name,vdep_path);

                        Printf(out,"Rule rvdcpp#; = { {&dcpp#;} , {&vdcpp#;} , {&exedcpp#;} } ;\n",ind,ind,ind,ind);

                        Printf(out,"Exe exedcpp#; = { #; , VMDEP , { OBJ_PATH+#; , OBJ_PATH+#; , '#;' } } ;\n\n",ind,DDLString("CC-VM-DEP "_c,fn.name),dep_path,vdep_path,ind);

                       } );
  }

  // cat

  {
   Putobj(out,"Target make_dep = { 'make_dep' , DEP } ;\n\n"_c);

   auto func1 = [&] (auto &out)
                    {
                     cpp_list.apply( [&] (ulen ind,const FileName &)
                                         {
                                          Printf(out,"\n,&vdcpp#;",ind);

                                         } );

                    } ;

   Printf(out,"Rule rmkdep = { {&obj#;} , {&make_dep} , {&intmkdep} } ; \n\n",PrintBy(func1));

   Putobj(out,"IntCmd intmkdep = { 'CAT' , &cat1 } ;\n\n"_c);

   auto func2 = [&] (auto &out)
                    {
                     PrintFirst stem("\n "_c,"\n,"_c);

                     cpp_list.apply( [&] (ulen ind,const FileName &)
                                         {
                                          Printf(out,"#;vdcpp#;.file",stem,ind);

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

