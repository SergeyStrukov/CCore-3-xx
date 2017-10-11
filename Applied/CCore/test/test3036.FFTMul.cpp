/* test3036.FFTMul.cpp */
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

#include <CCore/inc/TaskMemStack.h>

#include <CCore/inc/math/FFTMul.h>
#include <CCore/inc/math/IntegerFastAlgo.h>

#include <CCore/test/testIntBase.h>

namespace App {

namespace Private_3036 {

/* struct BaseAlgo */

constexpr unsigned Log(unsigned n)
 {
  return (n>1)?Log(n/2)+1:0;
 }

struct BaseAlgo : Math::IntegerFastAlgo
 {
  static constexpr unsigned LogUnitBits = Log(UnitBits) ;

  static ulen UMulTempLen(ulen) { return 0; }

  static void UMul(Unit *c,const Unit *a,const Unit *b,ulen nab,Unit *) // nc==2*nab
   {
    Math::IntegerFastAlgo::UMul(c,a,nab,b,nab);
   }
 };

/* struct Algo */

struct Algo : Math::FFTMul<BaseAlgo>
 {
  static void UMul(Unit *c,const Unit *a,const Unit *b,ulen nab) // nc==2*nab
   {
    StackArray<Unit> buf(UMulTempLen(nab));

    Math::FFTMul<BaseAlgo>::UMul(c,a,b,nab,buf.getPtr());
   }
 };

/* class TestEngine<Algo,Alt> */

template <class Algo,class Alt>
class TestEngine : TestIntBase
 {
   using Unit = typename Algo::Unit ;

   static const ulen Len = 1'000 ;
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

   void guard(Unit u,Unit u1,const char *msg)
    {
     if( u!=u1 || !Range(c,nc+GLen).equal(d) ) Error(msg);
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

/* ShowD() */

void ShowD(ulen n)
 {
  unsigned d=Algo::FindD(n);

  Printf(Con,"n = #; d = #;\n",n,d);
 }

} // namespace Private_3036

using namespace Private_3036;

/* Testit<3036> */

template<>
const char *const Testit<3036>::Name="Test3036 FFTMul";

template<>
bool Testit<3036>::Main()
 {
  TaskMemStack tms(64_KByte);

  ShowD(1);
  ShowD(10);
  ShowD(100);
  ShowD(1000);
  ShowD(10000);
  ShowD(100000);
  ShowD(1000000);
  ShowD(MaxULen/4);
  ShowD(MaxULen/2);
  ShowD(MaxULen);

  //TestEngine<Algo,Math::IntegerFastAlgo>().run(100'000);

  return true;
 }

} // namespace App

