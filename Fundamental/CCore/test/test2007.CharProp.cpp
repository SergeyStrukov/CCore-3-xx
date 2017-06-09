/* test2007.CharProp.cpp */
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

#include <CCore/inc/CharProp.h>

namespace App {

/* Testit<2007> */

template<>
const char *const Testit<2007>::Name="Test2007 CharProp";

template<>
bool Testit<2007>::Main()
 {
  for(uint8 ch=0; ch<128 ;ch++)
    {
     CharCode code(ch);

     Printf(Con,"#;",code);

     if( code.isSpecial() ) Printf(Con," special");

     if( code.isVisible() ) Printf(Con," visible");

     if( code.isSpace() ) Printf(Con," space");

     if( code.isPunct() ) Printf(Con," punct");

     if( code.isSpaceOrPunct() ) Printf(Con," space-or-punct");

     int dec=code.decValue();

     if( dec>=0 ) Printf(Con," dec = #;",dec);

     int hex=code.hexValue();

     if( hex>=0 ) Printf(Con," hex = #;",hex);

     Printf(Con,"\n");
    }

  return true;
 }

} // namespace App

