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

//enum TokFlags;

struct TokChar;

class TokCursor;

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

  bool is(unsigned char ch) const { return code==ch; }

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

/* enum TokFlags */

enum TokFlags : unsigned
 {
  TokNull   = 0,

  TokLetter = 1,
  TokDigit  = 2,
  TokPunct  = 4,
  TokHex    = 8,
  TokExt = 0x10,

  TokDel = 0x20,
  TokU4  = 0x40,
  TokU8  = 0x80
 };

inline TokFlags operator | (TokFlags a,TokFlags b) { return TokFlags(unsigned(a)|b); }

inline TokFlags operator |= (TokFlags &a,TokFlags b) { a=a|b; return a; }

/* struct TokChar */

struct TokChar : SrcChar
 {
  TokFlags flags;

  TokChar() {}

  TokChar(SrcChar ch) : SrcChar(ch),flags(Flags(ch.code)) {}

  static TokFlags Flags(Unicode ch);
 };

/* class TokCursor */

class TokCursor : NoCopy
 {
   SrcCursor src;

   TokChar buf[16];

   unsigned off = 0 ;
   unsigned lim = 0 ;

  private:

   bool provide();

   bool provide(unsigned count);

   void setFlags(unsigned count,TokFlags flags);

   bool testHex(unsigned base,unsigned len) const;

   void next();

  public:

   explicit TokCursor(StrLen text);

   bool operator + () const { return off<lim; }

   bool operator ! () const { return off>=lim; }

   TokChar operator * () const { return buf[off]; }

   void operator ++ ();
 };

} // namespace App

#endif

