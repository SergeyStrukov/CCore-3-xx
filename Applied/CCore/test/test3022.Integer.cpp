/* test3022.Integer.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Applied
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>
#include <CCore/test/testInt.h>

#include <CCore/inc/math/IntegerSlowAlgo.h>

namespace App {

namespace Private_3022 {

/* types */

using Algo8 = Math::IntegerSlowAlgo<uint8> ;

using Algou = Math::IntegerSlowAlgo<unsigned> ;

} // namespace Private_3022

using namespace Private_3022;

/* Testit<3022> */

template<>
const char *const Testit<3022>::Name="Test3022 Integer";

template<>
bool Testit<3022>::Main()
 {
  TestInteger<Algou>().run(10'000);
  TestInteger<Algo8>().run(10'000);

  // show

  using Int = Math::Integer<Algou,AtomicRefArray> ;
  using Int8 = Math::Integer<Algo8> ;

  Int a("123456789");
  Int b("876543210");

  Printf(Con,"a+b = #;\n",a+b);

  Int c("123456789");

  Printf(Con,"#; #;\n",c+210,210+c);

  Int p=c.pow(10);

  Printf(Con,"p = #;\n",p);

  p+=100;

  Printf(Con,"p = #;\n",p);

  p/=1000;

  Printf(Con,"p = #;\n",p);

  Int e("111112222233333444445555566666777778888899999000005555555555555555555555555555");

  Printf(Con,"e = #;\n",e);
  Printf(Con,"e = #+100;\n",e);
  Printf(Con,"e = #+103;\n",e);
  Printf(Con,"e = #+106;\n",e);

  // cast

  a=1000;

  Printf(Con,"a = #;\n",a);

  a=-1000;

  Printf(Con,"a = #;\n",a);

  a=unsigned(-1000);

  Printf(Con,"a = #;\n",a);

  a=short(1000);

  Printf(Con,"a = #;\n",a);

  a=short(-1000);

  Printf(Con,"a = #;\n",a);

  a=(unsigned short)(-1000);

  Printf(Con,"a = #;\n",a);

  Printf(Con,"gcd = #;\n",Math::GCDiv(Int("111111")*Int("222222223456789"),Int("111111")*Int("345678911111111111111111")));

  // cast 8

  Int8 d;

  d=1000;

  Printf(Con,"d = #;\n",d);

  d=-1000;

  Printf(Con,"d = #;\n",d);

  d=unsigned(-1000);

  Printf(Con,"d = #;\n",d);

  return true;
 }

} // namespace App

