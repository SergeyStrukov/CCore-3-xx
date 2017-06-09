/* test4017.ScanFile.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: HCore Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/Scan.h>

namespace App {

/* Testit<4017> */

template<>
const char *const Testit<4017>::Name="Test4017 ScanFile";

template<>
bool Testit<4017>::Main()
 {
  ScanFile scan("Makefile");
  PrintFile out("test4017.txt");

  for(; +scan ;++scan)
    Printf(out,"#; #;\n",CharCode(*scan),scan.getTextPos());

  scan.close();

  scan.open("Makefile",true);

  for(; +scan ;++scan)
    Printf(out,"#; #;\n",CharCode(*scan),scan.getTextPos());

  return true;
 }

} // namespace App

