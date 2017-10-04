/* IntegerAlgo.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.01
//
//  Tag: Applied
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_math_IntegerAlgo_h
#define CCore_inc_math_IntegerAlgo_h

#include <CCore/inc/Cmp.h>

namespace CCore {
namespace Math {

/* concept IntAlgo<Algo> */

template <class Algo,UIntType Unit>
concept bool IntAlgo2 = requires(Unit *c,const Unit *a,const Unit *b,ulen n,ulen m,ulen k,Unit A,Unit B,Unit C,unsigned shift)
 {
  // consts

  { Algo::UnitBits } -> unsigned ;

  { Algo::MaxUnit } -> Unit ;

  { Algo::MSBit } -> Unit ;

  // functions

  { Algo::SignExt(a,n) } -> Unit ;

  { Algo::CountZeroMSB(A) } -> unsigned ;

  { Algo::DoubleUDiv(A,B,C) } -> Unit ;

  // const operators

  { Algo::USign(a,n) } -> CmpResult ;

  { Algo::Sign(a,n) } -> CmpResult ;

  { Algo::UCmp(a,b,n) } -> CmpResult ;

  { Algo::UCmp(a,n,b,n) } -> CmpResult ;

  { Algo::Cmp(a,n,b,n) } -> CmpResult ;

  { Algo::UNormalize(a,n) } -> ulen ;

  { Algo::Normalize(a,n) } -> ulen ;

  // additive operators

  { Algo::UNeg(c,n) } -> Unit ;

  { Algo::Neg(c,n) } -> Unit ;

  { Algo::UAddUnit(c,n,A) } -> Unit ;

  { Algo::USubUnit(c,n,A) } -> Unit ;

  { Algo::UAdd(c,b,n) } -> Unit ;

  { Algo::Add(c,n,b,m) } -> Unit ;

  { Algo::USub(c,b,n) } -> Unit ;

  { Algo::Sub(c,n,b,m) } -> Unit ;

  { Algo::RevSub(c,n,b,m) } -> Unit ;

  // shift operators

  { Algo::ULShift(c,n,shift) } -> Unit ;

  { Algo::LShift(c,b,n,shift) } -> Unit ;

  { Algo::ShiftUp(c,n,m,shift) } -> Unit ;

  Algo::RShift(c,b,n,shift);

  Algo::ShiftDown(c,n,m,shift);

  // multiplicative operators

  Algo::UMul(c,a,n,b,m);

  Algo::UMulLo(c,k,a,n,b,m);

  Algo::Mul(c,a,n,b,m);

  Algo::Sq(c,a,n);

  // data functions

  Algo::Null(c,n);

  Algo::Copy(c,a,n);

  Algo::MoveUp(c,n,m);

  Algo::MoveDown(c,n,m);
 } ;

template <class Algo>
concept bool IntAlgo = requires()
 {
  typename Algo::Unit;

  requires ( IntAlgo2<Algo,typename Algo::Unit> );
 } ;

/* struct Algo */

#if 0

