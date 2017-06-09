/* test2500.PrintFile.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Fundamental Mini
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

namespace App {

namespace Private_2500 {

/* TestPrint() */

template <class P>
void TestPrint(P &&out)
 {
  for(int i=0; i<10000 ;i++)
    Printf(out,"--- #4; ---------------------------------------\n",i);
 }

} // namespace Private_2500

using namespace Private_2500;

/* Testit<2500> */

template<>
const char *const Testit<2500>::Name="Test2500 PrintFile";

template<>
bool Testit<2500>::Main()
 {
  TestPrint(Con);

  TaskEventRecorder recorder(100_MByte);

  {
   TickTask tick_task;
   TaskEventHostType::StartStop event_start_stop(TaskEventHost,&recorder);

   PrintFile out("testPrintFile.txt");

   TestPrint(out);
  }

  BinaryFile dev("test2500.bin");

  dev(recorder);

  return true;
 }

} // namespace App

