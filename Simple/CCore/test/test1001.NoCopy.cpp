/* test1001.NoCopy.cpp */
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

namespace App {

namespace Private_1001 {

struct Test : NoCopy
 {
  int a;
  int b;
 };

} // namespace Private_1001

using namespace Private_1001;

/* Testit<1001> */

template<>
const char *const Testit<1001>::Name="Test1001 NoCopy";

template<>
bool Testit<1001>::Main()
 {
  Printf(Con,"copy constructible = #;\n",std::is_copy_constructible<Test>::value);
  Printf(Con,"copy assignable = #;\n",std::is_copy_assignable<Test>::value);
  Printf(Con,"move constructible = #;\n",std::is_move_constructible<Test>::value);
  Printf(Con,"move assignable = #;\n",std::is_move_assignable<Test>::value);

  return true;
 }

} // namespace App

