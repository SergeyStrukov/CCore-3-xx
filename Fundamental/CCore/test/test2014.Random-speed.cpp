/* test2014.Random-speed.cpp */
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

#include <CCore/inc/Random.h>
#include <CCore/inc/Timer.h>

namespace App {

/* Testit<2014> */

template<>
const char *const Testit<2014>::Name="Test2014 Random speed";

template<>
bool Testit<2014>::Main()
 {
  Random random;
  uint8 sum=0;

  SecTimer timer;

  for(ulen count=1'000'000'000; count ;count--) sum+=random.next8();

  auto time=timer.get();

  Printf(Con,"time = #; sec\n",time,sum);

  return true;
 }

} // namespace App

