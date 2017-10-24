/* test6005.IntegerMulAlgo.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Target/WIN32utf8
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/Array.h>
#include <CCore/inc/PlatformRandom.h>
#include <CCore/inc/Timer.h>
#include <CCore/inc/PrintRatio.h>

#include <CCore/inc/math/IntegerMulAlgo.h>
#include <CCore/inc/math/IntegerFastAlgo.h>

#include <gmp.h>

namespace App {

namespace Private_6005 {

/* classes */

template <class Algo> class TestIntegerSpeed;

/* class TestIntegerSpeed<Algo> */

template <class Algo>
class TestIntegerSpeed
 {
   using Unit = typename Algo::Unit ;

   static constexpr ulen Len  = 5'000'000 ;
   static constexpr ulen Len1 =       500 ;
   static constexpr ulen Len2 =       800 ;
   static constexpr ulen Len3 =      8000 ;

   static constexpr unsigned Rep  =    10 ;
   static constexpr unsigned Rep2 =    32 ;

   using Stat = TimeStat<ClockTimer::ValueType> ;

  private:

   PlatformRandom gen;

   SimpleArray<Unit> buf;

   Unit *a; // Len
   Unit *b; // Len
   Unit *c; // 2*Len

   SimpleArray<Stat> table;

  private:

   TestIntegerSpeed()
    : buf(4*Len),
      table(Len+1)
    {
     a=buf.getPtr();
     b=a+Len;
     c=b+Len;
    }

   void fill(PtrLen<Unit> r) { gen.fill(r); }

  private:

   static unsigned Log(UIntType x) { return UIntBitsOf(x); }

   void funcUMul(ulen n,ulen m) CCORE_NOINLINE
    {
     Algo::UMul(c,a,n,b,m);
    }

   Stat testUMul(ulen n,ulen m,unsigned rep=Rep,unsigned rep2=Rep2)
    {
     Stat stat;

     for(unsigned cnt=rep; cnt ;cnt--)
       {
        fill(Range(a,n));
        fill(Range(b,m));

        ClockTimer timer;

        for(unsigned cnt=rep2; cnt ;cnt--) funcUMul(n,m);

        stat.add(timer.get());
       }

     return stat;
    }

  private:

   template <class P,class T>
   void show(P &&out,ulen n,T t)
    {
     if( (n%10)==0 ) Putch(out,'\n');

     auto l=Log(n);
     auto b=n*l*Log(l);

     if( b )
       {
        Printf(out,"n = #; best = #; O = #;\n",n,t,PrintRatio(t,b));
       }
     else
       {
        Printf(out,"n = #; best = #;\n",n,t);
       }
    }

   template <class P>
   void test1(P &&out)
    {
     for(ulen n=1; n<=Len1 ;n++)
       {
        Printf(Con,"n = #;\n",n);

        table[n]=testUMul(n,n);
       }

     for(ulen n=1; n<=Len1 ;n++)
       {
        Stat stat=table[n];

        stat.div(Rep2);

        show(out,n,stat.getMin());
       }

     Printf(Con,"test1 done\n");
    }

   template <class P>
   void test2(P &&out)
    {
     ulen N=Len2;

     for(ulen n=1; N<Len3 ;n++,N+=N/10)
       {
        Printf(Con,"n = #;\n",N);

        table[n]=testUMul(N,N,10,1);
       }

     N=Len2;

     for(ulen n=1; N<Len3 ;n++,N+=N/10)
       {
        Stat stat=table[n];

        show(out,N,stat.getMin());
       }

     Printf(Con,"test2 done\n");
    }

   template <class P>
   void test3(P &&out)
    {
     ulen N=Len3;

     for(ulen n=1; N<=Len ;n++,N*=2)
       {
        Printf(Con,"N = #;\n",N);

        table[n]=testUMul(N,N,10,1);
       }

     N=Len3;

     for(ulen n=1; N<=Len ;n++,N*=2)
       {
        Stat stat=table[n];

        show(out,N,stat.getMin());
       }

     Printf(Con,"test3 done\n");
    }

   template <class P>
   void run(P &&out,StrLen title)
    {
     Printf(out,"#;\n\n",Title(title));

     test1(out);
     //test2(out);
     //test3(out);

     Printf(out,"\n#;\n\n",TextDivider());
    }

  public:

   template <class P>
   static void Run(P &&out,StrLen title)
    {
     TestIntegerSpeed<Algo> obj;

     obj.run(out,title);
    }
 };

/* struct GMPAlgo */

struct GMPAlgo
 {
  // types and consts

  using Unit = mp_limb_t ;

  // multiplicative operators

  static void UMul(Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb) // nc==na+nb
   {
    if( na<nb )
      {
       Swap(a,b);
       Swap(na,nb);
      }

    if( nb==0 )
      {
       return;
      }

    mpn_mul(c,a,na,b,nb);
   }
 };

/* struct Base */

struct Base : Math::IntegerFastAlgo
 {
#if 0

  class Int
   {
    public:

     Int() {}

     explicit Int(PtrLen<const Unit>) {}

     Int(const Unit *data,ulen len) : Int(Range(data,len)) {}

     friend Int operator + (Int,Int) { return Int(); }

     friend Int operator * (Int,Int) { return Int(); }

     friend Int operator - (Int,Int) { return Int(); }

     friend Int operator << (Int,ulen) { return Int(); }
   };

  template <class I>
  static void GuardNull(I,const char *)
   {
   }

#endif

  static constexpr ulen Toom22Min =     30 ; // 30
  static constexpr ulen Toom33Min =    110 ; // 100
  static constexpr ulen Toom44Min =    170 ; // 170

  static constexpr ulen TopMin    =  4'000 ;

  static constexpr ulen Toom55Min = TopMin ;
  static constexpr ulen Toom66Min = TopMin ;
  static constexpr ulen Toom77Min = TopMin ;
  static constexpr ulen Toom88Min = TopMin ;

#if 1

  static void RawUMul(Unit *restrict c,const Unit *a,const Unit *b,ulen nab)
   {
    mpn_mul((mp_limb_t *)c,(const mp_limb_t *)a,nab,(const mp_limb_t *)b,nab);
   }

#endif
 };

using FastAlgo = Math::FastMulAlgo<Base> ;

} // namespace Private_6005

using namespace Private_6005;

/* Testit<6005> */

template<>
const char *const Testit<6005>::Name="Test6005 IntegerMulAlgo";

template<>
bool Testit<6005>::Main()
 {
  TaskMemStack tms(64_KByte);

  PrintFile out("test6005.txt");

  //TestIntegerSpeed<GMPAlgo>::Run(out,"GMPAlgo");

  TestIntegerSpeed<FastAlgo>::Run(out,"FastAlgo");

  return true;

  using A = Math::FFTMul<FastAlgo::FFTAlgo> ;

  for(unsigned d=A::LogUnitBits+1,dmax=A::FindD(MaxULen); d<=dmax ;d++)
    {
     ulen N=ulen(1)<<d;
     ulen K=(N-d)/2;
     ulen n=K*(ulen(1)<<(d-A::LogUnitBits));

     unsigned d1=A::FindD(n);

     Printf(out,"d = #; n = #; d1 = #;\n",d,n,d1);
    }

  return true;
 }

} // namespace App

