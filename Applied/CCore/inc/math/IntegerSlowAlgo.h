/* IntegerSlowAlgo.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
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

#ifndef CCore_inc_math_IntegerSlowAlgo_h
#define CCore_inc_math_IntegerSlowAlgo_h

#include <CCore/inc/Cmp.h>
#include <CCore/inc/Swap.h>

#include <CCore/inc/math/UIntSlowMulAlgo.h>

namespace CCore {
namespace Math {

/* classes */

template <UIntType UInt,unsigned Shift> struct RShiftConst_shift;

template <UIntType UInt> struct RShiftConst_zero;

template <UIntType UInt,class DUInt=Meta::DoubleUInt<UInt> > struct IntegerSlowMulAlgo;

template <UIntType UInt> struct IntegerSlowAlgo;

/* struct RShiftConst_shift<UInt,unsigned Shift> */

template <UIntType UInt,unsigned Shift>
struct RShiftConst_shift
 {
  static UInt Do(UInt val) { return UInt( val>>Shift ); }
 };

/* struct RShiftConst_zero<UInt> */

template <UIntType UInt>
struct RShiftConst_zero
 {
  static UInt Do(UInt) { return 0; }
 };

/* type RShiftConst<UInt,unsigned Shift,unsigned UIntBits> */

template <UIntType UInt,unsigned Shift,unsigned UIntBits=Meta::UIntBits<UInt> >
using RShiftConst = Meta::Select<( Shift<UIntBits ), RShiftConst_shift<UInt,Shift> , RShiftConst_zero<UInt> > ;

/* struct IntegerSlowMulAlgo<UInt,DUInt> */

template <UIntType UInt,class DUInt>
struct IntegerSlowMulAlgo
 {
  struct DoubleUMul
   {
    UInt hi;
    UInt lo;

    DoubleUMul(UInt a,UInt b);
   };

  static UInt DoubleUDiv(UInt hi,UInt lo,UInt den); // hi<den
 };

template <UIntType UInt,class DUInt>
IntegerSlowMulAlgo<UInt,DUInt>::DoubleUMul::DoubleUMul(UInt a,UInt b)
 {
  const unsigned Bits = Meta::UIntBits<UInt> ;

  DUInt c=DUInt(a)*b;

  lo=UInt(c);
  hi=UInt(c>>Bits);
 }

template <UIntType UInt,class DUInt>
UInt IntegerSlowMulAlgo<UInt,DUInt>::DoubleUDiv(UInt hi,UInt lo,UInt den)
 {
  const unsigned Bits = Meta::UIntBits<UInt> ;

  DUInt a=(DUInt(hi)<<Bits)|lo;

  return UInt(a/den);
 }

/* struct IntegerSlowMulAlgo<UInt,void> */

template <UIntType UInt>
struct IntegerSlowMulAlgo<UInt,void> : UIntSlowMulAlgo<UInt>
 {
 };

/* struct IntegerSlowAlgo<UInt> */

