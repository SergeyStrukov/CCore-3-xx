/* Tuple.h */
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

#ifndef CCore_inc_Tuple_h
#define CCore_inc_Tuple_h

#include <CCore/inc/FunctorType.h>

namespace CCore {

/* classes */

template <class IList,class ... TT> struct TupleFactory;

template <class ... TT> struct Tuple;

template <class IList,class ... TT> struct ForwardTupleFactory;

template <class ... TT> struct ForwardTuple;

/* struct TupleFactory<TT> */

template <class ... TT,int ... IList>
struct TupleFactory<Meta::IndexListBox<IList...>,TT...>
 {
  template <int Ind,class T>
  struct Field
   {
    T field;

    Field() {}

    explicit Field(const T &t) : field(t) {}
   };

  template <int I,class T>
  static Field<I,T> * Cast(Field<I,T> *ptr) { return ptr; }

  template <int I,class T>
  static const Field<I,T> * Cast(const Field<I,T> *ptr) { return ptr; }

  struct Tuple : Field<IList,TT>...
   {
    Tuple() {}

    explicit Tuple(const TT & ... tt) requires ( sizeof ... (TT) > 0 ) : Field<IList,TT>(tt)... {}

    template <int I>
    auto & ref() { return Cast<I>(this)->field; }

    template <int I>
    auto & ref() const { return Cast<I>(this)->field; }

    template <int I>
    auto & ref_const() const { return Cast<I>(this)->field; }

    template <FuncInitArgType<TT & ...> FuncInit>
    auto call(FuncInit func_init)
     {
      FunctorTypeOf<FuncInit> func(func_init);

      return func( ref<IList>()... );
     }

    template <FuncInitArgType<const TT & ...> FuncInit>
    auto call(FuncInit func_init) const
     {
      FunctorTypeOf<FuncInit> func(func_init);

      return func( ref<IList>()... );
     }
   };
 };

/* struct Tuple<TT> */

template <class ... TT>
using TupleAlias = typename TupleFactory< Meta::IndexList<1,TT...> ,TT...>::Tuple ;

template <class ... TT>
struct Tuple : TupleAlias<TT...>
 {
  using TupleAlias<TT...>::TupleAlias;
 };

template <class ... TT>
Tuple(const TT & ... tt) -> Tuple<TT...> ;

/* struct ForwardTupleFactory<TT> */

template <class ... TT,int ... IList>
struct ForwardTupleFactory<Meta::IndexListBox<IList...>,TT...>
 {
  template <int Ind,class T>
  struct Field
   {
    T &&field;

    explicit Field(T &&t) : field( std::forward<T>(t) ) {}

    Field(const Field<Ind,T> &obj) : field( std::forward<T>(obj.field) ) {}
   };

  template <int I,class T>
  static Field<I,T> * Cast(Field<I,T> *ptr) { return ptr; }

  template <int I,class T>
  static const Field<I,T> * Cast(const Field<I,T> *ptr) { return ptr; }

  struct Tuple : Field<IList,TT>...
   {
    explicit Tuple(TT && ... tt) : Field<IList,TT>( std::forward<TT>(tt) )... {}

    template <int I>
    auto && ref() const { return Cast<I>(this)->field; }

    template <FuncInitArgType<TT && ...> FuncInit>
    auto call(FuncInit func_init) const
     {
      FunctorTypeOf<FuncInit> func(func_init);

      return func( std::forward<TT>(ref<IList>())... );
     }
   };
 };

/* struct ForwardTuple<TT> */

template <class ... TT>
using ForwardTupleAlias = typename ForwardTupleFactory< Meta::IndexList<1,TT...> ,TT...>::Tuple ;

template <class ... TT>
struct ForwardTuple : ForwardTupleAlias<TT...>
 {
  using ForwardTupleAlias<TT...>::ForwardTupleAlias;
 };

} // namespace CCore

#endif


