/* test2008.Exception.cpp */
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
#include <CCore/test/testRun.h>

namespace App {

namespace Private_2008 {

/* testException() */

void testException()
 {
  SilentReportException report;

  ulen total=0;

  for(ulen count=100'000; count ;count--)
    try
      {
       Printf(Exception,"some exception");
      }
    catch(CatchType)
      {
       total++;
      }

  Printf(Con,"total = #;\n",total);
 }

} // namespace Private_2008

using namespace Private_2008;

/* Testit<2008> */

template<>
const char *const Testit<2008>::Name="Test2008 Exception";

template<>
bool Testit<2008>::Main()
 {
  const ulen TaskCount = 10 ;

  RunTask run_task;

  run_task(TaskCount,testException);

  return true;
 }

} // namespace App

