/* test3035.IntegerMulAlgo2.cpp */
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

#include <CCore/test/test.h>

#include <CCore/inc/Array.h>
#include <CCore/inc/PlatformRandom.h>
#include <CCore/inc/Timer.h>

#include <CCore/inc/math/IntegerMulAlgo.h>
#include <CCore/inc/math/IntegerFastAlgo.h>

#include <math.h>
#include <gmp.h>

namespace App {

namespace Private_3035 {

/* classes */

template <class Algo> class TestIntegerSpeed;

/* class TestIntegerSpeed<Algo> */

template <class Algo>
class TestIntegerSpeed
 {
   using Unit = typename Algo::Unit ;

   static constexpr ulen Len = 5'000'000 ;
   static constexpr ulen Len1 =      100 ;
   static constexpr ulen Len2 =     1000 ;
   static constexpr ulen Len3 =     4000 ;

   static constexpr unsigned Rep  = 100 ;
   static constexpr unsigned Rep2 =  10 ;

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
     if( n>=4 )
       Printf(out,"n = #; #; best/(n*log(n)*log(log(n))) = #;\n",n,t,int( t/(n*log2(n)*log2(log2(n))) ));
     else
       Printf(out,"n = #; #;\n",n,t);
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
     test2(out);
     test3(out);

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
  static constexpr ulen Toom22Min =     30 ;
  static constexpr ulen Toom33Min =    170 ;
  static constexpr ulen TopMin    =  4'000 ;

  static constexpr ulen Toom44Min = TopMin ;
  static constexpr ulen Toom55Min = TopMin ;
  static constexpr ulen Toom66Min = TopMin ;
  static constexpr ulen Toom77Min = TopMin ;
  static constexpr ulen Toom88Min = TopMin ;
 };

using FastAlgo = Math::FastMulAlgo<Base> ;

} // namespace Private_3035

using namespace Private_3035;

/* Testit<3035> */

template<>
const char *const Testit<3035>::Name="Test3035 IntegerMulAlgo2";

template<>
bool Testit<3035>::Main()
 {
  TaskMemStack tms(64_KByte);

  PrintFile out("test3035.txt");

  TestIntegerSpeed<GMPAlgo>::Run(out,"GMPAlgo");
  TestIntegerSpeed<FastAlgo>::Run(out,"FastAlgo");

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

