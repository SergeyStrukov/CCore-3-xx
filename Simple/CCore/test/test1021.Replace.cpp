/* test1021.Replace.cpp */
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

/* Testit<1021> */

template<>
const char *const Testit<1021>::Name="Test1021 Replace";

template<>
bool Testit<1021>::Main()
 {
  int x=2;

  int y=Replace_gen( [] (int x) -> int { return x*5; } ,x);

  Printf(Con,"x = #; y = #;\n",x,y);

  return true;
 }

} // namespace App

