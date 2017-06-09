/* test6008.Time.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Target/WIN64
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

/* Testit<6008> */

template<>
const char *const Testit<6008>::Name="Test6008 Time";

template<>
bool Testit<6008>::Main()
 {
  SecDiffTimer timer;

  SecDiffTimer t1;
  MSecDiffTimer t2;
  ClockDiffTimer t3;

  for(ulen count=10; count ;count--)
    {
     while( !timer.get() );

     Printf(Con,"#; #; #;\n",t1.get(),t2.get(),t3.get());
    }

  return true;
 }

} // namespace App

