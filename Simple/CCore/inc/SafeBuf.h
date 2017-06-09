/* SafeBuf.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
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

#ifndef CCore_inc_SafeBuf_h
#define CCore_inc_SafeBuf_h

#include <CCore/inc/Gadget.h>

namespace CCore {

/* classes */

class SafeBuf;

/* class SafeBuf */

class SafeBuf : NoCopy
 {
   static const ulen SafeLen = 32 ;

   char *ptr;
   ulen len;

   char safebuf[SafeLen];

  public:

   explicit SafeBuf(ulen len) noexcept;

   ~SafeBuf();

   // range access

   char * getPtr() const { return ptr; }

   char * getPtr_const() const { return ptr; }

   ulen getLen() const { return len; }
 };

} // namespace CCore

#endif


