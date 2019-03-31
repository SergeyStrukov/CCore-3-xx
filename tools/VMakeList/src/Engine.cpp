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

#include <CCore/inc/PrintStem.h>

#include <CCore/inc/Exception.h>

namespace App {

/* struct ScanStr */

ScanStr::ScanStr(StrLen str,char ch)
 {
  for(StrLen t=str; +t ;++t)
    if( *t==ch )
      {
       before=str.prefix(t);
       next=t;

       return;
      }

  before=str;
  next=Empty;
 }

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
     s_list.append_fill(pool.cat(path,"/"_c,name),name.len);
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

bool Engine::prepareRoot()
 {
  if( !root )
    {
     // TODO

     return false;
    }

  return true;
 }

bool Engine::prepareTarget()
 {
  if( !target )
    {
     // TODO

     return false;
    }

  return true;
 }

bool Engine::prepareTools()
 {
  if( !tools )
    {
     // TODO

     return false;
    }

  return true;
 }

bool Engine::TestSingle(StrLen str)
 {
  if( !str ) return false;

  if( str[0]!='#' || str.back(1)!=';' ) return false;

  for(char ch : str.inner(1,1) ) if( ch==';' ) return false;

  return true;
 }

template <class FuncSrc,class FuncDst>
void Engine::printSubList(PrinterType &out,PtrLen<DDL::MapText> list,FuncSrc psrc,FuncDst pdst)
 {
  for(ulen i : IndLim(list.len) )
    {
     if( i ) Putobj(out,"\n, "_c);

     StrLen str=list[i];

     printElem(out,str,psrc,pdst);
    }
 }

template <class FuncSrc,class FuncDst>
bool Engine::printSub(PrinterType &out,StrLen str,FuncSrc psrc,FuncDst pdst)
 {
  if( !TestSingle(str) ) return false;

  str=str.inner(1,1);

  PtrLen<DDL::MapText> list;

  if( str.equal("CCOPT_EXTRA"_c) )
    {
     printSubList(out,param->CCOPT_EXTRA,psrc,pdst);

     return true;
    }

  if( str.equal("LDOPT_EXTRA"_c) )
    {
     printSubList(out,param->LDOPT_EXTRA,psrc,pdst);

     return true;
    }

  if( str.equal("ASOPT_EXTRA"_c) )
    {
     printSubList(out,param->ASOPT_EXTRA,psrc,pdst);

     return true;
    }

  if( str.equal("LDOPT_DESKTOP"_c) )
    {
     if( param->target==TargetDesktop )
       printSubList(out,tools->LDOPT_DESKTOP,psrc,pdst);

     return true;
    }

  return false;
 }

template <class FuncSrc,class FuncDst>
void Engine::printVar(PrinterType &out,StrLen str,FuncSrc psrc,FuncDst pdst)
 {
  auto printFrame = [&] (StrLen str) { Printf(out,"\"#;\"",DDLString(str)); } ;

  if( str.equal("CCORE_ROOT"_c) )
    {
     printFrame(param->CCORE_ROOT);

     return;
    }

  if( str.equal("CCORE_TARGET"_c) )
    {
     printFrame(param->CCORE_TARGET);

     return;
    }

  if( str.equal("CORELIB"_c) )
    {
     printElem(out,tools->CORELIB,psrc,pdst);

     return;
    }

  if( str.equal("SRC"_c) )
    {
     psrc(out);

     return;
    }

  if( str.equal("DST"_c) )
    {
     pdst(out);

     return;
    }

  Printf(Exception,"unknown variable #.q;",str);
 }

template <class FuncSrc,class FuncDst>
void Engine::printElem(PrinterType &out,StrLen str,FuncSrc psrc,FuncDst pdst)
 {
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

              printVar(out,scan.before.part(1),psrc,pdst);

              str=scan.next.part(1);
             }
           else
             {
              printFrame(str);
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

template <class FuncSrc,class FuncDst>
void Engine::printList(PrinterType &out,PtrLen<DDL::MapText> list,FuncSrc psrc,FuncDst pdst)
 {
  Putobj(out,"\n{");

  for(ulen i : IndLim(list.len) )
    {
     if( i ) Putobj(out,"\n, "_c); else Putobj(out,"\n  "_c);

     StrLen str=list[i];

     if( !printSub(out,str,psrc,pdst) ) printElem(out,str,psrc,pdst);
    }

  Putobj(out,"\n}\n");
 }

Engine::Engine(TypeDef::Param *param_,StrLen src_file_name_,StrLen dst_file_name_)
 : param(param_),
   src_file_name(src_file_name_),
   dst_file_name(dst_file_name_)
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
  if( prepareRoot() && prepareTarget() && prepareTools() )
    {
     FindFiles find(param->SRC_PATH_LIST);

     FileList cpp_list(find.cpp_list);
     FileList s_list(find.s_list);

     cpp_list.process();
     s_list.process();

     PrintFile out(dst_file_name);

     Printf(out,"text OBJ_PATH = \"#;\" ;\n\n",DDLString(param->OBJ_PATH));

     Printf(out,"text CC = \"#;\" ;\n\n",DDLString(tools->CC));

     // 1

     {
      cpp_list.apply( [&] (ulen ind,FileName fn)
                          {
                           Printf(out,"Target cpp#; = { \"#;\" , \"#;\" } ;\n",ind,DDLString(fn.name),DDLString(fn.path));

                           StrLen cutname=fn.name.inner(0,4);

                           Printf(out,"Target ocpp#; = { \"#;.o\" , OBJ_PATH+\"/#;.o\" } ;\n",ind,DDLString(cutname),DDLString(cutname));

                           Printf(out,"Rule rcpp#; = { {&cpp#;} , {&ocpp#;} , {&execpp#;} } ;\n",ind,ind,ind,ind);

                           Printf(out,"Exe execpp#; = { \"CC #;\" , CC , ",ind,DDLString(fn.name));

                           printList(out,tools->CCOPT,
                                         [&] (auto &out) { Printf(out,"\"#;\"",DDLString(fn.path)); } ,
                                         [&] (auto &out) { Printf(out,"OBJ_PATH+\"/#;.o\"",DDLString(cutname)); } );

                           Putobj(out," } ;\n\n"_c);

                          } );
     }

     // 2

     {
     }

     return 0;
    }

  return 1;
 }

} // namespace App

