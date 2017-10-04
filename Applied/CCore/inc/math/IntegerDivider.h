/* IntegerDivider.h */
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

#ifndef CCore_inc_math_IntegerDivider_h
#define CCore_inc_math_IntegerDivider_h

#include <CCore/inc/math/IntegerBuilder.h>

#include <CCore/inc/Array.h>

namespace CCore {
namespace Math {

/* guards */

void GuardIntegerInverseNotNormalized();

void GuardIntegerInverseOverflow();

void GuardIntegerZeroDivide();

/* classes */

template <IntAlgo Algo,class TempArray> class IntegerInverse;

template <IntAlgo Algo,class TempArray> class IntegerDivider;

/* class IntegerInverse<Algo,TempArray> */

template <IntAlgo Algo,class TempArray>
class IntegerInverse : NoCopy
 {
   using Unit = typename Algo::Unit ;

   TempArray buf;

  private:

   static Unit Start(Unit a)
    {
     if( a==Algo::MaxUnit ) return 0;

     return Algo::DoubleUDiv(Algo::MaxUnit-a,0,a+1);
    }

  public:

   IntegerInverse(const Unit *a,ulen na,ulen K);

   // range access

   const Unit * getPtr() const { return buf.getPtr(); }

   const Unit * getPtr_const() const { return buf.getPtr(); }

   ulen getLen() const { return buf.getLen(); }
 };

template <IntAlgo Algo,class TempArray>
IntegerInverse<Algo,TempArray>::IntegerInverse(const Unit *a,ulen na,ulen K)
 {
  if( na==0 ) GuardIntegerInverseNotNormalized();

  Unit msa=a[na-1];

  if( (msa&Algo::MSBit)==0 ) GuardIntegerInverseNotNormalized();

  if( msa==Algo::MSBit && Algo::USign(a,na-1)==0 )
    {
     buf.extend_default(K);
     buf.append_copy(2);

     return;
    }

  if( K==0 )
    {
     buf.append_copy(1);

     return;
    }

  if( na>=MaxULen/2 || K>=MaxULen/2-na ) GuardIntegerInverseOverflow();

  ulen buf_len = 2*(K+na+1) ; // (K+1)+na+(na+K+1);

  Unit *X=buf.extend_raw(buf_len).ptr;
  ulen k=1;

  Unit *x=X+(K-k);
  Unit *d=X+K+1;
  Unit *P=d+na;

  // 1 x<- d<-

  {
   x[1]=1;

   x[0]=Start(msa);

   Algo::UMul(d,x,2,a,na);

   Algo::UNeg(d,na+1);

   while( Algo::UCmp(d,na+1,a,na)>=0 )
     {
      x[0]++;

      d[na]-=Algo::USub(d,a,na);
     }
  }

  // 2

  while( 2*k<=K )
    {
     Unit *y=x-k;

     Algo::UMul(P,x,k+1,d,na);

     Algo::Copy(y,P+na,k);

     Algo::UMulLo(P,na+1,a,na,y,k);

     Algo::UNeg(P,na+1);

     if( k<=na )
       {
        Algo::UAdd(P+k,d,na+1-k);
       }

     if( P[na] || Algo::UCmp(P,a,na)>=0 )
       {
        Algo::UAddUnit(y,2*k+1,1);
        Algo::USub(P,a,na);
       }

     Algo::Copy(d,P,na);

     k*=2;
     x=y;
    }

  // 3

  if( k<K )
    {
     ulen l=K-k; // l<k

     Algo::UMul(P,x,k+1,d,na);

     Algo::Copy(X,P+na+(k-l),l);

     Algo::UMulLo(P,na+1,a,na,X,l);

     Algo::UNeg(P,na+1);

     if( l<=na )
       {
        Algo::UAdd(P+l,d,na+1-l);
       }

     if( P[na] || Algo::UCmp(P,a,na)>=0 )
       {
        Algo::UAddUnit(X,K+1,1);
       }
    }

  // 4

  buf.shrink(buf_len-K-1);
 }

/* class IntegerDivider<Algo,TempArray> */

template <IntAlgo Algo,class TempArray>
class IntegerDivider : NoCopy
 {
   using Unit = typename Algo::Unit ;

   struct Normalize;

   TempArray buf;
   Unit minus_one;
   PtrLen<const Unit> result;
   TempArray mod_buf;
   PtrLen<const Unit> mod;

  public:

   explicit IntegerDivider(PtrLen<const Unit> a,PtrLen<const Unit> b,bool do_mod=false);

   PtrLen<const Unit> getResult() const { return result; } // [a/b]