template <UIntType UInt>
struct IntegerSlowAlgo : IntegerSlowMulAlgo<UInt>
 {
  using DoubleUMul = typename IntegerSlowMulAlgo<UInt>::DoubleUMul ;

  // types and consts

  using Unit = UInt ;

  static constexpr unsigned UnitBits = Meta::UIntBits<Unit> ;

  static constexpr Unit MaxUnit = Unit(-1) ;

  static constexpr Unit MSBit = Unit( MaxUnit^(MaxUnit>>1) );

  // functions

  static Unit SignExt(Unit a);

  static Unit SignExt(const Unit *a,ulen na);

  static CmpResult SignCmp(Unit a,Unit b);

  static unsigned CountZeroMSB(Unit a);

  static unsigned CountZeroLSB(Unit a);

  // private functions

  static Unit/* c */ Add(Unit &b,Unit a,Unit carry); // carry = 0,1

  static Unit/* c */ Sub(Unit &b,Unit a,Unit carry); // carry = 0,1

  static Unit/* c */ RevSub(Unit &b,Unit a,Unit carry); // carry = 0,1

  static Unit LShift(Unit hi,Unit lo,unsigned shift); // 0<shift<UnitBits

  static Unit RShift(Unit hi,Unit lo,unsigned shift); // 0<shift<UnitBits

  // private operators

  static CmpResult UCmp(Unit a,Unit b);

  static CmpResult UCmp_(const Unit *a,ulen na,const Unit *b,ulen nb); // na>=nb

  static CmpResult Cmp_(const Unit *a,ulen na,const Unit *b,ulen nb); // na>=nb

  // const operators

  static CmpResult USign(const Unit *a,ulen na);

  static CmpResult Sign(const Unit *a,ulen na);

  static CmpResult UCmp(const Unit *a,const Unit *b,ulen nab);

  static CmpResult UCmp(const Unit *a,ulen na,const Unit *b,ulen nb);

  static CmpResult Cmp(const Unit *a,const Unit *b,ulen nab);

  static CmpResult Cmp(const Unit *a,ulen na,const Unit *b,ulen nb);

  static ulen UNormalize(const Unit *a,ulen na);

  static ulen Normalize(const Unit *a,ulen na);

  // additive operators

  static Unit/* c */ UNeg(Unit *a,ulen na);

  static Unit/* msu */ Neg(Unit *a,ulen na);

  static Unit/* c */ UAddUnit(Unit *a,ulen na,Unit b);

  static Unit/* msu */ AddUnit(Unit *a,ulen na,Unit b);

  static Unit/* c */ USubUnit(Unit *a,ulen na,Unit b);

  static Unit/* msu */ SubUnit(Unit *a,ulen na,Unit b);

  static Unit/* c */ UNegAddUnit(Unit *a,ulen na,Unit b);

  static Unit/* msu */ NegAddUnit(Unit *a,ulen na,Unit b);

  static Unit/* c */ UAdd(Unit *restrict b,const Unit *a,ulen nab);

  static Unit/* msu */ Add(Unit *restrict b,ulen nb,const Unit *a,ulen na); // nb>=na

  static Unit/* c */ USub(Unit *restrict b,const Unit *a,ulen nab);

  static Unit/* msu */ Sub(Unit *restrict b,ulen nb,const Unit *a,ulen na); // nb>=na

  static Unit/* c */ URevSub(Unit *restrict b,const Unit *a,ulen nab);

  static Unit/* msu */ RevSub(Unit *restrict b,ulen nb,const Unit *a,ulen na); // nb>=na

  // shift operators

  static Unit/* msu */ ULShift(Unit *a,ulen na,unsigned shift); // 0<shift<UnitBits

  static Unit/* msu */ LShift(Unit *restrict b,const Unit *a,ulen nab,unsigned shift); // 0<shift<UnitBits

  static Unit/* msu */ UShiftUp(Unit *a,ulen na,ulen delta,unsigned shift); // a[na+delta] , 0<shift<UnitBits

  static Unit/* msu */ ShiftUp(Unit *a,ulen na,ulen delta,unsigned shift); // a[na+delta] , 0<shift<UnitBits

  static void URShift(Unit *a,ulen na,unsigned shift); // 0<shift<UnitBits

  static void RShift(Unit *restrict b,const Unit *a,ulen nab,unsigned shift); // 0<shift<UnitBits

  static void UShiftDown(Unit *a,ulen na,ulen delta,unsigned shift); // a[na+delta] , 0<shift<UnitBits

  static void ShiftDown(Unit *a,ulen na,ulen delta,unsigned shift); // a[na+delta] , 0<shift<UnitBits

  // multiplicative operators

  struct MulAcc;

  static void UMul(Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb); // nc==na+nb

  static Unit/* c */ UMac(Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb); // nc==na+nb

  static void UMulLo(Unit *restrict c,ulen nc,const Unit *a,ulen na,const Unit *b,ulen nb); // nc<=na+nb

  static void USq(Unit *restrict c,const Unit *a,ulen na); // nc==2*na

  static void Mul(Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb); // nc==na+nb

  static void Sq(Unit *restrict c,const Unit *a,ulen na); // nc==2*na

  // data functions

  static void Null(Unit *a,ulen na);

  static void Copy(Unit *restrict b,const Unit *a,ulen nab);

  static void MoveUp(Unit *a,ulen na,ulen delta); // a[na+delta]

  static void MoveDown(Unit *a,ulen na,ulen delta); // a[na+delta]
 };

 // functions

