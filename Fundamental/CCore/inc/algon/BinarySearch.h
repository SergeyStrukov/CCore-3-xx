/* BinarySearch.h */
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

#ifndef CCore_inc_algon_BinarySearch_h
#define CCore_inc_algon_BinarySearch_h

#include <CCore/inc/algon/BaseRangeAlgo.h>

namespace CCore {
namespace Algon {

/* classes */

template <RangeType R,class Algo=BaseRangeAlgo<R> > struct BinarySearchAlgo;

/* struct BinarySearchAlgo<R,Algo> */

template <RangeType R,class Algo>
struct BinarySearchAlgo : Algo
 {
  using LenType = typename Algo::LenType ;

  using Algo::GetLen;
  using Algo::Split;

  using T = Meta::PtrObjType<R> ;

  static LenType FindLen(R r,FuncType<bool,const T &> pred)
                         // pred(R) is 0,0,0,...,0,1,1,...
   {
    LenType len=GetLen(r);

    if( !len ) return 0;

    LenType off=0;

    // 0,0,... [off,len) 1,1,...

    while( len>1 )
      {
       LenType pref=len/2;

       if( pred(r[off+pref]) )
         {
          len=pref;
         }
       else
         {
          pref++;

          off+=pref;
          len-=pref;

          if( !len ) return off;
         }
      }

    if( pred(r[off]) )
      {
       return off;
      }
    else
      {
       return off+1;
      }
   }

  static R Find(R &r,FuncType<bool,const T &> pred)
                // pred(R) is 0,0,0,...,0,1,1,...
   {
    return Split(r,FindLen(r,pred));
   }

  template <class S>
  static R Find_less(R &r,const S &med) requires ( OpLessTypes<T,S> )
                     // R is decreasing
   {
    return Find(r, [&] (const T &obj) -> bool { return obj<med; } );
   }

  template <class S>
  static R Find_less_or_equal(R &r,const S &med) requires ( OpLessEqualTypes<T,S> )
                              // R is decreasing
   {
    return Find(r, [&] (const T &obj) -> bool { return obj<=med; } );
   }

  template <class S>
  static R Find_greater(R &r,const S &med) requires ( OpGreaterTypes<T,S> )
                        // R is increasing
   {
    return Find(r, [&] (const T &obj) -> bool { return obj>med; } );
   }

  template <class S>
  static R Find_greater_or_equal(R &r,const S &med) requires ( OpGreaterEqualTypes<T,S> )
                                 // R is increasing
   {
    return Find(r, [&] (const T &obj) -> bool { return obj>=med; } );
   }
 };

/* BinarySearch...() */

template <RangeType R,FuncType<bool,const Meta::PtrObjType<R> &> Pred>
R BinarySearch_if(R &r,Pred pred) { return BinarySearchAlgo<R>::Find(r,pred); }

template <RangeType R,class S>
R BinarySearch_less(R &r,const S &med) requires ( OpLessTypes<Meta::PtrObjType<R>,S> )
 {
  return BinarySearchAlgo<R>::Find_less(r,med);
 }

template <RangeType R,class S>
R BinarySearch_less_or_equal(R &r,const S &med) requires ( OpLessEqualTypes<Meta::PtrObjType<R>,S> )
 {
  return BinarySearchAlgo<R>::Find_less_or_equal(r,med);
 }

template <RangeType R,class S>
R BinarySearch_greater(R &r,const S &med) requires ( OpGreaterTypes<Meta::PtrObjType<R>,S> )
 {
  return BinarySearchAlgo<R>::Find_greater(r,med);
 }

template <RangeType R,class S>
R BinarySearch_greater_or_equal(R &r,const S &med) requires ( OpGreaterEqualTypes<Meta::PtrObjType<R>,S> )
 {
  return BinarySearchAlgo<R>::Find_greater_or_equal(r,med);
 }

} // namespace Algon
} // namespace CCore

#endif


