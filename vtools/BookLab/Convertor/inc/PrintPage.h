/* PrintPage.h */
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

#ifndef App_PrintPage_h
#define App_PrintPage_h

#include <CCore/inc/CharProp.h>
#include <CCore/inc/String.h>

#include <CCore/inc/Print.h>

namespace App {

/* using */

using namespace CCore;

/* functions */

inline bool SkipPrefix(StrLen &str,StrLen beg)
 {
  if( str.hasPrefix(beg) )
    {
     str+=beg.len;

     return true;
    }

  return false;
 }

inline bool SkipSuffix(StrLen &str,StrLen end)
 {
  if( str.hasSuffix(end) )
    {
     str.len-=end.len;

     return true;
    }

  return false;
 }

/* classes */

struct PageParam;

class PrintPtr;

class TransformInput;

class PrintText;

class PrintSpan;

/* struct PageParam */

struct PageParam
 {
  String name;
  String up;
  String prev;
  String next;
 };

/* class PrintPtr */

class PrintPtr
 {
   StrLen str;

  public:

   explicit PrintPtr(StrLen str_) : str(str_) {}

   explicit PrintPtr(const String &str_) : str(Range(str_)) {}

   void print(PrinterType &out) const
    {
     if( !str )
       {
        Putobj(out,"null"_c);
       }
     else
       {
        Printf(out,"& #;##page",str);
       }
    }
 };

/* class TransformInput */

class TransformInput : NoCopy
 {
   PrintString out;

   static constexpr ulen Len = 10 ;

   char buf[Len];
   ulen len = 0 ;

  private:

   static PrintFile Log;

   void finish();

   void amp();

  public:

   TransformInput() {}

   ~TransformInput() {}

   void put(char ch);

   String close();
 };

/* class PrintText */

class PrintText
 {
   StrLen str;

  private:

   static void PrintChar(PrinterType &out,char ch)
    {
     switch( ch )
       {
        case '"' :
        case '\\' :
         {
          out.put('\\');
          out.put(ch);
         }
        break;

        default:
         {
          if( CharIsSpecial(ch) )
            {
             Putobj(out,"$@$"_c);
            }
          else
            {
             out.put(ch);
            }
         }
       }
    }

  public:

   explicit PrintText(StrLen str_) : str(str_) {}

   explicit PrintText(const String &str_) : str(Range(str_)) {}

   void print(PrinterType &out) const
    {
     for(char ch : str ) PrintChar(out,ch);
    }
 };

/* class PrintSpan */

class PrintSpan
 {
   StrLen str;

  public:

   explicit PrintSpan(StrLen str_) : str(str_) {}

   explicit PrintSpan(const String &str_) : str(Range(str_)) {}

   void print(PrinterType &out) const
    {
     out.put('\"');

     Putobj(out,PrintText(str));

     out.put('\"');
    }
 };

} // namespace App

#endif


