/* ExpandWildcard.cpp */
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

#include <CCore/inc/ExpandWildcard.h>

#include <CCore/inc/Path.h>
#include <CCore/inc/ScanRange.h>

namespace CCore {

/* struct CheckWildcard */

CheckWildcard::CheckWildcard(StrLen path)
 {
  SplitPath split1(path);

  SplitName split2(split1.path);

  ScanStr scan(split2.name, [] (char ch) { return ch=='*' || ch=='?' ; } );

  if( +scan.next )
    {
     dir=path.prefix(split1.dev.len+split2.path.len);

     file=split2.name;

     ok=true;
    }
  else
    {
     ok=false;
    }
 }

/* class WildcardCursor */

WildcardCursor::WildcardCursor(FileSystem &fs,StrLen dir_,StrLen file)
 : dir(dir_),
   str(dir,"."_c),
   cur(fs,str.get()),
   filter(file)
 {
 }

WildcardCursor::~WildcardCursor()
 {
 }

bool WildcardCursor::next()
 {
  while( cur.next() )
    {
     StrLen file=cur.getFileName();

     if( cur.getFileType()==FileType_file && filter(file) )
       {
        str(dir,file);

        return true;
       }
    }

  return false;
 }

} // namespace CCore

