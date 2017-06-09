/* test6004.Timer.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Target/Vanilla-X
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/Timer.h>
#include <CCore/inc/Task.h>

namespace App {

/* Testit<6004> */

template<>
const char *const Testit<6004>::Name="Test6004 Timer";

template<>
bool Testit<6004>::Main()
 {
  ClockDiffTimer timer;

  for(ulen cnt=300; cnt ;cnt--)
    {
     Printf(Con,"#;\n",timer.get());

     Task::Sleep(10000_msec);
    }

  return true;
 }

} // namespace App

