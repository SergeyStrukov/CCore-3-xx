/* test1002.CreateAt.cpp */
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

namespace Private_1002 {

struct Type1
 {
  int a;

  explicit Type1(int a_) : a(a_) {}
 };

struct Type2
 {
  int a;
  int b;

  Type2(int a_,int b_) : a(a_),b(b_) {}
 };

union Test
 {
  Type1 t1;
  Type2 t2;

  Test() {}
 };

} // namespace Private_1002

using namespace Private_1002;

/* Testit<1002> */

template<>
const char *const Testit<1002>::Name="Test1002 CreateAt";

template<>
bool Testit<1002>::Main()
 {
  Test test;

  CreateAt(test.t1,12345);
  CreateAt(test.t2,12345,67890);

  return true;
 }

} // namespace App

