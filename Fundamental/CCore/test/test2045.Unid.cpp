/* test2045.Unid.cpp */
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

#include <CCore/inc/Unid.h>

namespace App {

namespace Private_2045 {

struct S1
 {
  static const Unid TypeUnid;
 };

const Unid S1::TypeUnid={{0xB4C7'DD04,0x714F'53C4,0x5E5F'E9E8,0x2844'19F0,0xCEDD'8488,0xD820'86EB,0x16EC'2386,1}};

struct S2
 {
  static const Unid TypeUnid;
 };

const Unid S2::TypeUnid={{0xB4C7'DD04,0x714F'53C4,0x5E5F'E9E8,0x2844'19F0,0xCEDD'8488,0xD820'86EB,0x16EC'2386,2}};

struct S3
 {
  static const Unid TypeUnid;
 };

const Unid S3::TypeUnid={{0xB4C7'DD04,0x714F'53C4,0x5E5F'E9E8,0x2844'19F0,0xCEDD'8488,0xD820'86EB,0x16EC'2386,3}};

} // namespace Private_2045

using namespace Private_2045;

/* Testit<2045> */

template<>
const char *const Testit<2045>::Name="Test2045 Unid";

template<>
bool Testit<2045>::Main()
 {
  UnidRegister reg;

  Printf(Con,"#;\n",reg.getTypeId<S1>());
  Printf(Con,"#;\n",reg.getTypeId<S2>());
  Printf(Con,"#;\n",reg.getTypeId<S3>());

  Printf(Con,"#;\n",reg.getTypeId<S1>());
  Printf(Con,"#;\n",reg.getTypeId<S2>());
  Printf(Con,"#;\n",reg.getTypeId<S3>());

  Printf(Con,"#;\n",reg.getTypeId<S1>());
  Printf(Con,"#;\n",reg.getTypeId<S2>());
  Printf(Con,"#;\n",reg.getTypeId<S3>());

  return true;
 }

} // namespace App

