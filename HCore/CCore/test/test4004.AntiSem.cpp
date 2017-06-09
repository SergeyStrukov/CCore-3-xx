/* test4004.AntiSem.cpp */
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

namespace App {

namespace Private_4004 {

/* class Test */

class Test : public Funchor_nocopy
 {
   AntiSem asem;

  private:

   void dec()
    {
     Task::Sleep(3_sec);

     asem.dec();

     Printf(Con,"dec()\n");
    }

   void wait()
    {
     asem.wait();

     Printf(Con,"wait()\n");
    }

  public:

   Test()
    : asem("testASem")
    {
     asem.inc();
    }

   Function<void (void)> function_dec() { return FunctionOf(this,&Test::dec); }

   Function<void (void)> function_wait() { return FunctionOf(this,&Test::wait); }

   void run()
    {
     RunTask run_task;

     run_task(function_dec());
     run_task(function_wait());
     run_task(function_wait());
     run_task(function_wait());
    }
 };

} // namespace Private_4004

using namespace Private_4004;

/* Testit<4004> */

template<>
const char *const Testit<4004>::Name="Test4004 AntiSem";

template<>
bool Testit<4004>::Main()
 {
  Test test;

  test.run();

  return true;
 }

} // namespace App

