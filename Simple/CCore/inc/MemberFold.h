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

#include <CCore/inc/Tuple.h>

namespace CCore {

/* classes */

template <class ... MM> struct MemberList;

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

  void per(auto *ptr,auto func) const
   {
    operator () (ptr, [&] (auto & ... x) { ( ... , func(x) ); } );
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