template <UIntType UInt>
UInt IntegerSlowAlgo<UInt>::SignExt(Unit a)
 {
  return Unit( -(a>>(UnitBits-1)) );
 }

template <UIntType UInt>
UInt IntegerSlowAlgo<UInt>::SignExt(const Unit *a,ulen na)
 {
  return (na>0)?SignExt(a[na-1]):0;
 }

template <UIntType UInt>
CmpResult IntegerSlowAlgo<UInt>::SignCmp(Unit a,Unit b)
 {
  return UCmp(Unit(a-MSBit),Unit(b-MSBit));
 }

template <UIntType UInt>
unsigned IntegerSlowAlgo<UInt>::CountZeroMSB(Unit a)
 {
  if( !a ) return UnitBits;

  if( a&MSBit ) return 0;

  unsigned ret=0;
  unsigned n=UnitBits;

  while( n>=2 )
    {
     unsigned m=n/2;

     Unit mask=Unit( MaxUnit<<(UnitBits-m) );

     if( a&mask )
       {
        n=m;
       }
     else
       {
        ret+=m;
        a<<=m;
        n-=m;
       }
    }

  return ret;
 }

template <UIntType UInt>
unsigned IntegerSlowAlgo<UInt>::CountZeroLSB(Unit a)
 {
  if( !a ) return UnitBits;

  if( a&Unit(1) ) return 0;

  unsigned ret=0;
  unsigned n=UnitBits;

  while( n>=2 )
    {
     unsigned m=n/2;

     Unit mask=(Unit(1)<<m)-1;

     if( a&mask )
       {
        n=m;
       }
     else
       {
        ret+=m;
        a>>=m;
        n-=m;
       }
    }

  return ret;
 }

 // private functions

template <UIntType UInt>
UInt/* c */ IntegerSlowAlgo<UInt>::Add(Unit &b,Unit a,Unit c)
 {
  a+=c;
  b+=a;

  return (b<a)|(a<c);
 }

template <UIntType UInt>
UInt/* c */ IntegerSlowAlgo<UInt>::Sub(Unit &b,Unit a,Unit c)
 {
  a+=c;

  Unit ret=(b<a)|(a<c);

  b-=a;

  return ret;
 }

template <UIntType UInt>
UInt/* c */ IntegerSlowAlgo<UInt>::RevSub(Unit &b,Unit a,Unit c)
 {
  Unit d=b+c;
  Unit ret=(a<d)|(d<c);

  b=a-d;

  return ret;
 }

template <UIntType UInt>
UInt IntegerSlowAlgo<UInt>::LShift(Unit hi,Unit lo,unsigned shift)
 {
  return Unit( (hi<<shift)|(lo>>(UnitBits-shift)) );
 }

template <UIntType UInt>
UInt IntegerSlowAlgo<UInt>::RShift(Unit hi,Unit lo,unsigned shift)
 {
  return Unit( (hi<<(UnitBits-shift))|(lo>>shift) );
 }

 // private operators

template <UIntType UInt>
CmpResult IntegerSlowAlgo<UInt>::UCmp(Unit a,Unit b)
 {
  return LessCmp(a,b);
 }

template <UIntType UInt>
CmpResult IntegerSlowAlgo<UInt>::UCmp_(const Unit *a,ulen na,const Unit *b,ulen nb)
 {
  for(; na>nb ;na--)
    if( a[na-1] ) return CmpGreater;

  for(; na>0 ;na--)
    if( CmpResult ret=UCmp(a[na-1],b[na-1]) ) return ret;

  return CmpEqual;
 }

template <UIntType UInt>
CmpResult IntegerSlowAlgo<UInt>::Cmp_(const Unit *a,ulen na,const Unit *b,ulen nb)
 {
  if( na==nb )
    {
     if( na>0 )
       {
        if( CmpResult ret=SignCmp(a[na-1],b[na-1]) ) return ret;

        for(na--; na>0 ;na--)
          if( CmpResult ret=UCmp(a[na-1],b[na-1]) ) return ret;
       }

     return CmpEqual;
    }

  if( nb>0 )
    {
     Unit bext=SignExt(b[nb-1]);

     if( CmpResult ret=SignCmp(a[na-1],bext) ) return ret;

     for(na--; na>nb ;na--)
       if( CmpResult ret=UCmp(a[na-1],bext) ) return ret;

     for(; na>0 ;na--)
       if( CmpResult ret=UCmp(a[na-1],b[na-1]) ) return ret;

     return CmpEqual;
    }

  return Sign(a,na);
 }

 // const operators

