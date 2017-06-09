/* test1005.NoThrowFlags.cpp */
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

namespace Private_1005 {

struct Test1
 {
  int a = 0 ;

  Test1() noexcept {}
 };

struct Test2 : SetNoThrowFlags<Test2,true,false>
 {
 };

struct Test3
 {
  Test3() {}
 };

template <class T>
void Show()
 {
  Printf(Con,"default #; copy #;\n",GetNoThrowFlags<T>::Default_no_throw,GetNoThrowFlags<T>::Copy_no_throw);
 }

} // namespace Private_1005

using namespace Private_1005;

/* Testit<1005> */

template<>
const char *const Testit<1005>::Name="Test1005 NoThrowFlags";

template<>
bool Testit<1005>::Main()
 {
  Show<Test1>();
  Show<Test2>();
  //Show<Test3>(); // warning

  return true;
 }

} // namespace App

