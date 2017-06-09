/* test3020.IntegerFastAlgo.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Applied
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>
#include <CCore/test/testIntAlgo.h>
#include <CCore/test/testInt.h>

#include <CCore/inc/math/IntegerFastAlgo.h>

namespace App {

namespace Private_3020 {

/* types */

using Fast = Math::IntegerFastAlgo ;

using Slow = Math::IntegerSlowAlgo<Fast::Unit> ;

} // namespace Private_3020

using namespace Private_3020;

/* Testit<3020> */

template<>
const char *const Testit<3020>::Name="Test3020 IntegerFastAlgo";

template<>
bool Testit<3020>::Main()
 {
  TestIntegerAlgo<Fast>().run(100'000);

  TestIntegerAlgo2<Fast,Slow>().run(10'000);

  TestInteger<Fast>().run(10'000);

  return true;
 }

} // namespace App