template <UIntType UInt>
CmpResult IntegerSlowAlgo<UInt>::USign(const Unit *a,ulen na)
 {
  for(; na>0 ;na--) if( a[na-1]!=0 ) return CmpGreater;

  return CmpEqual;
 }

template <UIntType UInt>
CmpResult IntegerSlowAlgo<UInt>::Sign(const Unit *a,ulen na)
 {
  if( na>0 )
    {
     Unit msa=a[na-1];

     if( msa&MSBit ) return CmpLess;

     if( msa!=0 ) return CmpGreater;

     return USign(a,na-1);
    }
  else
    {
     return CmpEqual;
    }
 }

template <UIntType UInt>
CmpResult IntegerSlowAlgo<UInt>::UCmp(const Unit *a,const Unit *b,ulen nab)
 {
  return UCmp_(a,nab,b,nab);
 }

template <UIntType UInt>
CmpResult IntegerSlowAlgo<UInt>::UCmp(const Unit *a,ulen na,const Unit *b,ulen nb)
 {
  if( na<nb ) return -UCmp_(b,nb,a,na);

  return UCmp_(a,na,b,nb);
 }

template <UIntType UInt>
CmpResult IntegerSlowAlgo<UInt>::Cmp(const Unit *a,const Unit *b,ulen nab)
 {
  return Cmp_(a,nab,b,nab);
 }

template <UIntType UInt>
CmpResult IntegerSlowAlgo<UInt>::Cmp(const Unit *a,ulen na,const Unit *b,ulen nb)
 {
  if( na<nb ) return -Cmp_(b,nb,a,na);

  return Cmp_(a,na,b,nb);
 }

template <UIntType UInt>
ulen IntegerSlowAlgo<UInt>::UNormalize(const Unit *a,ulen na)
 {
  for(; na>0 && a[na-1]==0 ;na--);

  return na;
 }

template <UIntType UInt>
ulen IntegerSlowAlgo<UInt>::Normalize(const Unit *a,ulen na)
 {
  while( na>=2 )
    {
     Unit msa=a[na-1];
     Unit msa1=a[na-2];

     if( msa==SignExt(msa1) )
       na--;
     else
       return na;
    }

  return ( na && a[0] );
 }

 // additive operators

template <UIntType UInt>
UInt/* c */ IntegerSlowAlgo<UInt>::UNeg(Unit *a,ulen na)
 {
  Unit c=0;

  for(; na>0 ;a++,na--)
    {
     c=RevSub(*a,0,c);
    }

  return c;
 }

template <UIntType UInt>
UInt/* msu */ IntegerSlowAlgo<UInt>::Neg(Unit *a,ulen na)
 {
  if( na==0 ) return 0;

  Unit aext=SignExt(a[na-1]);
  Unit c=UNeg(a,na);

  RevSub(aext,0,c);

  return aext;
 }

template <UIntType UInt>
UInt/* c */ IntegerSlowAlgo<UInt>::UAddUnit(Unit *a,ulen na,Unit b)
 {
  if( na==0 ) return b;

  Unit c=Add(*a,b,0);

  for(na--,a++; na>0 ;na--,a++)
    {
     c=Add(*a,0,c);
    }

  return c;
 }

template <UIntType UInt>
UInt/* msu */ IntegerSlowAlgo<UInt>::AddUnit(Unit *a,ulen na,Unit b)
 {
  if( na==0 ) return b;

  Unit aext=SignExt(a[na-1]);

  return aext+UAddUnit(a,na,b);
 }

template <UIntType UInt>
UInt/* c */ IntegerSlowAlgo<UInt>::USubUnit(Unit *a,ulen na,Unit b)
 {
  if( na==0 ) return b;

  Unit c=Sub(*a,b,0);

  for(na--,a++; na>0 ;na--,a++)
    {
     c=Sub(*a,0,c);
    }

  return c;
 }

template <UIntType UInt>
UInt/* msu */ IntegerSlowAlgo<UInt>::SubUnit(Unit *a,ulen na,Unit b)
 {
  if( na==0 ) return Unit(-b);

  Unit aext=SignExt(a[na-1]);

  return aext-USubUnit(a,na,b);
 }

