/* AutoCast.h */
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

#ifndef CCore_inc_gadget_AutoCast_h
#define CCore_inc_gadget_AutoCast_h

namespace CCore {

/* classes */

template <class T> class AutoCast;

/* class AutoCast<T> */

template <class T>
class AutoCast
 {
   T *ptr;

  public:

   explicit AutoCast(T *ptr_) : ptr(ptr_) {}

   template <class S>
   operator S * () const { return static_cast<S *>(ptr); }
 };

} // namespace CCore

#endif

