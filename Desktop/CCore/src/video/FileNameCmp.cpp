/* FileNameCmp.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Desktop
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/video/FileNameCmp.h>

#include <CCore/inc/video/Desktop.h>

#include <CCore/inc/Path.h>

namespace CCore {
namespace Video {

/* functions */

CmpResult NativeNameCmp(StrLen a,StrLen b)
 {
#if 1

  return StrCmp(a,b);

#else

  if( a.len<b.len )
    {
     ulen off=a.match(b.ptr);

     if( off<a.len ) return NativeCmp(a[off],b[off]);

     return CmpLess;
    }
  else
    {
     ulen off=b.match(a.ptr);

     if( off<b.len ) return NativeCmp(a[off],b[off]);

     return (a.len==b.len)?CmpEqual:CmpGreater;
    }

#endif
 }

CmpResult ExtNameCmp(StrLen a,StrLen b)
 {
  if( PathBase::IsDotDot(a) ) return PathBase::IsDotDot(b)?CmpEqual:CmpLess;

  if( PathBase::IsDotDot(b) ) return CmpGreater;

  for(;;)
    {
     SplitExt exta(a);
     SplitExt extb(b);

     if( !extb )
       {
        if( !exta )
          {
           return NativeNameCmp(a,b);
          }
        else
          {
           return CmpGreater;
          }
       }
     else
       {
        if( !exta )
          {
           return CmpLess;
          }
        else
          {
           if( CmpResult cmp=NativeNameCmp(exta.ext,extb.ext) ) return cmp;

           a=exta.name;
           b=extb.name;
          }
       }
    }
 }

} // namespace Video
} // namespace CCore