template <UIntType UInt>
UInt/* c */ IntegerSlowAlgo<UInt>::UNegAddUnit(Unit *a,ulen na,Unit b)
 {
  if( na==0 ) return Unit(-b);

  Unit c=RevSub(*a,b,0);

  for(na--,a++; na>0 ;a++,na--)
    {
     c=RevSub(*a,0,c);
    }

  return c;
 }

template <UIntType UInt>
UInt/* msu */ IntegerSlowAlgo<UInt>::NegAddUnit(Unit *a,ulen na,Unit b)
 {
  if( na==0 ) return b;

  Unit aext=SignExt(a[na-1]);

  return -aext-UNegAddUnit(a,na,b);
 }

template <UIntType UInt>
UInt/* c */ IntegerSlowAlgo<UInt>::UAdd(Unit *restrict b,const Unit *a,ulen nab)
 {
  Unit c=0;

  for(; nab>0 ;a++,b++,nab--)
    {
     c=Add(*b,*a,c);
    }

  return c;
 }

template <UIntType UInt>
UInt/* msu */ IntegerSlowAlgo<UInt>::Add(Unit *restrict b,ulen nb,const Unit *a,ulen na)
 {
  if( na==0 ) return SignExt(b,nb);

  Unit aext=SignExt(a[na-1]);
  Unit bext=SignExt(b[nb-1]);
  Unit c=0;

  for(nb-=na; na>0 ;a++,b++,na--)
    {
     c=Add(*b,*a,c);
    }

  for(; nb>0 ;b++,nb--)
    {
     c=Add(*b,aext,c);
    }

  Add(bext,aext,c);

  return bext;
 }

template <UIntType UInt>
UInt/* c */ IntegerSlowAlgo<UInt>::USub(Unit *restrict b,const Unit *a,ulen nab)
 {
  Unit c=0;

  for(; nab>0 ;a++,b++,nab--)
    {
     c=Sub(*b,*a,c);
    }

  return c;
 }

template <UIntType UInt>
UInt/* msu */ IntegerSlowAlgo<UInt>::Sub(Unit *restrict b,ulen nb,const Unit *a,ulen na)
 {
  if( na==0 ) return SignExt(b,nb);

  Unit aext=SignExt(a[na-1]);
  Unit bext=SignExt(b[nb-1]);
  Unit c=0;

  for(nb-=na; na>0 ;a++,b++,na--)
    {
     c=Sub(*b,*a,c);
    }

  for(; nb>0 ;b++,nb--)
    {
     c=Sub(*b,aext,c);
    }

  Sub(bext,aext,c);

  return bext;
 }

template <UIntType UInt>
UInt/* c */ IntegerSlowAlgo<UInt>::URevSub(Unit *restrict b,const Unit *a,ulen nab)
 {
  Unit c=0;

  for(; nab>0 ;a++,b++,nab--)
    {
     c=RevSub(*b,*a,c);
    }

  return c;
 }

template <UIntType UInt>
UInt/* msu */ IntegerSlowAlgo<UInt>::RevSub(Unit *restrict b,ulen nb,const Unit *a,ulen na)
 {
  if( na==0 ) return Neg(b,nb);

  Unit aext=SignExt(a[na-1]);
  Unit bext=SignExt(b[nb-1]);
  Unit c=0;

  for(nb-=na; na>0 ;a++,b++,na--)
    {
     c=RevSub(*b,*a,c);
    }

  for(; nb>0 ;b++,nb--)
    {
     c=RevSub(*b,aext,c);
    }

  RevSub(bext,aext,c);

  return bext;
 }

 // shift operators

template <UIntType UInt>
UInt/* msu */ IntegerSlowAlgo<UInt>::ULShift(Unit *a,ulen na,unsigned shift)
 {
  if( na==0 ) return 0;

  Unit ret=Unit( a[na-1]>>(UnitBits-shift) );

  for(; na>=2 ;na--)
    {
     a[na-1]=LShift(a[na-1],a[na-2],shift);
    }

  a[0]<<=shift;

  return ret;
 }

