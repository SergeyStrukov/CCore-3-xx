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

template <class FuncSrc,class FuncDst>
void Engine::printList(PrinterType &out,PtrLen<DDL::MapText> list,FuncSrc psrc,FuncDst pdst)
 {
  Putobj(out,"\n{\n");

  for(ulen i : IndLim(list.len) )
    {
     if( i ) Putobj(out,", "_c); else Putobj(out,"  "_c);


    }

  Putobj(out,"}\n");
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

     StrLen OBJ_PATH=param->OBJ_PATH;

     Printf(out,"text OBJ_PATH = #.q; ;\n\n",OBJ_PATH);

     // 1

     {
      cpp_list.apply( [&] (ulen ind,FileName fn)
                          {
                           Printf(out,"Target cpp#; = { #.q; , #.q; } ;\n",ind,fn.name,fn.path);

                           StrLen cutname=fn.name.inner(0,4);

                           Printf(out,"Target ocpp#; = { \"#;.o\" , OBJ_PATH+\"/#;.o\" } ;\n",ind,cutname,cutname);

                           Printf(out,"Rule rcpp#; = { {&cpp#;} , {&ocpp#;} , {&execpp#;} } ;\n",ind,ind,ind,ind);

                           Printf(out,"Exe execpp#; = { \"CC #;\" , \"#;\" , ",ind,fn.name,tools->CC);

                           //printList(out, [&] (auto &out) { Putobj(out,fn.path); } ,
                           //               [&] (auto &out) { Printf(out,"",cutname); } );

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

