/* VMakeIntCmd.h */
//----------------------------------------------------------------------------------------
//
//  Project: vmake 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef App_VMakeIntCmd_h
#define App_VMakeIntCmd_h

#include <CCore/inc/FileSystem.h>
#include <CCore/inc/MakeFileName.h>
#include <CCore/inc/FileNameMatch.h>

#include <CCore/inc/ddl/DDLMapTypes.h>

namespace App {

/* using */

using namespace CCore;

namespace VMake {

/* classes */

struct CheckWildcard;

class WildcardCursor;

class BuildFileName;

class IntCmdProc;

/* struct CheckWildcard */

struct CheckWildcard
 {
  StrLen dir; // before file
  StrLen file;
  bool ok;

  explicit CheckWildcard(StrLen path);
 };

/* class WildcardCursor */

class WildcardCursor : NoCopy
 {
   StrLen dir;
   MakeFileName str;
   FileSystem::DirCursor cur;
   FileNameFilter filter;

  public:

   WildcardCursor(FileSystem &fs,StrLen dir,StrLen file);

   ~WildcardCursor();

   bool next();

   StrLen getFileName() const { return str.get(); }

   template <FuncInitArgType<StrLen> FuncInit>
   auto apply(FuncInit func_init)
    {
     FunctorTypeOf<FuncInit> func(func_init);

     while( next() ) func(getFileName());

     return Algon::GetResult(func);
    }
 };

/* ExpandWildcard() */

template <FuncInitArgType<StrLen> FuncInit>
auto ExpandWildcard(FileSystem &fs,StrLen path,FuncInit func_init)
 {
  CheckWildcard check(path);

  if( check.ok )
    {
     WildcardCursor cur(fs,check.dir,check.file);

     return cur.apply(func_init);
    }
  else
    {
     FunctorTypeOf<FuncInit> func(func_init);

     if( fs.getFileType(path)==FileType_file ) func(path);

     return Algon::GetResult(func);
    }
 }

/* class BuildFileName */

class BuildFileName : NoCopy
 {
   MakeFileName buf;

   StrLen result;

  private:

   static bool IsRooted(StrLen name);

   static bool IsRel(StrLen file);

  public:

   BuildFileName(StrLen wdir,StrLen file);

   StrLen get() const { return result; }
 };

/* class IntCmdProc */

class IntCmdProc : NoCopy
 {
   FileSystem fs;

  public:

   IntCmdProc();

   ~IntCmdProc();

   // check

   bool checkExist(StrLen wdir,StrLen dst);

   bool checkOlder(StrLen wdir,StrLen dst,StrLen src); // dst.noexist OR dst.time < src.time

   // commands

   int echo(StrLen wdir,PtrLen<DDL::MapText> strs,StrLen outfile);

   int cat(StrLen wdir,PtrLen<DDL::MapText> files,StrLen outfile);

   int rm(StrLen wdir,PtrLen<DDL::MapText> files);

   int mkdir(StrLen wdir,PtrLen<DDL::MapText> paths);
 };

} // namespace VMake
} // namespace App

#endif


