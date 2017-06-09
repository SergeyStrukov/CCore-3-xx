/* SafeBuf.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Simple Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/SafeBuf.h>

#include <CCore/inc/MemBase.h>

namespace CCore {

/* class SafeBuf */

SafeBuf::SafeBuf(ulen len_) noexcept
 {
  if( len_>SafeLen )
    {
     if( void *mem=TryMemAlloc(len_) )
       {
        ptr=static_cast<char *>(mem);
        len=len_;

        return;
       }
    }

  ptr=safebuf;
  len=SafeLen;
 }

SafeBuf::~SafeBuf()
 {
  if( ptr!=safebuf )
    {
     MemFree(ptr);
    }
 }

} // namespace CCore


