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
#include <CCore/inc/PrintBits.h>

namespace App {

/* using */

using namespace CCore;

/* classes */

struct SrcChar;

class SrcCursor;

//enum TokFlags;

class FlagTable;

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

  TokLetter = Bit(0),
  TokDigit  = Bit(1),
  TokPunct  = Bit(2),
  TokHex    = Bit(3),

  TokSpace  = Bit(4),
  TokExt    = Bit(5),

  TokDel    = Bit(6),
  TokU4     = Bit(7),
  TokU8     = Bit(8)
 };

inline TokFlags operator | (TokFlags a,TokFlags b) { return TokFlags(unsigned(a)|b); }

inline TokFlags operator |= (TokFlags &a,TokFlags b) { a=a|b; return a; }

/* class FlagTable */

class FlagTable
 {
   TokFlags table[128];

  private:

   void set(unsigned char ch,TokFlags flags) { table[ch]|=flags; }

   void set(const char *zstr,TokFlags flags);

  public:

   FlagTable();

   TokFlags operator [] (Unicode ch) const;

   static FlagTable Object;
 };

/* struct TokChar */

struct TokChar : SrcChar
 {
  TokFlags flags;

  static TokFlags Flags(Unicode ch) { return FlagTable::Object[ch]; }

  TokChar() {}

  TokChar(SrcChar ch) : SrcChar(ch),flags(Flags(ch.code)) {}

  // print object

  void print(PrinterType &out) const
   {
    SrcChar::print(out);

    Putobj(out," : "_c);

    PrintBits<unsigned>(out,flags)
                       (TokLetter,"Letter"_c)
                       (TokDigit,"Digit"_c)
                       (TokPunct,"Punct"_c)
                       (TokHex,"Hex"_c)
                       (TokSpace,"Space"_c)
                       (TokExt,"Ext"_c)
                       (TokDel,"Del"_c)
                       (TokU4,"U4"_c)
                       (TokU8,"U8"_c)
                       .complete();
   }
 };

/* class TokCursor */

class TokCursor : NoCopy
 {
   SrcCursor src;

   static constexpr unsigned Len = 16 ;

   TokChar buf[Len];

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

