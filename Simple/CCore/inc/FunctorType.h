/* FunctorType.h */
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

#ifndef CCore_inc_FunctorType_h
#define CCore_inc_FunctorType_h

#include <CCore/inc/Gadget.h>

namespace CCore {

/* classes */

template <class FuncInit> struct FunctorTypeOfCtor;

template <class T> struct FunctorRef;

/* concept Has_FunctorType<T> */

template <class T>
concept bool Has_FunctorType = requires() { typename T::FunctorType; } ;

/* concept No_FunctorType<T> */

template <class T>
concept bool No_FunctorType = !Has_FunctorType<T> ;

/* struct FunctorTypeOfCtor<FuncInit> */

template <Has_FunctorType FuncInit>
struct FunctorTypeOfCtor<FuncInit>
 {
  using Ret = typename FuncInit::FunctorType ;
 };

template <No_FunctorType FuncInit>
struct FunctorTypeOfCtor<FuncInit>
 {
  using Ret = FuncInit ;
 };

/* type FunctorTypeOf<FuncInit> */

template <class FuncInit>
using FunctorTypeOf = typename FunctorTypeOfCtor<FuncInit>::Ret ;

/* concept FuncInitArgType<FuncInit,AA> */

template <CopyCtorType FuncInit,class ... AA>
concept bool FuncInitArgType = requires(FuncInit func_init)
 {
  FunctorTypeOf<FuncInit>(func_init);

  requires ( FuncArgType<FunctorTypeOf<FuncInit>,AA...> );
 } ;

/* concept FuncInitType<FuncInit,R,AA> */

template <class FuncInit,class R,class ... AA>
concept bool FuncInitType = FuncInitArgType<FuncInit,AA...> && requires(FuncInit func_init)
 {
  requires ( FuncType<FunctorTypeOf<FuncInit>,R,AA...> );
 } ;

/* struct FunctorRef<T> */

template <class T>
struct FunctorRef
 {
  T *obj;

  explicit FunctorRef(T &obj_) : obj(&obj_) {}

  using FunctorType = T & ;

  operator FunctorType() const { return *obj; }
 };

} // namespace CCore

#endif


