/* CharProp.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Fundamental Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_CharProp_h
#define CCore_inc_CharProp_h

#include <CCore/inc/Printf.h>

#ifdef CCORE_UTF8
# include <CCore/inc/Utf8.h>
#endif

namespace CCore {

/* concept CharCodeType<Char> */

template <class Char>
concept bool CharCodeType = Meta::OneOf<Char,char,signed char,unsigned char> ;

/* CutLine() */

StrLen CutLine(StrLen &text);

/* classes */

class ASCIICode;

class PrintCString;

/* class ASCIICode */

class ASCIICode
 {
  public:

   using CodeType = uint8 ;

   static char InverseMap(CodeType code) { return char(code); }

   //
   // (CodeType)InverseMap(code) == code
   //

  private:

   CodeType code;

    //
    // ASCII code table
    //
    // +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
    // |     I  00 |  01 |  02 |  03 |  04 |  05 |  06 |  07 |  08 |  09 |  0A |  0B |  0C |  0D |  0E |  0F |
    // +=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+
    // |  00 I     |     |     |     |     |     |     |     | \b  | \t  | \n  | \v  | \f  | \r  |     |     |
    // +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
    // |  10 I     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |
    // +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
    // |  20 I     |  !  |  "  |  #  |  $  |  %  |  &  |  '  |  (  |  )  |  *  |  +  |  ,  |  -  |  .  |  /  |
    // +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
    // |  30 I  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  :  |  ;  |  <  |  =  |  >  |  ?  |
    // +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
    // |  40 I  @  |  A  |  B  |  C  |  D  |  E  |  F  |  G  |  H  |  I  |  J  |  K  |  L  |  M  |  N  |  O  |
    // +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
    // |  50 I  P  |  Q  |  R  |  S  |  T  |  U  |  V  |  W  |  X  |  Y  |  Z  |  [  |  \  |  ]  |  ^  |  _  |
    // +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
    // |  60 I  `  |  a  |  b  |  c  |  d  |  e  |  f  |  g  |  h  |  i  |  j  |  k  |  l  |  m  |  n  |  o  |
    // +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
    // |  70 I  p  |  q  |  r  |  s  |  t  |  u  |  v  |  w  |  x  |  y  |  z  |  {  |  |  |  }  |  ~  |     |
    // +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
    //

   static const bool IsSpaceTable[256];

   static const bool IsPunctTable[256];

   static const bool IsSpaceOrPunctTable[256];

   static const signed char DecValueTable[256];

   static const signed char HexValueTable[256];

  public:

   // constructors

   ASCIICode() : code(0) {}

   explicit ASCIICode(CharCodeType ch) : code(ch) {}

   // properties

   bool isSpecial() const { return code<32 || code==127 ; }

        // special -- represents no character

   bool isVisible() const { return code>32 && code!=127 ; }

        // visible -- represents non-space character

   bool isPrintable() const { return code>=32 && code!=127 ; }

        // printable -- not a special char

   bool isSpace() const { return IsSpaceTable[code]; }

        // space-like -- " \t\n\v\f\r"

   bool isPunct() const { return IsPunctTable[code]; }

        // punctuation characters

   bool isSpaceOrPunct() const { return IsSpaceOrPunctTable[code]; }

        // space or punct

   int decValue() const { return DecValueTable[code]; }

       // decimal digit value or -1

   int hexValue() const { return HexValueTable[code]; }

       // hexadecimal digit value or -1

   char getChar() const { return InverseMap(code); }

   // print object

   void print(PrinterType &out) const
    {
     if( code>=32 && code!=127 )
       {
        switch( char ch=getChar() )
          {
           case '\\' : case '"' : out.put('\\'); [[fallthrough]];

           default: out.put(ch);
          }
       }
     else if( code>=8 && code<=13 )
       {
        out.put('\\');
        out.put("btnvfr"[code-8]);
       }
     else
       {
        Printf(out,"\\x#2.16i;",code);
       }
    }
 };

/* type CharCode */

using CharCode = ASCIICode ;

