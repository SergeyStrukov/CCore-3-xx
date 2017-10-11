/* IntegerMulAlgo.h */
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

#ifndef CCore_inc_math_IntegerMulAlgo_h
#define CCore_inc_math_IntegerMulAlgo_h

#include <CCore/inc/Swap.h>
#include <CCore/inc/TaskMemStack.h>

#include <CCore/inc/math/FFTMul.h>

namespace CCore {
namespace Math {

/* classes */

template <class Algo> struct FastMulAlgo;

/* struct FastMulAlgo<Algo> */

template <class Algo>
struct FastMulAlgo
 {
  // types and consts

  using Unit = typename Algo::Unit ;

  // memory

  class Temp : NoCopy
   {
     static constexpr ulen Len = 256 ; // TODO 256

     Unit buf[Len];
     Unit *ptr;

    public:

     explicit Temp(ulen len)
      {
       if( len<=Len )
         {
          ptr=buf;
         }
       else
         {
          ptr=static_cast<Unit *>(TaskMemStackAlloc(LenOf(len,sizeof (Unit))));
         }
      }

     ~Temp()
      {
       if( ptr!=buf ) TaskMemStackFree(ptr);
      }

     Unit * operator + () { return ptr; }

     operator Unit * () { return ptr; }
   };

  // aux functions

  static Unit UAdd(Unit *restrict c,const Unit *a,const Unit *b,ulen nabc)
   {
    Algo::Copy(c,a,nabc);

    return Algo::UAdd(c,b,nabc);
   }

  static Unit USub(Unit *restrict c,const Unit *a,const Unit *b,ulen nabc)
   {
    Algo::Copy(c,a,nabc);

    return Algo::USub(c,b,nabc);
   }

