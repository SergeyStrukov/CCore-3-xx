/* Engine.h */
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

#ifndef App_Engine_h
#define App_Engine_h

#include <CCore/inc/ElementPool.h>
#include <CCore/inc/Array.h>
#include <CCore/inc/Cmp.h>
#include <CCore/inc/Sort.h>
#include <CCore/inc/Path.h>
#include <CCore/inc/ForLoop.h>
#include <CCore/inc/DirTreeRun.h>
#include <CCore/inc/Print.h>

#include <CCore/inc/ddl/DDLMapTypes.h>

namespace App {

/* using */

using namespace CCore;

#ifndef VMakeList_TypeDef_h
#define VMakeList_TypeDef_h
#include "VMakeList.TypeDef.gen.h"
#endif

/* classes */

class FindFiles;

class FileList;

class Engine;

/* struct FileName */

struct FileName
 {
  StrLen path;
  StrLen name;

  FileName(StrLen path_,ulen name_len) : path(path_),name(path.suffix(name_len)) {}

  // operators

  bool operator < (FileName file) const { return StrLess(name,file.name); }

  bool operator == (FileName file) const { return name.equal(file.name); }
 };

/* class FindFiles */

class FindFiles : NoCopy
 {
   ElementPool pool;

  private:

   class Proc;

   void appendFile(StrLen path,StrLen name);

   void append(StrLen dir);

  public:

   Collector<FileName> cpp_list;
   Collector<FileName> s_list;

   explicit FindFiles(PtrLen<DDL::MapText> dir_list);
 };

/* class FileList */

class FileList
 {
   DynArray<FileName> buf;

  private:

   static void Guard(FileName a,FileName b)
    {
     if( a==b )
       {
        Printf(Exception,"File name duplication: #; #;",a.path,b.path);
       }
    }

   static void Process(PtrLen<FileName> r)
    {
     Sort(r);

     for(; r.len>=2 ;++r) Guard(r[0],r[1]);
    }

  public:

   explicit FileList(Collector<FileName> &src)
    {
     src.extractTo(buf);
    }

   void process()
    {
     Process(Range(buf));
    }

   void apply(FuncArgType<ulen,FileName> func) const
    {
     auto r=Range(buf);

     for(ulen i : IndLim(r.len) ) func(i+1,r[i]);
    }
 };

/* class Engine */

class Engine : NoCopy
 {
   TypeDef::Param *param;

   StrLen root;
   StrLen target;
   TypeDef::Tools *tools;

   StrLen src_file_name;
   StrLen dst_file_name;

  private:

   bool prepareRoot();

   bool prepareTarget();

   bool prepareTools();

   template <class FuncSrc,class FuncDst>
   void printList(PrinterType &out,PtrLen<DDL::MapText> list,FuncSrc psrc,FuncDst pdst);

  public:

   Engine(TypeDef::Param *param,StrLen src_file_name,StrLen dst_file_name);

   ~Engine();

   int run();
 };

} // namespace App

#endif

