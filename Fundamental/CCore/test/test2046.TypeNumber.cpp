/* test2046.TypeNumber.cpp */
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

#include <CCore/inc/TypeNumber.h>

namespace App {

namespace Private_2046 {

struct S1
 {
  static const Unid TypeUnid;
 };

const Unid S1::TypeUnid={{0xB4C7'DD04,0x714F'53C4,0x5E5F'E9E8,0x2844'19F0,0xCEDD'8488,0xD820'86EB,0x16EC'2386,101}};

struct S2
 {
  static const Unid TypeUnid;
 };

const Unid S2::TypeUnid={{0xB4C7'DD04,0x714F'53C4,0x5E5F'E9E8,0x2844'19F0,0xCEDD'8488,0xD820'86EB,0x16EC'2386,102}};

struct S3
 {
  static const Unid TypeUnid;
 };

const Unid S3::TypeUnid={{0xB4C7'DD04,0x714F'53C4,0x5E5F'E9E8,0x2844'19F0,0xCEDD'8488,0xD820'86EB,0x16EC'2386,103}};

struct S4
 {
  static const Unid TypeUnid;
 };

const Unid S4::TypeUnid={{0xB4C7'DD04,0x714F'53C4,0x5E5F'E9E8,0x2844'19F0,0xCEDD'8488,0xD820'86EB,0x16EC'2386,104}};

struct S5
 {
  static const Unid TypeUnid;
 };

const Unid S5::TypeUnid={{0xB4C7'DD04,0x714F'53C4,0x5E5F'E9E8,0x2844'19F0,0xCEDD'8488,0xD820'86EB,0x16EC'2386,105}};

} // namespace Private_2046

using namespace Private_2046;

/* Testit<2046> */

template<>
const char *const Testit<2046>::Name="Test2046 TypeNumber";

template<>
bool Testit<2046>::Main()
 {
  Printf(Con,"#;\n",TypeNumberOf<S1>().get());
  Printf(Con,"#;\n",TypeNumberOf<S2>().get());
  Printf(Con,"#;\n",TypeNumberOf<S3>().get());
  Printf(Con,"#;\n",TypeNumberOf<S4>().get());
  Printf(Con,"#;\n",TypeNumberOf<S5>().get());

  Printf(Con,"#;\n",TypeNumberOf<S1>().oneOf<S2,S3,S4,S5>());
  Printf(Con,"#;\n",TypeNumberOf<S1>().oneOf<S2,S3,S4,S5,S2,S3,S4,S5>());
  Printf(Con,"#;\n",TypeNumberOf<S1>().oneOf<S1,S2,S3,S4,S5>());
  Printf(Con,"#;\n",TypeNumberOf<S1>().oneOf<S2,S3,S1,S4,S5>());
  Printf(Con,"#;\n",TypeNumberOf<S1>().oneOf<S2,S3,S4,S5,S2,S3,S4,S5,S1>());

  return true;
 }

} // namespace App

