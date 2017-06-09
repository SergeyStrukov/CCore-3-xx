/* test2025.SimpleRotate.cpp */
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

#include <CCore/inc/algon/SimpleRotate.h>
#include <CCore/inc/PrintSet.h>

namespace App {

/* Testit<2025> */

template<>
const char *const Testit<2025>::Name="Test2025 SimpleRotate";

template<>
bool Testit<2025>::Main()
 {
  int buf[]={1,2,3,4,5};

  Printf(Con,"#;\n",PrintSet(Range(buf)));

  Algon::RangeRotateLeft(Range(buf));

  Printf(Con,"#;\n",PrintSet(Range(buf)));

  Algon::RangeRotateRight(Range(buf));

  Printf(Con,"#;\n",PrintSet(Range(buf)));

  return true;
 }

} // namespace App

