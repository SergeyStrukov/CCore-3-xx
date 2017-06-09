/* test5014.ReadCon.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: XCore
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
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

  for(char ch; (ch=con.get())!='x' ;)
    {
     Printf(Con,"#;\n",CharCode(ch));
    }

  con.put("Type 'x' to exit\n\n");

  for(char ch;;)
    {
     if( !con.get(3_sec,ch) )
       {
        Printf(Con,"input timeout\n");

        continue;
       }

     if( ch=='x' ) break;

     Printf(Con,"#;\n",CharCode(ch));
    }

  return true;
 }

} // namespace App

