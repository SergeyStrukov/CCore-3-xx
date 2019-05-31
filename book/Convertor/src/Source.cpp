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

     case BrokenTitle : return "Broken title"_c;

     default: return "???"_c;
    }
 }

/* class TestConvert */

 // frame

bool TestConvert::frame(String) { return true; }

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

bool TestConvert::tagP(String) { return true; }

bool TestConvert::tagPend() { return true; }

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

/* class LogConvert */

void LogConvert::setId(String id)
 {
  Printf(out,"id = #.q;\n",id);
 }

 // frame

bool LogConvert::frame(String str)
 {
  Printf(out,"<frame>\n#;\n</frame>\n",str);

  return true;
 }

 // text

bool LogConvert::tagH1()
 {
  Putobj(out,"<h1>\n"_c);

  return true;
 }

bool LogConvert::tagH1end()
 {
  Putobj(out,"</h1>\n"_c);

  return true;
 }

bool LogConvert::tagH2()
 {
  Putobj(out,"<h2>\n"_c);

  return true;
 }

bool LogConvert::tagH2end()
 {
  Putobj(out,"</h2>\n"_c);

  return true;
 }

bool LogConvert::tagH3()
 {
  Putobj(out,"<h3>\n"_c);

  return true;
 }

bool LogConvert::tagH3end()
 {
  Putobj(out,"</h3>\n"_c);

  return true;
 }

bool LogConvert::tagH4()
 {
  Putobj(out,"<h4>\n"_c);

  return true;
 }

bool LogConvert::tagH4end()
 {
  Putobj(out,"</h4>\n"_c);

  return true;
 }

bool LogConvert::tagH5()
 {
  Putobj(out,"<h5>\n"_c);

  return true;
 }

bool LogConvert::tagH5end()
 {
  Putobj(out,"</h5>\n"_c);

  return true;
 }

bool LogConvert::tagP()
 {
  Putobj(out,"<p>\n"_c);

  return true;
 }

bool LogConvert::tagP(String tclass)
 {
  Printf(out,"<p class=#.q; >\n",tclass);

  return true;
 }

bool LogConvert::tagPend()
 {
  Putobj(out,"</p>\n"_c);

  return true;
 }

bool LogConvert::tagPRE()
 {
  Putobj(out,"<pre>\n"_c);

  return true;
 }

bool LogConvert::tagPREend()
 {
  Putobj(out,"</pre>\n"_c);

  return true;
 }

 // format

bool LogConvert::tagB()
 {
  Putobj(out,"<b>\n"_c);

  return true;
 }

bool LogConvert::tagBend()
 {
  Putobj(out,"</b>\n"_c);

  return true;
 }

bool LogConvert::tagI()
 {
  Putobj(out,"<i>\n"_c);

  return true;
 }

bool LogConvert::tagIend()
 {
  Putobj(out,"</i>\n"_c);

  return true;
 }

bool LogConvert::tagU()
 {
  Putobj(out,"<u>\n"_c);

  return true;
 }

bool LogConvert::tagUend()
 {
  Putobj(out,"</u>\n"_c);

  return true;
 }

bool LogConvert::tagSUB()
 {
  Putobj(out,"<sub>\n"_c);

  return true;
 }

bool LogConvert::tagSUBend()
 {
  Putobj(out,"</sub>\n"_c);

  return true;
 }

bool LogConvert::tagSUP()
 {
  Putobj(out,"<sup>\n"_c);

  return true;
 }

bool LogConvert::tagSUPend()
 {
  Putobj(out,"</sup>\n"_c);

  return true;
 }

bool LogConvert::tagSPAN(String tclass)
 {
  Printf(out,"<span class=#.q; >\n",tclass);

  return true;
 }

bool LogConvert::tagSPANend()
 {
  Putobj(out,"</span>\n"_c);

  return true;
 }

 // hyperlink

bool LogConvert::tagA(String url)
 {
  Printf(out,"<a href=#.q; >\n",url);

  return true;
 }

bool LogConvert::tagA(String type,String url)
 {
  Printf(out,"<a type=#.q; href=#.q; >\n",type,url);

  return true;
 }

bool LogConvert::tagAend()
 {
  Putobj(out,"</a>\n"_c);

  return true;
 }

 // list

bool LogConvert::tagOL()
 {
  Putobj(out,"<ol>\n"_c);

  return true;
 }

bool LogConvert::tagOLend()
 {
  Putobj(out,"</ol>\n"_c);

  return true;
 }

bool LogConvert::tagUL()
 {
  Putobj(out,"<ul>\n"_c);

  return true;
 }

bool LogConvert::tagULend()
 {
  Putobj(out,"</ul>\n"_c);

  return true;
 }

bool LogConvert::tagLI()
 {
  Putobj(out,"<li>\n"_c);

  return true;
 }

bool LogConvert::tagLIend()
 {
  Putobj(out,"</li>\n"_c);

  return true;
 }

 // image

bool LogConvert::tagImg(String file_name)
 {
  Printf(out,"<img src=#.q; />\n",file_name);

  return true;
 }

 // complete

bool LogConvert::complete()
 {
  Putobj(out,"<END />\n"_c);

  return true;
 }

} // namespace App

