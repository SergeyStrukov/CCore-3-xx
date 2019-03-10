/* TagTest.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: Book Convertor 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/TagTest.h>

namespace App {

/* class TagTest */

StrLen TagTest::ToString(int code)
 {
  switch( code )
    {
     case Error_NoBlock : return "No text block"_c;

     default: return "???"_c;
    }
 }

 // frame

auto TagTest::frame(String str) -> TagErrorId
 {
  return {};
 }

 // text

auto TagTest::tagH1() -> TagErrorId
   {
    return {};
   }

auto TagTest::tagH1end() -> TagErrorId
   {
    return {};
   }

auto TagTest::tagH2() -> TagErrorId
   {
    return {};
   }

auto TagTest::tagH2end() -> TagErrorId
   {
    return {};
   }

auto TagTest::tagH3() -> TagErrorId
   {
    return {};
   }

auto TagTest::tagH3end() -> TagErrorId
   {
    return {};
   }

auto TagTest::tagH4() -> TagErrorId
   {
    return {};
   }

auto TagTest::tagH4end() -> TagErrorId
   {
    return {};
   }

auto TagTest::tagH5() -> TagErrorId
   {
    return {};
   }

auto TagTest::tagH5end() -> TagErrorId
   {
    return {};
   }

auto TagTest::tagP() -> TagErrorId
   {
    return {};
   }

auto TagTest::tagPend() -> TagErrorId
   {
    return {};
   }

auto TagTest::tagP(String tclass) -> TagErrorId
   {
    return {};
   }

auto TagTest::tagPRE() -> TagErrorId
   {
    return {};
   }

auto TagTest::tagPREend() -> TagErrorId
   {
    return {};
   }

 // format

auto TagTest::tagBR() -> TagErrorId
   {
    return {};
   }

auto TagTest::tagB() -> TagErrorId
   {
    return {};
   }

auto TagTest::tagBend() -> TagErrorId
   {
    return {};
   }

auto TagTest::tagI() -> TagErrorId
   {
    return {};
   }

auto TagTest::tagIend() -> TagErrorId
   {
    return {};
   }

auto TagTest::tagU() -> TagErrorId
   {
    return {};
   }

auto TagTest::tagUend() -> TagErrorId
   {
    return {};
   }

auto TagTest::tagSUB() -> TagErrorId
   {
    return {};
   }

auto TagTest::tagSUBend() -> TagErrorId
   {
    return {};
   }

auto TagTest::tagSUP() -> TagErrorId
   {
    return {};
   }

auto TagTest::tagSUPend() -> TagErrorId
   {
    return {};
   }

auto TagTest::tagSPAN(String tclass) -> TagErrorId
   {
    return {};
   }

auto TagTest::tagSPANend() -> TagErrorId
   {
    return {};
   }

 // hyperlink

auto TagTest::tagA(String url) -> TagErrorId
   {
    return {};
   }

auto TagTest::tagA(String type,String url) -> TagErrorId
   {
    return {};
   }

auto TagTest::tagAname(String name) -> TagErrorId
   {
    return {};
   }

auto TagTest::tagAend() -> TagErrorId
   {
    return {};
   }

 // list

auto TagTest::tagOL() -> TagErrorId
   {
    return {};
   }

auto TagTest::tagOLend() -> TagErrorId
   {
    return {};
   }

auto TagTest::tagUL() -> TagErrorId
   {
    return {};
   }

auto TagTest::tagULend() -> TagErrorId
   {
    return {};
   }

auto TagTest::tagLI() -> TagErrorId
   {
    return {};
   }

auto TagTest::tagLIend() -> TagErrorId
   {
    return {};
   }

 // image

auto TagTest::tagImg(String file_name) -> TagErrorId
   {
    return {};
   }

 // complete

auto TagTest::complete() -> TagErrorId
   {
    return {};
   }

} // namespace App

