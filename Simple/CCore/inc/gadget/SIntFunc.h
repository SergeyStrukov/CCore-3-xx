/* SIntFunc.h */
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

#ifndef CCore_inc_gadget_SIntFunc_h
#define CCore_inc_gadget_SIntFunc_h

#include <CCore/inc/gadget/UIntFunc.h>
#include <CCore/inc/gadget/Classification.h>

namespace CCore {

/* classes */

template <S2sIntType SInt> struct SIntFunc;

/* struct SIntFunc<SInt> */

template <S2sIntType SInt>
struct SIntFunc
 {
  // types

  using UInt = typename Meta::SIntToUInt<SInt>::UType ;

  static SInt ToSInt(UInt a) { return SInt(a); }

   //
   // assume
   //
   //  SInt a; // non-singular
   //
   //  ToSInt( (UInt)a ) == a
   //

  // consts

  static constexpr UInt MaxPositiveAbs = UIntFunc<UInt>::MaxPositive ; // 2's complement property

  static constexpr UInt MinNegativeAbs = UIntFunc<UInt>::MinNegative ; // 2's complement property

  static constexpr SInt MaxPositive = SInt(MaxPositiveAbs) ;

  static constexpr SInt MinNegative = SInt(MinNegativeAbs) ;

  // abs

  static SInt PosAbs(UInt abs) { return ToSInt(abs); }

  static SInt NegAbs(UInt abs) { return ToSInt(UIntFunc<UInt>::Neg(abs)); }

  // shift

  static SInt LShift(SInt a,unsigned shift) { return ToSInt(UInt(a)<<shift); } // ASL

  static SInt RShift(SInt a,unsigned shift) { return a>>shift; } // TODO ASR

  // mask

  static SInt Mask(SInt a,UInt mask) { return ToSInt(UInt(a)&mask); }

  // dist/move

  static UInt Dist(SInt a,SInt b) // a <= b
   {
    return UInt(b)-UInt(a);
   }

  static SInt MovePos(SInt a,UInt delta)
   {
    return ToSInt(UInt(a)+delta);
   }

  static SInt MoveNeg(SInt a,UInt delta)
   {
    return ToSInt(UInt(a)-delta);
   }

  static SInt Move(SInt a,SInt e,UInt delta)
   {
    return (e>0)?MovePos(a,delta):MoveNeg(a,delta);
   }
 };

} // namespace CCore

#endif


