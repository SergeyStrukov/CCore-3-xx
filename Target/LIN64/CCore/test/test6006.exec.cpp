/* test6006.exec.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Target/LIN64
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/FileSystem.h>

namespace App {

/* Testit<6006> */

template<>
const char *const Testit<6006>::Name="Test6006 exec";

template<>
bool Testit<6006>::Main()
 {
  FileSystem fs;

  fs.exec(".","../../../tools/PTPServer/root/exectest.exe","1 2 '3 4 5' \"6 7 8\"");

  return true;
 }

} // namespace App

