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

void GuardUtf8Broken()
 {
  Printf(Exception,"CCore::PeekUtf8_guarded(...) : broken UTF8 sequence");
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

Utf8Code PeekUtf8(StrLen text)
 {
  char b1=*text;

  switch( Utf8Len(b1) )
    {
     case 0 : default: [[fallthrough]];

     case 1 : return Utf8Code(b1);

     case 2 :
      {
       if( text.len<2 ) return Utf8Code(b1);

       char b2=text[1];

       if( !Utf8Ext(b2) ) return Utf8Code(b1);

       Utf8Code ret(b1,b2);

       if( ret.toUnicode()<0x80u ) return Utf8Code(b1);

       return ret;
      }

     case 3 :
      {
       if( text.len<3 ) return Utf8Code(b1);

       char b2=text[1];
       char b3=text[2];

       if( !Utf8Ext(b2) || !Utf8Ext(b3) ) return Utf8Code(b1);

       Utf8Code ret(b1,b2,b3);

       if( ret.toUnicode()<0x800u ) return Utf8Code(b1);

       return ret;
      }

     case 4 :
      {
       if( text.len<4 ) return Utf8Code(b1);

       char b2=text[1];
       char b3=text[2];
       char b4=text[3];

       if( !Utf8Ext(b2) || !Utf8Ext(b3) || !Utf8Ext(b4) ) return Utf8Code(b1);

       Utf8Code ret(b1,b2,b3,b4);

       if( ret.toUnicode()<0x10000u ) return Utf8Code(b1);

       return ret;
      }
    }
 }

Utf8Code CutUtf8(StrLen &text)
 {
  auto ret=PeekUtf8(text);

  text+=ret.getLen();

  return ret;
 }

Utf8Code PeekUtf8_guarded(StrLen text)
 {
  char b1=*text;

  switch( Utf8Len(b1) )
    {
     case 0 : default: GuardUtf8Broken(); [[fallthrough]];

     case 1 : return Utf8Code(b1);

     case 2 :
      {
       if( text.len<2 ) GuardUtf8Broken();

       char b2=text[1];

       if( !Utf8Ext(b2) ) GuardUtf8Broken();

       Utf8Code ret(b1,b2);

       if( ret.toUnicode()<0x80u ) GuardUtf8Broken();

       return ret;
      }

     case 3 :
      {
       if( text.len<3 ) GuardUtf8Broken();

       char b2=text[1];
       char b3=text[2];

       if( !Utf8Ext(b2) || !Utf8Ext(b3) ) GuardUtf8Broken();

       Utf8Code ret(b1,b2,b3);

       if( ret.toUnicode()<0x800u ) GuardUtf8Broken();

       return ret;
      }

     case 4 :
      {
       if( text.len<4 ) GuardUtf8Broken();

       char b2=text[1];
       char b3=text[2];
       char b4=text[3];

       if( !Utf8Ext(b2) || !Utf8Ext(b3) || !Utf8Ext(b4) ) GuardUtf8Broken();

       Utf8Code ret(b1,b2,b3,b4);

       if( ret.toUnicode()<0x10000u ) GuardUtf8Broken();

       return ret;
      }
    }
 }

Utf8Code CutUtf8_guarded(StrLen &text)
 {
  auto ret=PeekUtf8_guarded(text);

  text+=ret.getLen();

  return ret;
 }

Unicode CutUtf8_unicode(StrLen &text)
 {
  char b1=*text;

  switch( Utf8Len(b1) )
    {
     case 0 : default: return Unicode(-1);

     case 1 : ++text; return Utf8Code::ToUnicode(b1);

     case 2 :
      {
       if( text.len<2 ) return Unicode(-1);

       char b2=text[1];

       if( !Utf8Ext(b2) ) return Unicode(-1);

       Unicode ret=Utf8Code::ToUnicode(b1,b2);

       if( ret<0x80u ) return Unicode(-1);

       text+=2;

       return ret;
      }

     case 3 :
      {
       if( text.len<3 ) return Unicode(-1);

       char b2=text[1];
       char b3=text[2];

       if( !Utf8Ext(b2) || !Utf8Ext(b3) ) return Unicode(-1);

       Unicode ret=Utf8Code::ToUnicode(b1,b2,b3);

       if( ret<0x800u ) return Unicode(-1);

       text+=3;

       return ret;
      }

     case 4 :
      {
       if( text.len<4 ) return Unicode(-1);

       char b2=text[1];
       char b3=text[2];
       char b4=text[3];

       if( !Utf8Ext(b2) || !Utf8Ext(b3) || !Utf8Ext(b4) ) return Unicode(-1);

       Unicode ret=Utf8Code::ToUnicode(b1,b2,b3,b4);

       if( ret<0x10000u ) return Unicode(-1);

       text+=4;

       return ret;
      }
    }
 }

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

  for(; +text ;CutUtf8(text)) ret++;

  return ret;
 }

ulen Utf8Len_guarded(StrLen text)
 {
  ulen ret=0;

  for(; +text ;CutUtf8_guarded(text)) ret++;

  return ret;
 }

} // namespace CCore

