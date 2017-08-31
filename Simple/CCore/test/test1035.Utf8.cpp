/* test1035.Utf8.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Simple Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/Utf8.h>
#include <CCore/inc/LaunchPath.h>

namespace App {

namespace Private_1035 {


} // namespace Private_1035

using namespace Private_1035;

/* Testit<1035> */

template<>
const char *const Testit<1035>::Name="Test1035 Utf8";

template<>
bool Testit<1035>::Main()
 {
  Printf(Con,"Русский текст\n");

  LaunchPath path;

  Printf(Con,"#;\n",path.getPath());

  return true;
 }

} // namespace App

