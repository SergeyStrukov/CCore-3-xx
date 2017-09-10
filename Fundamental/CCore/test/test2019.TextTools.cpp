/* test2019.TextTools.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Fundamental Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/TextTools.h>
#include <CCore/inc/Scanf.h>

namespace App {

namespace Private_2019 {

/* class Test */

class Test : public CharPropTable<bool,false>
 {
  public:

   Test()
    {
     setIf(CharIsHex,true);
    }
 };

/* test1() */

void test1()
 {
  Test test;

  for(int i=-128; i<128 ;i++)
    {
     char ch(i);

     Printf(Con,"#; #;\n",CharCode(ch),test[ch]);
    }
 }

/* test2() */

void test2()
 {
  StrLen str=
"Духовной жаждою томим\r\n\r"
"В пустыне мрачной я влачился\n\r"
"И шестикрылый серафим\r\r\n"
"На перепутье мне явился"_c;

  ScanString inp(str);

  while( inp.isOk() )
    {
     String s;

     Scanf(inp," #;",s);

     if( s.getLen()==0 ) break;

     auto pos=inp.getTextPos();

     Printf(Con,"#; #;\n",pos,s);
    }

  TextPos pos;

  pos.update("Духовной жаждою томим"_c);

  Printf(Con,"#;\n",pos);

  pos.update("\r\n\rВ пустыне мрачной я влачился"_c);

  Printf(Con,"#;\n",pos);

  pos.update("\n\rИ шестикрылый серафим"_c);

  Printf(Con,"#;\n",pos);

  pos.update("\r\r\nНа перепутье мне явился"_c);

  Printf(Con,"#;\n",pos);
 }

} // namespace Private_2019

using namespace Private_2019;

/* Testit<2019> */

template<>
const char *const Testit<2019>::Name="Test2019 TextTools";

template<>
bool Testit<2019>::Main()
 {
  //test1();
  test2();

  return true;
 }

} // namespace App

