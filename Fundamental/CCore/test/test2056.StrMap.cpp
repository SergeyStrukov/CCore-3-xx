/* test2056.StrMap.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: Fundamental
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/StrMap.h>

namespace App {

namespace Private_2056 {

/* class Test */

class Test : public StrMap<StrLen>
 {
   using StrMap<StrLen>::add;

   void add(StrLen str) { add(str,str); }

  public:

   Test()
    {
     add("name"_c);
     add("nouse"_c);
     add("net"_c);
     add("network"_c);
     add("abs"_c);
     add("absolute"_c);

     complete();
    }

   void show(StrLen key) const
    {
     const StrLen *obj=(*this)[key];

     if( obj )
       Printf(Con,"#; = #;\n",key,*obj);
     else
       Printf(Con,"#;\n",key);
    }
 };

} // namespace Private_2056

using namespace Private_2056;

/* Testit<2056> */

template<>
const char *const Testit<2056>::Name="Test2056 StrMap";

template<>
bool Testit<2056>::Main()
 {
  Test test;

  test.show("name"_c);
  test.show("nouse"_c);
  test.show("net"_c);
  test.show("network"_c);
  test.show("abs"_c);
  test.show("absolute"_c);
  test.show("some"_c);

  return true;
 }

} // namespace App

