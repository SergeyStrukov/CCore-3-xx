/* test7001.DrawAlgo.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Desktop
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/wintest.h>

#include <CCore/inc/video/DrawAlgo.h>

#include <CCore/inc/Random.h>

namespace App {

namespace Private_7001 {

/* test1() */

void test1(unsigned sx,unsigned sy)
 {
  DrawAlgo::LineDriverBase<unsigned> driver(sx,sy);

  unsigned x=0;
  unsigned y=0;

  for(unsigned count=sx; count ;count--)
    {
     y+=driver.step();
     x++;

     UIntFunc<unsigned>::Mul mul(x,sy);
     UIntFunc<unsigned>::DivMod divmod(mul.hi,mul.lo,sx);

     unsigned z=divmod.div;

     if( divmod.mod>sx/2 ) z++;

     if( y!=z )
       {
        Printf(Exception,"1 failed #; #;",sx,sy);
       }
    }
 }

/* test2() */

void test2(unsigned sx,unsigned sy,unsigned off,unsigned len)
 {
  DrawAlgo::LineDriverBase<unsigned> driver(sx,sy);

  unsigned y=0;

  for(unsigned count=off; count ;count--)
    {
     y+=driver.step();
    }

  unsigned y0=y;

  DrawAlgo::LineDriverBase<unsigned> driver1(driver);

  for(unsigned count=len; count ;count--)
    {
     y+=driver.step();
    }

  unsigned y1=y;

  if( driver1.step(len)!=y1-y0 )
    {
     Printf(Exception,"2 failed #; #;",sx,sy);
    }
 }

/* test3() */

void test3(uCoord sx,uCoord sy,uCoord y)
 {
  DrawAlgo::LineDriver driver(sx,sy);
  DrawAlgo::LineDriver driver1(driver);

  uCoord x=driver.clipToX(y);

  if( driver.step(x)<y || x==0 )
    {
     Printf(Exception,"3 failed #; #; #;",sx,sy,y);
    }

  if( driver1.step(x-1)>=y )
    {
     Printf(Exception,"4 failed #; #; #;",sx,sy,y);
    }
 }

void test3(unsigned sx,unsigned sy)
 {
  for(unsigned y=1; y<=sy ;y++) test3(sx,sy,y);
 }

/* class TestResultBuilder */

class TestResultBuilder : public ResultBuilder
 {
   static const unsigned Total = 10'000 ;

  private:

   virtual void work()
    {
     Random random;

     for(unsigned pos=0; pos<Total ;setCurrent(++pos))
       {
        if( getCancel() )
          {
           setResult("test cancelled"_def);

           return;
          }

        unsigned sy=random.select(1,1000);
        unsigned sx=sy+random.select(10000);

        test1(sx,sy);

        test2(sx,sy,random.select(1,1000),random.select(1,1000));

        test3((uCoord)sx,(uCoord)sy);
       }

     setResult("test ok"_def);
    }

  public:

   explicit TestResultBuilder(Function<void (void)> interrupt)
    : ResultBuilder(interrupt,Total)
    {
    }

   ~TestResultBuilder()
    {
    }
 };

} // namespace Private_7001

using namespace Private_7001;

/* TestMain() */

template <>
int TestMain<7001>(CmdDisplay cmd_display)
 {
  return ClientApplication<ResultWindow>::MainExtra<TestResultBuilder>(cmd_display,"Test7001"_def);
 }

} // namespace App


