/* test3033.IntegerSpeed.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Applied
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2011 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>
#include <CCore/test/testIntSpeed.h>

#include <CCore/inc/math/IntegerSlowAlgo.h>
#include <CCore/inc/math/IntegerFastAlgo.h>

namespace App {

namespace Private_3033 {

/* types */

using Fast = Math::IntegerFastAlgo ;

using Slow = Math::IntegerSlowAlgo<Fast::Unit> ;

} // namespace Private_3033

using namespace Private_3033;

/* Testit<3033> */

template<>
const char *const Testit<3033>::Name="Test3033 Integer speed";

template<>
bool Testit<3033>::Main()
 {
  PrintFile out("test3033.txt");

  TestIntegerSpeed<Fast>::Run(out,"Fast");
  TestIntegerSpeed<Slow>::Run(out,"Slow");

  return true;
 }

} // namespace App

