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

/* classes */

struct PageParam;

class PrintPtr;

class PrintSpan;

class PrintText;

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
        Printf(out,"& #;",str);
       }
    }
 };

/* class PrintSpan */

class PrintSpan
 {
   StrLen str;

  private:

   static constexpr bool SoftAmp = true ;

   static PrintFile Log;

   static void PrintAmp(PrinterType &out,StrLen text)
    {
     if( text.equal("lt"_c) )
       {
        out.put('<');

        return;
       }

     if( text.equal("gt"_c) )
       {
        out.put('>');

        return;
       }

     if( text.equal("amp"_c) )
       {
        out.put('&');

        return;
       }

     if( text.equal("mdash"_c) )
       {
        Putobj(out,"—"_c);

        return;
       }

     if( text.equal("minus"_c) )
       {
        Putobj(out,"−"_c);

        return;
       }

     if( text.equal("pi"_c) )
       {
        Putobj(out,"π"_c);

        return;
       }

     if constexpr ( SoftAmp )
       {
        out.put('&');

        Putobj(out,text);

        out.put(';');

        Printf(Log,"&#;;\n",text);
       }
     else
       {
        Putobj(out,"$@$"_c);
       }
    }

   static void PrintChar(PrinterType &out,StrLen &text)
    {
     char ch=*text;

     ++text;

     switch( ch )
       {
        case '&' :
         {
          StrLen next=text;

          for(; +next && *next!=';' ;++next);

          if( !next )
            {
             if constexpr( SoftAmp )
               {
                out.put('&');

                Putobj(out,text);

                Printf(Log,"&#;`\n",text);
               }
             else
               {
                Putobj(out,"$@$"_c);
               }

             text=next;
            }
          else
            {
             PrintAmp(out,text.prefix(next));

             ++next;

             text=next;
            }
         }
        break;

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

   explicit PrintSpan(StrLen str_) : str(str_) {}

   explicit PrintSpan(const String &str_) : str(Range(str_)) {}

   void print(PrinterType &out) const
    {
     out.put('\"');

     for(StrLen text=str; +text ;) PrintChar(out,text);

     out.put('\"');
    }
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

} // namespace App

#endif


