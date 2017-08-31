/* Utf8.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Simple Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_Utf8_h
#define CCore_inc_Utf8_h

#include <CCore/inc/CharProp.h>

namespace CCore {

/* type Unicode */

using Unicode = uint32 ;

/* guard functions */

void GuardUtf8Broken();

/* classes */

class Utf8Code;

/* class Utf8Code */

class Utf8Code
 {
   char sym[4];
   unsigned len;

  public:

   Utf8Code() noexcept : sym{},len(1) {}

   explicit Utf8Code(char b1) : sym{b1},len(1) {}

   Utf8Code(char b1,char b2) : sym{b1,b2},len(2) {}

   Utf8Code(char b1,char b2,char b3) : sym{b1,b2,b3},len(3) {}

   Utf8Code(char b1,char b2,char b3,char b4) : sym{b1,b2,b3,b4},len(4) {}

   // methods

   unsigned getLen() const { return len; }

   uint8 operator [] (unsigned ind) const { return uint8( sym[ind] ); }

   static Unicode ToUnicode(uint8 b1)
    {
     return b1;
    }

   static Unicode ToUnicode(uint8 b1,uint8 b2)
    {
     return (uint32(b1&0x1Fu)<<6)|(b2&0x3Fu);
    }

   static Unicode ToUnicode(uint8 b1,uint8 b2,uint8 b3)
    {
     return (uint32(b1&0x0Fu)<<12)|(uint32(b2&0x3Fu)<<6)|(b3&0x3Fu);
    }

   static Unicode ToUnicode(uint8 b1,uint8 b2,uint8 b3,uint8 b4)
    {
     return (uint32(b1&0x07u)<<18)|(uint32(b2&0x3Fu)<<12)|(uint32(b3&0x3Fu)<<6)|(b4&0x3Fu);
    }

   Unicode toUnicode() const;

   bool isPrintable() const { return len>1 || CharIsPrintable(sym[0]) ; }

   // print object

   void print(PrinterType &out) const
    {
     switch( len )
       {
        case 1 :
         {
          Putobj(out,CharCode(sym[0]));
         }
        break;

        case 2 :
         {
          out.put(sym[0]);
          out.put(sym[1]);
         }
        break;

        case 3 :
         {
          out.put(sym[0]);
          out.put(sym[1]);
          out.put(sym[2]);
         }
        break;

        case 4 :
         {
          out.put(sym[0]);
          out.put(sym[1]);
          out.put(sym[2]);
          out.put(sym[3]);
         }
        break;
       }
    }
 };

/* functions */

Utf8Code ToUtf8(Unicode unicode); // 21 bit

inline unsigned Utf8Len(uint8 b1)
 {
  if( b1&0x80u )
    {
     if( (b1&0b1110'0000u)==0b1100'0000u ) return 2;

     if( (b1&0b1111'0000u)==0b1110'0000u ) return 3;

     if( (b1&0b1111'1000u)==0b1111'0000u ) return 4;

     return 0;
    }
  else
    {
     return 1;
    }
 }

inline bool Utf8Ext(uint8 b)
 {
  return (b&0b1100'0000u)==0b1000'0000u;
 }

Utf8Code PeekUtf8(StrLen text); // +text

Utf8Code CutUtf8(StrLen &text); // +text

Utf8Code PeekUtf8_guarded(StrLen text); // +text

Utf8Code CutUtf8_guarded(StrLen &text); // +text

void TrimUtf8End(StrLen &text); // removes non-complete trailing sequence

} // namespace CCore

#endif

