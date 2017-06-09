/* FileSystem.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: HCore Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_FileSystem_h
#define CCore_inc_FileSystem_h

#include <CCore/inc/sys/SysFileSystem.h>

#include <CCore/inc/algon/ApplyToRange.h>

namespace CCore {

/* classes */

class FileSystem;

/* class FileSystem */

class FileSystem : NoCopy
 {
   Sys::FileSystem fs;

  public:

   FileSystem();

   ~FileSystem();

   FileType getFileType(StrLen path);

   CmpFileTimeType getFileUpdateTime(StrLen path);

   void createFile(StrLen file_name);

   void deleteFile(StrLen file_name);

   void createDir(StrLen dir_name);

   void deleteDir(StrLen dir_name,bool recursive);

   void rename(StrLen old_path,StrLen new_path,bool allow_overwrite);

   void remove(StrLen path);

   void exec(StrLen dir,StrLen program,StrLen arg);

   StrLen pathOf(StrLen path,char buf[MaxPathLen+1]);

   class DirCursor;
 };

/* class FileSystem::DirCursor */

class FileSystem::DirCursor : NoCopy
 {
   Sys::FileSystem::DirCursor cur;
   bool ok;

  public:

   DirCursor(FileSystem &fs,StrLen dir_name);

   ~DirCursor();

   bool next();

   StrLen getFileName() const;

   FileType getFileType() const;

   template <FuncInitArgType<StrLen,FileType> FuncInit>
   auto apply(FuncInit func_init)
    {
     FunctorTypeOf<FuncInit> func(func_init);

     while( next() ) func(getFileName(),getFileType());

     return Algon::GetResult(func);
    }
 };

} // namespace CCore

#endif


