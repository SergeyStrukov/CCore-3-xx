/* MetaList.h */
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
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_gadget_MetaList_h
#define CCore_inc_gadget_MetaList_h

#include <CCore/inc/gadget/Meta.h>

namespace CCore {
namespace Meta {

/* classes */

template <int Base,class T> struct BaseBox;

template <int ... IList> struct IndexListBox;

template <class ... TT> struct TypeListBox;

template <class Box1,class Box2> struct JoinTypeListCtor;

template <unsigned Index,class Box> struct SplitTypeListBox;

template <unsigned Index,class ... TT> requires ( Index <= sizeof ... (TT) ) struct SplitTypeList;

template <class T,unsigned Ret,bool Ok> struct IndexOfBox;

template <class ... TT> requires ( sizeof ... (TT) > 0 ) struct PopTypeList;

/* type EraseType<T> */

template <class T>
using EraseType = int ;

/* struct BaseBox<int Base,T> */

template <int Base,class T>
struct BaseBox
 {
 };

/* struct IndexListBox<int ... IList> */

template <int ... IList>
struct IndexListBox
 {
  template <int Base,class T>
  IndexListBox<IList...,Base+sizeof ... (IList)> operator + (BaseBox<Base,T>);
 };

/* type IndexList<int Base,TT> */

template <int Base,class ... TT>
using IndexList = decltype( ( IndexListBox<>() + ... + BaseBox<Base,TT>() ) ) ;

/* struct TypeListBox<TT> */

template <>
struct TypeListBox<>
 {
  using Type = TypeListBox<> ;

  template <class ... SS>
  using Extend = TypeListBox<SS...> ;
 };

template <class T,class ... TT>
struct TypeListBox<T,TT...>
 {
  using Type = TypeListBox<T,TT...> ;

  using FirstType = T ;

  template <class ... SS>
  using Extend = TypeListBox<T,TT...,SS...> ;
 };

/* struct JoinTypeListCtor<Box1,Box2> */

template <class Box,class ... TT>
struct JoinTypeListCtor<Box,TypeListBox<TT...> >
 {
  using Ret = typename Box::template Extend<TT...> ;
 };

/* type JoinTypeList<Box1,Box2> */

template <class Box1,class Box2>
using JoinTypeList = typename JoinTypeListCtor<Box1,Box2>::Ret ;

/* struct SplitTypeListBox<unsigned Index,Box> */

template <unsigned Index,class ... TT>
struct SplitTypeListBox<Index,TypeListBox<TT...> > : SplitTypeList<Index,TT...> {};

/* struct SplitTypeList<unsigned Index,TT> */

template <unsigned Index,class ... TT> requires ( Index >= 10 && Index <= sizeof ... (TT) )
struct SplitTypeList<Index,TT...>
 {
  using SplitA = SplitTypeList<( Index/2 ),TT...> ;

  using SplitB = SplitTypeListBox<( Index - Index/2 ),typename SplitA::Last> ;

  using First = JoinTypeList<typename SplitA::First,typename SplitB::First> ;

  using Last = typename SplitB::Last ;
 };

template <class ... TT>
struct SplitTypeList<0,TT...>
 {
  using First = TypeListBox<> ;

  using Last = TypeListBox<TT...> ;
 };

template <class T1,class ... TT>
struct SplitTypeList<1,T1,TT...>
 {
  using First = TypeListBox<T1> ;

  using Last = TypeListBox<TT...> ;
 };

template <class T1,class T2,class ... TT>
struct SplitTypeList<2,T1,T2,TT...>
 {
  using First = TypeListBox<T1,T2> ;

  using Last = TypeListBox<TT...> ;
 };

template <class T1,class T2,class T3,class ... TT>
struct SplitTypeList<3,T1,T2,T3,TT...>
 {
  using First = TypeListBox<T1,T2,T3> ;

