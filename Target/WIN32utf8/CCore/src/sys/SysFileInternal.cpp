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

/* struct MakeZStr */

MakeZStr::MakeZStr(StrLen str,PtrLen<WChar> out)
 {
  ulen start_len=out.len;

  while( +str )
    {
     Unicode sym=CutUtf8_unicode(str);

     if( sym==Unicode(-1) ) { setError(FileError_BadName); return; }

     if( IsSurrogate(sym) )
       {
        if( out.len<2 ) { setError(FileError_TooLongPath); return; }

        SurrogateCouple couple(sym);

        out[0]=couple.hi;
        out[1]=couple.lo;

        out+=2;
       }
     else
       { // may insert forbidden symbol
        if( !out ) { setError(FileError_TooLongPath); return; }

        *out=WChar(sym);

        ++out;
       }
    }

  if( !out ) { setError(FileError_TooLongPath); return; }

  *out=0;

  error=FileError_Ok;
  len=start_len-out.len;
 }

} // namespace Sys
} // namespace CCore


