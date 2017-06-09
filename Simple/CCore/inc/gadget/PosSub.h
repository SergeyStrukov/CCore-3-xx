/* PosSub.h */
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

#ifndef CCore_inc_gadget_PosSub_h
#define CCore_inc_gadget_PosSub_h

#include <CCore/inc/gadget/Classification.h>

namespace CCore {

/* classes */

template <UIntType UInt> struct PosSubDeltaType;

template <UIntType UInt> struct PosSubResult;

/* struct PosSubDeltaType<UInt> */

template <UIntType UInt>
struct PosSubDeltaType
 {
  UInt delta;

  constexpr explicit PosSubDeltaType(UInt delta_) : delta(delta_) {}

  constexpr operator UInt() const { return delta; }
 };

template <UIntType UInt>
constexpr PosSubDeltaType<UInt> PosSubDelta(UInt delta) { return PosSubDeltaType<UInt>(delta); }

/* struct PosSubResult<UInt> */

template <UIntType UInt>
struct PosSubResult
 {
  // result

  UInt value;
  bool ok;

  // constructors

  constexpr explicit PosSubResult(UInt value_,bool ok_=true) : value(value_),ok(ok_) {}

  // methods

  constexpr operator UInt() const { return value; }

  constexpr PosSubResult<UInt> operator - (PosSubDeltaType<UIntType> obj) const
   {
    return (obj<=value)?PosSubResult(UInt(value-obj),ok):PosSubResult(0,false);
   }
 };

/* PosSub() */

template <UIntType UInt,UIntType ... Args>
constexpr PosSubResult<UInt> PosSub(UInt value,Args ... args)
 {
  return ( PosSubResult<UInt>(value) - ... - PosSubDelta(args) );
 }

/* Enough() */

template <UIntType UInt,UIntType ... Args>
constexpr bool Enough(UInt value,Args ... args)
 {
  return PosSub(value,args...).ok;
 }

} // namespace CCore

#endif


