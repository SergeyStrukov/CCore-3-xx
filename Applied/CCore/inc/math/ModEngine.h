/* ModEngine.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: Applied
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_math_ModEngine_h
#define CCore_inc_math_ModEngine_h

#include <CCore/inc/math/Integer.h>

namespace CCore {
namespace Math {

/* classes */

template <class Integer> class IntegerBitScanner;

template <class Integer> class UnitsPowInteger;

template <class Integer> class ModEngine;

/* class IntegerBitScanner<Integer> */

template <class Integer>
class IntegerBitScanner : NoCopy
 {
   using Unit = typename Integer::Unit ;

   Integer d;

   PtrLenReverse<const Unit> body;
   Unit mask;

  public:

   explicit IntegerBitScanner(const Integer &d_) // d_ >= 0
    : d(d_)
    {
     body=d.getBodyReverse();

     if( +body )
       {
        mask=UIntFunc<Unit>::MSBit;

        if( Unit msu=*body )
          {
           mask >>= UIntFunc<Unit>::CountZeroMSB(msu) ;
          }
        else
          {
           ++body;
          }
       }
     else
       {
        mask=0;
       }
    }

   ~IntegerBitScanner() {}

   Unit operator + () const { return mask; }

   Unit operator * () const { return (*body)&mask; }

   void operator ++ ()
    {
     mask>>=1;

     if( !mask )
       {
        ++body;

        if( +body ) mask=UIntFunc<Unit>::MSBit;
       }
    }
 };

/* class UnitsPowInteger<Integer> */

template <class Integer>
class UnitsPowInteger : public Integer
 {
   class Builder
    {
      ulen n;

     public:

      explicit Builder(ulen n_) : n(n_) {}

      ulen getLen() const { return LenAdd(n,1); }

      using Unit = typename Integer::Unit ;

      PtrLen<Unit> operator () (Place<void> place) const
       {
        Unit *base=place;

        Integer::AlgoType::Null(base,n);

        base[n]=1;

        return Range(base,n+1);
       }
    };

  public:

   explicit UnitsPowInteger(ulen n) // creates B^n , B = 2^UnitBits
    : Integer(DoBuild,Builder(n))
    {
    }

   ~UnitsPowInteger() {}
 };

/* class ModEngine<Integer> */

template <class Integer>
class ModEngine : NoCopy
 {
   Integer M;
   Integer A;
   ulen n;

  public:

   explicit ModEngine(const Integer &M_) // M_ > 0
    : M(M_)
    {
     n=M.getBody().len;

     n=LenAdd(n,n);

     A=UnitsPowInteger<Integer>(n)/M;
    }

   ~ModEngine() {}

   const Integer & getModule() const { return M; }

   Integer prepare(const Integer &a) const { return a%M; } // a >= 0

   Integer mod(Integer a) const // a >= 0 , a < M^2
    {
     Integer b=a*A;

     auto body=b.getBody();

     if( body.len>n )
       {
        body+=n;

        a-=Integer::Mul(M.getBody(),body);
       }

     if( a>=M ) a-=M;

     return a;
    }

   Integer mul(const Integer &a,const Integer &b) const { return mod(a*b); } // a,b >= 0 , a,b < M

   Integer sq(const Integer &a) const { return mod(a.sq()); } // a >= 0 , a < M

   Integer mac(const Integer &s,const Integer &a,const Integer &b) const { return mod(s+a*b); } // s,a,b >= 0 , s,a,b < M

   Integer squac(const Integer &s,const Integer &a) const { return mod(s+a.sq()); } // s,a >= 0 , s,a < M

   template <class Scanner>
   Integer pow_scanner(const Integer &a,Scanner &scanner) const
    {
     if( +scanner )
       {
        Integer ret=a;

        for(++scanner; +scanner ;++scanner)
          {
           ret=sq(ret);

           if( *scanner ) ret=mul(ret,a);
          }

        return ret;
       }

     return 1u;
    }

   template <UIntType UInt>
   Integer pow(const Integer &a,UInt d) const // a >=0 , a < M , M > 1
    {
     BitScanner<UInt> scanner(d);

     return pow_scanner(a,scanner);
    }

   Integer pow(const Integer &a,const Integer &d) const // a,d >=0 , a < M , M > 1
    {
     IntegerBitScanner<Integer> scanner(d);

     return pow_scanner(a,scanner);
    }
 };

} // namespace Math
} // namespace CCore

#endif