  using Last = TypeListBox<TT...> ;
 };

template <class T1,class T2,class T3,class T4,class ... TT>
struct SplitTypeList<4,T1,T2,T3,T4,TT...>
 {
  using First = TypeListBox<T1,T2,T3,T4> ;

  using Last = TypeListBox<TT...> ;
 };

template <class T1,class T2,class T3,class T4,class T5,class ... TT>
struct SplitTypeList<5,T1,T2,T3,T4,T5,TT...>
 {
  using First = TypeListBox<T1,T2,T3,T4,T5> ;

  using Last = TypeListBox<TT...> ;
 };

template <class T1,class T2,class T3,class T4,class T5,class T6,class ... TT>
struct SplitTypeList<6,T1,T2,T3,T4,T5,T6,TT...>
 {
  using First = TypeListBox<T1,T2,T3,T4,T5,T6> ;

  using Last = TypeListBox<TT...> ;
 };

template <class T1,class T2,class T3,class T4,class T5,class T6,class T7,class ... TT>
struct SplitTypeList<7,T1,T2,T3,T4,T5,T6,T7,TT...>
 {
  using First = TypeListBox<T1,T2,T3,T4,T5,T6,T7> ;

  using Last = TypeListBox<TT...> ;
 };

template <class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8,class ... TT>
struct SplitTypeList<8,T1,T2,T3,T4,T5,T6,T7,T8,TT...>
 {
  using First = TypeListBox<T1,T2,T3,T4,T5,T6,T7,T8> ;

  using Last = TypeListBox<TT...> ;
 };

template <class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8,class T9,class ... TT>
struct SplitTypeList<9,T1,T2,T3,T4,T5,T6,T7,T8,T9,TT...>
 {
  using First = TypeListBox<T1,T2,T3,T4,T5,T6,T7,T8,T9> ;

  using Last = TypeListBox<TT...> ;
 };

/* type PrefixTypeList<unsigned Len,TT> */

template <unsigned Len,class ... TT> requires ( Len <= sizeof ... (TT) )
using PrefixTypeList = typename SplitTypeList<Len,TT...>::First ;

/* type PartTypeList<unsigned Off,TT> */

template <unsigned Off,class ... TT> requires ( Off <= sizeof ... (TT) )
using PartTypeList = typename SplitTypeList<Off,TT...>::Last ;

/* type TypeSubList<unsigned Off,unsigned Len,TT> */

template <unsigned Off,unsigned Len,class ... TT> requires ( Off+Len <= sizeof ... (TT) )
using TypeSubList = typename SplitTypeListBox<Len,PartTypeList<Off,TT...> >::First ;

/* type SelectList<unsigned Index,TT> */

template <unsigned Index,class ... TT> requires ( Index < sizeof ... (TT) )
using SelectList = typename SplitTypeList<Index,TT...>::Last::FirstType ;

/* struct IndexOfBox<T,unsigned Ret,bool Ok> */

template <class T,unsigned Ret=1,bool Ok=false>
struct IndexOfBox
 {
  constexpr IndexOfBox<T,Ret,true> operator + (TypeBox<T>) { return {}; }

  template <class S>
  constexpr IndexOfBox<T,Ret+1,false> operator + (TypeBox<S>) { return {}; }
 };

template <class T,unsigned Ret>
struct IndexOfBox<T,Ret,true>
 {
  template <class S>
  constexpr IndexOfBox<T,Ret,true> operator + (TypeBox<S>) { return {}; }

  constexpr operator unsigned() const { return Ret; }
 };

/* const IndexOf<TT> */

template <class T,class ... TT>
inline constexpr unsigned IndexOf = ( IndexOfBox<T>() + ... + TypeBox<TT>() ) ;

/* struct PopTypeList<TT> */

template <class ... TT> requires ( sizeof ... (TT) > 0 )
struct PopTypeList
 {
  using Split = SplitTypeList<( sizeof ... (TT) - 1 ),TT...> ;

  using Start = typename Split::First ;

  using Last = typename Split::Last::FirstType ;
 };

} // namespace Meta
} // namespace CCore

#endif

