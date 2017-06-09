/* test4016.PrintFile.cpp */
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

namespace App {

/* Testit<4016> */

template<>
const char *const Testit<4016>::Name="Test4016 PrintFile";

template<>
bool Testit<4016>::Main()
 {
  PrintFile out("testPrintFile.txt",Open_ToWrite|Open_AutoDelete);

  for(ulen i=0; i<100'000 ;i++)
    Printf(out,"--- Line #10l; -----------------------------------\n",i);

  out.preserveFile();

  out.close();

  return true;
 }

} // namespace App

