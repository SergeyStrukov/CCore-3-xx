/* test3038.CmdlineParser.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.60
//
//  Tag: Applied
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/CmdlineParser.h>
#include <CCore/inc/Array.h>

namespace App {

namespace Private_3038 {

void show(StrLen text)
 {
  CmdlineParser parser(text);

  for(;;)
    {
     auto builder=parser.next();

     if( !builder ) break;

     DynArray<char> temp(DoBuild,builder);

     Printf(Con,"#.q;\n",StrLen(Range(temp)));
    }

  Putch(Con,'\n');
 }

} // namespace Private_3038

using namespace Private_3038;

/* Testit<3038> */

template<>
const char *const Testit<3038>::Name="Test3038 CmdlineParser";

template<>
bool Testit<3038>::Main()
 {
  show("123 456 abc"_c);
  show("'123' '456'abc ABC"_c);
  show("123 \"456 \\\" \\\\ \\t \" abc"_c);

  return true;
 }

} // namespace App

