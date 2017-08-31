/* CapString.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: Simple
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_CapString_h
#define CCore_inc_CapString_h

#include <CCore/inc/Gadget.h>

#ifdef CCORE_UTF8
#include <CCore/inc/Utf8.h>
#endif

namespace CCore {

/* classes */

template <ulen MaxLen=TextBufLen> requires ( MaxLen>0 ) class CapString;

/* class CapString<ulen MaxLen> */

template <ulen MaxLen> requires ( MaxLen>0 )
class CapString : NoCopy
 {
   char buf[MaxLen+1];

  public:

   explicit CapString(StrLen str)
    {
     Replace_min(str.len,MaxLen); // cap length

#ifdef CCORE_UTF8

     TrimUtf8End(str);

#endif

     str.copyTo(buf);

     buf[str.len]=0;
    }

   operator const char * () const { return buf; }
 };

} // namespace CCore

#endif


