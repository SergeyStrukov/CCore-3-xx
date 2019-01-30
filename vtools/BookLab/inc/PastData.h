/* PastData.h */
//----------------------------------------------------------------------------------------
//
//  Project: BookLab 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef PastData_h
#define PastData_h

#include <inc/BookLab.h>

namespace App {

/* namespace CppText */

namespace CppText {

/* classes */

//enum CharFlags;

class FlagTable;

struct FlagChar;

//enum TokenClass;

struct Token;

class Tokenizer;

/* enum CharFlags */

enum CharFlags : unsigned
 {
  CharNull   = 0,

  CharLetter = Bit(0),
  CharDigit  = Bit(1),
  CharPunct  = Bit(2),
  CharQuote  = Bit(3),
  CharHex    = Bit(4),
  CharSpace  = Bit(5),
  CharEOL    = Bit(6),

  CharPunct2 = Bit(7),
  CharPunct3 = Bit(8)
 };

inline CharFlags operator | (CharFlags a,CharFlags b) { return CharFlags(unsigned(a)|b); }

inline CharFlags operator |= (CharFlags &a,CharFlags b) { a=a|b; return a; }

/* class FlagTable */

class FlagTable
 {
   CharFlags table[256];

  private:

   void set(unsigned char ch,CharFlags flags) { table[ch]|=flags; }

   void set(const char *zstr,CharFlags flags);

  public:

   FlagTable();

   CharFlags operator [] (unsigned char ch) const;

   static FlagTable Object;
 };

/* struct FlagChar */

struct FlagChar
 {
  CharFlags flags;
  char ch;

  FlagChar(char ch_) : flags(FlagTable::Object[ch_]),ch(ch_) {}

  auto test(CharFlags f) const { return flags&f; }
 };

/* enum TokenClass; */

enum TokenClass
 {
  TokenNull = 0,

  TokenId,
  TokenKeyword,
  TokenNumber,
  TokenOp,
  TokenString,
  TokenChar,

  TokenSpace,
  TokenEOL,
  TokenShortComment,
  TokenLongComment,
  TokenOther
 };

/* struct Token */

struct Token
 {
  StrLen str;
  TokenClass tc = TokenNull ;
 };

/* class Tokenizer */

class Tokenizer
 {
   StrLen text;

  private:

   static StrLen ScanId(StrLen text);

   static bool IsSign(char ch) { return ch=='+' || ch=='-' ; }

   static StrLen ScanNumber(StrLen text);

   static StrLen ScanOp(StrLen text);

   static StrLen ScanChar(StrLen text);

   static StrLen ScanString(StrLen text);

   static StrLen ScanShortComment(StrLen text);

   static StrLen ScanLongComment(StrLen text);

   static StrLen ScanSpace(StrLen text);

   static StrLen ScanEOL(StrLen text);

   static StrLen ScanOther(StrLen text);

   static bool TestKeyword(StrLen str);

  private:

   StrLen cut(StrLen suffix);

   Token nextId();

   Token nextNumber();

   Token nextOp();

   Token nextChar();

   Token nextString();

   Token nextShortComment();

   Token nextLongComment();

   Token nextSpace();

   Token nextEOL();

   Token nextOther();

  public:

   explicit Tokenizer(StrLen text_) : text(text_) {}

   Token next();
 };

} // namespace CppText

/* classes */

class PastData;

/* class PastData */

class PastData : public Funchor
 {
  public:

   struct Span
    {
     String body;
     String format;
     String ref;

     BookLab::Span build() const
      {
       BookLab::Span ret;

       ret.body=body;
       ret.format.name=format;
       ret.ref.name=ref;

       return ret;
      }
    };

   struct Line
    {
     DynArray<Span> list;

     BookLab::TextLine build() const
      {
       BookLab::TextLine ret;

       extend(ret);

       return ret;
      }

     void extend(BookLab::TextLine &line) const
      {
       ulen len=list.getLen();

       auto r=line.list.extend_default(len);

       for(ulen i : IndLim(len) ) r[i]=list[i].build();
      }
    };

   DynArray<Line> list;

   PastData() {}

   ~PastData() {}

   bool operator ! () const { return !list.getLen(); }

   bool isSimple() const { return list.getLen()==1 && list[0].list.getLen()==1 ; }

   StrLen getSimple() const { return Range(list[0].list[0].body); }

   Function<void (StrLen)> function_load() { return FunctionOf(this,&PastData::load); }

   Function<void (StrLen)> function_loadCPP() { return FunctionOf(this,&PastData::loadCPP); }

  private:

   static bool ParseChar(StrLen &text,char ch);

   static bool ParseString(StrLen &text,String &ret);

   static bool ParseSpan(StrLen &text,Span &ret);

   static bool ParseSpan(StrLen &text,Collector<Span> &buf);

   static bool ParseLine(StrLen &text,Line &ret);

   static bool ParseLine(StrLen &text,Collector<Line> &buf);

   static bool ParseCombo(StrLen text,Collector<Line> &buf);

   bool parseCombo(StrLen text);

   static void ParseSimpleLine(StrLen text,Collector<Span> &buf);

   static void ParseSimpleLine(StrLen text,Line &ret);

   static void ParseSimple(StrLen text,Collector<Line> &buf);

   void parseSimple(StrLen text);

   void load(StrLen text);

  private:

   void loadCPP(StrLen text);
 };

} // namespace App

#endif
