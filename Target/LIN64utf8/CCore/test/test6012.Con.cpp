/* test6012.Con.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Target/LIN64utf8
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

namespace App {

namespace Private_6012 {


} // namespace Private_6012

using namespace Private_6012;

/* Testit<6012> */

template<>
const char *const Testit<6012>::Name="Test6012 Con";

template<>
bool Testit<6012>::Main()
 {
  StrLen text="Русский текст"_c;

  Printf(Con,"#;\n",text);

  Printf(Con,"#;\n",StrLen(text.prefix(2)));
  Printf(Con,"#;\n",StrLen(text.prefix(3)));
  Printf(Con,"#;\n",StrLen(text.prefix(4)));

  Printf(Con,"#;",StrLen(text.prefix(1)));
  Printf(Con,"#;\n",StrLen(text.part(1)));

  return true;
 }

} // namespace App

