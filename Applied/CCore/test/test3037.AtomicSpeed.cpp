/* test3037.AtomicSpeed.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.60
//
//  Tag: Applied
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/task/Atomic.h>

namespace App {

namespace Private_3037 {


} // namespace Private_3037

using namespace Private_3037;

/* Testit<3037> */

template<>
const char *const Testit<3037>::Name="Test3037 AtomicSpeed";

template<>
bool Testit<3037>::Main()
 {
  // 1

  {
   Atomic test;

   ClockTimer timer;

   for(ulen cnt=1000; cnt ;cnt--) test++;

   Printf(Con,"#;\n",timer.get());
  }

  // 2

  {
   volatile unsigned test = 0 ;

   ClockTimer timer;

   for(ulen cnt=1000; cnt ;cnt--) test++;

   Printf(Con,"#;\n",timer.get());
  }

  return true;
 }

} // namespace App

