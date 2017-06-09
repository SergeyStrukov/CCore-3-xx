/* test2026.Partition.cpp */
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

#include <CCore/inc/algon/Partition.h>
#include <CCore/inc/PrintSet.h>

namespace App {

namespace Private_2026 {


} // namespace Private_2026

using namespace Private_2026;

/* Testit<2026> */

template<>
const char *const Testit<2026>::Name="Test2026 Partition";

template<>
bool Testit<2026>::Main()
 {
  int buf[]={1,2,3,4,5,6,7,8,9};

  ulen count=Algon::Partition(Range(buf), [] (int a) { return a%2; } );

  Printf(Con,"#; #;\n",PrintSet(Range(buf)),count);

  return true;
 }

} // namespace App