struct Algo
 {
  // types and consts

! using Unit = ??? ; // unsigned integral type

! static constexpr unsigned UnitBits = ??? ;

/ static constexpr Unit MaxUnit = ??? ;

/ static constexpr Unit MSBit = ??? ;

  // functions

  static Unit SignExt(Unit a);

! static Unit SignExt(const Unit *a,ulen na);

  static CmpResult SignCmp(Unit a,Unit b);

! static unsigned CountZeroMSB(Unit a);

  static unsigned CountZeroLSB(Unit a);

/ static Unit DoubleUDiv(Unit hi,Unit lo,Unit den); // hi<den

  // const operators

/ static CmpResult USign(const Unit *a,ulen na);

! static CmpResult Sign(const Unit *a,ulen na);

/ static CmpResult UCmp(const Unit *a,const Unit *b,ulen nab);

/ static CmpResult UCmp(const Unit *a,ulen na,const Unit *b,ulen nb);

  static CmpResult Cmp(const Unit *a,const Unit *b,ulen nab);

! static CmpResult Cmp(const Unit *a,ulen na,const Unit *b,ulen nb);

/ static ulen UNormalize(const Unit *a,ulen na);

! static ulen Normalize(const Unit *a,ulen na);

  // additive operators

/ static Unit/* c */ UNeg(Unit *a,ulen na);

! static Unit/* msu */ Neg(Unit *a,ulen na);

/ static Unit/* c */ UAddUnit(Unit *a,ulen na,Unit b);

  static Unit/* msu */ AddUnit(Unit *a,ulen na,Unit b);

/ static Unit/* c */ USubUnit(Unit *a,ulen na,Unit b);

  static Unit/* msu */ SubUnit(Unit *a,ulen na,Unit b);

  static Unit/* c */ UNegAddUnit(Unit *a,ulen na,Unit b);

  static Unit/* msu */ NegAddUnit(Unit *a,ulen na,Unit b);

/ static Unit/* c */ UAdd(Unit *restrict b,const Unit *a,ulen nab);

! static Unit/* msu */ Add(Unit *restrict b,ulen nb,const Unit *a,ulen na); // nb>=na

/ static Unit/* c */ USub(Unit *restrict b,const Unit *a,ulen nab);

! static Unit/* msu */ Sub(Unit *restrict b,ulen nb,const Unit *a,ulen na); // nb>=na

  static Unit/* c */ URevSub(Unit *restrict b,const Unit *a,ulen nab);

! static Unit/* msu */ RevSub(Unit *restrict b,ulen nb,const Unit *a,ulen na); // nb>=na

  // shift operators

/ static Unit/* msu */ ULShift(Unit *a,ulen na,unsigned shift); // 0<shift<UnitBits

! static Unit/* msu */ LShift(Unit *restrict b,const Unit *a,ulen nab,unsigned shift); // 0<shift<UnitBits

  static Unit/* msu */ UShiftUp(Unit *a,ulen na,ulen delta,unsigned shift); // a[na+delta] , 0<shift<UnitBits

! static Unit/* msu */ ShiftUp(Unit *a,ulen na,ulen delta,unsigned shift); // a[na+delta] , 0<shift<UnitBits

  static void URShift(Unit *a,ulen na,unsigned shift); // 0<shift<UnitBits

! static void RShift(Unit *restrict b,const Unit *a,ulen nab,unsigned shift); // 0<shift<UnitBits

  static void UShiftDown(Unit *a,ulen na,ulen delta,unsigned shift); // a[na+delta] , 0<shift<UnitBits

! static void ShiftDown(Unit *a,ulen na,ulen delta,unsigned shift); // a[na+delta] , 0<shift<UnitBits

  // multiplicative operators

/ static void UMul(Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb); // nc==na+nb

  static Unit/* c */ UMac(Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb); // nc==na+nb

/ static void UMulLo(Unit *restrict c,ulen nc,const Unit *a,ulen na,const Unit *b,ulen nb); // nc<=na+nb

  static void USq(Unit *restrict c,const Unit *a,ulen na); // nc==2*na

! static void Mul(Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb); // nc==na+nb

! static void Sq(Unit *restrict c,const Unit *a,ulen na); // nc==2*na

  // data functions

! static void Null(Unit *a,ulen na);

! static void Copy(Unit *restrict b,const Unit *a,ulen nab);

! static void MoveUp(Unit *a,ulen na,ulen delta); // a[na+delta]

! static void MoveDown(Unit *a,ulen na,ulen delta); // a[na+delta]
 };

#endif

/* guards */

void GuardAddLenOverflow_ulen(ulen a,ulen b);

void GuardAddLenOverflow_ulen();

void GuardAddLenOverflow(UIntType a,ulen b)
 {
  if( a<=MaxULen )
    GuardAddLenOverflow_ulen(ulen(a),b);
  else
    GuardAddLenOverflow_ulen();
 }

/* functions */

ulen AddLen(UIntType a,ulen b)
 {
  if( a>MaxULen-b ) GuardAddLenOverflow(a,b);

  return ulen(a+b);
 }

ulen AddLen(UIntType a,ulen b,ulen c) { return AddLen(a,AddLen(b,c)); }

} // namespace Math
} // namespace CCore

#endif