/* type ExtCharCode */

#ifdef CCORE_UTF8

class ExtCharCode
 {
   Utf8Code code;

  public:

   explicit ExtCharCode(const Utf8Code &code_) : code(code_) {}

   explicit ExtCharCode(Unicode ch) : code(ToUtf8(ch)) {}

   // print object

   void print(PrinterType &out) const
    {
     if( code.getLen()==1 )
       Putobj(out,CharCode(code[0]));
     else
       Putobj(out,code);
    }
 };

#else

using ExtCharCode = CharCode ;

#endif

/* class PrintCString */

class PrintCString
 {
   StrLen str;

  public:

   explicit PrintCString(StrLen str_) : str(str_) {}

   using PrintOptType = StrPrintOpt ;

   void print(PrinterType &out,PrintOptType opt) const
    {
     if( opt.quoted ) out.put('"');

     for(auto r=str; +r ;++r) Putobj(out,CharCode(*r));

     if( opt.quoted ) out.put('"');
    }
 };

/* functions */

bool CharIsSpecial(CharCodeType ch) { return CharCode(ch).isSpecial(); }

bool CharIsVisible(CharCodeType ch) { return CharCode(ch).isVisible(); }

bool CharIsPrintable(CharCodeType ch) { return CharCode(ch).isPrintable(); }

bool CharIsSpace(CharCodeType ch) { return CharCode(ch).isSpace(); }

bool CharIsPunct(CharCodeType ch) { return CharCode(ch).isPunct(); }

bool CharIsSpaceOrPunct(CharCodeType ch) { return CharCode(ch).isSpaceOrPunct(); }

int CharDecValue(CharCodeType ch) { return CharCode(ch).decValue(); }

int CharHexValue(CharCodeType ch) { return CharCode(ch).hexValue(); }

/* ext functions */

#ifdef CCORE_UTF8

inline bool CharIsSpecial(Utf8Code code) { return (code.getLen()==1)?CharIsSpecial(code[0]):false; }

inline bool CharIsVisible(Utf8Code code) { return (code.getLen()==1)?CharIsVisible(code[0]):true; }

inline bool CharIsPrintable(Utf8Code code) { return (code.getLen()==1)?CharIsPrintable(code[0]):true; }

inline bool CharIsSpace(Utf8Code code) { return (code.getLen()==1)?CharIsSpace(code[0]):false; }

inline int CharDecValue(Utf8Code code) { return (code.getLen()==1)?CharDecValue(code[0]):(-1); }

inline int CharHexValue(Utf8Code code) { return (code.getLen()==1)?CharHexValue(code[0]):(-1); }

inline bool CharIsSpecial(Unicode ch) { return (ch<128)?CharIsSpecial((char)ch):false; }

inline bool CharIsVisible(Unicode ch) { return (ch<128)?CharIsVisible((char)ch):true; }

inline bool CharIsPrintable(Unicode ch) { return (ch<128)?CharIsPrintable((char)ch):true; }

inline bool CharIsSpace(Unicode ch) { return (ch<128)?CharIsSpace((char)ch):false; }

inline int CharDecValue(Unicode ch) { return (ch<128)?CharDecValue((char)ch):(-1); }

inline int CharHexValue(Unicode ch) { return (ch<128)?CharHexValue((char)ch):(-1); }

#endif

/* ParseSpace() */

template <CharPeekType Dev>
void ParseSpace(Dev &dev)
 {
  for(;;++dev)
    {
     typename Dev::Peek peek(dev);

     if( !peek || !CharIsSpace(*peek) ) break;
    }
 }

/* char sets */

inline const char * GetSpaceChars() { return " \t\f\v\r\n"; }

inline const char * GetPunctChars() { return "!\"#$%&'()*+,-./:;<=>?@[\\]^`{|}~"; }

inline const char * GetDigitChars() { return "0123456789"; }

inline const char * GetHexDigitChars() { return "0123456789abcdefABCDEF"; }

inline const char * GetCLetterChars() { return "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_"; }

} // namespace CCore

#endif


