/* CppToken.h */
//----------------------------------------------------------------------------------------
//
//  Project: CppLab 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CppToken_h
#define CppToken_h

#include <CCore/inc/Utf8.h>
#include <CCore/inc/CharProp.h>
#include <CCore/inc/Printf.h>

namespace App {

/* using */

using namespace CCore;

/* classes */

struct SrcChar;

class SrcCursor;

/* struct SrcChar */

struct SrcChar
 {
  static constexpr Unicode    Eof = 0xFFFF'FFFF ;
  static constexpr Unicode Broken = Eof-1 ;

  ulen line;
  ulen  pos;
  Unicode code;

  bool operator + () const { return code!=Eof; }

  bool operator ! () const { return code==Eof; }

  // print object

  void print(PrinterType &out) const
   {
    Printf(out,"(#;,#;,",line,pos);

    if( code==Eof )
      {
       Putobj(out,"Eof"_c);
      }
    else if( code==Broken )
      {
       Putobj(out,"Broken"_c);
      }
    else if( code<32 )
      {
       Printf(out,"'#;'",CharCode((char)code));
      }
    else
      {
       Printf(out,"'#;'",ToUtf8(code));
      }

    out.put(')');
   }
 };

/* class SrcCursor */

class SrcCursor
 {
   StrLen text;
   SrcChar cur;

  private:

   void nextSym();

   void next();

  public:

   explicit SrcCursor(StrLen text);

   bool operator + () const { return +cur; }

   bool operator ! () const { return !cur; }

   SrcChar operator * () const { return cur; }

   void operator ++ ();
 };

} // namespace App

#endif