template <UIntType UInt>
UInt/* msu */ IntegerSlowAlgo<UInt>::LShift(Unit *restrict b,const Unit *a,ulen nab,unsigned shift)
 {
  if( nab==0 ) return 0;

  b[0]=Unit( a[0]<<shift );

  for(ulen i=1; i<nab ;i++)
    {
     b[i]=LShift(a[i],a[i-1],shift);
    }

  return LShift(SignExt(a[nab-1]),a[nab-1],shift);
 }

template <UIntType UInt>
UInt/* msu */ IntegerSlowAlgo<UInt>::UShiftUp(Unit *a,ulen na,ulen delta,unsigned shift)
 {
  if( na==0 ) return 0;

  Unit ret=Unit( a[na-1]>>(UnitBits-shift) );

  for(; na>=2 ;na--)
    {
     a[delta+na-1]=LShift(a[na-1],a[na-2],shift);
    }

  a[delta]=Unit( a[0]<<shift );

  return ret;
 }

template <UIntType UInt>
UInt/* msu */ IntegerSlowAlgo<UInt>::ShiftUp(Unit *a,ulen na,ulen delta,unsigned shift)
 {
  if( na==0 ) return 0;

  Unit ret=LShift(SignExt(a[na-1]),a[na-1],shift);

  for(; na>=2 ;na--)
    {
     a[delta+na-1]=LShift(a[na-1],a[na-2],shift);
    }

  a[delta]=Unit( a[0]<<shift );

  return ret;
 }

template <UIntType UInt>
void IntegerSlowAlgo<UInt>::URShift(Unit *a,ulen na,unsigned shift)
 {
  if( na==0 ) return;

  for(ulen i=0; i<na-1 ;i++)
    {
     a[i]=RShift(a[i+1],a[i],shift);
    }

  a[na-1]>>=shift;
 }

template <UIntType UInt>
void IntegerSlowAlgo<UInt>::RShift(Unit *restrict b,const Unit *a,ulen nab,unsigned shift)
 {
  if( nab==0 ) return;

  for(ulen i=0; i<nab-1 ;i++)
    {
     b[i]=RShift(a[i+1],a[i],shift);
    }

  b[nab-1]=RShift(SignExt(a[nab-1]),a[nab-1],shift);
 }

template <UIntType UInt>
void IntegerSlowAlgo<UInt>::UShiftDown(Unit *a,ulen na,ulen delta,unsigned shift)
 {
  if( na==0 ) return;

  na--;

  for(ulen i=0; i<na ;i++) a[i]=RShift(a[delta+i+1],a[delta+i],shift);

  a[na]=Unit( a[delta+na]>>shift );
 }

template <UIntType UInt>
void IntegerSlowAlgo<UInt>::ShiftDown(Unit *a,ulen na,ulen delta,unsigned shift)
 {
  if( na==0 ) return;

  na--;

  for(ulen i=0; i<na ;i++) a[i]=RShift(a[delta+i+1],a[delta+i],shift);

  a[na]=RShift(SignExt(a[delta+na]),a[delta+na],shift);
 }

 // multiplicative operators

template <UIntType UInt>
struct IntegerSlowAlgo<UInt>::MulAcc
 {
  Unit lo;
  Unit hi;
  ulen hi2;

  MulAcc(Unit a,Unit b)
   {
    DoubleUMul prod(a,b);

    lo=prod.lo;
    hi=prod.hi;
    hi2=0;
   }

  void mac(Unit a,Unit b)
   {
    DoubleUMul prod(a,b);

    Unit c=Add(lo,prod.lo,0);

    c=Add(hi,prod.hi,c);

    hi2+=c;
   }

  void mac2(Unit a,Unit b)
   {
    DoubleUMul prod(a,b);

    Unit c1=prod.hi>>(UnitBits-1);

    prod.hi=LShift(prod.hi,prod.lo,1);
    prod.lo<<=1;

    Unit c=Add(lo,prod.lo,0);

    c=Add(hi,prod.hi,c);

    hi2+=c+c1;
   }

  Unit shift()
   {
    Unit ret=lo;

    lo=hi;
    hi=Unit(hi2);

    hi2=RShiftConst<ulen,UnitBits>::Do(hi2);

    return ret;
   }
 };

