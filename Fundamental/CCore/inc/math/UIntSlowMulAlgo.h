/* UIntSlowMulAlgo.h */
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

#ifndef CCore_inc_math_UIntSlowMulAlgo_h
#define CCore_inc_math_UIntSlowMulAlgo_h

#include <CCore/inc/Gadget.h>

namespace CCore {
namespace Math {

/* classes */

template <UIntType UInt> struct UIntSlowMulAlgo;

template <UIntType UInt> struct UIntSlowMulFunc;

/* struct UIntSlowMulAlgo<UInt> */

template <UIntType UInt>
struct UIntSlowMulAlgo
 {
  static constexpr unsigned Bits = Meta::UIntBits<UInt> ;

  static constexpr UInt MaxVal = MaxUInt<UInt> ;

  struct DoubleUMul
   {
    UInt hi;
    UInt lo;

    DoubleUMul(UInt a,UInt b);
   };

  static UInt Inv(UInt den);

  static UInt LShift(UInt hi,UInt lo,unsigned shift);

  static UInt DoubleUDiv(UInt hi,UInt lo,UInt den); // hi<den
 };

template <UIntType UInt>
UIntSlowMulAlgo<UInt>::DoubleUMul::DoubleUMul(UInt a,UInt b)
 {
  static_assert( (Bits%2)==0 ,"CCore::Math::UIntSlowMulAlgo<UInt> : odd bits number");

  const unsigned Bits2 = Bits/2 ;

  const UInt LoMask=UInt(MaxVal>>Bits2);

  UInt a1=UInt( a>>Bits2 );
  UInt a0=UInt( a&LoMask );

  UInt b1=UInt( b>>Bits2 );
  UInt b0=UInt( b&LoMask );

  UInt p0=a0*b0;
  UInt p1=a0*b1;
  UInt p2=a1*b0;
  UInt p3=a1*b1;

  p1+=p2;

  p3+=UInt( UInt(p1<p2)<<Bits2 );

  UInt p1hi=UInt( p1<<Bits2 );

  p0+=p1hi;
  p3+=UInt( p1>>Bits2 );

  p3+=UInt( p0<p1hi );

  hi=p3;
  lo=p0;
 }

template <UIntType UInt>
UInt UIntSlowMulAlgo<UInt>::Inv(UInt den)
 {
  static_assert( (Bits%2)==0 ,"CCore::Math::UIntSlowMulAlgo<UInt,E> : odd bits number");

  const unsigned Bits2 = Bits/2 ;

  const UInt MSBit = UInt(1)<<(Bits-1) ;

  const UInt M2 = UInt(1)<<Bits2 ;

  if( den<=MSBit ) return 0;

  UInt a;
  UInt d;

  // 1
  {
   UInt b = (den>>Bits2) + 1 ;

   a = 1 + UInt(-b)/b ;

   DoubleUMul p(a,den);

   if( p.lo )
     {
      p.lo=-p.lo;
      p.hi=M2-1-p.hi;
     }
   else
     {
      p.hi=M2-p.hi;
     }

   while( p.hi || p.lo>=den )
     {
      a++;

      p.hi-=(p.lo<den);
      p.lo-=den;
     }

   d=p.lo;
  }

  // 2
  {
   UInt e = (a<<Bits2) + DoubleUMul(a,d).hi ;

   DoubleUMul p(e,den);

   p.hi+=den;

   if( p.lo )
     {
      p.lo=-p.lo;
      p.hi=~p.hi;
     }
   else
     {
      p.hi=-p.hi;
     }

   return e + ( p.hi || p.lo>=den ) ;
  }
 }

template <UIntType UInt>
UInt UIntSlowMulAlgo<UInt>::LShift(UInt hi,UInt lo,unsigned shift)
 {
  return UInt( (hi<<shift)|(lo>>(Bits-shift)) );
 }

template <UIntType UInt>
UInt UIntSlowMulAlgo<UInt>::DoubleUDiv(UInt hi,UInt lo,UInt den)
 {
  // 1
  {
   if( unsigned n=UIntFunc<UInt>::CountZeroMSB(den) )
     {
      den<<=n;
      hi=LShift(hi,lo,n);
      lo<<=n;
     }
  }

  // 2
  {
   if( UInt e=Inv(den) )
     {
      UInt ret=hi+DoubleUMul(hi,e).hi;

      DoubleUMul p(ret,den);

      bool c=(lo<p.lo);

      lo-=p.lo;
      hi-=p.hi+c;

      for(;;)
        {
         bool c=(lo<den);

         if( hi<c ) return ret;

         lo-=den;
         hi-=c;

         ret++;
        }
     }
   else
     {
      return LShift(hi,lo,1);
     }
  }
 }

/* struct UIntSlowMulFunc<UInt> */

template <UIntType UInt>
struct UIntSlowMulFunc
 {
  using Algo = UIntSlowMulAlgo<UInt> ;

  using Mul = typename Algo::DoubleUMul ;

  static UInt Div(UInt hi,UInt lo,UInt den)
   {
    return Algo::DoubleUDiv(hi,lo,den);
   }

  static UInt Mod(UInt hi,UInt lo,UInt den)
   {
    UInt div=Div(hi,lo,den);

    return lo-UInt(div*den);
   }

  static UInt MulDiv(UInt a,UInt b,UInt den)
   {
    Mul mul(a,b);

    return Div(mul.hi,mul.lo,den);
   }

  struct DivMod
   {
    UInt div;
    UInt mod;

    DivMod(UInt hi,UInt lo,UInt den)
     {
      div=Div(hi,lo,den);
      mod=lo-UInt(div*den);
     }
   };

  static UInt ModMul(UInt a,UInt b,UInt mod)
   {
    Mul mul(a,b);

    return Mod(mul.hi,mul.lo,mod);
   }

  static UInt ModMac(UInt s,UInt a,UInt b,UInt mod)
   {
    Mul mul(a,b);

    mul.hi+=UIntAdd(mul.lo,s);

    return Mod(mul.hi,mul.lo,mod);
   }
 };

} // namespace Math
} // namespace CCore

#endif


