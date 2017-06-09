/* BaseRangeAlgo.h */
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

#ifndef CCore_inc_algon_BaseRangeAlgo_h
#define CCore_inc_algon_BaseRangeAlgo_h

#include <CCore/inc/Swap.h>

namespace CCore {
namespace Algon {

/* concept RangeAlgo<Algo,R> */

template <class Algo,class R,UIntType LenType>
concept bool RangeAlgo2 = requires(R r,LenType len)
 {
  r[len];

  Algo::GetPtr(r);

  { Algo::GetLen(r) } -> LenType ;

  { Algo::GetPrefix(r,len) } -> R ;

  { Algo::GetSuffix(r,len) } -> R ;

  { Algo::Split(r,len) } -> R ;

  { Algo::GetPrefix(r,r) } -> R ;

  Algo::RangeSwap(r,r);

  Algo::Reverse(r);
 } ;

template <class Algo,class R>
concept bool RangeAlgo = requires(R r)
 {
  typename Algo::LenType;

  requires ( RangeAlgo2<Algo,R,typename Algo::LenType> ) ;
 } ;

/* concept Has_RangeAlgo<R> */

template <class R>
concept bool Has_RangeAlgo = requires()
 {
  typename R::RangeAlgo;

  requires ( RangeAlgo<typename R::RangeAlgo,R> ) ;
 } ;

/* concept RangeType<R> */

template <CursorType R>
concept bool RangeType = IsPtrLen<R> || IsPtrLenReverse<R> || Has_RangeAlgo<R> ;

/* classes */

template <class R> struct BaseRangeAlgo_gen;

template <class R> struct BaseRangeAlgo;

/* struct BaseRangeAlgo_gen<R> */

template <class R>
struct BaseRangeAlgo_gen
 {
  using LenType = ulen ;

  static auto GetPtr(R r) { return r.ptr; }

  static LenType GetLen(R r) { return r.len; }

  static R GetPrefix(R r,LenType len) { return r.prefix(len); }

  static R GetSuffix(R r,LenType len) { return r.suffix(len); }

  static R Split(R &r,LenType prefix) { return r+=prefix; }

  static R GetPrefix(R r,R suffix) { return r.prefix(suffix); }

  static void RangeSwap(R a,R b)
   {
    for(; +a ;++a,++b) Swap(*a,*b);
   }

  static auto Reverse(R r) { return r.reverse(); }
 };

/* struct BaseRangeAlgo<R> */

template <Has_RangeAlgo R>
struct BaseRangeAlgo<R> : R::RangeAlgo {};

template <class T>
struct BaseRangeAlgo<PtrLen<T> > : BaseRangeAlgo_gen<PtrLen<T> >
 {
  static void RangeSwap(PtrLen<T> a,PtrLen<T> b)
   {
    for(T *p=b.ptr; +a ;++a,++p) Swap(*a,*p);
   }

  static PtrLenReverse<T> Reverse(PtrLen<T> r) { return RangeReverse(r); }
 };

template <class T>
struct BaseRangeAlgo<PtrLenReverse<T> > : BaseRangeAlgo_gen<PtrLenReverse<T> >
 {
  static T * GetPtr(PtrLenReverse<T> r) { return r.ptr-1; }

  static void RangeSwap(PtrLenReverse<T> a,PtrLenReverse<T> b)
   {
    for(T *p=b.ptr; +a ;++a,--p) Swap(*a,p[-1]);
   }
 };

} // namespace Algon
} // namespace CCore

#endif


