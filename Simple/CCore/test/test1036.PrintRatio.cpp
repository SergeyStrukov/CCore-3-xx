/* test1036.PrintRatio.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Simple
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/Print.h>
#include <CCore/inc/PrintRatio.h>

namespace App {

namespace Private_1036 {


} // namespace Private_1036

using namespace Private_1036;

/* Testit<1036> */

template<>
const char *const Testit<1036>::Name="Test1036 PrintRatio";

template<>
bool Testit<1036>::Main()
 {
  Printf(Con,"--- #; ---\n",PrintRatio(10u,3u));
  Printf(Con,"--- #+; ---\n",PrintRatio(10u,3u));
  Printf(Con,"--- #+.10; ---\n",PrintRatio(10u,3u));

  Printf(Con,"--- #20; ---\n",PrintRatio(10u,3u));
  Printf(Con,"--- #+20; ---\n",PrintRatio(10u,3u));
  Printf(Con,"--- #+20.10; ---\n",PrintRatio(10u,3u));

  Printf(Con,"--- #20l; ---\n",PrintRatio(10u,3u));
  Printf(Con,"--- #+20l; ---\n",PrintRatio(10u,3u));
  Printf(Con,"--- #+20.10l; ---\n",PrintRatio(10u,3u));

  Printf(Con,"--- #20i; ---\n",PrintRatio(10u,3u));
  Printf(Con,"--- #+20i; ---\n",PrintRatio(10u,3u));
  Printf(Con,"--- #+20.10i; ---\n",PrintRatio(10u,3u));

  return true;
 }

} // namespace App

