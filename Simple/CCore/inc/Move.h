/* Move.h */
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

#ifndef CCore_inc_Move_h
#define CCore_inc_Move_h

#include <CCore/inc/Swap.h>
#include <CCore/inc/ToMoveCtor.h>

namespace CCore {

/* concept SwapMovableType<T> */

template <class T>
concept bool SwapMovableType = NothrowDefaultCtorType<T> && Has_objSwap<T> ;

/* functions */

template <CopyCtorType T>
[[deprecated("throw copy-constructible type")]]
T * CopyMove(T *obj,Place<void> place) noexcept requires ( !NothrowCopyCtorType<T> )
 {
  T *ret=new(place) T(*obj);

  obj->~T();

  return ret;
 }

template <NothrowCopyCtorType T>
T * CopyMove(T *obj,Place<void> place) noexcept
 {
  T *ret=new(place) T(*obj);

  obj->~T();

  return ret;
 }

template <SwapMovableType T>
T * SwapMove(T *obj,Place<void> place) noexcept
 {
  T *ret=new(place) T();

  Swap(*obj,*ret);

  obj->~T();

  return ret;
 }

template <MoveCtorType T>
T * MoveMove(T *obj,Place<void> place) noexcept
 {
  T *ret=new(place) T(std::move(*obj));

  obj->~T();

  return ret;
 }

template <Has_ToMoveCtor T>
T * CtorMove(T *obj,Place<void> place) noexcept
 {
  T *ret=new(place) T(ToMoveCtor(*obj));

  obj->~T();

  return ret;
 }

/* concept Has_objMove<T> */

template <class T>
concept bool Has_objMove = requires() { { &T::objMove } -> T * (T::*)(Place<void>) ; } ;

/* concept No_objMove<T> */

template <class T>
concept bool No_objMove = !Has_objMove<T> ;

/* classes */

template <class T> struct MoveAdapter;

/* struct MoveAdapter<T> */

template <Has_objMove T>
struct MoveAdapter<T>
 {
  static T * Move(T *obj,Place<void> place) { return obj->objMove(place); }
 };

template <No_objMove T> requires ( Has_ToMoveCtor<T> )
struct MoveAdapter<T>
 {
  static T * Move(T *obj,Place<void> place) { return CtorMove(obj,place); }
 };

template <No_objMove T> requires ( No_ToMoveCtor<T> && MoveCtorType<T> )
struct MoveAdapter<T>
 {
  static T * Move(T *obj,Place<void> place) { return MoveMove(obj,place); }
 };

template <No_objMove T> requires ( No_ToMoveCtor<T> && !MoveCtorType<T> && SwapMovableType<T> )
struct MoveAdapter<T>
 {
  static T * Move(T *obj,Place<void> place) { return SwapMove(obj,place); }
 };

template <No_objMove T> requires ( No_ToMoveCtor<T> && !MoveCtorType<T> && !SwapMovableType<T> )
struct MoveAdapter<T>
 {
  static T * Move(T *obj,Place<void> place) { return CopyMove(obj,place); }
 };

/* concept ReplaceableType<T> */

template <class T>
concept bool ReplaceableType = Has_objMove<T> || Has_ToMoveCtor<T> || MoveCtorType<T> || SwapMovableType<T> || CopyCtorType<T> ;

/* Move() */

template <ReplaceableType T>
T * Move(T *obj,Place<void> place) noexcept { return MoveAdapter<T>::Move(obj,place); }

} // namespace CCore

#endif


