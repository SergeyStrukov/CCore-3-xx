/* test1007.FunctorType.cpp */
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

#include <CCore/inc/FunctorType.h>

namespace App {

namespace Private_1007 {

struct Test1
 {
  static const char *Name;
 };

const char * Test1::Name="Test1";

struct Test2
 {
  static const char *Name;

  using FunctorType = Test1 ;
 };

const char * Test2::Name="Test2";

} // namespace Private_1007

using namespace Private_1007;

/* Testit<1007> */

template<>
const char *const Testit<1007>::Name="Test1007 FunctorType";

template<>
bool Testit<1007>::Main()
 {
  Printf(Con,"#;\n",FunctorTypeOf<Test1>::Name);
  Printf(Con,"#;\n",FunctorTypeOf<Test2>::Name);

  return true;
 }

} // namespace App