template <UIntType UInt>
void IntegerSlowAlgo<UInt>::UMul(Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb)
 {
  if( na==0 || nb==0 )
    {
     Null(c,na+nb);

     return;
    }

  if( na>nb )
    {
     Swap(a,b);
     Swap(na,nb);
    }

  if( na==1 )
    {
     if( nb==1 )
       {
        MulAcc acc(a[0],b[0]);

        c[0]=acc.lo;
        c[1]=acc.hi;

        return;
       }

     MulAcc acc(a[0],b[0]);

     c[0]=acc.shift();

     for(ulen k=1; k<nb-1 ;k++)
       {
        acc.mac(a[0],b[k]);

        c[k]=acc.shift();
       }

     acc.mac(a[0],b[nb-1]);

     c[nb-1]=acc.lo;
     c[nb]=acc.hi;

     return;
    }

  MulAcc acc(a[0],b[0]);

  c[0]=acc.shift();

  for(ulen k=1; k<na ;k++)
    {
     for(ulen i=0; i<=k ;i++) acc.mac(a[i],b[k-i]);

     c[k]=acc.shift();
    }

  for(ulen k=na; k<nb ;k++)
    {
     for(ulen i=0; i<na ;i++) acc.mac(a[i],b[k-i]);

     c[k]=acc.shift();
    }

  for(ulen k=nb; k<na+nb-2 ;k++)
    {
     for(ulen i=k-(nb-1); i<na ;i++) acc.mac(a[i],b[k-i]);

     c[k]=acc.shift();
    }

  acc.mac(a[na-1],b[nb-1]);

  c[na+nb-2]=acc.lo;
  c[na+nb-1]=acc.hi;
 }

template <UIntType UInt>
UInt/* c */ IntegerSlowAlgo<UInt>::UMac(Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb)
 {
  if( na==0 || nb==0 ) return 0;

  if( na>nb )
    {
     Swap(a,b);
     Swap(na,nb);
    }

  if( na==1 )
    {
     if( nb==1 )
       {
        MulAcc acc(a[0],b[0]);
        Unit carry=0;

        carry=Add(c[0],acc.lo,carry);
        carry=Add(c[1],acc.hi,carry);

        return carry;
       }

     MulAcc acc(a[0],b[0]);
     Unit carry=0;

     carry=Add(c[0],acc.shift(),carry);

     for(ulen k=1; k<nb-1 ;k++)
       {
        acc.mac(a[0],b[k]);

        carry=Add(c[k],acc.shift(),carry);
       }

     acc.mac(a[0],b[nb-1]);

     carry=Add(c[nb-1],acc.lo,carry);
     carry=Add(c[nb],acc.hi,carry);

     return carry;
    }

  MulAcc acc(a[0],b[0]);
  Unit carry=0;

  carry=Add(c[0],acc.shift(),carry);

  for(ulen k=1; k<na ;k++)
    {
     for(ulen i=0; i<=k ;i++) acc.mac(a[i],b[k-i]);

     carry=Add(c[k],acc.shift(),carry);
    }

  for(ulen k=na; k<nb ;k++)
    {
     for(ulen i=0; i<na ;i++) acc.mac(a[i],b[k-i]);

     carry=Add(c[k],acc.shift(),carry);
    }

  for(ulen k=nb; k<na+nb-2 ;k++)
    {
     for(ulen i=k-(nb-1); i<na ;i++) acc.mac(a[i],b[k-i]);

     carry=Add(c[k],acc.shift(),carry);
    }

  acc.mac(a[na-1],b[nb-1]);

  carry=Add(c[na+nb-2],acc.lo,carry);
  carry=Add(c[na+nb-1],acc.hi,carry);

  return carry;
 }

