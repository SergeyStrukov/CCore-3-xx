/* ExpandWildcard.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.60
//
//  Tag: HCore
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_ExpandWildcard_h
#define CCore_inc_ExpandWildcard_h

#include <CCore/inc/MakeFileName.h>
#include <CCore/inc/FileSystem.h>
#include <CCore/inc/FileNameMatch.h>

namespace CCore {

/* classes */

struct CheckWildcard;

class WildcardCursor;

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

   template <FuncInitType<bool,StrLen> FuncInit>
   auto apply(FuncInit func_init)
    {
     FunctorTypeOf<FuncInit> func(func_init);

     while( next() ) if( !func(getFileName()) ) break;

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

} // namespace CCore

#endif

