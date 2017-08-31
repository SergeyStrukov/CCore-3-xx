/* ScanBit.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Simple Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_ScanBit_h
#define CCore_inc_ScanBit_h

#include <CCore/inc/Gadget.h>

#include <CCore/inc/base/Quick.h>

namespace CCore {

/* classes */

struct ScanMSBitAlgo;

struct ScanLSBitAlgo;

template <class Algo,ulen Len> class ScanBit;

/* struct ScanMSBitAlgo */

struct ScanMSBitAlgo
 {
  using Unit = Quick::ScanUInt ;

  static constexpr ulen UnitBits = Meta::UIntBits<Unit> ; // expect power of 2

  static constexpr Unit Unit_msb = UIntFunc<Unit>::MSBit ;

  static constexpr Unit Unit_all = UIntFunc<Unit>::MaxUnsigned ;

  static Unit BitNum(ulen number) { return Unit_msb>>number; }

  static Unit MaskUp(ulen number) { return Unit_all>>number; }

  static ulen ScanUp(Unit bit) { return UnitBits-1-Quick::ScanMSBit(bit); }

  static Unit MaskDown(ulen number) { return Unit_all<<(UnitBits-1-number); }

  static ulen ScanDown(Unit bit) { return UnitBits-1-Quick::ScanLSBit(bit); }
 };

/* struct ScanLSBitAlgo */

struct ScanLSBitAlgo
 {
  using Unit = Quick::ScanUInt ;

  static constexpr ulen UnitBits = Meta::UIntBits<Unit> ; // expect power of 2

  static constexpr Unit Unit_lsb = 1 ;

  static constexpr Unit Unit_all = UIntFunc<Unit>::MaxUnsigned ;

  static Unit BitNum(ulen number) { return Unit_lsb<<number; }

  static Unit MaskUp(ulen number) { return Unit_all<<number; }

  static ulen ScanUp(Unit bit) { return Quick::ScanLSBit(bit); }

  static Unit MaskDown(ulen number) { return Unit_all>>(UnitBits-1-number); }

  static ulen ScanDown(Unit bit) { return Quick::ScanMSBit(bit); }
 };

/* class ScanBit<Algo,ulen Len> */

template <class Algo,ulen Len>
class ScanBit
 {
   using Unit = typename Algo::Unit ;

   Unit bits[Len];

  public:

   static constexpr ulen IndexLim = Len*Algo::UnitBits ;

   ScanBit() noexcept : bits() {}

   void set(ulen ind) { BitSet( bits[ind/Algo::UnitBits] , Algo::BitNum(ind%Algo::UnitBits) ); }

   void clear(ulen ind) { BitClear( bits[ind/Algo::UnitBits] , Algo::BitNum(ind%Algo::UnitBits) ); }

   Unit test(ulen ind) const { return BitTest( bits[ind/Algo::UnitBits] , Algo::BitNum(ind%Algo::UnitBits) ); }

   ulen findMin(ulen ind) const; // min>=ind , if( not found ) return IndexLim;

   ulen findMax(ulen ind) const; // max<=ind , if( not found ) return IndexLim;
 };

template <class Algo,ulen Len>
ulen ScanBit<Algo,Len>::findMin(ulen ind) const
 {
  ulen i = ind/Algo::UnitBits ;
  ulen j = ind%Algo::UnitBits ;

  Unit mask=Algo::MaskUp(j);

  if( Unit bit=bits[i]&mask )
    {
     return Algo::ScanUp(bit)+i*Algo::UnitBits;
    }

  for(i++; i<Len ;i++)
    {
     if( Unit bit=bits[i] )
       {
        return Algo::ScanUp(bit)+i*Algo::UnitBits;
       }
    }

  return IndexLim;
 }

template <class Algo,ulen Len>
ulen ScanBit<Algo,Len>::findMax(ulen ind) const
 {
  ulen i = ind/Algo::UnitBits ;
  ulen j = ind%Algo::UnitBits ;

  Unit mask=Algo::MaskDown(j);

  if( Unit bit=bits[i]&mask )
    {
     return Algo::ScanDown(bit)+i*Algo::UnitBits;
    }

  while( i-- )
    {
     if( Unit bit=bits[i] )
       {
        return Algo::ScanDown(bit)+i*Algo::UnitBits;
       }
    }

  return IndexLim;
 }

} // namespace CCore

#endif


