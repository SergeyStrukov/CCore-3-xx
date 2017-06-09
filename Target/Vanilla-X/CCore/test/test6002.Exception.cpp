/* test6002.Exception.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Target/Vanilla-X
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>
#include <CCore/test/testRun.h>

namespace App {

namespace Private_6002 {

/* testException() */

void testException()
 {
  SilentReportException report;

  ulen count=0;

  for(ulen cnt=100000; cnt ;cnt--)
    try
      {
       Printf(Exception,"some exception");
      }
    catch(CatchType)
      {
       count++;
      }

  Printf(Con,"count = #;\n",count);
 }

} // namespace Private_6002

using namespace Private_6002;

/* Testit<6002> */

template<>
const char *const Testit<6002>::Name="Test6002 Exception";

template<>
bool Testit<6002>::Main()
 {
  RunTask run_task;

  run_task(ulen(10),testException);

  return true;
 }

} // namespace App

