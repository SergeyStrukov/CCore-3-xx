/* test5014.ReadCon.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: XCore
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/ReadCon.h>
#include <CCore/inc/CharProp.h>

namespace App {

/* Testit<5014> */

template<>
const char *const Testit<5014>::Name="Test5014 ReadCon";

template<>
bool Testit<5014>::Main()
 {
  ReadCon con;

  con.put("Type 'x' to stop\n\n");

  for(ReadConCode ch; ToChar(ch=con.get())!='x' ;)
    {
     Printf(Con,"#;\n",ExtCharCode(ch));
    }

  con.put("Type 'x' to exit\n\n");

  for(ReadConCode ch;;)
    {
     if( !con.get(3_sec,ch) )
       {
        Printf(Con,"input timeout\n");

        continue;
       }

     if( ToChar(ch)=='x' ) break;

     Printf(Con,"#;\n",ExtCharCode(ch));
    }

  return true;
 }

} // namespace App

