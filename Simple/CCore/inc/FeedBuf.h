/* FeedBuf.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Simple
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_FeedBuf_h
#define CCore_inc_FeedBuf_h

#include <CCore/inc/Gadget.h>

namespace CCore {

/* classes */

template <class T> struct FeedBuf;

/* struct FeedBuf<T> */

template <class T>
struct FeedBuf
 {
  ulen delta;
  bool overflow;

  FeedBuf(PtrLen<T> dst,PtrLen<const T> src)
   {
    if( dst.len>=src.len )
      {
       src.copyTo(dst.ptr);

       delta=src.len;
       overflow=false;
      }
    else
      {
       dst.copy(src.ptr);

       delta=dst.len;
       overflow=true;
      }
   }
 };

/* Feedup()  */

template <class T>
bool Feedup(PtrLen<T> &dst,PtrLen<const T> src)
 {
  FeedBuf feed(dst,src);

  dst+=feed.delta;

  return feed.overflow;
 }

} // namespace CCore

#endif

