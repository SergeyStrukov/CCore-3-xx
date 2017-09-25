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

#include <CCore/inc/Gadget.h>

namespace CCore {

/* type Unicode */

using Unicode = uint32 ;

/* guard functions */

void GuardUtf8Broken(const char *name);

/* classes */

class Utf8Code;

/* class Utf8Code */

class Utf8Code
 {
   char sym[4];
   unsigned len;

  public:

   Utf8Code() noexcept : sym{},len(1) {}

   Utf8Code(NothingType) : Utf8Code() {}

   explicit Utf8Code(char b1) : sym{b1},len(1) {}

   Utf8Code(char b1,char b2) : sym{b1,b2},len(2) {}

   Utf8Code(char b1,char b2,char b3) : sym{b1,b2,b3},len(3) {}

   Utf8Code(char b1,char b2,char b3,char b4) : sym{b1,b2,b3,b4},len(4) {}

   Utf8Code(const char *ptr,ulen len)
    {
     switch( len )
       {
        case 1 : (*this)=Utf8Code(ptr[0]); break;
        case 2 : (*this)=Utf8Code(ptr[0],ptr[1]); break;
        case 3 : (*this)=Utf8Code(ptr[0],ptr[1],ptr[2]); break;
        case 4 : (*this)=Utf8Code(ptr[0],ptr[1],ptr[2],ptr[3]); break;

        default: (*this)=Utf8Code(); break;
       }
    }

   explicit Utf8Code(StrLen str) : Utf8Code(str.ptr,str.len) {}

   // methods

   unsigned getLen() const { return len; }

   PtrLen<const char> getRange() const { return Range(sym,len); }

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

   Unicode toUnicode() const
    {
     switch( len )
       {
        case 1 : return ToUnicode(sym[0]);
        case 2 : return ToUnicode(sym[0],sym[1]);
        case 3 : return ToUnicode(sym[0],sym[1],sym[2]);
        case 4 : return ToUnicode(sym[0],sym[1],sym[2],sym[3]);

        default: return 0;
       }
    }

   // print object

   void print(PrinterType &out) const
    {
     out.put(sym,len);
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

/* parse functions */

template <class Ret>
Ret PeekUtf8_gen(StrLen text) // +text
 {
  char b1=*text;

  switch( Utf8Len(b1) )
    {
     case 0 : default: return Ret(b1);

     case 1 : return Ret(b1,Utf8Code::ToUnicode(b1));

     case 2 :
      {
       if( text.len<2 ) return Ret(b1);

       char b2=text[1];

       if( !Utf8Ext(b2) ) return Ret(b1);

       Unicode ch=Utf8Code::ToUnicode(b1,b2);

       if( ch<0x80u ) return Ret(b1);

       return Ret(b1,b2,ch);
      }

     case 3 :
      {
       if( text.len<3 ) return Ret(b1);

       char b2=text[1];
       char b3=text[2];

       if( !Utf8Ext(b2) || !Utf8Ext(b3) ) return Ret(b1);

       Unicode ch=Utf8Code::ToUnicode(b1,b2,b3);

       if( ch<0x800u ) return Ret(b1);

       return Ret(b1,b2,b3,ch);
      }

     case 4 :
      {
       if( text.len<4 ) return Ret(b1);

       char b2=text[1];
       char b3=text[2];
       char b4=text[3];

       if( !Utf8Ext(b2) || !Utf8Ext(b3) || !Utf8Ext(b4) ) return Ret(b1);

       Unicode ch=Utf8Code::ToUnicode(b1,b2,b3,b4);

       if( ch<0x10000u ) return Ret(b1);

       return Ret(b1,b2,b3,b4,ch);
      }
    }
 }

Utf8Code PeekUtf8(StrLen text); // +text

Utf8Code CutUtf8(StrLen &text); // +text

Utf8Code PeekUtf8_guarded(StrLen text); // +text

Utf8Code CutUtf8_guarded(StrLen &text); // +text

Unicode PeekUtf8_unicode(StrLen text); // +text , Unicode(-1) on error

Unicode CutUtf8_unicode(StrLen &text); // +text , Unicode(-1) on error

/* functions */

void TrimUtf8End(StrLen &text); // removes non-complete trailing sequence

ulen Utf8Len(StrLen text);

ulen Utf8Len_guarded(StrLen text);

} // namespace CCore

#endif

