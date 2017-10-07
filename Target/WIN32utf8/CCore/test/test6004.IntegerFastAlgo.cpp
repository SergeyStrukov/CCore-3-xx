/* test6004.IntegerFastAlgo.cpp */
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

#include <CCore/inc/TaskMemStack.h>
#include <CCore/inc/Array.h>

#include <CCore/inc/math/IntegerSlowAlgo.h>
#include <CCore/inc/math/IntegerFastAlgo.h>

#include <CCore/test/testIntBase.h>

#include <gmp.h>

#define mpn_mul_basecase __MPN(mul_basecase)
extern "C" __GMP_DECLSPEC void mpn_mul_basecase (mp_ptr, mp_srcptr, mp_size_t, mp_srcptr, mp_size_t);

namespace App {

namespace Private_6004 {

/* types */

using Algo = Math::IntegerFastAlgo ;

using Alt = Math::IntegerSlowAlgo<Algo::Unit> ;

/* class TestEngine<Algo,Alt> */

template <class Algo,class Alt>
class TestEngine : TestIntBase
 {
   using Unit = typename Algo::Unit ;

   static const ulen Len = 100 ;
   static const ulen GLen = 10 ;

  private:

   SimpleArray<Unit> buf;

   Unit *a; // Len
   ulen na;
   Unit *b; // Len
   ulen nb;

   Unit *c; // 2*Len+GLen
   Unit *d; // 2*Len+GLen
   ulen nc;

  private:

   void fill_c(ulen n)
    {
     nc=n;

     fill(Range(c,nc+GLen));

     Range(c,nc+GLen).copyTo(d);
    }

   void fill_a(ulen n)
    {
     na=n;

     fill(Range(a,na));
    }

   void fill_a()
    {
     fill_a(select(0,Len));
    }

   void fill_b(ulen n)
    {
     nb=n;

     fill(Range(b,nb));
    }

   void fill_b()
    {
     fill_b(select(0,Len));
    }

   void fill_abn(ulen n)
    {
     fill_a(n);
     fill_b(n);
     fill_c(na+nb);
    }

   void fill_abc()
    {
     fill_a();
     fill_b();
     fill_c(na+nb);
    }

   void fill_abn()
    {
     fill_a();
     fill_b(na);
     fill_c(na+nb);
    }

   void guard(const char *msg)
    {
     if( !Range(c,nc+GLen).equal(d) ) Error(msg);
    }

   void guard(Unit u,Unit u1,const char *msg)
    {
     if( u!=u1 || !Range(c,nc+GLen).equal(d) ) Error(msg);
    }

  private:

   void test1()
    {
     fill_abn();

     Algo::RawUMul(c,a,b,na);
     Alt::UMul(d,a,na,b,nb);

     guard("RawUMul");
    }

   void test2()
    {
     fill_a(1);

     Algo::Copy(b,a,na);

     Unit m=Algo::UDiv3(a,na);

     Unit d[1]={3};

     Algo::UMul(c,a,na,d,1);

     Unit u=Algo::UAddUnit(c,na+1,m);

     if( u || c[na] || Algo::UCmp(c,b,na) )
       {
        Printf(Exception,"UDiv3 failed");
       }
    }

  public:

   TestEngine()
    : buf(2*(Len+2*Len+GLen))
    {
     a=buf.getPtr();
     b=a+Len;
     c=b+Len;
     d=c+(2*Len+GLen);
    }

   void run(ulen rep)
    {
     static_assert( Meta::IsSame<typename Algo::Unit,typename Alt::Unit> ,"Algo::Unit");

     for(; rep ;rep--)
       {
        test1();
        test2();
       }
    }
 };

/* class TestSpeed<Algo> */

template <class Algo>
class TestSpeed
 {
   using Unit = typename Algo::Unit ;

   static constexpr ulen Len = 30 ;
   static constexpr unsigned Rep = 100 ;
   static constexpr unsigned Rep2 = 10 ;

   using Stat = TimeStat<ClockTimer::ValueType> ;

  private:

   PlatformRandom gen;

   SimpleArray<Unit> buf;

   Unit *a; // Len
   Unit *b; // Len
   Unit *c; // 2*Len

   SimpleArray<Stat> table;

  private:

   TestSpeed()
    : buf(4*Len),
      table(Len+1)
    {
     a=buf.getPtr();
     b=a+Len;
     c=b+Len;
    }

   void fill(PtrLen<Unit> r) { gen.fill(r); }

  private:

   void funcUMul(ulen n) CCORE_NOINLINE
    {
     Algo::RawUMul(c,a,b,n);
    }

   Stat testUMul(ulen n)
    {
     Stat stat;

     for(unsigned cnt=Rep; cnt ;cnt--)
       {
        fill(Range(a,n));
        fill(Range(b,n));

        ClockTimer timer;

        for(unsigned cnt=Rep2; cnt ;cnt--) funcUMul(n);

        stat.add(timer.get());
       }

     return stat;
    }

  private:

   template <class P>
   void showStat(P &&out)
    {
     for(ulen n=1; n<=Len ;n++)
       {
        Stat stat=table[n];

        stat.div(Rep2);

        Printf(out,"n = #; #;\n",n,stat.getMin());
       }
    }

   template <class P>
   void show(P &&out,StrLen title)
    {
     Printf(out,"#;\n",Title(title));

     showStat(out);
    }

   template <class P>
   void run(P &&out,StrLen title)
    {
     Printf(out,"#;\n\n",Title(title));

     for(ulen n=1; n<=Len ;n++)
       {
        table[n]=testUMul(n);
       }

     show(out,"UMul");

     Printf(out,"\n#;\n\n",TextDivider());
    }

  public:

   template <class P>
   static void Run(P &&out,StrLen title)
    {
     TestSpeed<Algo> obj;

     obj.run(out,title);
    }
 };

/* struct GMPAlgo */

struct GMPAlgo
 {
  // types and consts

  using Unit = mp_limb_t ;

  // multiplicative operators

  static void RawUMul(Unit *restrict c,const Unit *a,const Unit *b,ulen nab)
   {
    if( nab==0 ) return;

    mpn_mul_basecase(c,a,nab,b,nab);
   }
 };

} // namespace Private_6004

using namespace Private_6004;

/* Testit<6004> */

template<>
const char *const Testit<6004>::Name="Test6004 IntegerFastAlgo";

template<>
bool Testit<6004>::Main()
 {
  TaskMemStack tms(64_KByte);

  TestEngine<Algo,Alt>().run(100'000);

  PrintFile out("test6004.txt");

  TestSpeed<Algo>::Run(out,"FastAlgo");
  TestSpeed<GMPAlgo>::Run(out,"GMPAlgo");

  return true;
 }

} // namespace App

