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
     static constexpr ulen Len = 256 ;

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

    return Algo::UnitAdd(c+nb,nac-nb,carry);
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

  static bool ModSub1(Unit *restrict c,const Unit *a,const Unit *b,ulen nac) // return a<b
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

  // Toom functions

  static ulen Toom22MulTempLen(ulen nab) // nab >= 2 TODO
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

  static void Toom22Mul(Unit *restrict c,const Unit *a,const Unit *b,ulen nab,Unit *temp) // nab >= 2 TODO
   {
    // inf, 0, -1

    ulen n1=nab/2;
    ulen n0=nab-n1;

    UMul(c,a,b,n0,temp);
    UMul(c+2*n0,a+n0,b+n0,n1,temp);

    if( n0==n1 )
      {
       bool fa=ModSub(temp,a,a+n0,n0);
       bool fb=ModSub(temp+n0,b,b+n0,n0);

       UMul(temp+nab,temp,temp+n0,n0,temp+2*nab);

       Unit carry=UAdd(temp,c,c+nab,nab);

       if( fa==fb )
         {
          carry-=Algo::USub(temp,temp+nab,nab);
         }
       else
         {
          carry+=Algo::UAdd(temp,temp+nab,nab);
         }

       carry+=Algo::UAdd(c+n0,temp,nab);

       Algo::UAddUnit(c+nab+n0,n1,carry);
      }
    else
      {
       bool fa=ModSub1(temp,a,a+n0,n0);
       bool fb=ModSub1(temp+n0,b,b+n0,n0);

       UMul(temp+2*n0,temp,temp+n0,n0,temp+4*n0);

       Unit carry=UAdd(temp,c,2*n0,c+2*n0,2*n1);

       if( fa==fb )
         {
          carry-=Algo::USub(temp,temp+2*n0,2*n0);
         }
       else
         {
          carry+=Algo::UAdd(temp,temp+2*n0,2*n0);
         }

       carry+=Algo::UAdd(c+n0,temp,2*n0);

       Algo::UAddUnit(c+3*n0,n1-1,carry);
      }
   }

  static void Toom22Mul(Unit *restrict c,const Unit *a,const Unit *b,ulen nab) // nab >= 2
   {
    Temp temp(Toom22MulTempLen(nab));

    Toom22Mul(c,a,b,nab,temp);
   }


  static ulen Toom33MulTempLen(ulen nab) // nab >= 3 TODO
   {
    return 0;
   }

  static void Toom33Mul(Unit *restrict c,const Unit *a,const Unit *b,ulen nab,Unit *temp) // nab >= 3 TODO
   {
    // inf, 0, +1, -1, +2
   }

  static void Toom33Mul(Unit *restrict c,const Unit *a,const Unit *b,ulen nab) // nab >= 3
   {
    Temp temp(Toom33MulTempLen(nab));

    Toom33Mul(c,a,b,nab,temp);
   }


  static ulen Toom44MulTempLen(ulen nab) // nab >= 4 TODO
   {
    return 0;
   }

  static void Toom44Mul(Unit *restrict c,const Unit *a,const Unit *b,ulen nab,Unit *temp) // nab >= 4 TODO
   {
    // inf, 0, +1, -1, +2, -2, +1/2
   }

  static void Toom44Mul(Unit *restrict c,const Unit *a,const Unit *b,ulen nab) // nab >= 4
   {
    Temp temp(Toom44MulTempLen(nab));

    Toom44Mul(c,a,b,nab,temp);
   }


  static ulen Toom55MulTempLen(ulen nab) // nab >= 5 TODO
   {
    return 0;
   }

  static void Toom55Mul(Unit *restrict c,const Unit *a,const Unit *b,ulen nab,Unit *temp) // nab >= 5 TODO
   {
    // inf, 0, +1, -1, +2, -2, +1/2, -1/2, +4
   }

  static void Toom55Mul(Unit *restrict c,const Unit *a,const Unit *b,ulen nab) // nab >= 5
   {
    Temp temp(Toom55MulTempLen(nab));

    Toom55Mul(c,a,b,nab,temp);
   }


  static ulen Toom66MulTempLen(ulen nab) // nab >= 6 TODO
   {
    return 0;
   }

  static void Toom66Mul(Unit *restrict c,const Unit *a,const Unit *b,ulen nab,Unit *temp) // nab >= 6 TODO
   {
    // inf, 0, +1, -1, +2, -2, +1/2, -1/2, +4, -4, +1/4
   }

  static void Toom66Mul(Unit *restrict c,const Unit *a,const Unit *b,ulen nab) // nab >= 6
   {
    Temp temp(Toom66MulTempLen(nab));

    Toom66Mul(c,a,b,nab,temp);
   }


  static ulen Toom77MulTempLen(ulen nab) // nab >= 7 TODO
   {
    return 0;
   }

  static void Toom77Mul(Unit *restrict c,const Unit *a,const Unit *b,ulen nab,Unit *temp) // nab >= 7 TODO
   {
    // inf, 0, +1, -1, +2, -2, +1/2, -1/2, +4, -4, +1/4, -1/4, +8
   }

  static void Toom77Mul(Unit *restrict c,const Unit *a,const Unit *b,ulen nab) // nab >= 7
   {
    Temp temp(Toom77MulTempLen(nab));

    Toom77Mul(c,a,b,nab,temp);
   }


  static ulen Toom88MulTempLen(ulen nab) // nab >= 8 TODO
   {
    return 0;
   }

  static void Toom88Mul(Unit *restrict c,const Unit *a,const Unit *b,ulen nab,Unit *temp) // nab >= 8 TODO
   {
    // inf, 0, +1, -1, +2, -2, +1/2, -1/2, +4, -4, +1/4, -1/4, +8, -8, +1/8
   }

  static void Toom88Mul(Unit *restrict c,const Unit *a,const Unit *b,ulen nab) // nab >= 8
   {
    Temp temp(Toom88MulTempLen(nab));

    Toom88Mul(c,a,b,nab,temp);
   }

  // FFT functions

  static ulen FFTMulTempLen(ulen nab) // nab >= 8 TODO
   {
    return 0;
   }

  static void FFTMul(Unit *restrict c,const Unit *a,const Unit *b,ulen nab,Unit *temp) // nab >= 8 TODO
   {
   }

  static void FFTMul(Unit *restrict c,const Unit *a,const Unit *b,ulen nab) // nab >= 8
   {
    Temp temp(FFTMulTempLen(nab));

    FFTMul(c,a,b,nab,temp);
   }

  // functions

  static_assert( 2 <= Algo::Toom22Min &&
                 3 <= Algo::Toom33Min &&
                 4 <= Algo::Toom44Min &&
                 5 <= Algo::Toom55Min &&
                 6 <= Algo::Toom66Min &&
                 7 <= Algo::Toom77Min &&
                 8 <= Algo::Toom88Min &&
                 Algo::Toom22Min <= Algo::Toom33Min &&
                 Algo::Toom33Min <= Algo::Toom44Min &&
                 Algo::Toom44Min <= Algo::Toom55Min &&
                 Algo::Toom55Min <= Algo::Toom66Min &&
                 Algo::Toom66Min <= Algo::Toom77Min &&
                 Algo::Toom77Min <= Algo::Toom88Min &&
                 Algo::Toom88Min <= Algo::FFTMin

               ,"CCore::Math::FastMulAlgo<Algo> : bad Algo tunning");

  static ulen UMulTempLen(ulen nab)
   {
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
    else if( nab<Algo::FFTMin )
      {
       return Toom88MulTempLen(nab);
      }
    else
      {
       return FFTMulTempLen(nab);
      }
   }

  static void UMul(Unit *restrict c,const Unit *a,const Unit *b,ulen nab,Unit *temp)
   {
    if( nab<Algo::Toom22Min )
      {
       Algo::RawMul(c,a,b,nab);
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
    else if( nab<Algo::FFTMin )
      {
       Toom88Mul(c,a,b,nab,temp);
      }
    else
      {
       FFTMul(c,a,b,nab,temp);
      }
   }

  static void UMul(Unit *restrict c,const Unit *a,const Unit *b,ulen nab) // nc==2*nab
   {
    if( nab<Algo::Toom22Min )
      {
       Algo::RawMul(c,a,b,nab);
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
    else if( nab<Algo::FFTMin )
      {
       Toom88Mul(c,a,b,nab);
      }
    else
      {
       FFTMul(c,a,b,nab);
      }
   }

  // multiplicative operators

  static ulen UMulTempLen(ulen na,ulen nb) // na >= nb > 0 TODO
   {
    if( na==nb ) return UMulTempLen(na);



    return 0;
   }

  static void UMul(Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb,Unit *temp) // na >= nb > 0 TODO
   {
    if( na==nb ) return UMul(c,a,b,na,temp);


   }

  static void UMul(Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb) // nc==na+nb
   {
    if( na<nb )
      {
       Swap(a,b);
       Swap(na,nb);
      }

    if( nb==0 )
      {
       Algo::Null(c,na);

       return;
      }

    // na >= nb > 0

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

