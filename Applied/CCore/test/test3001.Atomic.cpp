/* test3001.Atomic.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Applied Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>
#include <CCore/test/testRun.h>

namespace App {

namespace Private_3001 {

/* test1() */

void test1()
 {
  const ulen TaskCount = 10 ;
  const ulen LoopCount = 10'000'000 ;

  Atomic atomic;

  {
   RunTask run_task;

   run_task(TaskCount, [&] () {
                               for(ulen count=LoopCount; count ;count--) atomic++;

                              } );
  }

  Printf(Con,"atomic = #;\n",atomic);
 }

/* test2() */

void test2()
 {
  const ulen LoopCount = 10'000'000 ;

  Atomic atomic;

  {
   RunTask run_task;

   run_task( [&] () {
                     ulen count=0;

                     while( count<LoopCount )
                       if( atomic.trySet(0,1)==0 ) count++;

                    } );

   run_task( [&] () {
                     ulen count=0;

                     while( count<LoopCount )
                       if( atomic.trySet(1,0)==1 ) count++;

                    } );
  }
 }

} // namespace Private_3001

using namespace Private_3001;

/* Testit<3001> */

template<>
const char *const Testit<3001>::Name="Test3001 Atomic";

template<>
bool Testit<3001>::Main()
 {
  test1();
  test2();

  return true;
 }

} // namespace App

