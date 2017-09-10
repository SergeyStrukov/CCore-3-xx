/* test4033.exec.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: HCore
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/FileSystem.h>

namespace App {

namespace Private_4033 {


} // namespace Private_4033

using namespace Private_4033;

/* Testit<4033> */

template<>
const char *const Testit<4033>::Name="Test4033 exec";

template<>
bool Testit<4033>::Main()
 {
  FileSystem fs;

  fs.exec("."_c,"../../../tools/PTPServer/root/exectest.exe"_c,"ключ гайка молоток"_c);

  return true;
 }

} // namespace App