   PtrLen<const Unit> getMod() const { return mod; }
 };

template <IntAlgo Algo,class TempArray>
struct IntegerDivider<Algo,TempArray>::Normalize
 {
  PtrLen<Unit> result_a;
  PtrLen<Unit> result_b;
  unsigned shift;
  bool neg;

  void doB(const Unit *b,ulen nb,Unit *c) // [nb+1]
   {
    Algo::Copy(c,b,nb);

    switch( Algo::Sign(c,nb) )
     {
      case CmpEqual : GuardIntegerZeroDivide(); [[fallthrough]];

      case CmpLess :
       {
        neg=true;

        Algo::UNeg(c,nb);
       }
      break;

      default: // case CmpGreater :
       {
        neg=false;
       }
     }

    nb=Algo::UNormalize(c,nb);

    shift=Algo::CountZeroMSB(c[nb-1]);

    if( shift ) Algo::ULShift(c,nb,shift);

    c[nb]=0;

    result_b=Range(c,nb+1);
   }

  void doA(const Unit *a,ulen na,Unit *d) // [na+1]
   {
    if( shift )
      {
       d[na]=Algo::LShift(d,a,na,shift);
      }
    else
      {
       Algo::Copy(d,a,na);

       d[na]=Algo::SignExt(d,na);
      }

    if( neg ) Algo::UNeg(d,na+1); // 2 msb of d the same

    result_a=Range(d,na+1);
   }

  Normalize(PtrLen<const Unit> a,PtrLen<const Unit> b,Unit *temp) // [a.len+b.len+2]
   {
    doB(b.ptr,b.len,temp);
    doA(a.ptr,a.len,temp+b.len+1);
   };
 };

template <IntAlgo Algo,class TempArray>
IntegerDivider<Algo,TempArray>::IntegerDivider(PtrLen<const Unit> a,PtrLen<const Unit> b,bool do_mod)
 {
  ulen len=AddLen(a.len,b.len,2);

  TempArray temp(DoRaw{len});

  Normalize norm(a,b,temp.getPtr());

  ulen nb=norm.result_b.len-1;
  ulen na=norm.result_a.len;

  if( na<=nb )
    {
     if( Algo::Sign(norm.result_a.ptr,na)<0 )
       {
        minus_one=MaxUInt<Unit>;

        result.ptr=&minus_one;
        result.len=1;

        if( do_mod ) // mod = a+b
          {
           mod_buf.extend(IntegerAddBuilder<Algo>(a,b));

           ulen nlen=Algo::Normalize(mod_buf.getPtr(),mod_buf.getLen());

           mod=Range_const(mod_buf.getPtr(),nlen);
          }
       }
     else
       {
        // result == 0

        if( do_mod ) // mod = a
          {
           ulen nlen=Algo::Normalize(a.ptr,a.len);

           mod_buf.extend_copy(nlen,a.ptr);

           mod=Range_const(mod_buf);
          }
       }
    }
  else
    {
     IntegerInverse<Algo,TempArray> c(norm.result_b.ptr,nb,na-nb); // c = [ (M^na)/norm_b ]

     TempArray ac(DoBuild,IntegerMulBuilder<Algo>(Range_const(norm.result_a),Range_const(c)));

     PtrLen<Unit> p(ac.getPtr()+na,ac.getLen()-na); // p = [ (norm_a*c)/(M^na) ]

     if( Algo::Sign(norm.result_a.ptr,na)>=0 )
       {
        Algo::UAddUnit(p.ptr,p.len,1);
       }

     TempArray bp(DoBuild,IntegerMulBuilder<Algo>(Range_const(norm.result_b),Range_const(p)));

     if( Algo::Cmp(bp.getPtr(),bp.getLen(),norm.result_a.ptr,na)>0 )
       {
        Algo::USubUnit(p.ptr,p.len,1);

        if( do_mod )
          {
           Algo::Sub(bp.getPtr(),bp.getLen(),norm.result_b.ptr,norm.result_b.len);
          }
       }

     ulen np=Algo::Normalize(p.ptr,p.len);

     result=Range_const(p.ptr,np);

     Swap(buf,ac);

     if( do_mod )
       {
        Algo::USub(norm.result_a.ptr,bp.getPtr(),norm.result_b.len);

        if( norm.shift ) Algo::URShift(norm.result_a.ptr,norm.result_b.len,norm.shift);

        if( norm.neg ) Algo::UNeg(norm.result_a.ptr,norm.result_b.len);

        ulen nlen=Algo::Normalize(norm.result_a.ptr,norm.result_b.len);

        mod=Range_const(norm.result_a.ptr,nlen);

        Swap(mod_buf,temp);
       }
    }
 }

} // namespace Math
} // namespace CCore

#endif

