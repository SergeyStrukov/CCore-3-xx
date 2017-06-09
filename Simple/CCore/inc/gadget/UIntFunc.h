/* UIntFunc.h */
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

#ifndef CCore_inc_gadget_UIntFunc_h
#define CCore_inc_gadget_UIntFunc_h

#include <CCore/inc/gadget/Classification.h>
#include <CCore/inc/gadget/NoCopy.h>

#include <CCore/inc/base/Quick.h>

namespace CCore {

/* const MaxUInt<UInt> */

template <UIntType UInt>
inline constexpr UInt MaxUInt = UInt(-1) ;

/* functions */

inline constexpr unsigned Bit(unsigned num) { return 1u<<num; }

template <UIntType UInt>
constexpr UInt UIntBit(unsigned num) { return UInt(1)<<num; }

/* classes */

template <UIntType UInt,UIntType ExtUInt = Quick::UIntMulSelect< Meta::UIntBits<UInt> > > struct UIntMulFunc;

template <UIntType UInt> struct UIntBitFunc_gen;

template <UIntType UInt> struct UIntBitFunc;

template <UIntType UInt> struct UIntFunc;

template <UIntType UInt> class BitScanner;

/* struct UIntMulFunc<UInt,ExtUInt> */

template <UIntType UInt,UIntType ExtUInt> requires ( 2*Meta::UIntBits<UInt> <= Meta::UIntBits<ExtUInt> )
struct UIntMulFunc<UInt,ExtUInt>
 {
  static constexpr unsigned Bits = Meta::UIntBits<UInt> ;

  static ExtUInt Combine(UInt hi,UInt lo)
   {
    return (ExtUInt(hi)<<Bits)|lo;
   }

  struct Mul
   {
    UInt hi;
    UInt lo;

    Mul(UInt a,UInt b)
     {
      ExtUInt p=(ExtUInt)a*b;

      lo=UInt(p);
      hi=UInt(p>>Bits);
     }
   };

  static UInt Div(UInt hi,UInt lo,UInt den)
   {
    return UInt(Combine(hi,lo)/den);
   }

  static UInt Mod(UInt hi,UInt lo,UInt den)
   {
    return UInt(Combine(hi,lo)%den);
   }

  static UInt MulDiv(UInt a,UInt b,UInt den)
   {
    ExtUInt p=(ExtUInt)a*b;

    return UInt(p/den);
   }

  struct DivMod
   {
    UInt div;
    UInt mod;

    DivMod(UInt hi,UInt lo,UInt den)
     {
      ExtUInt p=Combine(hi,lo);

      div=UInt(p/den);
      mod=UInt(p%den);
     }
   };

  static UInt ModMul(UInt a,UInt b,UInt mod)
   {
    ExtUInt p=(ExtUInt)a*b;

    return UInt(p%mod);
   }

  static UInt ModMac(UInt s,UInt a,UInt b,UInt mod)
   {
    ExtUInt p=(ExtUInt)a*b+s;

    return UInt(p%mod);
   }
 };

template <UIntType UInt,UIntType ExtUInt> requires ( Meta::UIntBits<UInt> == Meta::UIntBits<ExtUInt> )
struct UIntMulFunc<UInt,ExtUInt>
 {
  using Algo = Quick::UIntMulFunc<ExtUInt> ;

  struct Mul
   {
    UInt hi;
    UInt lo;

    Mul(UInt a,UInt b)
     {
      typename Algo::Mul res(a,b);

      hi=res.hi;
      lo=res.lo;
     }
   };

  static UInt Div(UInt hi,UInt lo,UInt den)
   {
    return Algo::Div(hi,lo,den);
   }

  static UInt Mod(UInt hi,UInt lo,UInt den)
   {
    return Algo::Mod(hi,lo,den);
   }

  static UInt MulDiv(UInt a,UInt b,UInt den)
   {
    return Algo::MulDiv(a,b,den);
   }

  struct DivMod
   {
    UInt div;
    UInt mod;

