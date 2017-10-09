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

   //
   // d >= 2
   // N = 2^d
   // K > 0
   // 2*K+d <= N
   //

  // private functions

   //
   // T = ceil( (N+1)/UnitBits )
   //

  static ulen GetT(ulen N)
   {
    return N/UnitBits+1;
   }

  static void Norm(ulen N,ulen T,Unit *A) // TODO
   {
   }

  static void AddC(ulen N,ulen T,Unit *A) // TODO
   {
   }

  static void SubC(ulen N,ulen T,Unit *A) // TODO
   {
   }

  static void ModMul(ulen N,ulen T,Unit *A,const Unit *B,Unit *temp) // TODO
   {
   }

  static void ModLShift(ulen N,ulen T,Unit *A,ulen s,Unit *temp) // s<N // TODO
   {
    if( s==0 ) return;


   }

  static void ModRShift(ulen N,ulen T,Unit *A,ulen s,Unit *temp) // s<N // TODO
   {
    if( s==0 ) return;


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

  static void DirectFFT(unsigned d,ulen N,ulen T,Unit *A,Unit *temp) // A half filled
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

    for(delta/=2,ds*=2; delta>=T ;)
      {
       for(Unit *p=A; p<Lim ;)
         {
          ulen s=0;

          for(Unit *lim=p+delta; p<lim ;p+=T,s+=ds) AddSubMul(N,T,p,p+delta,s,temp);

          p+=delta;
         }
      }
   }

  static void InverseFFT(unsigned d,ulen N,ulen T,Unit *A,Unit *temp)
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

  static void Fill(unsigned d,ulen N,ulen K,ulen T,Unit *A,const Unit *a,ulen na) // TODO
   {
   }

  static void Sum(unsigned d,ulen N,ulen K,ulen T,Unit *c,ulen nc,const Unit *C) // TODO
   {
   }

  // functions

   //
   // nab*UnitBits <= K*N
   //

  static void UMul(unsigned d,ulen N,ulen K,Unit *temp,
                   Unit *c,const Unit *a,const Unit *b,ulen nab) // nc==2*nab
   {
    ulen T=GetT(N);
    ulen L=2*N*T;

    Unit *A=temp;
    Unit *B=A+L;
    Unit *t=B+L;

    Fill(d,N,K,T,A,a,nab);
    Fill(d,N,K,T,B,b,nab);

    DirectFFT(d,N,T,A,t);
    DirectFFT(d,N,T,B,t);

    for(ulen off=0; off<L ;off+=T) ModMul(N,T,A+off,B+off,t);

    InverseFFT(d,N,T,A,t);

    for(ulen off=0; off<L ;off+=T) DivNorm(N,T,A+off,d+1,t);

    Sum(d,N,K,T,c,2*nab,A);
   }
 };

} // namespace Math
} // namespace CCore

#endif

