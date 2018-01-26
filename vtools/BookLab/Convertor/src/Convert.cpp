/* Convert.cpp */
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

#include <inc/Convert.h>

#include <CCore/inc/Path.h>
#include <CCore/inc/video/PrintDDL.h>

namespace App {

/* using */

using Video::DDLString;
using Video::DDLPrintableString;

/* class Convert */

void Convert::start()
 {
  Printf(out,"/* #;.book.ddl */\n\n",name);

  Printf(out,"include <#;.style.ddl>\n\n",name);

  Putobj(out,"scope Pages {\n\n");
 }

Convert::Convert(StrLen output_file_name)
 : out(output_file_name)
 {
  SplitPath split1(output_file_name);
  SplitName split2(split1.path);
  SplitFullExt split3(split2.name);

  name=String(split3.name);

  start();
 }

bool Convert::word(String word)
 {
  Used(word);

  return false;
 }

bool Convert::tagH1()
 {
  return false;
 }

bool Convert::tagH1end()
 {
  return false;
 }

bool Convert::tagH2()
 {
  return false;
 }

bool Convert::tagH2end()
 {
  return false;
 }

bool Convert::tagH3()
 {
  return false;
 }

bool Convert::tagH3end()
 {
  return false;
 }

bool Convert::tagH4()
 {
  return false;
 }

bool Convert::tagH4end()
 {
  return false;
 }

bool Convert::tagH5()
 {
  return false;
 }

bool Convert::tagH5end()
 {
  return false;
 }

bool Convert::tagP()
 {
  return false;
 }

bool Convert::tagPend()
 {
  return false;
 }

bool Convert::tagB()
 {
  return false;
 }

bool Convert::tagBend()
 {
  return false;
 }

bool Convert::tagI()
 {
  return false;
 }

bool Convert::tagIend()
 {
  return false;
 }

bool Convert::tagA(String url)
 {
  Used(url);

  return false;
 }

bool Convert::tagAend()
 {
  return false;
 }

bool Convert::tagOL()
 {
  return false;
 }

bool Convert::tagOLend()
 {
  return false;
 }

bool Convert::tagLI()
 {
  return false;
 }

bool Convert::tagLIend()
 {
  return false;
 }

bool Convert::tagImg(String file_name)
 {
  Used(file_name);

  return false;
 }

bool Convert::complete()
 {
  Putobj(out,"Page page1 = { Pages#PageName , {\n");

#if 0

  for(ulen i=1; i<ind ;i++)
    {
     if( i==1 )
       Printf(out,"{ &text#; }\n",i);
     else
       Printf(out,",{ &text#; }\n",i);
    }

#endif

  Putobj(out,"} };\n\n");

  Putobj(out,"} // scope Pages\n\n");

  Putobj(out,"Book Data = { Pages#BookName , {&Pages#page1} , Pages#Back , Pages#Fore } ;");

  return true;
 }

} // namespace App

