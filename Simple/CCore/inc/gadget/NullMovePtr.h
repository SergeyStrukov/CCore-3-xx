/* NullMovePtr.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.60
//
//  Tag: Simple Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_gadget_NullMovePtr_h
#define CCore_inc_gadget_NullMovePtr_h

#include <CCore/inc/gadget/NoCopy.h>
#include <CCore/inc/gadget/Replace.h>

namespace CCore {

/* classes */

template <class T> class NullMovePtr;

/* class NullMovePtr<T> */

template <class T>
class NullMovePtr : NoCopy
 {
   T *ptr;

  public:

   // constructors

   NullMovePtr() noexcept : ptr(0) {}

   explicit NullMovePtr(T *ptr_) : ptr(ptr_) {}

   // std move

   NullMovePtr(NullMovePtr<T> &&obj) noexcept : ptr(Replace_null(obj.ptr)) {}

   NullMovePtr<T> & operator = (NullMovePtr<T> &&obj) noexcept
    {
     if( this!=&obj )
       {
        ptr=Replace_null(obj.ptr);
       }

     return *this;
    }

   // object ptr

   T * operator + () const { return ptr; }

   bool operator ! () const { return !ptr; }

   T * getPtr() const { return ptr; }

   T & operator * () const { return *ptr; }

   T * operator -> () const { return ptr; }
 };

} // namespace CCore

#endif