    DivMod(UInt hi,UInt lo,UInt den)
     {
      typename Algo::DivMod res(hi,lo,den);

      div=res.div;
      mod=res.mod;
     }
   };

  static UInt ModMul(UInt a,UInt b,UInt mod)
   {
    return Algo::ModMul(a,b,mod);
   }

  static UInt ModMac(UInt s,UInt a,UInt b,UInt mod)
   {
    return Algo::ModMac(s,a,b,mod);
   }
 };

/* struct UIntBitFunc_gen<UInt> */

template <UIntType UInt>
struct UIntBitFunc_gen
 {
  static constexpr unsigned Bits = Meta::UIntBits<UInt> ;

  static constexpr UInt MaxUnsigned = MaxUInt<UInt> ;

  static constexpr UInt MSBit = MaxUnsigned^(MaxUnsigned>>1) ;

  static constexpr unsigned ScanBits = Meta::UIntBits<Quick::ScanUInt> ;

  static unsigned CountZeroMSB(UInt a)
   {
    if( !a ) return Bits;

    if( a&MSBit ) return 0;

    unsigned ret=0;
    unsigned n=Bits;

    while( n>ScanBits )
      {
       unsigned m=n/2;

       UInt mask=MaxUnsigned<<(Bits-m);

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

    unsigned msbit=Quick::ScanMSBit(Quick::ScanUInt( a>>(Bits-n) ));

    return ret+(n-1-msbit);
   }

  static unsigned CountZeroLSB(UInt a)
   {
    if( !a ) return Bits;

    if( a&UInt(1) ) return 0;

    unsigned ret=0;
    unsigned n=Bits;

    while( n>ScanBits )
      {
       unsigned m=n/2;

       UInt mask=(UInt(1)<<m)-1;

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

    unsigned lsbit=Quick::ScanLSBit(Quick::ScanUInt(a));

    return ret+lsbit;
   }

  static unsigned BitsOf(UInt a) { return Bits-CountZeroMSB(a); }
 };

/* struct UIntBitFunc<UInt> */

template <UIntType UInt> requires ( MaxUInt<UInt> > MaxUInt<Quick::ScanUInt> )
struct UIntBitFunc<UInt> : UIntBitFunc_gen<UInt> {};

template <UIntType UInt> requires ( MaxUInt<UInt> <= MaxUInt<Quick::ScanUInt> )
struct UIntBitFunc<UInt>
 {
  static constexpr unsigned Bits = Meta::UIntBits<UInt> ;

  static unsigned CountZeroMSB(UInt a)
   {
    if( !a ) return Bits;

    return Bits-1-Quick::ScanMSBit(a);
   }

  static unsigned CountZeroLSB(UInt a)
   {
    if( !a ) return Bits;

    return Quick::ScanLSBit(a);
   }

  static unsigned BitsOf(UInt a)
   {
    if( !a ) return 0;

    return Quick::ScanMSBit(a)+1;
   }
 };

/* struct UIntFunc<UInt> */

template <UIntType UInt>
struct UIntFunc : UIntMulFunc<UInt> , UIntBitFunc<UInt>
 {
  // consts

  static constexpr unsigned Bits = Meta::UIntBits<UInt> ;

  static constexpr UInt MaxUnsigned = MaxUInt<UInt> ;

  static constexpr UInt MSBit = MaxUnsigned^(MaxUnsigned>>1) ;

  static constexpr UInt MaxPositive = MaxUnsigned>>1 ;

  static constexpr UInt MinNegative = MSBit ;

  // sign

  static UInt Neg(UInt value) { return UInt(-value); }

  static bool IsNegative(UInt value) { return value&MSBit; }

  static bool NotNegative(UInt value) { return !(value&MSBit); }

  static bool IsPositive(UInt value) { return UInt(value-1)<=(MaxPositive-1); }

  static bool NotPositive(UInt value) { return UInt(value-1)>(MaxPositive-1); }

  // additive

  struct Add
   {
    UInt result;
    bool carry;

    Add(UInt a,UInt b)
     {
      result=a+b;
      carry=(result<a);
     }
   };

  struct Sub
   {
    UInt result;
    bool borrow;

    Sub(UInt a,UInt b)
     {
      result=a-b;
      borrow=(a<b);
     }
   };

  struct Inc
   {
    UInt result;
    bool carry;

    explicit Inc(UInt a)
     {
      result=a+1;
      carry=(result==0);
     }
   };

  struct Dec
   {
    UInt result;
    bool borrow;

    explicit Dec(UInt a)
     {
      result=a-1;
      borrow=(a==0);
     }
   };

  // square root

  static UInt SqRoot(UInt S,UInt x) // S,x > 0
   {
    {
     UInt y=S/x;

     if( y<x )
       {
        x=y+(x-y)/2;
       }
     else
       {
        x=x+(y-x)/2;
       }
    }

    for(;;)
      {
       UInt y=S/x;

       if( y<x )
         {
          x=y+(x-y)/2;
         }
       else
         {
          if( y==x ) return x;

          if( y==x+1 && S==x*y ) return x;

          return x+1;
         }
      }
   }

  static UInt SqRoot(UInt S)
   {
    if( !S ) return 0;

    unsigned bits=UIntFunc<UInt>::BitsOf(S);

    UInt x=UInt(1)<<((bits+1)/2);

    return SqRoot(S,x);
   }
 };

/* class BitScanner<UInt> */

template <UIntType UInt>
class BitScanner : NoCopy
 {
   UInt d;
   UInt mask;

  public:

   explicit BitScanner(UInt d_)
    : d(d_),
      mask(UIntFunc<UInt>::MSBit)
    {
     if( d_ )
       {
        mask >>= UIntFunc<UInt>::CountZeroMSB(d_) ;
       }
     else
       {
        mask=0;
       }
    }

   UInt operator + () const { return mask; }

   UInt operator * () const { return d&mask; }

   void operator ++ () { mask>>=1; }
 };

/* functions */

template <UIntType UInt>
UInt UIntNeg(UInt a)
 {
  return UIntFunc<UInt>::Neg(a);
 }

template <UIntType UInt>
unsigned UIntBitsOf(UInt a)
 {
  return UIntFunc<UInt>::BitsOf(a);
 }

template <UIntType UInt>
bool UIntAdd(UInt &a,UInt b)
 {
  typename UIntFunc<UInt>::Add add(a,b);

  a=add.result;

  return add.carry;
 }

template <UIntType UInt>
bool UIntSub(UInt &a,UInt b)
 {
  typename UIntFunc<UInt>::Sub sub(a,b);

  a=sub.result;

  return sub.borrow;
 }

template <UIntType UInt>
bool UIntInc(UInt &a)
 {
  typename UIntFunc<UInt>::Inc inc(a);

  a=inc.result;

  return inc.carry;
 }

template <UIntType UInt>
bool UIntDec(UInt &a)
 {
  typename UIntFunc<UInt>::Dec dec(a);

  a=dec.result;

  return dec.borrow;
 }

template <UIntType UInt>
UInt UIntMulDiv(UInt a,UInt b,UInt den)
 {
  return UIntFunc<UInt>::MulDiv(a,b,den);
 }

template <UIntType UInt>
UInt UIntDiv(UInt hi,UInt lo,UInt den)
 {
  return UIntFunc<UInt>::Div(hi,lo,den);
 }

template <UIntType UInt>
UInt UIntMod(UInt hi,UInt lo,UInt den)
 {
  return UIntFunc<UInt>::Mod(hi,lo,den);
 }

template <UIntType UInt>
UInt UIntModMul(UInt a,UInt b,UInt mod)
 {
  return UIntFunc<UInt>::ModMul(a,b,mod);
 }

template <UIntType UInt>
UInt UIntModMac(UInt s,UInt a,UInt b,UInt mod)
 {
  return UIntFunc<UInt>::ModMac(s,a,b,mod);
 }

template <UIntType UInt>
UInt UIntSqRoot(UInt S)
 {
  return UIntFunc<UInt>::SqRoot(S);
 }

} // namespace CCore

#endif


