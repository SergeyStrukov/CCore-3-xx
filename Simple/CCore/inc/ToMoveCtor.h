/* ToMoveCtor.h */
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

#ifndef CCore_inc_ToMoveCtor_h
#define CCore_inc_ToMoveCtor_h

#include <CCore/inc/Gadget.h>

namespace CCore {

/* classes */

template <class T> struct ToMoveCtor;

/* struct ToMoveCtor<T> */

template <class T>
struct ToMoveCtor
 {
  T *obj;

  explicit ToMoveCtor(T &obj_) { obj=&obj_; }

  T * operator -> () const { return obj; }

  template <class S>
  ToMoveCtor<S> cast() const { return ToMoveCtor<S>(*obj); }
 };

/* concept Has_ToMoveCtor<T> */

template <class T>
concept bool Has_ToMoveCtor = requires(ToMoveCtor<T> arg)
 {
  T(arg);
 } ;

/* concept No_ToMoveCtor<T> */

template <class T>
concept bool No_ToMoveCtor = !Has_ToMoveCtor<T> ;

} // namespace CCore

#endif


