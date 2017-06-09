/* test1018.PrintSet.cpp */
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

#include <CCore/inc/PrintSet.h>
#include <CCore/inc/List.h>

namespace App {

namespace Private_1018 {

/* struct Test */

struct Test
 {
  SLink<Test> link;
  unsigned value;

  using PrintProxyType = unsigned ;

  operator unsigned() const { return value; }
 };

} // namespace Private_1018

using namespace Private_1018;

/* Testit<1018> */

template<>
const char *const Testit<1018>::Name="Test1018 PrintSet";

template<>
bool Testit<1018>::Main()
 {
  {
   int data[]={-1,2,-3,4,-5,6,-7,8,-9,10};

   Printf(Con,"#;\n",PrintSet(Range(data)));
   Printf(Con,"#+3;\n",PrintSet(RangeReverse(data)));
  }

  {
   using Algo = SLink<Test>::LinearAlgo<&Test::link> ;

   Test test[10];
   Algo::Top top;

   for(unsigned i=0; i<DimOf(test) ;i++)
     {
      test[i].value=i;

      top.ins(test+i);
     }

   Printf(Con,"#;\n",PrintSet(top.start()));
  }

  return true;
 }

} // namespace App

