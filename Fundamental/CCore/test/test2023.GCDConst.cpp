/* test2023.GCDConst.cpp */
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

#include <CCore/inc/algon/GCDConst.h>

namespace App {

/* Testit<2023> */

template<>
const char *const Testit<2023>::Name="Test2023 GCDConst";

template<>
bool Testit<2023>::Main()
 {
  Printf(Con,"#;\n",Algon::GCDConst<unsigned,100*19,100*12>);
  Printf(Con,"#;\n",Algon::LCMConst<unsigned,100*19,100*12>);

  return true;
 }

} // namespace App

