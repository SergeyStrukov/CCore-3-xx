/* test1013.for.cpp */
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

#include <CCore/inc/Array.h>
#include <CCore/inc/PrintSet.h>

namespace App {

/* Testit<1013> */

template<>
const char *const Testit<1013>::Name="Test1013 for";

template<>
bool Testit<1013>::Main()
 {
  DynArray<int> buf(10);

  int i=1;

  for(int &x : buf) x=i++;

  Printf(Con,"buf = #;\n",PrintSet(Range(buf)));

  for(int &x : Range(buf).part(3,5) ) x=i++;

  Printf(Con,"buf = #;\n",PrintSet(Range(buf)));

  return true;
 }

} // namespace App

