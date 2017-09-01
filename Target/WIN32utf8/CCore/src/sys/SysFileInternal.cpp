/* SysFileInternal.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Target/WIN32utf8
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/sys/SysFileInternal.h>

namespace CCore {
namespace Sys {

/* functions */

FileError MakeZStr(StrLen str,PtrLen<WChar> out)
 {
  while( +str )
    {
     Unicode sym=CutUtf8_unicode(str);

     if( sym==Unicode(-1) ) return FileError_BadName;

     if( IsSurrogate(sym) )
       {
        if( out.len<2 ) return FileError_TooLongPath;

        SurrogateCouple couple(sym);

        out[0]=couple.hi;
        out[1]=couple.lo;

        out+=2;
       }
     else
       { // may insert forbidden symbols
        if( !out ) return FileError_TooLongPath;

        *out=WChar(sym);

        ++out;
       }
    }

  if( !out ) return FileError_TooLongPath;

   *out=0;

  return FileError_Ok;
 }

} // namespace Sys
} // namespace CCore


