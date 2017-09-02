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

#include <CCore/inc/PrintTitle.h>
#include <CCore/inc/CapString.h>

#include <CCore/inc/Utf8.h>

namespace App {

namespace Private_1035 {

/* test1() */

void test1()
 {
  Printf(Con,"Русский текст\n");

  Printf(Con,"#.c;",0xD1);
  Printf(Con,"#.c;\n",0x83);

  Printf(Con,"*** #20l; ***\n","text");
  Printf(Con,"*** #20c; ***\n","text");
  Printf(Con,"*** #20r; ***\n","text");

  Printf(Con,"*** #20l; ***\n","успех");
  Printf(Con,"*** #20c; ***\n","успех");
  Printf(Con,"*** #20r; ***\n","успех");

  Printf(Con,"#;\n",Title("title"));
  Printf(Con,"#;\n",Title("успех"));

  Printf(Con,"#;\n",PrintTitle("title"));
  Printf(Con,"#;\n",PrintTitle("успех"));
 }

/* test2() */

void test2()
 {
  CapString<10> cap("Русский текст");

  Printf(Con,"#.q;\n",(const char *)cap);
 }

/* test3() */

void test3()
 {
  for(Unicode unicode=0; unicode<Bit(21) ;unicode++)
    {
     Utf8Code code=ToUtf8(unicode);

     if( code.toUnicode()!=unicode )
       {
        Printf(Exception,"Failed #.h;\n",unicode);
       }
    }
 }

} // namespace Private_1035

using namespace Private_1035;

/* Testit<1035> */

template<>
const char *const Testit<1035>::Name="Test1035 Utf8";

template<>
bool Testit<1035>::Main()
 {
  //test1();
  //test2();
  //test3();

  return true;
 }

} // namespace App

