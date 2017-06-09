/* test5011.Ticker.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: XCore
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/Task.h>
#include <CCore/inc/Timer.h>

namespace App {

namespace Private_5011 {

/* Func() */

void Func()
 {
  SecTimer timer;
  Event event;
  Ticker ticker(event.function_trigger_int());

  ticker.start(5_sec,2_sec);

  for(ulen cnt=10; cnt ;cnt--)
    {
     event.wait();

     Printf(Con,"timer = #; sec\n",timer.get());
    }
 }

} // namespace Private_5011

using namespace Private_5011;

/* Testit<5011> */

template<>
const char *const Testit<5011>::Name="Test5011 Ticker";

template<>
bool Testit<5011>::Main()
 {
  Event stop_event;

  RunFuncTask(Function<void (void)>(Func),stop_event.function_trigger());

  stop_event.wait();

  return true;
 }

} // namespace App

