/* test4019.TaskHeap.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: HCore Mini
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

#include <CCore/inc/Array.h>
#include <CCore/inc/TaskHeap.h>
#include <CCore/inc/Timer.h>
#include <CCore/inc/Random.h>

namespace App {

namespace Private_4019 {

void test()
 {
  TaskHeapScope scope;

  const ulen Rep = 1'000'000 ;

  MSecDiffTimer timer;
  Random random;

  for(ulen count=Rep; count ;count--)
    {
     ulen len=random.select(1000);
     TaskDynArray<int> temp(len);
    }

  Printf(Con,"#;\n",timer.get());
 }

} // namespace Private_4019

using namespace Private_4019;

/* Testit<4019> */

template<>
const char *const Testit<4019>::Name="Test4019 TaskHeap";

template<>
bool Testit<4019>::Main()
 {
  const ulen TaskCount = 10 ;

  TaskHeap task_heap;
  RunTask run_task;

  run_task(TaskCount,test);

  return true;
 }

} // namespace App

