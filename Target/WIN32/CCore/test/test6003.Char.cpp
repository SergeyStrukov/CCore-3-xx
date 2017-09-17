/* test6003.Char.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: Target/WIN32
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/video/Desktop.h>

#include <CCore/inc/Sort.h>
#include <CCore/inc/CharProp.h>

namespace App {

namespace Private_6003 {


} // namespace Private_6003

using namespace Private_6003;

/* Testit<6003> */

template<>
const char *const Testit<6003>::Name="Test6003 Char";

template<>
bool Testit<6003>::Main()
 {
  char temp[256];

  for(int i=0; i<256 ;i++) temp[i]=char(i);

  for(int i=0; i<256 ;i++)
    {
     Printf(Con,"#;) #; #;\n",i,CharCode(temp[i]),CharCode(Video::ToLowerCase(temp[i])));
    }

  return true;
 }

} // namespace App

