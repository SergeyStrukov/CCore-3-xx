/* test1004.Function.cpp */
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

namespace Private_1004 {

struct Test1
 {
  int a;

  Test1() : a(12345) {}
 };

struct Test : Test1 , Funchor
 {
  int a;

  Test() : a(67890) {}

  void print()
   {
    Printf(Con,"#;\n",a);
   }

  Function<void (void)> function_print() { return FunctionOf(this,&Test::print); }
 };

} // namespace Private_1004

using namespace Private_1004;

/* Testit<1004> */

template<>
const char *const Testit<1004>::Name="Test1004 Function";

template<>
bool Testit<1004>::Main()
 {
  Test test;

  test.print();

  test.function_print()();

  return true;
 }

} // namespace App

