/* test1003.Blank.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
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

namespace App {

namespace Private_1003 {


} // namespace Private_1003

using namespace Private_1003;

/* Testit<1003> */

template<>
const char *const Testit<1003>::Name="Test1003 Meta Detect";

template<>
bool Testit<1003>::Main()
 {
  return true;
 }

} // namespace App

