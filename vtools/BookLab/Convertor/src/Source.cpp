/* Source.cpp */
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

#include <inc/Source.h>

namespace App {

/* class SourceErrorId */

StrLen SourceErrorId::Func(int code)
 {
  switch( code )
    {
     case UnknownTag : return "Unknown tag"_c;

     case BadTagText : return "Bad tag text"_c;

     default: return "???"_c;
    }
 }

/* class TestConvert */

 // word

bool TestConvert::word(String) { return true; }

 // text

bool TestConvert::tagH1() { return true; }

bool TestConvert::tagH1end() { return true; }

bool TestConvert::tagH2() { return true; }

bool TestConvert::tagH2end() { return true; }

bool TestConvert::tagH3() { return true; }

bool TestConvert::tagH3end() { return true; }

bool TestConvert::tagH4() { return true; }

bool TestConvert::tagH4end() { return true; }

bool TestConvert::tagH5() { return true; }

bool TestConvert::tagH5end() { return true; }

bool TestConvert::tagP() { return true; }

bool TestConvert::tagPend() { return true; }

bool TestConvert::tagP(String) { return true; }

bool TestConvert::tagPRE() { return true; }

bool TestConvert::tagPREend() { return true; }

 // format

bool TestConvert::tagB() { return true; }

bool TestConvert::tagBend() { return true; }

bool TestConvert::tagI() { return true; }

bool TestConvert::tagIend() { return true; }

bool TestConvert::tagU() { return true; }

bool TestConvert::tagUend() { return true; }

bool TestConvert::tagSUB() { return true; }

bool TestConvert::tagSUBend() { return true; }

bool TestConvert::tagSUP() { return true; }

bool TestConvert::tagSUPend() { return true; }

bool TestConvert::tagSPAN(String) { return true; }

bool TestConvert::tagSPANend() { return true; }

 // hyperlink

bool TestConvert::tagA(String) { return true; }

bool TestConvert::tagA(String,String) { return true; }

bool TestConvert::tagAname(String) { return true; }

bool TestConvert::tagAend() { return true; }

 // list

bool TestConvert::tagOL() { return true; }

bool TestConvert::tagOLend() { return true; }

bool TestConvert::tagUL() { return true; }

bool TestConvert::tagULend() { return true; }

bool TestConvert::tagLI() { return true; }

bool TestConvert::tagLIend() { return true; }

 // image

bool TestConvert::tagImg(String) { return true; }

 // complete

bool TestConvert::complete() { return true; }

} // namespace App

