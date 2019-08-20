/* Creator.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: Fundamental Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_array_Creator_h
#define CCore_inc_array_Creator_h

#include <CCore/inc/Tuple.h>
#include <CCore/inc/FunctorType.h>

namespace CCore {

/* concept CreatorType<Creator,T> */

template <class Creator,class T>
concept bool CreatorType = requires()
 {
  { Creator::NoThrow } -> bool ;

  requires ( FuncInitType<Creator,T *,Place<void> > ) ;
 } ;

/* classes */

template <class T,bool no_throw> struct Creator_default;

template <class T,class ... SS> struct Creator_fill;

template <class T,bool no_throw> struct Creator_copy;

template <class T,class S> struct Creator_cast;

template <class T,class Algo> struct Creator_swap;

template <class T,class S,FuncInitType<T,S> FuncInit,bool NoThrow=false> struct Creator_transform;

/* struct Creator_default<T,bool no_throw> */

template <class T,bool no_throw>
struct Creator_default
 {
  enum NoThrowFlagType { NoThrow = no_throw };

  Creator_default() {}

  T * operator () (Place<void> place) noexcept( no_throw )
   {
    return new(place) T();
   }
 };

/* struct Creator_fill<T,SS> */

template <class T,class ... SS>
struct Creator_fill
 {
  enum NoThrowFlagType { NoThrow = false };

  ForwardTuple<SS...> ss;

  explicit Creator_fill(SS && ... ss_) : ss( std::forward<SS>(ss_)... ) {}

  T * operator () (Place<void> place)
   {
    return ss.call( [place] (SS && ... ss) { return new(place) T( std::forward<SS>(ss)... ); } );
   }
 };

/* struct Creator_copy<T,bool no_throw> */

template <class T,bool no_throw>
struct Creator_copy
 {
  enum NoThrowFlagType { NoThrow = no_throw };

  const T *src;

  explicit Creator_copy(const T *src_) : src(src_) {}

  T * operator () (Place<void> place) noexcept( no_throw )
   {
    return new(place) T(*(src++));
   }
 };

/* struct Creator_cast<T,S> */

template <class T,class S>
struct Creator_cast
 {
  enum NoThrowFlagType { NoThrow = false };

  const S *src;

  explicit Creator_cast(const S *src_) : src(src_) {}

  T * operator () (Place<void> place)
   {
    return new(place) T(*(src++));
   }
 };

/* struct Creator_swap<T,Algo> */

template <class T,class Algo>
struct Creator_swap
 {
  enum NoThrowFlagType { NoThrow = Algo::Default_no_throw };

  T *objs;

  explicit Creator_swap(T *objs_) : objs(objs_) {}

  T * operator () (Place<void> place) noexcept( Algo::Default_no_throw )
   {
    return Algo::Create_swap(place,*(objs++));
   }
 };

/* struct Creator_transform<T,S,FuncInit,bool NoThrow> */

template <class T,class S,FuncInitType<T,S> FuncInit,bool NoThrow_>
struct Creator_transform
 {
  enum NoThrowFlagType { NoThrow = NoThrow_ };

  S *src;
  FuncInit func_init;

  Creator_transform(S *src_,const FuncInit &func_init_) : src(src_),func_init(func_init_) {}

  struct FunctorType : NoCopy
   {
    S *src;
    FunctorTypeOf<FuncInit> func;

    explicit FunctorType(Creator_transform init) : src(init.src),func(init.func_init) {}

    T * operator () (Place<void> place) noexcept(NoThrow)
     {
      return new(place) T( func(*(src++)) );
     }
   };
 };

} // namespace CCore

#endif


