/* test1019.PrintTime.cpp */
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

#include <CCore/inc/PrintTime.h>

namespace App {

/* Testit<1019> */

template<>
const char *const Testit<1019>::Name="Test1019 PrintTime";

template<>
bool Testit<1019>::Main()
 {
  Printf(Con,"#;\n",PrintTime(1u));
  Printf(Con,"#;\n",PrintTime(100u));
  Printf(Con,"#;\n",PrintTime(3661u));
  Printf(Con,"#;\n",PrintTime(10000u));
  Printf(Con,"#;\n",PrintTime(1000000u));

  return true;
 }

} // namespace App

