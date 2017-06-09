/* test5013.ForcedTimeout.cpp */
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

namespace App {

/* Testit<5013> */

template<>
const char *const Testit<5013>::Name="Test5013 ForcedTimeout";

template<>
bool Testit<5013>::Main()
 {
  ForcedTimeout fto;

  Ticker ticker(fto.function_abort_int());

  ticker.start(3_sec);

  Sem sem;

  sem.take(100_sec);
  //sem.take();

  Printf(Con,"done #;\n",fto.clear());

  return true;
 }

} // namespace App

