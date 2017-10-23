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

template <class Algo,bool UseSafeWork=false> struct FastMulAlgo;

/* struct FastMulAlgo<Algo,bool UseSafeWork> */

template <class Algo,bool UseSafeWork>
struct FastMulAlgo
 {
  // types and consts

  using Unit = typename Algo::Unit ;

  static constexpr unsigned UnitBits = Algo::UnitBits ;

  static_assert( UnitBits>=16 ,"CCore::Math::FastMulAlgo<Algo> : bad UnitBits");

  // memory

  class SafeWork
   {
     PtrLen<Unit> space;

    public:

     SafeWork(Unit *ptr,ulen len) : space(ptr,len) {}

     operator Unit * () const { return space.ptr; }

     Unit * operator () (ulen len)
      {
       GuardLen(len,space.len);

       auto buf = (space+=len) ;

       return buf.ptr;
      }
   };

  class UnsafeWork
   {
     Unit *space;

    public:

     UnsafeWork(Unit *ptr,ulen /* len */) : space(ptr) {}

     operator Unit * () const { return space; }

     Unit * operator () (ulen len)
      {
       return Replace_add(space,len);
      }
   };

  using Work = Meta::Select<UseSafeWork,SafeWork,UnsafeWork> ;

  class Temp : NoCopy
   {
     static constexpr ulen Len = 256 ;

     Unit buf[Len];
     Unit *ptr;
     ulen len;

    public:

     explicit Temp(ulen len_)
      : len(len_)
      {
       if( len_<=Len )
         {
          ptr=buf;
         }
       else
         {
          ptr=static_cast<Unit *>(TaskMemStackAlloc(LenOf(len_,sizeof (Unit))));
         }
      }

     ~Temp()
      {
       if( ptr!=buf ) TaskMemStackFree(ptr);
      }

     operator Work() { return Work(ptr,len); }
   };

  // aux functions

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
             Algo::USub(c,b,a,nabc);

             return true;
            }
          else
            {
             Algo::USub(c,a,b,nabc);

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
          c[nac-1]=A-Algo::USub(c,a,b,nac-1);

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
             Algo::USub(c,b,a,nac);

             return true;
            }
          else
            {
             Algo::USub(c,a,b,nac);

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

  struct ToomAcc
   {
    ulen n;
    Unit *c; // 2*n+1

    ToomAcc(ulen n_,Unit *c_,unsigned shift,const Unit *a) : n(n_),c(c_) { c[n]=Algo::ULShift(c,a,n,shift); }


    ToomAcc(ulen n_,Unit *c_,const Unit *a,const Unit *b)
     : n(n_),c(c_)
     {
      c[n]=Algo::UAdd(c,a,b,n);
     }

    ToomAcc(ulen n_,Unit *c_,const Unit *a,const Unit *b,ulen m)
     : n(n_),c(c_)
     {
      c[n]=Algo::UAdd(c,a,n,b,m);
     }

    ToomAcc(ulen n_,Unit *c_,const Unit *a,unsigned shift,const Unit *b)
     : n(n_),c(c_)
     {
      Unit *d=c+n+1;

      Unit u=Algo::ULShift(d,b,n,shift);

      c[n]=u+Algo::UAdd(c,a,d,n);
     }

    ToomAcc(ulen n_,Unit *c_,const Unit *a,ulen m,unsigned shift,const Unit *b)
     : n(n_),c(c_)
     {
      c[n]=Algo::ULShift(c,b,n,shift);

      UAdd(c,n+1,a,m);
     }


    ToomAcc & operator () (const Unit *a)
     {
      c[n]+=Algo::UAdd(c,a,n);

      return *this;
     }

    ToomAcc & operator () (const Unit *a,ulen m)
     {
      UAdd(c,n+1,a,m);

      return *this;
     }

    ToomAcc & operator () (unsigned shift,const Unit *a)
     {
      Unit *d=c+n+1;

      Unit u=Algo::ULShift(d,a,n,shift);

      c[n]+=Algo::UAdd(c,d,n)+u;

      return *this;
     }

    ToomAcc & operator () (unsigned shift,const Unit *a,ulen m)
     {
      if( m<n )
        {
         Unit *d=c+n+1;

         d[m]=Algo::ULShift(d,a,m,shift);

         return (*this)(d,m+1);
        }
      else
        {
         return (*this)(shift,a);
        }
     }
   };

  // Toom functions

  static constexpr ulen Toom22MinLen = 2 ;

  static ulen Toom22MulTempLen(ulen nab)
   {
    ulen m=nab/2;
    ulen n=nab-m;

    if( n==m || n<Algo::Toom33Min )
      {
       return UMulTempLen(n)+4*n;
      }
    else
      {
       return Max_cast(UMulTempLen(m),UMulTempLen(n)+4*n);
      }
   }

  static void Toom22Mul(Unit *restrict c,const Unit *a,const Unit *b,ulen nab,Work temp)
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
       Unit *p=temp(n);
       Unit *q=temp(n);
       Unit *P=temp(nab);

       bool neg = ( ModSub(p,a,a1,n) == ModSub(q,b,b1,n) );

       UMul(P,p,q,n,temp);

       Unit carry=Algo::UAdd(p,c,c+nab,nab);

       if( neg )
         {
          carry-=Algo::USub(p,P,nab);
         }
       else
         {
          carry+=Algo::UAdd(p,P,nab);
         }

       carry+=Algo::UAdd(c+n,p,nab);

       Algo::UAddUnit(c+nab+n,n,carry);
      }
    else
      {
       Unit *p=temp(n);
       Unit *q=temp(n);
       Unit *P=temp(2*n);

       bool neg = ( ModSub1(p,a,a1,n) == ModSub1(q,b,b1,n) );

       UMul(P,p,q,n,temp);

       Algo::UAdd(p,c,2*n,c+2*n,2*m);

       if( neg )
         {
          Algo::USub(p,P,2*n);
         }
       else
         {
          Algo::UAdd(p,P,2*n);
         }

       Unit carry=Algo::UAdd(c+n,p,2*n);

       Algo::UAddUnit(c+3*n,n-2,carry);
      }
   }

  static void Toom22Mul(Unit *restrict c,const Unit *a,const Unit *b,ulen nab)
   {
    Temp temp(Toom22MulTempLen(nab));

    Toom22Mul(c,a,b,nab,temp);
   }


  static constexpr ulen Toom33MinLen = 5 ;

  static ulen Toom33MulTempLen(ulen nab)
   {
    ulen n=(nab+2)/3;
    ulen m=nab-2*n;

    ulen k=2*n+2;

    return 5*k+Max_cast(UMulTempLen(m),UMulTempLen(n),UMulTempLen(n+1));
   }

  static void Toom33Mul(Unit *restrict c,const Unit *a,const Unit *b,ulen nab,Work temp)
   {
    // inf, 0, +1, -1, +2

    ulen n=(nab+2)/3;
    ulen m=nab-2*n;

    ulen k=2*n+2;
    ulen l=n+1;

    const Unit *a1=a+n;
    const Unit *b1=b+n;

    const Unit *a2=a1+n;
    const Unit *b2=b1+n;

    Unit *A=c;          // 2*n
    Unit *E=c+4*n;      // 2*m

    Unit *B=temp(k);
    Unit *C=temp(k);
    Unit *D=temp(k);

    Unit *p=temp(k);
    Unit *q=temp(k);

    Unit *p1=p+l;
    Unit *q1=q+l;

    // A , E

    UMul(A,a,b,n,temp);
    UMul(E,a2,b2,m,temp);

    // B , C

    bool pos;

    {
     ToomAcc(n,p,a,a2,m);

     p1[n]=p[n]+Algo::UAdd(p1,p,a1,n);

     bool fa=ModSub1(p,a1,l);

     ToomAcc(n,q,b,b2,m);

     q1[n]=q[n]+Algo::UAdd(q1,q,b1,n);

     pos = ( fa == ModSub1(q,b1,l) );

     UMul(C,p,q,l,temp);
     UMul(B,p1,q1,l,temp);
    }

    // D

    {
     ToomAcc(n,p,a,1,a1)(2,a2,m);
     ToomAcc(n,q,b,1,b1)(2,b2,m);

     UMul(D,p,q,l,temp);
    }

    Unit *P=q; // k

    {
     // P

     if( pos )
       Algo::USub(P,B,C,k);
     else
       Algo::UAdd(P,B,C,k);

     Algo::URShift(P,k,1);

     // B

     Algo::USub(B,P,k);

     USub(B,k,A,2*n);
     USub(B,k,E,2*m);

     // D

     USub(D,k,A,2*n);

     Algo::URShift(D,k,1);

     Algo::USub(D,P,k);

     Algo::ULShift(p,B,k,1);

     Algo::USub(D,p,k);

     p[2*m]=Algo::ULShift(p,E,2*m,3);

     USub(D,k,p,2*m+1);

     Algo::UDiv3(D,k);

     // P

     USub(P,k,D,n+m+1);
    }

    Algo::Copy(c+2*n,B,2*n);
    Algo::UAddUnit(c+4*n,2*m,B[2*n]);

    UAdd(c+n,2*nab-n,P,k-1);
    UAdd(c+3*n,2*nab-3*n,D,n+m+1);
   }

  static void Toom33Mul(Unit *restrict c,const Unit *a,const Unit *b,ulen nab)
   {
    Temp temp(Toom33MulTempLen(nab));

    Toom33Mul(c,a,b,nab,temp);
   }


  static constexpr ulen Toom44MinLen = 14 ;

  static ulen Toom44MulTempLen(ulen nab)
   {
    ulen n=(nab+2)/3;
    ulen m=nab-2*n;

    ulen k=2*n+2;

    return 2*n+2*m+(7*k-1)+Max_cast(k,UMulTempLen(m),UMulTempLen(n),UMulTempLen(n+1));
   }

  static void Toom44Mul(Unit *restrict c,const Unit *a,const Unit *b,ulen nab,Work temp)
   {
    // inf, 0, +1, -1, +2, -2, +1/2

    ulen n=(nab+3)/4;
    ulen m=nab-3*n;

    ulen k=2*n+2;
    ulen l=k-1;

    const Unit *a1=a+n;
    const Unit *a2=a1+n;
    const Unit *a3=a2+n;

    const Unit *b1=b+n;
    const Unit *b2=b1+n;
    const Unit *b3=b2+n;

    Unit *A=temp(2*n);
    Unit *B=temp(k);
    Unit *C=temp(k);
    Unit *D=temp(k);
    Unit *E=temp(k);
    Unit *F=temp(k);
    Unit *G=temp(2*m);
    Unit *q1=temp(l);
    Unit *p2=temp(n+1);
    Unit *q2=temp(n+1);

    Unit *p=c;
    Unit *q=c+l;
    Unit *p1=q+l;

    // A , G

    {
     UMul(A,a,b,n,temp);
     UMul(G,a3,b3,m,temp);
    }

    // B , C

    bool posC;

    {
     ToomAcc(n,p,a,a2);
     ToomAcc(n,p1,a1,a3,m);

     bool f=ModSub(p2,p,p1,n+1);

     Algo::UAdd(p,p1,n+1);

     ToomAcc(n,q,b,b2);
     ToomAcc(n,q1,b1,b3,m);

     posC=( f == ModSub(q2,q,q1,n+1) );

     Algo::UAdd(q,q1,n+1);

     UMul(C,p2,q2,n+1,temp);
     UMul(B,p,q,n+1,temp);
    }

    // D , E

    bool posE;

    {
     ToomAcc(n,p,a,2,a2);
     ToomAcc(n,p1,1,a1)(3,a3,m);

     bool f=ModSub(p2,p,p1,n+1);

     Algo::UAdd(p,p1,n+1);

     ToomAcc(n,q,b,2,b2);
     ToomAcc(n,q1,1,b1)(3,b3,m);

     posE=( f == ModSub(q2,q,q1,n+1) );

     Algo::UAdd(q,q1,n+1);

     UMul(E,p2,q2,n+1,temp);
     UMul(D,p,q,n+1,temp);
    }

    // F

    {
     ToomAcc(n,p,a3,m,1,a2)(2,a1)(3,a);
     ToomAcc(n,q,b3,m,1,b2)(2,b1)(3,b);

     UMul(F,p,q,n+1,temp);
    }

    Unit *P=q1;
    Unit *Q=p2;

    {
     if( posC )
       Algo::UAdd(P,B,C,l);
     else
      Algo::USub(P,B,C,l);

     Algo::URShift(P,l,1); // P : A+C+E+G

     if( posC )
       Algo::USub(B,C,l);
     else
       Algo::UAdd(B,C,l);

     Algo::URShift(B,l,1); // B : B+D+F

     if( posE )
       Algo::UAdd(Q,D,E,l);
     else
       Algo::USub(Q,D,E,l);

     Algo::URShift(Q,l,1); // Q : A+4C+16E+64G

     if( posE )
       Algo::USub(D,E,l);
     else
       Algo::UAdd(D,E,l);

     Algo::URShift(D,l,2); // D : B+4D+16F

     USub(P,l,A,2*n);
     USub(P,l,G,2*m);      // P : C+E

     USub(Q,l,A,2*n);

     Algo::Copy(C,G,2*m);
     C[2*m]=Algo::ULShift(C,2*m,6);

     USub(Q,l,C,2*m+1);

     Algo::URShift(Q,l,2); // Q : C+4E

     Algo::USub(Q,P,l);
     Algo::UDiv3(Q,l);     // Q : E
     Algo::USub(P,Q,l);    // P : C

     USub(F,l,G,2*m);

     Algo::Copy(C,Q,l);
     Algo::ULShift(C,l,2);

     Algo::USub(F,C,l);

     Algo::Copy(C,P,l);
     Algo::ULShift(C,l,4);

     Algo::USub(F,C,l);

     Algo::Copy(C,A,2*n);
     C[2*n]=Algo::ULShift(C,2*n,6);

     Algo::USub(F,C,l);

     Algo::URShift(F,l,1); // F : 16B+4D+F

     Algo::USub(D,B,l);
     Algo::UDiv3(D,l);     // D : D+5F

     Algo::USub(F,B,l);
     Algo::UDiv3(F,l);     // F : 5B+D

     Algo::UAdd(F,D,l);

     Algo::Copy(C,B,l);
     Algo::ULShift(C,l,1);

     Algo::USub(F,C,l);
     Algo::UDiv3(F,l);     // F : B+F

     Algo::USub(B,F,l);    // B : D
     Algo::USub(D,B,l);
     Algo::UDiv5(D,l);     // D : F
     Algo::USub(F,D,l);    // F : B
    }

    Algo::Copy(c,A,2*n);
    Algo::Copy(c+2*n,P,l);
    Algo::Copy(c+6*n,G,2*m);
    Algo::Null(c+4*n+1,2*n-1);

    UAdd(c+n,5*n+2*m,F,l);
    UAdd(c+3*n,3*n+2*m,B,l);
    UAdd(c+4*n,2*n+2*m,Q,l);

    ulen s=n+2*m;

    UAdd(c+5*n,s,D,Min(l,s));
   }

  static void Toom44Mul(Unit *restrict c,const Unit *a,const Unit *b,ulen nab)
   {
    Temp temp(Toom44MulTempLen(nab));

    Toom44Mul(c,a,b,nab,temp);
   }


  static constexpr ulen Toom55MinLen = 17 ;

  static ulen Toom55MulTempLen(ulen nab) // TODO
   {
    Used(nab);

    return 0;
   }

  static void Toom55Mul(Unit *restrict c,const Unit *a,const Unit *b,ulen nab,Work temp) // TODO
   {
    // inf, 0, +1, -1, +2, -2, +1/2, -1/2, +4

    Used(c);
    Used(a);
    Used(b);
    Used(nab);
    Used(temp);
   }

  static void Toom55Mul(Unit *restrict c,const Unit *a,const Unit *b,ulen nab)
   {
    Temp temp(Toom55MulTempLen(nab));

    Toom55Mul(c,a,b,nab,temp);
   }


  static constexpr ulen Toom66MinLen = 26 ;

  static ulen Toom66MulTempLen(ulen nab) // TODO
   {
    Used(nab);

    return 0;
   }

  static void Toom66Mul(Unit *restrict c,const Unit *a,const Unit *b,ulen nab,Work temp) // TODO
   {
    // inf, 0, +1, -1, +2, -2, +1/2, -1/2, +4, -4, +1/4

    Used(c);
    Used(a);
    Used(b);
    Used(nab);
    Used(temp);
   }

  static void Toom66Mul(Unit *restrict c,const Unit *a,const Unit *b,ulen nab)
   {
    Temp temp(Toom66MulTempLen(nab));

    Toom66Mul(c,a,b,nab,temp);
   }


  static constexpr ulen Toom77MinLen = 37 ;

  static ulen Toom77MulTempLen(ulen nab) // TODO
   {
    Used(nab);

    return 0;
   }

  static void Toom77Mul(Unit *restrict c,const Unit *a,const Unit *b,ulen nab,Work temp) // TODO
   {
    // inf, 0, +1, -1, +2, -2, +1/2, -1/2, +4, -4, +1/4, -1/4, +8

    Used(c);
    Used(a);
    Used(b);
    Used(nab);
    Used(temp);
   }

  static void Toom77Mul(Unit *restrict c,const Unit *a,const Unit *b,ulen nab)
   {
    Temp temp(Toom77MulTempLen(nab));

    Toom77Mul(c,a,b,nab,temp);
   }


  static constexpr ulen Toom88MinLen = 50 ;

  static ulen Toom88MulTempLen(ulen nab) // TODO
   {
    Used(nab);

    return 0;
   }

  static void Toom88Mul(Unit *restrict c,const Unit *a,const Unit *b,ulen nab,Work temp) // TODO
   {
    // inf, 0, +1, -1, +2, -2, +1/2, -1/2, +4, -4, +1/4, -1/4, +8, -8, +1/8

    Used(c);
    Used(a);
    Used(b);
    Used(nab);
    Used(temp);
   }

  static void Toom88Mul(Unit *restrict c,const Unit *a,const Unit *b,ulen nab)
   {
    Temp temp(Toom88MulTempLen(nab));

    Toom88Mul(c,a,b,nab,temp);
   }

  // FFT functions

  struct FFTAlgo : Algo
   {
    using Work = typename FastMulAlgo::Work ;

    static ulen UMulTempLen(ulen nab)
     {
      return FastMulAlgo::UMulTempLen(nab);
     }

    static void UMul(Unit *restrict c,const Unit *a,const Unit *b,ulen nab,Work temp)
     {
      FastMulAlgo::UMul(c,a,b,nab,temp);
     }
   };

  static ulen TopMulTempLen(ulen nab) // nab >= 8
   {
    return FFTMul<FFTAlgo>::UMulTempLen(nab);
   }

  static void TopMul(Unit *restrict c,const Unit *a,const Unit *b,ulen nab,Work temp) // nab >= 8
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
    static_assert( Toom22MinLen <= Algo::Toom22Min &&
                   Toom33MinLen <= Algo::Toom33Min &&
                   Toom44MinLen <= Algo::Toom44Min &&
                   Toom55MinLen <= Algo::Toom55Min &&
                   Toom66MinLen <= Algo::Toom66Min &&
                   Toom77MinLen <= Algo::Toom77Min &&
                   Toom88MinLen <= Algo::Toom88Min &&
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

  static void UMul(Unit *restrict c,const Unit *a,const Unit *b,ulen nab,Work temp)
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

  static void UMul(Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb,Work temp) // na > nb > 0 TODO
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

  static Unit/* c */ UMac(Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb,Work temp) // na >= nb > 0
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

