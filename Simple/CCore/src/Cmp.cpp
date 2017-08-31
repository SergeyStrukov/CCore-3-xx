/* Cmp.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Simple Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/Cmp.h>

namespace CCore {

/* enum CmpResult */

const char * GetTextDesc(CmpResult cmp)
 {
  switch( cmp )
    {
     case CmpLess    : return "<";
     case CmpEqual   : return "=";
     case CmpGreater : return ">";

     default: return "???";
    }
 }

/* Str...() */

CmpResult StrCmp(StrLen a,StrLen b)
 {
  if( a.len<b.len )
    {
     ulen off=a.match(b.ptr);

     if( off<a.len ) return LessCmp(uint8(a[off]),uint8(b[off]));

     return CmpLess;
    }
  else
    {
     ulen off=b.match(a.ptr);

     if( off<b.len ) return LessCmp(uint8(a[off]),uint8(b[off]));

     return (a.len==b.len)?CmpEqual:CmpGreater;
    }
 }

bool StrLess(StrLen a,StrLen b)
 {
  if( a.len<b.len )
    {
     ulen off=a.match(b.ptr);

     if( off<a.len ) return uint8(a[off])<uint8(b[off]);

     return true;
    }
  else
    {
     ulen off=b.match(a.ptr);

     if( off<b.len ) return uint8(a[off])<uint8(b[off]);

     return false;
    }
 }

} // namespace CCore


