/* test6002.SysError.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Target/WIN32
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/PrintError.h>

namespace App {

/* Testit<6002> */

template<>
const char *const Testit<6002>::Name="Test6002 SysError";

template<>
bool Testit<6002>::Main()
 {
  for(int e=1; e<100 ;e++) Printf(Con,"#;\n",PrintError(Sys::ErrorType(e)));

  return true;
 }

} // namespace App

