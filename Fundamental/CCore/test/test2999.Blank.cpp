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

#include <CCore/inc/video/pref/ColorListWindow.h>
#include <CCore/inc/Print.h>
#include <CCore/inc/ForLoop.h>

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
  PrintFile out("ColorSet.ddl");

  Video::ColorSet set;

  for(ulen i : IndLim(set->getLineCount()) )
    {
     auto line=set->getLine(i);

     Printf(out,"VColor #16l; = #8.hi; ;\n",line.name,line.vc);
    }

  return true;
 }

} // namespace App

