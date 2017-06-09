/* test2020.BinarySearch.cpp */
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

#include <CCore/inc/algon/BinarySearch.h>

namespace App {

/* Testit<2020> */

template<>
const char *const Testit<2020>::Name="Test2020 BinarySearch";

template<>
bool Testit<2020>::Main()
 {
  const int Len = 10 ;

  int buf[Len];

  for(int i=0; i<Len ;i++) buf[i]=i;

  for(int i=0; i<=Len ;i++)
    {
     PtrLen<int> r=Range(buf);

     Algon::BinarySearch_greater_or_equal(r,i);

     Printf(Con,"i = #; , found ",i);

     if( +r ) Printf(Con,"#;\n",*r); else Printf(Con,"none\n");
    }

  return true;
 }

} // namespace App

