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
     fill_abn(3);

     Algo::RawUMul(c,a,b,na);
     Alt::UMul(d,a,na,b,nb);

     Printf(Con,"#8.16; #8.16; #8.16; #8.16; #8.16; #8.16;\n",c[0],c[1],c[2],c[3],c[4],c[5]);
     Printf(Con,"#8.16; #8.16; #8.16; #8.16; #8.16; #8.16;\n",d[0],d[1],d[2],d[3],d[4],d[5]);

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

   void test3()
    {
     a[0]=0;
     a[1]=0x8101'0101;
     b[0]=0;
     b[1]=0x0010'1010;

     Algo::RawUMul(c,a,b,1);

     Printf(Con,"#8.16; #8.16;\n",c[0],c[1]);
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
     return test3();

     static_assert( Meta::IsSame<typename Algo::Unit,typename Alt::Unit> ,"Algo::Unit");

     for(; rep ;rep--)
       {
        test1();
        test2();
       }
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

  return true;
 }

} // namespace App

