/* Utf8.cpp */
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

#include <CCore/inc/Utf8.h>

#include <CCore/inc/Exception.h>

namespace CCore {

/* guard functions */

void GuardUtf8Broken(const char *name)
 {
  Printf(Exception,"#; : broken UTF8 sequence",name);
 }

/* functions */

Utf8Code ToUtf8(Unicode unicode)
 {
  if( unicode<0x80u )
    {
     uint8 b1=uint8(unicode);

     return Utf8Code(b1);
    }

  if( unicode<0x800u )
    {
     uint8 b1=0b1100'0000u|((unicode>>6)&0b01'1111u); // 5 bit
     uint8 b2=0b1000'0000u|((unicode   )&0b11'1111u); // 6 bit

     return Utf8Code(b1,b2);
    }

  if( unicode<0x10000u )
    {
     uint8 b1=0b1110'0000u|((unicode>>12)&0b00'1111u); // 4 bit
     uint8 b2=0b1000'0000u|((unicode>> 6)&0b11'1111u); // 6 bit
     uint8 b3=0b1000'0000u|((unicode    )&0b11'1111u); // 6 bit

     return Utf8Code(b1,b2,b3);
    }

  uint8 b1=0b1111'0000u|((unicode>>18)&0b00'0111u); // 3 bit
  uint8 b2=0b1000'0000u|((unicode>>12)&0b11'1111u); // 6 bit
  uint8 b3=0b1000'0000u|((unicode>> 6)&0b11'1111u); // 6 bit
  uint8 b4=0b1000'0000u|((unicode    )&0b11'1111u); // 6 bit

  return Utf8Code(b1,b2,b3,b4);
 }

/* parse functions */

Utf8Code PeekUtf8(StrLen text)
 {
  struct Ret : Utf8Code
   {
    Ret(char) : Utf8Code() {}

    Ret(char b1,Unicode) : Utf8Code(b1) {}

    Ret(char b1,char b2,Unicode) : Utf8Code(b1,b2) {}

    Ret(char b1,char b2,char b3,Unicode) : Utf8Code(b1,b2,b3) {}

    Ret(char b1,char b2,char b3,char b4,Unicode) : Utf8Code(b1,b2,b3,b4) {}
   };

  return PeekUtf8_gen<Ret>(text);
 }

Utf8Code CutUtf8(StrLen &text)
 {
  auto ret=PeekUtf8(text);

  text+=ret.getLen();

  return ret;
 }

Utf8Code PeekUtf8_guarded(StrLen text)
 {
  struct Ret : Utf8Code
   {
    Ret(char) : Utf8Code() { GuardUtf8Broken("CCore::PeekUtf8_guarded(...)"); }

    Ret(char b1,Unicode) : Utf8Code(b1) {}

    Ret(char b1,char b2,Unicode) : Utf8Code(b1,b2) {}

    Ret(char b1,char b2,char b3,Unicode) : Utf8Code(b1,b2,b3) {}

    Ret(char b1,char b2,char b3,char b4,Unicode) : Utf8Code(b1,b2,b3,b4) {}
   };

  return PeekUtf8_gen<Ret>(text);
 }

Utf8Code CutUtf8_guarded(StrLen &text)
 {
  auto ret=PeekUtf8_guarded(text);

  text+=ret.getLen();

  return ret;
 }

Unicode PeekUtf8_unicode(StrLen text)
 {
  struct Ret
   {
    Unicode ch;

    Ret(char) : ch(-1) {}

    Ret(char,Unicode ch_) : ch(ch_) {}

    Ret(char,char,Unicode ch_) : ch(ch_) {}

    Ret(char,char,char,Unicode ch_) : ch(ch_) {}

    Ret(char,char,char,char,Unicode ch_) : ch(ch_) {}

    operator Unicode() const { return ch; }
   };

  return PeekUtf8_gen<Ret>(text);
 }

Unicode CutUtf8_unicode(StrLen &text)
 {
  struct Ret
   {
    Unicode ch;
    unsigned len;

    Ret(char) : ch(-1),len(1) {}

    Ret(char,Unicode ch_) : ch(ch_),len(1) {}

    Ret(char,char,Unicode ch_) : ch(ch_),len(2) {}

    Ret(char,char,char,Unicode ch_) : ch(ch_),len(3) {}

    Ret(char,char,char,char,Unicode ch_) : ch(ch_),len(4) {}
   };

  Ret ret=PeekUtf8_gen<Ret>(text);

  text+=ret.len;

  return ret.ch;
 }

/* functions */

void TrimUtf8End(StrLen &text)
 {
  auto cur=RangeReverse(text);
  unsigned count=0;

  for(; +cur && count<2 && Utf8Ext(*cur) ;++cur,count++);

  unsigned len;

  if( +cur && (len=Utf8Len(*cur))!=0 && count<len-1 )
    {
     // trim

     text.len-=count+1;
    }
 }

ulen Utf8Len(StrLen text)
 {
  ulen ret=0;

  while( +text )
    {
     struct Ret
      {
       unsigned len;

       Ret(char) : len(1) {}

       Ret(char,Unicode) : len(1) {}

       Ret(char,char,Unicode) : len(2) {}

       Ret(char,char,char,Unicode) : len(3) {}

       Ret(char,char,char,char,Unicode) : len(4) {}

       operator unsigned() const { return len; }
      };

     unsigned len=PeekUtf8_gen<Ret>(text);

     text+=len;

     ret++;
    }

  return ret;
 }

ulen Utf8Len_guarded(StrLen text)
 {
  ulen ret=0;

  while( +text )
    {
     struct Ret
      {
       unsigned len;

       Ret(char) : len(1) { GuardUtf8Broken("CCore::Utf8Len_guarded(...)"); }

       Ret(char,Unicode) : len(1) {}

       Ret(char,char,Unicode) : len(2) {}

       Ret(char,char,char,Unicode) : len(3) {}

       Ret(char,char,char,char,Unicode) : len(4) {}

       operator unsigned() const { return len; }
      };

     unsigned len=PeekUtf8_gen<Ret>(text);

     text+=len;

     ret++;
    }

  return ret;
 }

} // namespace CCore

