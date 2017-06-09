/* UtilFunc.h */
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

#ifndef CCore_inc_gadget_UtilFunc_h
#define CCore_inc_gadget_UtilFunc_h

#include <CCore/inc/gadget/OpAddHelper.h>

namespace CCore {

/* functions */

template <class T>
const T & ToConst(T &obj) { return obj; }

template <class T>
constexpr T Min(T a,T b) { return (a<b)?a:b; }

template <class T>
constexpr T Max(T a,T b) { return (a<b)?b:a; }

template <class T>
constexpr T Min_cast(T a,AnyType ... args)
 {
  return ( OpAddHelper<T,Min>(a) + ... + OpAddHelper<T,Min>(args) ).val;
 }

template <class T>
constexpr T Max_cast(T a,AnyType ... args)
 {
  return ( OpAddHelper<T,Max>(a) + ... + OpAddHelper<T,Max>(args) ).val;
 }

template <class T>
constexpr T Cap(T a,T x,T b) { return (x<a)?a:( (b<x)?b:x ); }

template <class T>
constexpr bool Fit(T a,T x,T b) { return a<=x && x<=b; }

template <class T>
constexpr T Sq(T x) { return x*x; }

template <class T>
T Diff(T &obj,T a)
 {
  T ret(a-obj);

  obj=a;

  return ret;
 }

template <class T>
bool Change(T &obj,T val)
 {
  if( obj!=val )
    {
     obj=val;

     return true;
    }

  return false;
 }

template <class T>
T AddToCap(T val,T delta,T cap)
 {
  if( val<cap )
    {
     return val+Min_cast(delta,cap-val);
    }
  else
    {
     return val;
    }
 }

template <class T,class S>
void CapDown(T &obj,S cap)
 {
  if( obj>cap ) obj=(T)cap;
 }

/* functions */

template <UIntType UInt,class S>
void BitSet(UInt &obj,S bits)
 {
  obj |= UInt(bits) ;
 }

template <UIntType UInt,class S>
void BitClear(UInt &obj,S bits)
 {
  obj &= ~UInt(bits) ;
 }

template <UIntType UInt,class S>
UInt BitTest(UInt val,S bits)
 {
  return UInt( val&UInt(bits) );
 }

template <UIntType UInt,class S>
bool BitTestAll(UInt val,S bits_)
 {
  UInt bits=UInt(bits_);

  return UInt( val&bits )==bits;
 }

} // namespace CCore

#endif


