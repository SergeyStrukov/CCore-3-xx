/* test2002.Exception.cpp */
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

#include <CCore/inc/Abort.h>
#include <CCore/inc/MemBase.h>

#include <new>

namespace App {

namespace Private_2002 {

/* class Test1 */

class Test1
 {
  public:

   ~Test1()
    {
     Printf(NoException,"~Test1()");
    }
 };

/* class Test2 */

class Test2 : Test1
 {
  public:

   ~Test2()
    {
     Printf(NoException,"~Test2()");
    }
 };

/* class TestReport */

class TestReport : public ReportException
 {
   virtual void start(ExceptionType ex)
    {
     print("TestReport) ");
     print(GetTextDesc(ex));
    }
 };

} // namespace Private_2002

using namespace Private_2002;

/* Testit<2002> */

template<>
const char *const Testit<2002>::Name="Test2002 Exception";

template<>
bool Testit<2002>::Main()
 {
  //Abort("abort");

  try
    {
     TestReport report;
     //SilentReportException report;

     {
      Test2 test;

      Used(test);

      Printf(Exception,"exception");
     }

     report.guard();
    }
  catch(CatchType)
    {
     Printf(Con,"catch\n\n");
    }

  try
    {
     GuardNoMem(1000);
    }
  catch(std::bad_alloc &)
    {
     Printf(Con,"catch bad_alloc\n\n");
    }
  catch(CatchType)
    {
     Printf(Con,"catch\n\n");
    }

  try
    {
     GuardNoMem(1000);
    }
  catch(CatchType)
    {
     Printf(Con,"catch\n\n");
    }
  catch(std::bad_alloc &)
    {
     Printf(Con,"catch bad_alloc\n\n");
    }

  ReportException::Clear();

  return true;
 }

} // namespace App

