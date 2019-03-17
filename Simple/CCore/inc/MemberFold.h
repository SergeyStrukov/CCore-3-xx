/* MemberFold.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.60
//
//  Tag: Simple
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_MemberFold_h
#define CCore_inc_MemberFold_h

#include <CCore/inc/Gadget.h>

namespace CCore {

/* classes */

template <class IList,class ... TT> struct ConstTupleFactory;

template <class ... TT> struct ConstTuple;

template <class ... MM> struct MemberList;

/* struct ConstTupleFactory<TT> */

template <class ... TT,int ... IList>
struct ConstTupleFactory<Meta::IndexListBox<IList...>,TT...>
 {
  template <int Ind,class T>
  struct Field
   {
    T field;

    explicit constexpr Field(const T &t) : field(t) {}
   };

  template <int I,class T>
  static constexpr const Field<I,T> * Cast(const Field<I,T> *ptr) { return ptr; }

  struct Tuple : Field<IList,TT>...
   {
    explicit constexpr Tuple(const TT & ... tt) : Field<IList,TT>(tt)... {}

    template <int I>
    constexpr decltype(auto) get() const { return Cast<I>(this)->field; }

    template <class Func>
    constexpr decltype(auto) call(Func func) const { return func( get<IList>()... ); }
   };
 };

/* struct ConstTuple<TT> */

template <class ... TT>
using ConstTupleAlias = typename ConstTupleFactory< Meta::IndexList<1,TT...> ,TT...>::Tuple ;

template <class ... TT>
struct ConstTuple : ConstTupleAlias<TT...>
 {
  using ConstTupleAlias<TT...>::ConstTupleAlias;
 };

template <class ... TT>
ConstTuple(const TT & ... tt) -> ConstTuple<TT...> ;

/* struct MemberList<MM> */

template <class ... MM>
struct MemberList
 {
  ConstTuple<MM...> list;

  constexpr MemberList(const MM & ... mm) : list(mm...) {}

  decltype(auto) operator () (auto *ptr,auto func) const
   {
    return list.call( [&] (auto ... mm) { return func( (ptr->*mm)... ); } );
   }

  template <class Func>
  struct Apply
   {
    Func &func;

    template <class S,class ... SS>
    constexpr decltype(auto) operator () (SS S::* ...)
     {
      return func.template operator() <SS...> ();
     }
   };

  template <class Func>
  constexpr decltype(auto) operator () (Func func) const
   {
    return list.call( Apply<Func>{func} );
   }
 };

/* MembersOf<T>() */

template <class T>
constexpr auto MembersOf()
 {
  return T::template Fold<MemberList,T>();
 }

/* const Members<T> */

template <class T>
inline constexpr auto Members = MembersOf<T>() ;

} // namespace CCore

#endif