template <UIntType UInt>
void IntegerSlowAlgo<UInt>::UMulLo(Unit *restrict c,ulen nc,const Unit *a,ulen na,const Unit *b,ulen nb)
 {
  if( nc==0 ) return;

  if( na==0 || nb==0 )
    {
     Null(c,nc);

     return;
    }

  if( na>nb )
    {
     Swap(a,b);
     Swap(na,nb);
    }

  if( na==1 )
    {
     if( nb==1 )
       {
        MulAcc acc(a[0],b[0]);

        c[0]=acc.lo;

        if( 1>=nc ) return;

        c[1]=acc.hi;

        return;
       }

     MulAcc acc(a[0],b[0]);

     c[0]=acc.shift();

     for(ulen k=1; k<nb-1 ;k++)
       {
        if( k>=nc ) return;

        acc.mac(a[0],b[k]);

        c[k]=acc.shift();
       }

     if( nb-1>=nc ) return;

     acc.mac(a[0],b[nb-1]);

     c[nb-1]=acc.lo;

     if( nb>=nc ) return;

     c[nb]=acc.hi;

     return;
    }

  MulAcc acc(a[0],b[0]);

  c[0]=acc.shift();

  for(ulen k=1; k<na ;k++)
    {
     if( k>=nc ) return;

     for(ulen i=0; i<=k ;i++) acc.mac(a[i],b[k-i]);

     c[k]=acc.shift();
    }

  for(ulen k=na; k<nb ;k++)
    {
     if( k>=nc ) return;

     for(ulen i=0; i<na ;i++) acc.mac(a[i],b[k-i]);

     c[k]=acc.shift();
    }

  for(ulen k=nb; k<na+nb-2 ;k++)
    {
     if( k>=nc ) return;

     for(ulen i=k-(nb-1); i<na ;i++) acc.mac(a[i],b[k-i]);

     c[k]=acc.shift();
    }

  if( na+nb-2>=nc ) return;

  acc.mac(a[na-1],b[nb-1]);

  c[na+nb-2]=acc.lo;

  if( na+nb-1>=nc ) return;

  c[na+nb-1]=acc.hi;
 }

template <UIntType UInt>
void IntegerSlowAlgo<UInt>::USq(Unit *restrict c,const Unit *a,ulen na)
 {
  if( na==0 ) return;

  if( na==1 )
    {
     MulAcc acc(a[0],a[0]);

     c[0]=acc.lo;
     c[1]=acc.hi;

     return;
    }

  MulAcc acc(a[0],a[0]);

  c[0]=acc.shift();

  for(ulen k=1; k<na ;k++)
    {
     for(ulen i=0; 2*i<k ;i++) acc.mac2(a[i],a[k-i]);

     if( (k%2)==0 ) acc.mac(a[k/2],a[k/2]);

     c[k]=acc.shift();
    }

  for(ulen k=na; k<2*na-2 ;k++)
    {
     for(ulen i=k-(na-1); 2*i<k ;i++) acc.mac2(a[i],a[k-i]);

     if( (k%2)==0 ) acc.mac(a[k/2],a[k/2]);

     c[k]=acc.shift();
    }

  acc.mac(a[na-1],a[na-1]);

  c[2*na-2]=acc.lo;
  c[2*na-1]=acc.hi;
 }

template <UIntType UInt>
void IntegerSlowAlgo<UInt>::Mul(Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb)
 {
  if( na==0 || nb==0 )
    {
     Null(c,na+nb);

     return;
    }

  UMul(c,a,na,b,nb);

  if( a[na-1]&MSBit )
    {
     USub(c+na,b,nb);
    }

  if( b[nb-1]&MSBit )
    {
     USub(c+nb,a,na);
    }
 }

template <UIntType UInt>
void IntegerSlowAlgo<UInt>::Sq(Unit *restrict c,const Unit *a,ulen na)
 {
  if( na==0 ) return;

  USq(c,a,na);

  if( a[na-1]&MSBit )
    {
     USub(c+na,a,na);
     USub(c+na,a,na);
    }
 }

 // data functions

template <UIntType UInt>
void IntegerSlowAlgo<UInt>::Null(Unit *a,ulen na)
 {
  Range(a,na).set_null();
 }

template <UIntType UInt>
void IntegerSlowAlgo<UInt>::Copy(Unit *restrict b,const Unit *a,ulen nab)
 {
  Range(b,nab).copy(a);
 }

template <UIntType UInt>
void IntegerSlowAlgo<UInt>::MoveUp(Unit *a,ulen na,ulen delta)
 {
  if( na==0 || delta==0 ) return;

  for(; na>0 ;na--) a[delta+na-1]=a[na-1];
 }

template <UIntType UInt>
void IntegerSlowAlgo<UInt>::MoveDown(Unit *a,ulen na,ulen delta)
 {
  if( na==0 || delta==0 ) return;

  for(ulen i=0; i<na ;i++) a[i]=a[delta+i];
 }

} // namespace Math
} // namespace CCore

#endif


