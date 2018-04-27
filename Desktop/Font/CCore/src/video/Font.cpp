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

/* enum FontClass */

FontClass Correct(FontClass fc)
 {
  switch( fc )
    {
     case FontOldstyleSerif :
     case FontTransitionalSerif :
     case FontModernSerif :
     case FontClarendonSerif :
     case FontSlabSerif :
     case FontFreedomSerif :
     case FontSansSerif :
     case FontOrnamental :
     case FontScript :
     case FontSymbol :

       return fc;

     default: return FontHasNoClass;
    }
 }

const char * GetTextDesc(FontClass fc)
 {
  switch( fc )
    {
     case FontOldstyleSerif : return "Oldstyle Serif";
     case FontTransitionalSerif : return "Transitional Serif";
     case FontModernSerif : return "Modern Serif";
     case FontClarendonSerif : return "Clarendon Serif";
     case FontSlabSerif : return "Slab Serif";
     case FontFreedomSerif : return "Freedom Serif";
     case FontSansSerif : return "Sans Serif";
     case FontOrnamental : return "Ornamental";
     case FontScript : return "Script";
     case FontSymbol : return "Symbol";

     default: return "NoClass";
    }
 }

/* struct AbstractSparseString */

void AbstractSparseString::cutSuffix(ulen len,ulen &index)
 {
  index=getLen()-len;

  cutSuffix(len);
 }

bool AbstractSparseString::cutCenter(ulen len)
 {
  ulen total=getLen();

  GuardLen(len,total);

  ulen extra=total-len;
  ulen delta=extra/2;

  cutPrefix(total-=delta);
  cutSuffix(total-=delta);

  return extra&1u;
 }

bool AbstractSparseString::cutCenter(ulen len,ulen &index)
 {
  index=(getLen()-len)/2;

  return cutCenter(len);
 }

#ifdef CCORE_UTF8

/* class SingleString */

SingleString::SingleString(StrLen str_)
 : str(str_),
   cur(str_)
 {
  total=Utf8Len(str);
  count=total;
 }

 // props

ulen SingleString::getLen() const
 {
  return total;
 }

 // cursor

void SingleString::restart()
 {
  cur=str;
  count=total;
 }

auto SingleString::next() -> Result
 {
  if( +cur )
    {
     Char ch=CutUtf8_unicode(cur);

     count--;

     return {ch,true};
    }
  else
    {
     return {0,false};
    }
 }

ulen SingleString::getCount() const
 {
  return count;
 }

 // self-modification

void SingleString::cutPrefix(ulen len)
 {
  GuardLen(len,total);

  StrLen suffix=Utf8Move(str,len);
  str=str.prefix(suffix);
  total=len;

  cur=str;
  count=total;
 }

void SingleString::cutSuffix(ulen len)
 {
  GuardLen(len,total);

  str=Utf8Move(str,total-len);
  total=len;

  cur=str;
  count=total;
 }

/* class DoubleString */

DoubleString::DoubleString(StrLen str1_,StrLen str2_)
 : str1(str1_),
   str2(str2_),
   cur(str1_)
 {
  total1=Utf8Len(str1);
  total2=Utf8Len(str2);
  count=LenAdd(total1,total2);
 }

 // props

ulen DoubleString::getLen() const
 {
  return total1+total2;
 }

 // cursor

void DoubleString::restart()
 {
  cur=str1;
  first=true;
  count=total1+total2;
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

  Char ch=CutUtf8_unicode(cur);

  count--;

  return {ch,true};
 }

ulen DoubleString::getCount() const
 {
  return count;
 }

 // self-modification

void DoubleString::cutPrefix(ulen len)
 {
  if( len>total1 )
    {
     len-=total1;

     GuardLen(len,total2);

     StrLen suffix=Utf8Move(str2,len);
     str2=str2.prefix(suffix);
     total2=len;
    }
  else
    {
     StrLen suffix=Utf8Move(str1,len);
     str1=str1.prefix(suffix);
     total1=len;

     str2=Empty;
     total2=0;
    }

  cur=str1;
  first=true;
  count=total1+total2;
 }

void DoubleString::cutSuffix(ulen len)
 {
  if( len>total2 )
    {
     len-=total2;

     GuardLen(len,total1);

     str1=Utf8Move(str1,total1-len);
     total1=len;
    }
  else
    {
     str1=Utf8Move(str2,total2-len);
     total1=len;

     str2=Empty;
     total2=0;
    }

  cur=str1;
  first=true;
  count=total1+total2;
 }

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

#endif

/* class Font */

Font::Font() noexcept
 : ptr(&Object)
 {
  ptr->incRef();
 }

} // namespace Video
} // namespace CCore


