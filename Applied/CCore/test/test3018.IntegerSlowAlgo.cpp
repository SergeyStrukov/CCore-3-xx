/* test3018.IntegerSlowAlgo.cpp */
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

namespace App {

namespace Private_3018 {

/* types */

using Algo8 = Math::IntegerSlowAlgo<uint8> ;

using Algou = Math::IntegerSlowAlgo<unsigned> ;

} // namespace Private_3018

using namespace Private_3018;

/* Testit<3018> */

template<>
const char *const Testit<3018>::Name="Test3018 IntegerSlowAlgo";

template<>
bool Testit<3018>::Main()
 {
  TestIntegerAlgo<Algo8>().run(100'000);
  TestIntegerAlgo<Algou>().run(100'000);

  TestIntegerAlgo2<Algo8,Algo8>().run(10'000);

  return true;
 }

} // namespace App

