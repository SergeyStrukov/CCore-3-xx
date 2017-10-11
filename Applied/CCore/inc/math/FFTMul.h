/* FFTMul.h */
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

#ifndef CCore_inc_math_FFTMul_h
#define CCore_inc_math_FFTMul_h

#include <CCore/inc/Gadget.h>

namespace CCore {
namespace Math {

/* classes */

template <class Algo> struct FFTMul;

/* struct FFTMul<Algo> */

template <class Algo>
struct FFTMul
 {
  // types and consts

  using Unit = typename Algo::Unit ;

  static constexpr unsigned UnitBits = Algo::UnitBits ;

  static constexpr unsigned LogUnitBits = Algo::LogUnitBits ;

  static_assert( (1u<<LogUnitBits)==UnitBits ,"CCore::Math::FFTMul<Algo> : bad UnitBits OR LogUnitBits");

  // Unit functions

  static Unit Bit(unsigned s) { return Unit(1)<<s; }

  static Unit Mask(unsigned s) { return Bit(s)-1; }

  struct BitLen
   {
    ulen len;
    unsigned bits; // < UnitBits

    explicit BitLen(ulen len_,unsigned bits_=0) : len(len_),bits(bits_) {}

    bool operator + () const { return len || bits ; }

    bool operator > (BitLen obj) const
     {
      if( len>obj.len ) return true;

      if( len<obj.len ) return false;

      return bits>obj.bits;
     }

    BitLen operator - (BitLen obj) const
     {
      if( bits>=obj.bits )
        return BitLen(len-obj.len,bits-obj.bits);
      else
        return BitLen(len-obj.len-1,UnitBits+bits-obj.bits);
     }

    BitLen operator + (BitLen obj) const
     {
      ulen l=len+obj.len;
      unsigned b=bits+obj.bits;

      if( b<UnitBits )
        return BitLen(l,b);
      else
        return BitLen(l+1,b-UnitBits);
     }

    static BitLen OfBits(ulen blen)
     {
      return BitLen(blen/UnitBits,blen%UnitBits);
     }
   };

  struct BitPtr
   {
    const Unit *ptr;
    unsigned off; // < UnitBits

    explicit BitPtr(const Unit *ptr_,unsigned off_=0) : ptr(ptr_),off(off_) {}

    BitPtr operator + (BitLen delta) const
     {
      const Unit *p=ptr+delta.len;
      unsigned o=off+delta.bits;

      if( o<UnitBits )
        return BitPtr(p,o);
      else
        return BitPtr(p+1,o-UnitBits);
     }

    static Unit MaskBits(Unit a,unsigned bits)
     {
      return a&Mask(bits);
     }

    void fill(Unit *A,ulen T,BitLen blen) const
     {
      if( off )
        {
         blen=blen+BitLen(0,off);

         Algo::Copy(A,ptr,blen.len);

         if( blen.bits )
           {
            A[blen.len]=MaskBits(ptr[blen.len],blen.bits);

            Algo::URShift(A,blen.len+1,off);

            Algo::Null(A+blen.len+1,T-blen.len-1);
           }
         else
           {
            Algo::URShift(A,blen.len,off);

            Algo::Null(A+blen.len,T-blen.len);
           }
        }
      else
        {
         Algo::Copy(A,ptr,blen.len);

         if( blen.bits )
           {
            A[blen.len]=MaskBits(ptr[blen.len],blen.bits);

            Algo::Null(A+blen.len+1,T-blen.len-1);
           }
         else
           {
            Algo::Null(A+blen.len,T-blen.len);
           }
        }
     }
   };

  // private functions

   //
   // d >= 2
   // N = 2^d , N > UnitBits
   // K > 0
   // 2*K+d <= N
   //
   // T = ceil( (N+1)/UnitBits ) , T*UnitBits >= N+1
   //

  static constexpr ulen GetT(ulen N)
   {
    return N/UnitBits+1;
   }

  static Unit UAdd(Unit *restrict b,ulen nb,const Unit *a,ulen na) // nb>=na
   {
    Unit carry=Algo::UAdd(b,a,na);

    return Algo::UAddUnit(b+na,nb-na,carry);
   }

  static Unit USub(Unit *restrict b,ulen nb,const Unit *a,ulen na) // nb>=na
   {
    Unit borrow=Algo::USub(b,a,na);

    return Algo::USubUnit(b+na,nb-na,borrow);
   }


  static void Norm(ulen N,ulen T,Unit *A)
   {
#if 0

    if( unsigned s=unsigned( N%UnitBits ) )
      {
       Unit b=(A[T-1]>>s);

       A[T-1]&=Mask(s);

       if( Algo::USubUnit(A,T,b) ) SubC(N,T,A);
      }
    else

#endif
      {
       Unit b=A[T-1];

       A[T-1]=0;

       if( Algo::USubUnit(A,T,b) ) SubC(N,T,A);
      }
   }

