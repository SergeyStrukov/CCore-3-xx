/* PrintDDL.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: Desktop
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_video_PrintDDL_h
#define CCore_inc_video_PrintDDL_h

#include <CCore/inc/CharProp.h>

namespace CCore {
namespace Video {

/* DDLBool() */

inline StrLen DDLBool(bool val) { return val?"True"_c:"False"_c; }

/* classes */

struct DDLString;

struct DDLPrintableString;

/* struct DDLString */

struct DDLString
 {
  StrLen str;

  explicit DDLString(StrLen str_) : str(str_) {}

  explicit DDLString(const ConstTypeRangeableType<char> &obj) : str(Range_const(obj)) {}

  // print object

  static void PrintChar(PrinterType &out,char ch)
   {
    switch( ch )
      {
       case '\b' : out.put('\\'); out.put('b'); break;

       case '\t' : out.put('\\'); out.put('t'); break;

       case '\n' : out.put('\\'); out.put('n'); break;

       case '\v' : out.put('\\'); out.put('v'); break;

       case '\f' : out.put('\\'); out.put('f'); break;

       case '\r' : out.put('\\'); out.put('r'); break;

       case '"' : out.put('\\'); out.put('"'); break;

       case '\\' : out.put('\\'); out.put('\\'); break;

       default:
        {
         if( CharIsPrintable(ch) ) out.put(ch); else out.put(' ');
        }
      }
   }

  void print(PrinterType &out) const
   {
    out.put('"');

    for(char ch : str ) PrintChar(out,ch);

    out.put('"');
   }
 };

/* struct DDLPrintableString */

struct DDLPrintableString
 {
  StrLen str;

  explicit DDLPrintableString(StrLen str_) : str(str_) {}

  explicit DDLPrintableString(const ConstTypeRangeableType<char> &obj) : str(Range_const(obj)) {}

  // print object

  static void GuardNotPrintable();

  static void PrintChar(PrinterType &out,char ch)
   {
    switch( ch )
      {
       case '"' : out.put('\\'); out.put('"'); break;

       case '\\' : out.put('\\'); out.put('\\'); break;

       default:
        {
         if( CharIsPrintable(ch) ) out.put(ch); else GuardNotPrintable();
        }
      }
   }

  void print(PrinterType &out) const
   {
    out.put('"');

    for(char ch : str ) PrintChar(out,ch);

    out.put('"');
   }
 };

} // namespace Video
} // namespace CCore

#endif