  static Unit UAdd(Unit *restrict c,const Unit *a,ulen nac,const Unit *b,ulen nb) // nac>=nb
   {
    Algo::Copy(c,a,nac);

    Unit carry=Algo::UAdd(c,b,nb);

    return Algo::UAddUnit(c+nb,nac-nb,carry);
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

  static Unit ULShift(Unit *restrict b,const Unit *a,ulen nab,unsigned shift)
   {
    Algo::Copy(b,a,nab);

    return Algo::ULShift(b,nab,shift);
   }

  static bool ModSub(Unit *restrict c,const Unit *a,const Unit *b,ulen nabc) // return a<b
   {
    for(; nabc>0 ;nabc--)
      {
       Unit A=a[nabc-1];
       Unit B=b[nabc-1];

       if( A!=B )
         {
          if( A<B )
            {
             USub(c,b,a,nabc);

             return true;
            }
          else
            {
             USub(c,a,b,nabc);

             return false;
            }
         }

       c[nabc-1]=0;
      }

    return false;
   }

  static bool ModSub1(Unit *restrict c,const Unit *a,const Unit *b,ulen nac) // nb == nac-1 , return a<b
   {
    if( nac>0 )
      {
       Unit A=a[nac-1];

       if( A>0 )
         {
          c[nac-1]=A-USub(c,a,b,nac-1);

          return false;
         }

       c[nac-1]=0;

       nac--;
      }

    for(; nac>0 ;nac--)
      {
       Unit A=a[nac-1];
       Unit B=b[nac-1];

       if( A!=B )
         {
          if( A<B )
            {
             USub(c,b,a,nac);

             return true;
            }
          else
            {
             USub(c,a,b,nac);

             return false;
            }
         }

       c[nac-1]=0;
      }

    return false;
   }

  static bool ModSub1(Unit *restrict b,const Unit *a,ulen nb) // na == nb-1 , return b<a
   {
    if( nb>0 )
      {
       Unit B=b[nb-1];

       if( B>0 )
         {
          b[nb-1]=B-Algo::USub(b,a,nb-1);

          return false;
         }

       nb--;
      }

    for(; nb>0 ;nb--)
      {
       Unit B=b[nb-1];
       Unit A=a[nb-1];

       if( B!=A )
         {
          if( B<A )
            {
             Algo::URevSub(b,a,nb);

             return true;
            }
          else
            {
             Algo::USub(b,a,nb);

             return false;
            }
         }

       b[nb-1]=0;
      }

    return false;
   }

  // Toom functions

  static ulen Toom22MulTempLen(ulen nab) // nab >= 2
   {
    ulen n1=nab/2;
    ulen n0=nab-n1;

    if( n0==n1 || n0<Algo::Toom33Min )
      {
       return UMulTempLen(n0)+4*n0;
      }
    else
      {
       return Max_cast(UMulTempLen(n1),UMulTempLen(n0)+4*n0);
      }
   }

  static void Toom22Mul(Unit *restrict c,const Unit *a,const Unit *b,ulen nab,Unit *temp) // nab >= 2
   {
    // inf, 0, -1

    ulen m=nab/2;
    ulen n=nab-m;

    const Unit *a1=a+n;
    const Unit *b1=b+n;

    UMul(c,a,b,n,temp);
    UMul(c+2*n,a1,b1,m,temp);

    if( n==m )
      {
       bool neg = ( ModSub(temp,a,a1,n) == ModSub(temp+n,b,b1,n) );

       UMul(temp+nab,temp,temp+n,n,temp+2*nab);

       Unit carry=UAdd(temp,c,c+nab,nab);

       if( neg )
         {
          carry-=Algo::USub(temp,temp+nab,nab);
         }
       else
         {
          carry+=Algo::UAdd(temp,temp+nab,nab);
         }

       carry+=Algo::UAdd(c+n,temp,nab);

       Algo::UAddUnit(c+nab+n,n,carry);
      }
    else
      {
       bool neg = ( ModSub1(temp,a,a1,n) == ModSub1(temp+n,b,b1,n) );

       UMul(temp+2*n,temp,temp+n,n,temp+4*n);

       UAdd(temp,c,2*n,c+2*n,2*m);

       if( neg )
         {
          Algo::USub(temp,temp+2*n,2*n);
         }
       else
         {
          Algo::UAdd(temp,temp+2*n,2*n);
         }

       Unit carry=Algo::UAdd(c+n,temp,2*n);

       Algo::UAddUnit(c+3*n,n-2,carry);
      }
   }

  static void Toom22Mul(Unit *restrict c,const Unit *a,const Unit *b,ulen nab) // nab >= 2
   {
    Temp temp(Toom22MulTempLen(nab));

    Toom22Mul(c,a,b,nab,temp);
   }


  static ulen Toom33MulTempLen(ulen nab) // nab >= 5
   {
    ulen n=(nab+2)/3;
    ulen m=nab-2*n;

    ulen k=2*n+2;

    return 2*n+2*m+3*k+Max_cast(k,UMulTempLen(m),UMulTempLen(n),UMulTempLen(n+1));
   }

  static void Toom33Mul(Unit *restrict c,const Unit *a,const Unit *b,ulen nab,Unit *temp) // nab >= 5
   {
    // inf, 0, +1, -1, +2

    ulen n=(nab+2)/3;
    ulen m=nab-2*n;

    ulen k=2*n+2;

    const Unit *a1=a+n;
    const Unit *b1=b+n;

    const Unit *a2=a1+n;
    const Unit *b2=b1+n;

    Unit *A=temp;
    Unit *E=A+2*n;
    Unit *B=E+2*m;
    Unit *C=B+k;
    Unit *D=C+k;
    Unit *t=D+k;

    // A , E

    UMul(A,a,b,n,t);
    UMul(E,a2,b2,m,t);

    // B

    {
     {
      Unit u=UAdd(c,a,a1,n);

      u+=UAdd(c,n,a2,m);

      c[n]=u;
     }

     Unit *c1=c+n+1;

     {
      Unit u=UAdd(c1,b,b1,n);

      u+=UAdd(c1,n,b2,m);

      c1[n]=u;
     }

     UMul(B,c,c1,n+1,t);
    }

    // D

    {
     Unit *s=c+k;

     {
      Unit u=ULShift(s,a1,n,1);

      u+=UAdd(c,a,s,n);

      if( n==m )
        {
         u+=ULShift(s,a2,m,2);

         u+=Algo::UAdd(c,s,n);
        }
      else
        {
         s[m]=ULShift(s,a2,m,2);

         u+=UAdd(c,n,s,m+1);
        }

      c[n]=u;
     }

     Unit *c1=c+n+1;

     {
      Unit u=ULShift(s,b1,n,1);

      u+=UAdd(c1,b,s,n);

      if( n==m )
        {
         u+=ULShift(s,b2,m,2);

         u+=Algo::UAdd(c1,s,n);
        }
      else
        {
         s[m]=ULShift(s,b2,m,2);

         u+=UAdd(c1,n,s,m+1);
        }

      c1[n]=u;
     }

     UMul(D,c,c1,n+1,t);
    }

    // C

    bool pos;

    {
     c[n]=UAdd(c,a,n,a2,m);

     bool fa=ModSub1(c,a1,n+1);

     Unit *c1=c+n+1;

     c1[n]=UAdd(c1,b,n,b2,m);

     pos = ( fa == ModSub1(c1,b1,n+1) );

     UMul(C,c,c1,n+1,t);
    }

    Unit *P=t; // k

    {
     // P

     if( pos )
       USub(P,B,C,k);
     else
       UAdd(P,B,C,k);

     Algo::URShift(P,k,1);

     // B

     Algo::USub(B,P,k);

     USub(B,k,A,2*n);
     USub(B,k,E,2*m);

     // D

     USub(D,k,A,2*n);

     Algo::URShift(D,k,1);

     Algo::USub(D,P,k);

     ULShift(c,B,k,1);

     Algo::USub(D,c,k);

     c[2*m]=ULShift(c,E,2*m,3);

     USub(D,k,c,2*m+1);

     Algo::UDiv3(D,k);

     // P

     USub(P,k,D,n+m+1);
    }

    Algo::Copy(c,A,2*n);
    Algo::Copy(c+4*n,E,2*m);

    Algo::Copy(c+2*n,B,2*n);
    Algo::UAddUnit(c+4*n,2*m,B[2*n]);

    UAdd(c+n,2*nab-n,P,k-1);
    UAdd(c+3*n,2*nab-3*n,D,n+m+1);
   }

  static void Toom33Mul(Unit *restrict c,const Unit *a,const Unit *b,ulen nab) // nab >= 5
   {
    Temp temp(Toom33MulTempLen(nab));

    Toom33Mul(c,a,b,nab,temp);
   }


  static ulen Toom44MulTempLen(ulen nab) // nab >= 10 TODO
   {
    Used(nab);

    return 0;
   }

  static void Toom44Mul(Unit *restrict c,const Unit *a,const Unit *b,ulen nab,Unit *temp) // nab >= 10 TODO
   {
    // inf, 0, +1, -1, +2, -2, +1/2

    Used(c);
    Used(a);
    Used(b);
    Used(nab);
    Used(temp);
   }

  static void Toom44Mul(Unit *restrict c,const Unit *a,const Unit *b,ulen nab) // nab >= 10
   {
    Temp temp(Toom44MulTempLen(nab));

    Toom44Mul(c,a,b,nab,temp);
   }


  static ulen Toom55MulTempLen(ulen nab) // nab >= 17 TODO
   {
    Used(nab);

    return 0;
   }

  static void Toom55Mul(Unit *restrict c,const Unit *a,const Unit *b,ulen nab,Unit *temp) // nab >= 17 TODO
   {
    // inf, 0, +1, -1, +2, -2, +1/2, -1/2, +4

    Used(c);
    Used(a);
    Used(b);
    Used(nab);
    Used(temp);
   }

  static void Toom55Mul(Unit *restrict c,const Unit *a,const Unit *b,ulen nab) // nab >= 17
   {
    Temp temp(Toom55MulTempLen(nab));

    Toom55Mul(c,a,b,nab,temp);
   }


  static ulen Toom66MulTempLen(ulen nab) // nab >= 26 TODO
   {
    Used(nab);

    return 0;
   }

  static void Toom66Mul(Unit *restrict c,const Unit *a,const Unit *b,ulen nab,Unit *temp) // nab >= 26 TODO
   {
    // inf, 0, +1, -1, +2, -2, +1/2, -1/2, +4, -4, +1/4

    Used(c);
    Used(a);
    Used(b);
    Used(nab);
    Used(temp);
   }

  static void Toom66Mul(Unit *restrict c,const Unit *a,const Unit *b,ulen nab) // nab >= 26
   {
    Temp temp(Toom66MulTempLen(nab));

    Toom66Mul(c,a,b,nab,temp);
   }


  static ulen Toom77MulTempLen(ulen nab) // nab >= 37 TODO
   {
    Used(nab);

    return 0;
   }

  static void Toom77Mul(Unit *restrict c,const Unit *a,const Unit *b,ulen nab,Unit *temp) // nab >= 37 TODO
   {
    // inf, 0, +1, -1, +2, -2, +1/2, -1/2, +4, -4, +1/4, -1/4, +8

    Used(c);
    Used(a);
    Used(b);
    Used(nab);
    Used(temp);
   }

  static void Toom77Mul(Unit *restrict c,const Unit *a,const Unit *b,ulen nab) // nab >= 37
   {
    Temp temp(Toom77MulTempLen(nab));

    Toom77Mul(c,a,b,nab,temp);
   }


  static ulen Toom88MulTempLen(ulen nab) // nab >= 50 TODO
   {
    Used(nab);

    return 0;
   }

  static void Toom88Mul(Unit *restrict c,const Unit *a,const Unit *b,ulen nab,Unit *temp) // nab >= 50 TODO
   {
    // inf, 0, +1, -1, +2, -2, +1/2, -1/2, +4, -4, +1/4, -1/4, +8, -8, +1/8

    Used(c);
    Used(a);
    Used(b);
    Used(nab);
    Used(temp);
   }

  static void Toom88Mul(Unit *restrict c,const Unit *a,const Unit *b,ulen nab) // nab >= 50
   {
    Temp temp(Toom88MulTempLen(nab));

    Toom88Mul(c,a,b,nab,temp);
   }

  // FFT functions

  struct FFTAlgo : Algo
   {
    static ulen UMulTempLen(ulen nab)
     {
      return FastMulAlgo::UMulTempLen(nab);
     }

    static void UMul(Unit *restrict c,const Unit *a,const Unit *b,ulen nab,Unit *temp)
     {
      FastMulAlgo::UMul(c,a,b,nab,temp);
     }
   };

  static ulen TopMulTempLen(ulen nab) // nab >= 8
   {
    return FFTMul<FFTAlgo>::UMulTempLen(nab);
   }

  static void TopMul(Unit *restrict c,const Unit *a,const Unit *b,ulen nab,Unit *temp) // nab >= 8
   {
    return FFTMul<FFTAlgo>::UMul(c,a,b,nab,temp);
   }

  static void TopMul(Unit *restrict c,const Unit *a,const Unit *b,ulen nab) // nab >= 8
   {
    Temp temp(TopMulTempLen(nab));

    TopMul(c,a,b,nab,temp);
   }

  // functions

  static ulen UMulTempLen(ulen nab)
   {
    static_assert( 2 <= Algo::Toom22Min &&
                   5 <= Algo::Toom33Min &&
                   10 <= Algo::Toom44Min &&
                   17 <= Algo::Toom55Min &&
                   26 <= Algo::Toom66Min &&
                   37 <= Algo::Toom77Min &&
                   50 <= Algo::Toom88Min &&
                   FFTMul<FFTAlgo>::MinNAB <= Algo::TopMin &&
                   Algo::Toom22Min <= Algo::Toom33Min &&
                   Algo::Toom33Min <= Algo::Toom44Min &&
                   Algo::Toom44Min <= Algo::Toom55Min &&
                   Algo::Toom55Min <= Algo::Toom66Min &&
                   Algo::Toom66Min <= Algo::Toom77Min &&
                   Algo::Toom77Min <= Algo::Toom88Min &&
                   Algo::Toom88Min <= Algo::TopMin

                 ,"CCore::Math::FastMulAlgo<Algo> : bad Algo tunning");

    if( nab<Algo::Toom22Min )
      {
       return 0;
      }
    else if( nab<Algo::Toom33Min )
      {
       return Toom22MulTempLen(nab);
      }
    else if( nab<Algo::Toom44Min )
      {
       return Toom33MulTempLen(nab);
      }
    else if( nab<Algo::Toom55Min )
      {
       return Toom44MulTempLen(nab);
      }
    else if( nab<Algo::Toom66Min )
      {
       return Toom55MulTempLen(nab);
      }
    else if( nab<Algo::Toom77Min )
      {
       return Toom66MulTempLen(nab);
      }
    else if( nab<Algo::Toom88Min )
      {
       return Toom77MulTempLen(nab);
      }
    else if( nab<Algo::TopMin )
      {
       return Toom88MulTempLen(nab);
      }
    else
      {
       return TopMulTempLen(nab);
      }
   }

  static void UMul(Unit *restrict c,const Unit *a,const Unit *b,ulen nab,Unit *temp)
   {
    if( nab<Algo::Toom22Min )
      {
       Algo::RawUMul(c,a,b,nab);
      }
    else if( nab<Algo::Toom33Min )
      {
       Toom22Mul(c,a,b,nab,temp);
      }
    else if( nab<Algo::Toom44Min )
      {
       Toom33Mul(c,a,b,nab,temp);
      }
    else if( nab<Algo::Toom55Min )
      {
       Toom44Mul(c,a,b,nab,temp);
      }
    else if( nab<Algo::Toom66Min )
      {
       Toom55Mul(c,a,b,nab,temp);
      }
    else if( nab<Algo::Toom77Min )
      {
       Toom66Mul(c,a,b,nab,temp);
      }
    else if( nab<Algo::Toom88Min )
      {
       Toom77Mul(c,a,b,nab,temp);
      }
    else if( nab<Algo::TopMin )
      {
       Toom88Mul(c,a,b,nab,temp);
      }
    else
      {
       TopMul(c,a,b,nab,temp);
      }
   }

  static void UMul(Unit *restrict c,const Unit *a,const Unit *b,ulen nab) // nc==2*nab
   {
    if( nab<Algo::Toom22Min )
      {
       Algo::RawUMul(c,a,b,nab);
      }
    else if( nab<Algo::Toom33Min )
      {
       Toom22Mul(c,a,b,nab);
      }
    else if( nab<Algo::Toom44Min )
      {
       Toom33Mul(c,a,b,nab);
      }
    else if( nab<Algo::Toom55Min )
      {
       Toom44Mul(c,a,b,nab);
      }
    else if( nab<Algo::Toom66Min )
      {
       Toom55Mul(c,a,b,nab);
      }
    else if( nab<Algo::Toom77Min )
      {
       Toom66Mul(c,a,b,nab);
      }
    else if( nab<Algo::Toom88Min )
      {
       Toom77Mul(c,a,b,nab);
      }
    else if( nab<Algo::TopMin )
      {
       Toom88Mul(c,a,b,nab);
      }
    else
      {
       TopMul(c,a,b,nab);
      }
   }

  // multiplicative operators

  static ulen UMulTempLen(ulen na,ulen nb) // na > nb > 0 TODO
   {
    Used(na);
    Used(nb);

    return 0;
   }

  static void UMul(Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb,Unit *temp) // na > nb > 0 TODO
   {
    Used(c);
    Used(a);
    Used(na);
    Used(b);
    Used(nb);
    Used(temp);
   }

  static void UMul(Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb) // nc==na+nb
   {
    if( na==nb ) return UMul(c,a,b,na);

    if( na<nb )
      {
       Swap(a,b);
       Swap(na,nb);
      }

    if( nb==0 ) return Algo::Null(c,na);

    // na > nb > 0

    Temp temp(UMulTempLen(na,nb));

    UMul(c,a,na,b,nb,temp);
   }

  static ulen UMacTempLen(ulen na,ulen nb) // na >= nb > 0
   {
    ulen nc=na+nb;

    return LenAdd(UMulTempLen(na,nb),nc);
   }

  static Unit/* c */ UMac(Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb,Unit *temp) // na >= nb > 0
   {
    ulen nc=na+nb;
    Unit *d=temp;
    Unit *t=d+nc;

    UMul(d,a,na,b,nb,t);

    return Algo::UAdd(c,d,nc);
   }

  static Unit/* c */ UMac(Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb) // nc==na+nb
   {
    if( na<nb )
      {
       Swap(a,b);
       Swap(na,nb);
      }

    if( nb==0 ) return 0;

    // na >= nb > 0

    Temp temp(UMulTempLen(na,nb));

    return UMac(c,a,na,b,nb,temp);
   }
 };

} // namespace Math
} // namespace CCore

#endif

