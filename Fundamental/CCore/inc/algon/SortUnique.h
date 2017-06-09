/* SortUnique.h */
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

#ifndef CCore_inc_algon_SortUnique_h
#define CCore_inc_algon_SortUnique_h

#include <CCore/inc/Sort.h>
#include <CCore/inc/FunctorType.h>
#include <CCore/inc/algon/BaseRangeAlgo.h>

namespace CCore {
namespace Algon {

/* classes */

template <RangeType R,class Algo=BaseRangeAlgo<R> > struct ApplyUniqueAlgo;

/* struct ApplyUniqueAlgo<R,Algo> */

template <RangeType R,class Algo>
struct ApplyUniqueAlgo : Algo
 {
  using Algo::GetPtr;
  using Algo::GetPrefix;

  using T = Meta::PtrObjType<R> ;

  template <FuncInitArgType<T &> FuncInit>
  static void ApplyUnique(R r,FuncInit func_init) requires ( OpNotEqualType<T> )
   {
    FunctorTypeOf<FuncInit> func(func_init);

    if( +r )
      {
       auto last=GetPtr(r);

       func(*last);

       for(++r; +r ;++r)
         {
          if( *last!=*r )
            {
             last=GetPtr(r);

             func(*last);
            }
         }
      }
   }

  template <ToOpNotEqualFuncType<T> Func,FuncInitArgType<T &> FuncInit>
  static void ApplyUniqueBy(R r,Func by,FuncInit func_init)
   {
    FunctorTypeOf<FuncInit> func(func_init);

    if( +r )
      {
       auto last=GetPtr(r);

       func(*last);

       for(++r; +r ;++r)
         {
          if( by(*last)!=by(*r) )
            {
             last=GetPtr(r);

             func(*last);
            }
         }
      }
   }

  template <FuncInitArgType<R> FuncInit>
  static void ApplyUniqueRange(R r,FuncInit func_init) requires ( OpNotEqualType<T> )
   {
    FunctorTypeOf<FuncInit> func(func_init);

    if( +r )
      {
       R last=r;

       for(++r; +r ;++r)
         {
          if( *last!=*r )
            {
             R delta=GetPrefix(last,r);

             last=r;

             func(delta);
            }
         }

       func(last);
      }
   }

  template <ToOpNotEqualFuncType<T> Func,FuncInitArgType<R> FuncInit>
  static void ApplyUniqueRangeBy(R r,Func by,FuncInit func_init)
   {
    FunctorTypeOf<FuncInit> func(func_init);

    if( +r )
      {
       R last=r;

       for(++r; +r ;++r)
         {
          if( by(*last)!=by(*r) )
            {
             R delta=GetPrefix(last,r);

             last=r;

             func(delta);
            }
         }

       func(last);
      }
   }
 };

/* ...SortBy() */

template <RanType Ran,ULenType Len,PtrToOpLessFuncType<Ran> Func>
void IncrSortBy(Ran ptr,Len len,Func by)
 {
  using T = Meta::PtrObjType<Ran> ;

  IncrSort(ptr,len, [=] (const T &a,const T &b) -> bool { return by(a) < by(b) ; } );
 }

template <RanType Ran,ULenType Len,PtrToOpLessFuncType<Ran> Func>
void DecrSortBy(Ran ptr,Len len,Func by)
 {
  using T = Meta::PtrObjType<Ran> ;

  DecrSort(ptr,len, [=] (const T &a,const T &b) -> bool { return by(a) < by(b) ; } );
 }

template <class T,ToOpLessFuncType<T> Func>
void IncrSortBy(PtrLen<T> range,Func by) { IncrSortBy(range.ptr,range.len,by); }

template <class T,ToOpLessFuncType<T> Func>
void DecrSortBy(PtrLen<T> range,Func by) { DecrSortBy(range.ptr,range.len,by); }

template <class T,ToOpLessFuncType<T> Func>
void IncrSortBy(PtrLenReverse<T> range,Func by) { DecrSortBy(range.reverse(),by); }

template <class T,ToOpLessFuncType<T> Func>
void DecrSortBy(PtrLenReverse<T> range,Func by) { IncrSortBy(range.reverse(),by); }

/* ApplyUnique() */

template <RangeType R,class FuncInit>
void ApplyUnique(R r,FuncInit func_init)
 {
  ApplyUniqueAlgo<R>::ApplyUnique(r,func_init);
 }

/* SortThenApplyUnique() */

template <RangeType R,class FuncInit>
void SortThenApplyUnique(R r,FuncInit func_init)
 {
  Sort(r);
  ApplyUnique(r,func_init);
 }

/* ApplyUniqueBy() */

template <RangeType R,class Func,class FuncInit>
void ApplyUniqueBy(R r,Func by,FuncInit func_init)
 {
  ApplyUniqueAlgo<R>::ApplyUniqueBy(r,by,func_init);
 }

/* ...SortThenApplyUniqueBy() */

template <RangeType R,class Func,class FuncInit>
void IncrSortThenApplyUniqueBy(R r,Func by,FuncInit func_init)
 {
  IncrSortBy(r,by);
  ApplyUniqueBy(r,by,func_init);
 }

template <RangeType R,class Func,class FuncInit>
void DecrSortThenApplyUniqueBy(R r,Func by,FuncInit func_init)
 {
  DecrSortBy(r,by);
  ApplyUniqueBy(r,by,func_init);
 }

/* ApplyUniqueRange() */

template <RangeType R,class FuncInit>
void ApplyUniqueRange(R r,FuncInit func_init)
 {
  ApplyUniqueAlgo<R>::ApplyUniqueRange(r,func_init);
 }

/* SortThenApplyUniqueRange() */

template <RangeType R,class FuncInit>
void SortThenApplyUniqueRange(R r,FuncInit func_init)
 {
  Sort(r);
  ApplyUniqueRange(r,func_init);
 }

/* ApplyUniqueRangeBy() */

template <RangeType R,class Func,class FuncInit>
void ApplyUniqueRangeBy(R r,Func by,FuncInit func_init)
 {
  ApplyUniqueAlgo<R>::ApplyUniqueRangeBy(r,by,func_init);
 }

/* ...SortThenApplyUniqueRangeBy() */

template <RangeType R,class Func,class FuncInit>
void IncrSortThenApplyUniqueRangeBy(R r,Func by,FuncInit func_init)
 {
  IncrSortBy(r,by);
  ApplyUniqueRangeBy(r,by,func_init);
 }

template <RangeType R,class Func,class FuncInit>
void DecrSortThenApplyUniqueRangeBy(R r,Func by,FuncInit func_init)
 {
  DecrSortBy(r,by);
  ApplyUniqueRangeBy(r,by,func_init);
 }

} // namespace Algon
} // namespace CCore

#endif


