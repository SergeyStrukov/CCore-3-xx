/* Font.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Desktop
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
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

  auto operator () (Char ch) const
   {
#ifdef CCORE_UTF8

    if( ch>=128 ) return DefaultFont(0);

    return DefaultFont((char)ch);

#else

    return DefaultFont(ch);

#endif
   }
 };

using DefFont = DotFontBase<DefFontShape> ;

DefFont Object CCORE_INITPRI_3 ;

} // namespace Private_Font

using namespace Private_Font;

#ifdef CCORE_UTF8

#else

/* class SingleString */

SingleString::SingleString(StrLen str_)
 : str(str_),
   cur(str_)
 {
 }

 // props

ulen SingleString::getLen() const
 {
  return str.len;
 }

// cursor

void SingleString::restart()
 {
  cur=str;
 }

auto SingleString::next() -> Result
 {
  if( +cur )
    {
     Char ch=*cur;

     ++cur;

     return {ch,true};
    }
  else
    {
     return {0,false};
    }
 }

ulen SingleString::getCount() const
 {
  return cur.len;
 }

 // self-modification

void SingleString::cutPrefix(ulen len)
 {
  GuardLen(len,str.len);

  str=str.prefix(len);

  cur=str;
 }

void SingleString::cutSuffix(ulen len)
 {
  GuardLen(len,str.len);

  str=str.suffix(len);

  cur=str;
 }

void SingleString::cutSuffix(ulen len,ulen &index)
 {
  GuardLen(len,str.len);

  index=str.len-len;

  str=str.suffix(len);

  cur=str;
 }

bool SingleString::cutCenter(ulen len)
 {
  GuardLen(len,str.len);

  ulen extra=str.len-len;
  ulen delta=extra/2;

  str=str.inner(delta,delta);

  cur=str;

  return extra&1u;
 }

bool SingleString::cutCenter(ulen len,ulen &index)
 {
  GuardLen(len,str.len);

  ulen extra=str.len-len;
  ulen delta=extra/2;

  index=delta;

  str=str.inner(delta,delta);

  cur=str;

  return extra&1u;
 }

/* class DoubleString */

DoubleString::DoubleString(StrLen str1_,StrLen str2_)
 : str1(str1_),
   str2(str2_),
   cur(str1_)
 {
  total=LenAdd(str1.len,str2.len);
 }

 // props

ulen DoubleString::getLen() const
 {
  return total;
 }

 // cursor

void DoubleString::restart()
 {
  cur=str1;
  first=true;
 }

auto DoubleString::next() -> Result
 {
  if( !cur )
    {
     if( first )
       {
        cur=str2;
        first=false;

        if( !cur ) return {0,false};
       }
     else
       {
        return {0,false};
       }
    }

  Char ch=*cur;

  ++cur;

  return {ch,true};
 }

ulen DoubleString::getCount() const
 {
  if( first )
    return cur.len+str2.len;
  else
    return cur.len;
 }

 // self-modification

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

  cur=str1;
  first=true;
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

  cur=str1;
  first=true;
 }

void DoubleString::cutSuffix(ulen len,ulen &index)
 {
  index=total-len;

  cutSuffix(len);
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

        cur=str1;
        first=true;

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

        cur=str1;
        first=true;

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

        cur=str1;
        first=true;

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

        cur=str1;
        first=true;

        return ret;
       }
    }
 }

bool DoubleString::cutCenter(ulen len,ulen &index)
 {
  index=(total-len)/2;

  return cutCenter(len);
 }

#endif

#ifdef CCORE_UTF8

/* class CharString */

CharString::CharString(PtrLen<const Char> str_)
 : str(str_),
   cur(str_)
 {
 }

 // props

ulen CharString::getLen() const
 {
  return str.len;
 }

 // cursor

void CharString::restart()
 {
  cur=str;
 }

auto CharString::next() -> Result
 {
  if( +cur )
    {
     Char ch=*cur;

     ++cur;

     return {ch,true};
    }
  else
    {
     return {0,false};
    }
 }

ulen CharString::getCount() const
 {
  return cur.len;
 }

 // self-modification

void CharString::cutPrefix(ulen len)
 {
  GuardLen(len,str.len);

  str=str.prefix(len);

  cur=str;
 }

void CharString::cutSuffix(ulen len)
 {
  GuardLen(len,str.len);

  str=str.suffix(len);

  cur=str;
 }

void CharString::cutSuffix(ulen len,ulen &index)
 {
  GuardLen(len,str.len);

  index=str.len-len;

  str=str.suffix(len);

  cur=str;
 }

bool CharString::cutCenter(ulen len)
 {
  GuardLen(len,str.len);

  ulen extra=str.len-len;
  ulen delta=extra/2;

  str=str.inner(delta,delta);

  cur=str;

  return extra&1u;
 }

bool CharString::cutCenter(ulen len,ulen &index)
 {
  GuardLen(len,str.len);

  ulen extra=str.len-len;
  ulen delta=extra/2;

  index=delta;

  str=str.inner(delta,delta);

  cur=str;

  return extra&1u;
 }

#endif

/* class Font */

Font::Font() noexcept
 : ptr(&Object)
 {
  ptr->incRef();
 }

} // namespace Video
} // namespace CCore


