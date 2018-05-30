/* test6011.Char.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Target/WIN64utf8
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/video/Desktop.h>
#include <CCore/inc/ReadCon.h>

namespace App {

namespace Private_6011 {


} // namespace Private_6011

using namespace Private_6011;

/* Testit<6011> */

template<>
const char *const Testit<6011>::Name="Test6011 Char";

template<>
bool Testit<6011>::Main()
 {
  ReadCon con;

  con.put("Type 'x' to exit\n\n");

  for(Symbol ch; ToChar(ch=con.get())!='x' ;)
    {
     Char uch=ch.toUnicode();

     Char lch=Video::ToLowerCase(uch);

     Printf(Con,"#; #; #;\n",ExtCharCode(ch),ExtCharCode(lch));
    }

  return true;
 }

} // namespace App

