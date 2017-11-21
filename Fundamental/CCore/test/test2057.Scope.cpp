/* test2057.Scope.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Fundamental Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/Scope.h>

namespace App {

namespace Private_2057 {


} // namespace Private_2057

using namespace Private_2057;

/* Testit<2057> */

template<>
const char *const Testit<2057>::Name="Test2057 Scope";

template<>
bool Testit<2057>::Main()
 {
  Scope a("outer"_c);
  Scope b("medium"_c);
  Scope c("inner"_c);

  try
    {
     Printf(Exception,"test exception");
    }
  catch(CatchType) {}

  ReportException::Clear();

  return true;
 }

} // namespace App

