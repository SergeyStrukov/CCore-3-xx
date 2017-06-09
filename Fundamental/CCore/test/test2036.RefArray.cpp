/* test2036.RefArray.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Fundamental Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>
#include <CCore/test/testArray.h>

namespace App {

/* Testit<2036> */

template<>
const char *const Testit<2036>::Name="Test2036 RefArray";

template<>
bool Testit<2036>::Main()
 {
  const int buf[]={1,2,3,4,5};

  RefArray<int> a;
  RefArray<int> b(a);

  Show(a);

  a.extend_default(2);

  Show(a);

  a.extend_fill(5,23);

  Show(a);

  a.extend_copy(5,buf);

  Show(a);

  Show(b);

  b=a;

  a.extend_default(5);

  Show(a);
  Show(b);

  b=a;

  a.shrink(12);

  Show(a);
  Show(b);

  b=a;

  a.modify().set(13);

  Show(a);
  Show(b);

  return true;
 }

} // namespace App

