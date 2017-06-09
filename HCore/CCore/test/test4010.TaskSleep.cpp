/* test4010.Task.cpp */
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

#include <CCore/inc/Task.h>
#include <CCore/inc/Timer.h>

namespace App {

namespace Private_4010 {


} // namespace Private_4010

using namespace Private_4010;

/* Testit<4010> */

template<>
const char *const Testit<4010>::Name="Test4010 Task";

template<>
bool Testit<4010>::Main()
 {
  MSecDiffTimer timer1;
  ClockDiffTimer timer2;

  for(ulen cnt=10; cnt ;cnt--)
    {
     Task::Sleep(10_msec);

     Printf(Con,"MSec = #; Clock = #;\n",timer1.get(),timer2.get());
    }

  Printf(Con,"\n---\n\n");

  for(ulen cnt=10; cnt ;cnt--)
    {
     SlowSem sem;

     sem.take(10_msec);

     Printf(Con,"MSec = #; Clock = #;\n",timer1.get(),timer2.get());
    }

  return true;
 }

} // namespace App

