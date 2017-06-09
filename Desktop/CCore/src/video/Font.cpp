/* Font.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: Desktop
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/video/Font.h>

#include <CCore/inc/video/SimpleConsole.h>

#include <CCore/inc/Exception.h>

namespace CCore {
namespace Video {

namespace Private_Font {

struct DefFontShape
 {
  static Coord dX() { return DefaultFont::DX; }

  static Coord dY() { return DefaultFont::DY; }

  static Coord bY() { return DefaultFont::BY; }

  auto operator () (char ch) const { return DefaultFont(ch); }
 };

using DefFont = DotFontBase<DefFontShape> ;

DefFont Object CCORE_INITPRI_3 ;

} // namespace Private_Font

using namespace Private_Font;

/* struct AbstractSparseString */

ULenSat AbstractSparseString::countLen(bool guard_overflow)
 {
  ULenSat ret;

  apply( [&ret] (StrLen str) { ret+=str.len; } );

  if( guard_overflow && ret.overflow )
    {
     Printf(Exception,"CCore::Video::AbstractSparseString::countLen(true) : overflow");
    }

  return ret;
 }

/* class SingleString */

void SingleString::restart()
 {
  first=true;
 }

StrLen SingleString::next()
 {
  if( first )
    {
     first=false;

     return str;
    }

  return Empty;
 }

void SingleString::cutPrefix(ulen len)
 {
  GuardLen(len,str.len);

  str=str.prefix(len);

  first=true;
 }

void SingleString::cutSuffix(ulen len)
 {
  GuardLen(len,str.len);

  str=str.suffix(len);

  first=true;
 }

bool SingleString::cutCenter(ulen len)
 {
  GuardLen(len,str.len);

  ulen extra=str.len-len;
  ulen delta=extra/2;

  str=str.inner(delta,delta);

  first=true;

  return extra&1u;
 }

/* class DoubleString */

DoubleString::DoubleString(StrLen str1_,StrLen str2_)
 : str1(str1_),
   str2(str2_)
 {
  if( !str1 )
    {
     str1=str2;
     str2=Empty;
    }
 }

void DoubleString::restart()
 {
  ind=1;
 }

StrLen DoubleString::next()
 {
  switch( ind )
    {
     case 1 : ind++; return str1;
     case 2 : ind++; return str2;

     default: return Empty;
    }
 }

void DoubleString::cutPrefix(ulen len)
 {
  if( len>str1.len )
    {
     len-=str1.len;

     GuardLen(len,str2.len);

     str2=str2.prefix(len);
    }
  else
    {
     str1=str1.prefix(len);
     str2=Empty;
    }

  ind=1;
 }

void DoubleString::cutSuffix(ulen len)
 {
  if( len>str2.len )
    {
     len-=str2.len;

     GuardLen(len,str1.len);

     str1=str1.suffix(len);
    }
  else
    {
     str1=str2.suffix(len);
     str2=Empty;
    }

  ind=1;
 }

bool DoubleString::cutCenter(ulen len)
 {
  if( str1.len>str2.len )
    {
     ulen d=str1.len-str2.len;

     if( d>=len )
       {
        auto s=str1.suffix(d);

        ulen extra=d-len;
        ulen delta=extra/2;

        str1=s.inner(delta,delta);
        str2=Empty;

        ind=1;

        return extra&1u;
       }
     else
       {
        ulen s=len-d;

        bool ret = s&1u ;

        ulen len2=s/2+ret;
        ulen len1=d+len2;

        GuardLen(len2,str2.len);

        str1=str1.suffix(len1);
        str2=str2.prefix(len2);

        ind=1;

        return ret;
       }
    }
  else
    {
     ulen d=str2.len-str1.len;

     if( d>=len )
       {
        auto s=str2.prefix(d);

        ulen extra=d-len;
        ulen delta=extra/2;

        str1=s.inner(delta,delta);
        str2=Empty;

        ind=1;

        return extra&1u;
       }
     else
       {
        ulen s=len-d;

        bool ret = s&1u ;

        ulen len1=s/2+ret;
        ulen len2=d+len1;

        GuardLen(len1,str1.len);

        str1=str1.suffix(len1);
        str2=str2.prefix(len2);

        ind=1;

        return ret;
       }
    }
 }

/* class Font */

Font::Font() noexcept
 : ptr(&Object)
 {
  ptr->incRef();
 }

} // namespace Video
} // namespace CCore


