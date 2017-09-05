/* test6003.Char.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Target/WIN32utf8
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/Utf8.h>
#include <CCore/inc/Sort.h>
#include <CCore/inc/Array.h>

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
  StrLen text="абвгдеёжзийклмнопрстуфхцчшщъыьэюя"
              "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"_c;

  DynArray<Unicode> buf;

  while( +text ) buf.append_copy(CutUtf8_unicode(text));

  Sort(Range(buf));

  for(Unicode sym : buf ) Putobj(Con,ToUtf8(sym));

  Putch(Con,'\n');

  return true;
 }

} // namespace App

