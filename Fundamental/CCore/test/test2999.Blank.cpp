/* test2999.Blank.cpp */
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

#include <CCore/inc/video/Desktop.h>
#include <CCore/inc/PrintSet.h>

namespace App {

namespace Private_2999 {


} // namespace Private_2999

using namespace Private_2999;

/* Testit<2999> */

template<>
const char *const Testit<2999>::Name="Test2999 Blank";

template<>
bool Testit<2999>::Main()
 {
  Video::HomeDir temp1;

  Printf(Con,"#.q;\n",temp1.get());

  Video::SystemFontDirs temp2;

  Printf(Con,"#.q;\n",PrintSet(temp2.getList()));

  return true;
 }

} // namespace App

