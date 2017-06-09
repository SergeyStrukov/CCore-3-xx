/* test1027.Timer.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Simple Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/Timer.h>

namespace App {

/* Testit<1027> */

template<>
const char *const Testit<1027>::Name="Test1027 Time";

template<>
bool Testit<1027>::Main()
 {
  // 1

  {
   ClockDiffTimer::ValueType buf[20];

   ClockDiffTimer timer;

   for(auto &t : buf ) t=timer.get();

   for(auto t : buf ) Printf(Con,"#;\n",t);
  }

  // 2

  {
   SecDiffTimer sec_timer;
   MSecDiffTimer msec_timer;
   ClockDiffTimer clock_timer;

   for(ulen count=10; count ;count--)
     {
      while( sec_timer.get()==0 );

      auto t1=msec_timer.get();
      auto t2=clock_timer.get();

      Printf(Con,"#; #;\n",t1,t2);
     }
  }

  return true;
 }

} // namespace App

