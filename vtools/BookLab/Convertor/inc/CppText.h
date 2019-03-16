/* CppText.h */
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

#ifndef App_CppText_h
#define App_CppText_h

#include <CCore/inc/CharProp.h>

namespace App {

/* using */

using namespace CCore;

namespace CppText {

/* classes */

//enum CharFlags;

class FlagTable;

struct FlagChar;

//enum TokenClass;

struct Token;

//enum TokenizerState;

class Tokenizer;

/* enum CharFlags */

enum CharFlags : unsigned
 {
  CharNull   = 0,

  CharLetter = Bit(0),
  CharDigit  = Bit(1),
  CharPunct  = Bit(2),
  CharQuote  = Bit(3),
  CharSpace  = Bit(4),
  CharEOL    = Bit(5),

  CharHex    = Bit(6),
  CharOct    = Bit(7),

  CharPunct2 = Bit(8),
  CharPunct3 = Bit(9)
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

/* enum TokenizerState */

enum TokenizerState
 {
  Tokenizer_InText = 0,

  Tokenizer_InShortComment,
  Tokenizer_InLongComment
 };

/* class Tokenizer */

class Tokenizer
 {
   StrLen text;
   TokenizerState state;

  private:

   static StrLen ScanId(StrLen text);

   static bool IsSign(char ch) { return ch=='+' || ch=='-' ; }

   static StrLen ScanNumber(StrLen text);

   static StrLen ScanOp(StrLen text);

   static StrLen ScanEscape(StrLen text);

   static StrLen ScanChar(StrLen text);

   static StrLen ScanString(StrLen text);

   static StrLen ScanSpace(StrLen text);

   static StrLen ScanOther(StrLen text);

   static bool TestKeyword(StrLen str);

   // ---

   static StrLen ScanShortComment(StrLen text);

   static StrLen ScanLongComment(StrLen text);

   static StrLen ScanEOL(StrLen text);

  private:

   StrLen cut(StrLen suffix);

   Token nextId();

   Token nextNumber();

   Token nextOp();

   Token nextChar();

   Token nextString();

   Token nextSpace();

   Token nextOther();

   // ---

   Token nextShortComment();

   Token nextLongComment();

   Token nextEOL();

  public:

   Tokenizer(StrLen text_,TokenizerState state_) : text(text_),state(state_) {}

   TokenizerState getState() const { return state; }

   Token next();
 };

} // namespace CppText
} // namespace App

#endif


