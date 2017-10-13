/* test3034.IntegerMulAlgo1.cpp */
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

#include <CCore/test/testIntBase.h>

#include <CCore/inc/math/IntegerSlowAlgo.h>
#include <CCore/inc/math/IntegerMulAlgo.h>

namespace App {

namespace Private_3034 {

/* type Alt */

using Alt = Math::IntegerSlowAlgo<uint16> ;

/* struct Base */

struct Base : Alt
 {
  static constexpr unsigned LogUnitBits = 4 ;

  static constexpr ulen Toom22Min = 2 ;
  static constexpr ulen Toom33Min = 5 ;
  static constexpr ulen Toom44Min = 50 ;
  static constexpr ulen Toom55Min = 50 ;
  static constexpr ulen Toom66Min = 50 ;
  static constexpr ulen Toom77Min = 50 ;
  static constexpr ulen Toom88Min = 50 ;
  static constexpr ulen TopMin    = 50 ;

  static void RawUMul(Unit *restrict c,const Unit *a,const Unit *b,ulen nab)
   {
    UMul(c,a,nab,b,nab);
   }

  struct DivMod3 : UIntFunc<Unit>::DivMod
   {
    DivMod3(Unit hi,Unit lo) : UIntFunc<Unit>::DivMod(hi,lo,3) {}
   };

  static void UDiv3(Unit *a,ulen na)
   {
    Unit hi=0;

    for(; na ;na--)
      {
       Unit lo=a[na-1];

       DivMod3 result(hi,lo);

       a[na-1]=result.div;

       hi=result.mod;
      }
   }

  struct DivMod5 : UIntFunc<Unit>::DivMod
   {
    DivMod5(Unit hi,Unit lo) : UIntFunc<Unit>::DivMod(hi,lo,5) {}
   };

  static void UDiv5(Unit *a,ulen na)
   {
    Unit hi=0;

    for(; na ;na--)
      {
       Unit lo=a[na-1];

       DivMod5 result(hi,lo);

       a[na-1]=result.div;

       hi=result.mod;
      }
   }
 };

using Algo = Math::FastMulAlgo<Base> ;

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

   void fill_abn()
    {
     na=select(0,Len);
     nb=na;

     fill(Range(a,na));
     fill(Range(b,nb));

     fill_c(na+nb);
    }

   void fill_abn(ulen n)
    {
     na=n;
     nb=na;

     fill(Range(a,na));
     fill(Range(b,nb));

     fill_c(na+nb);
    }

   void guard(const char *msg)
    {
     if( !Range(c,nc+GLen).equal(d) ) Error(msg);
    }

  private:

   void test1()
    {
     fill_abn();

     Algo::UMul(c,a,b,na);
     Alt::UMul(d,a,na,b,nb);

     guard("Algo::UMul");
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
       }
    }
 };

} // namespace Private_3034

using namespace Private_3034;

/* Testit<3034> */

template<>
const char *const Testit<3034>::Name="Test3034 IntegerMulAlgo1";

template<>
bool Testit<3034>::Main()
 {
  TaskMemStack tms(64_KByte);

  TestEngine<Algo,Alt>().run(100'000);

  return true;
 }

} // namespace App

