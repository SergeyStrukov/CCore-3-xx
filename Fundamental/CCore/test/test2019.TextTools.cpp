/* test2019.TextTools.cpp */
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

#include <CCore/inc/TextTools.h>

namespace App {

namespace Private_2019 {

class Test : public CharPropTable<bool,false>
 {
  public:

   Test()
    {
     setIf(CharIsHex,true);
    }
 };

} // namespace Private_2019

using namespace Private_2019;

/* Testit<2019> */

template<>
const char *const Testit<2019>::Name="Test2019 TextTools";

template<>
bool Testit<2019>::Main()
 {
  Test test;

  for(int i=-128; i<128 ;i++)
    {
     char ch(i);

     Printf(Con,"#; #;\n",CharCode(ch),test[ch]);
    }

  return true;
 }

} // namespace App