  static void Mod(ulen N,ulen T,Unit *A,const Unit *P)
   {
#if 0

    if( unsigned s=unsigned( N%UnitBits ) )
      {
       // TODO
      }
    else

#endif
      {
       Algo::Copy(A,P,T-1);

       Unit c=UAdd(A,T-1,P+2*(T-1),2);
       Unit b=Algo::USub(A,P+(T-1),T-1);

       A[T-1]=c-b;

       if( c<b ) SubC(N,T,A);
      }
   }

  static void AddC(ulen N,ulen T,Unit *A)
   {
#if 0

    if( unsigned s=unsigned( N%UnitBits ) )
      {
       Unit b=(A[T-1]>>s)|Bit(UnitBits-s);

       A[T-1]&=Mask(s);

       if( Algo::USubUnit(A,T,b) ) SubC(N,T,A);
      }
    else

#endif
      {
       Unit b[2]={A[T-1],1};

       A[T-1]=0;

       if( USub(A,T,b,2) ) SubC(N,T,A);
      }
   }

  static void SubC(ulen N,ulen T,Unit *A)
   {
    Used(N);

#if 0

    if( unsigned s=unsigned( N%UnitBits ) )
      {
       Unit b=Bit(UnitBits-s)-(A[T-1]>>s);

       A[T-1]&=Mask(s);

       Algo::UAddUnit(A,T,b);
      }
    else

#endif
      {
       if( Unit u=A[T-1] )
         {
          A[T-1]=0;

          Algo::UAddUnit(A,T,UIntNeg<Unit>(u));
         }
       else
         {
          Algo::UAddUnit(A+1,T-1,1);
         }
      }
   }


  static void ModMul(ulen N,ulen T,Unit *A,const Unit *B,Unit *temp)
   {
    Unit *P=temp;
    Unit *t=P+2*T;

    Algo::UMul(P,A,B,T,t);

    Mod(N,T,A,P);
   }

  static void ModLShift(ulen N,ulen T,Unit *A,ulen s,Unit *temp) // s<N
   {
    if( s==0 ) return;

    Unit *P=temp;

    ulen delta=s/UnitBits;
    unsigned shift=unsigned( s%UnitBits );

    Algo::Null(P,delta);

    Unit *a=P+delta;

    Algo::Copy(a,A,T);

    if( shift )
      {
       a[T]=Algo::ULShift(a,T,shift);

       Algo::Null(a+T+1,T-delta-1);
      }
    else
      {
       Algo::Null(a+T,T-delta);
      }

    Mod(N,T,A,P);
   }

  static void ModRShift(ulen N,ulen T,Unit *A,ulen s,Unit *temp) // s<N
   {
    if( s==0 ) return;

    ModLShift(N,T,A,N-s,temp);
    ModNeg(N,T,A);
   }

  static void ModNeg(ulen N,ulen T,Unit *A)
   {
    if( Algo::UNeg(A,T) ) SubC(N,T,A);
   }

  static void ModAdd(ulen N,ulen T,Unit *A,const Unit *B)
   {
    if( Algo::UAdd(A,B,T) ) AddC(N,T,A);
   }

  static void ModSub(ulen N,ulen T,Unit *A,const Unit *B)
   {
    if( Algo::USub(A,B,T) ) SubC(N,T,A);
   }


  static void AddSubMul(ulen N,ulen T,Unit *A,Unit *B,ulen s,Unit *temp) // A <- (A-B)*(2^s) , B <- A+B , s<N
   {
    Algo::Copy(temp,B,T);

    ModAdd(N,T,B,A);
    ModSub(N,T,A,temp);

    ModLShift(N,T,A,s,temp);
   }

  static void InvAddSubMul(ulen N,ulen T,Unit *A,Unit *B,ulen s,Unit *temp)
   {
    ModRShift(N,T,A,s,temp);

    Algo::Copy(temp,B,T);

    ModSub(N,T,B,A);
    ModAdd(N,T,A,temp);
   }

  static void DivNorm(ulen N,ulen T,Unit *A,ulen s,Unit *temp) // s<N
   {
    ModRShift(N,T,A,s,temp);

    Norm(N,T,A);
   }

  static void DirectFFT(ulen N,ulen T,Unit *A,Unit *temp) // A half filled
   {
    Unit *Lim=A+2*N*T;
    ulen ds=1;

    ulen delta=N*T;

    Algo::Copy(A+delta,A,delta);

    {
     Unit *p=A+T;
     ulen s=1;

     for(Unit *lim=A+delta; p<lim ;p+=T,s++) ModLShift(N,T,p,s,temp);
    }

    for(delta/=2,ds*=2; delta>=T ;delta/=2,ds*=2)
      {
       for(Unit *p=A; p<Lim ;)
         {
          ulen s=0;

          for(Unit *lim=p+delta; p<lim ;p+=T,s+=ds) AddSubMul(N,T,p,p+delta,s,temp);

          p+=delta;
         }
      }
   }

