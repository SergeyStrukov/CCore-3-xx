/* test6003.Blank.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Target/WIN64utf8
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/math/IntegerFastAlgo.h>

namespace App {

namespace Private_6003 {


} // namespace Private_6003

using namespace Private_6003;

/* Testit<6003> */

template<>
const char *const Testit<6003>::Name="Test6003 Blank";

template<>
bool Testit<6003>::Main()
 {
  Printf(Con,"#;\n",+Math::IntegerFastAlgo::UnitBits);

  return true;
 }

} // namespace App

