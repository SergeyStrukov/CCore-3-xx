/* ToMemBase.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: Applied Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_ToMemBase_h
#define CCore_inc_ToMemBase_h

#include <CCore/inc/Move.h>

namespace CCore {

/* classes */

class ToMemBase;

/* class ToMemBase */

class ToMemBase : NoCopy
 {
   uint8 *ptr;
   ulen len;

  protected:

   uint8 * alloc(ulen len); // one-time call

  public:

   ToMemBase() noexcept;

   ~ToMemBase();

   // range access

   const uint8 * getPtr_const() const { return ptr; }

   const uint8 * getPtr() const { return ptr; }

   ulen getLen() const { return len; }

   // std move

   ToMemBase(ToMemBase &&obj) noexcept : ptr(Replace_null(obj.ptr)),len(Replace_null(obj.len)) {}

   ToMemBase & operator = (ToMemBase &&obj) noexcept;

   // swap/move objects

   void objSwap(ToMemBase &obj)
    {
     Swap(ptr,obj.ptr);
     Swap(len,obj.len);
    }

   explicit ToMemBase(ToMoveCtor<ToMemBase> obj)
    : ptr(Replace_null(obj->ptr)),
      len(obj->len)
    {
    }
 };

} // namespace CCore

#endif