  static void InverseFFT(ulen N,ulen T,Unit *A,Unit *temp)
   {
    Unit *Lim=A+2*N*T;
    ulen ds=N;

    for(ulen delta=T; ds ;delta*=2,ds/=2)
      {
       for(Unit *p=A; p<Lim ;)
         {
          ulen s=0;

          for(Unit *lim=p+delta; p<lim ;p+=T,s+=ds) InvAddSubMul(N,T,p,p+delta,s,temp);

          p+=delta;
         }
      }
   }

  static void Fill(ulen N,ulen K,ulen T,Unit *A,const Unit *a,ulen na)
   {
    BitPtr ptr(a);
    BitLen delta=BitLen::OfBits(K);
    BitLen len(na);

    ulen L=N*T;

    while( +len )
      {
       if( len>delta )
         {
          ptr.fill(A,T,delta);

          A+=T;
          L-=T;

          ptr=ptr+delta;
          len=len-delta;
         }
       else
         {
          ptr.fill(A,T,len);

          A+=T;
          L-=T;

          break;
         }
      }

    Algo::Null(A,L);
   }

  static void Sum(Unit *c,ulen nc,Unit *C,ulen T,BitLen off)
   {
    if( nc<=off.len ) return;

    c+=off.len;
    nc-=off.len;

    Unit u;

    if( off.bits )
      u=Algo::ULShift(C,T,off.bits);
    else
      u=0;

    if( nc<=T )
      {
       Algo::UAdd(c,C,nc);
      }
    else
      {
       u+=Algo::UAdd(c,C,T);

       Algo::UAddUnit(c+T,nc-T,u);
      }
   }

  static void Sum(ulen N,ulen K,ulen T,Unit *c,ulen nc,Unit *C)
   {
    Algo::Null(c,nc);

    Unit *Lim=C+T*(2*N-1);

    ulen T1=T;

    if( (N%UnitBits)==0 ) T1--;

    BitLen off(0);
    BitLen delta=BitLen::OfBits(K);

    for(; C<Lim ;C+=T)
      {
       Sum(c,nc,C,T1,off);

       off=off+delta;
      }
   }

  // private mul functions

  static ulen InternalUMulTempLen(ulen N)
   {
    ulen T=GetT(N);

    return LenOf( 2*T, 2*N+1 , Algo::UMulTempLen(T) );
   }

   //
   // nab*UnitBits <= K*N
   //

  static void InternalUMul(unsigned d,ulen N,ulen K,
                           Unit *c,const Unit *a,const Unit *b,ulen nab,Unit *temp) // nc==2*nab
   {
    ulen T=GetT(N);
    ulen L=2*N*T;

    Unit *A=temp;
    Unit *B=A+L;
    Unit *t=B+L;

    Fill(N,K,T,A,a,nab);
    Fill(N,K,T,B,b,nab);

    DirectFFT(N,T,A,t);
    DirectFFT(N,T,B,t);

    for(ulen off=0; off<L ;off+=T) ModMul(N,T,A+off,B+off,t);

    InverseFFT(N,T,A,t);

    for(ulen off=0; off<L ;off+=T) DivNorm(N,T,A+off,d+1,t);

    Sum(N,K,T,c,2*nab,A);
   }


  // mul functions

  static unsigned FindD(ulen nab)
   {
    unsigned k=Max(LogUnitBits,UIntBitsOf(nab));
    unsigned d0=(k+LogUnitBits)/2+1;

    for(unsigned d=d0;;d++)
      {
       ulen N=ulen(1)<<d;
       ulen K=(N-d)/2;

       unsigned s=d-LogUnitBits;
       ulen m=(ulen(1)<<s)-1;

       if( K >= ( nab>>s )+( (nab&m)!=0 ) ) return d;
      }

    // d+1 < Meta::UIntBits<ulen>
   }

  static ulen UMulTempLen(ulen nab)
   {
    unsigned d=FindD(nab);
    ulen N=ulen(1)<<d;

    return InternalUMulTempLen(N);
   }

  static void UMul(Unit *c,const Unit *a,const Unit *b,ulen nab,Unit *temp) // nc==2*nab
   {
    unsigned d=FindD(nab);
    ulen N=ulen(1)<<d;
    ulen K=(N-d)/2;

    InternalUMul(d,N,K,c,a,b,nab,temp);
   }
 };

} // namespace Math
} // namespace CCore

#endif

