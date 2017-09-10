/* test4011.ReadCon.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: HCore Mini
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
#include <CCore/inc/Utf8.h>

namespace App {

/* Testit<4011> */

template<>
const char *const Testit<4011>::Name="Test4011 ReadCon";

[[maybe_unused]]
static bool Is(Utf8Code ch,uint8 ch1)
 {
  return ch.getLen()==1 && ch[0]==ch1 ;
 }

[[maybe_unused]]
static bool Is(uint8 ch,uint8 ch1)
 {
  return ch==ch1 ;
 }

template<>
bool Testit<4011>::Main()
 {
  ReadCon con;

  con.put("Type 'x' to stop\n\n");

  for(ReadConCode ch; !Is(ch=con.get(),'x') ;)
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

     if( Is(ch,'x') ) break;

     Printf(Con,"#;\n",ExtCharCode(ch));
    }

  return true;
 }

} // namespace App
