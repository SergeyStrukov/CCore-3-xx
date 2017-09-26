/* StrToChar.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Applied
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_StrToChar_h
#define CCore_inc_StrToChar_h

#include <CCore/inc/Symbol.h>
#include <CCore/inc/Array.h>

namespace CCore {

/* classes */

class StrToChar;

class CharToStr;

/* class StrToChar */

#ifdef CCORE_UTF8

class StrToChar : NoCopy
 {
   DynArray<Char> buf;

  public:

   explicit StrToChar(StrLen text);

   ~StrToChar() {}

   PtrLen<const Char> operator + () const { return Range(buf); }

   operator PtrLen<const Char>() const { return Range(buf); }
 };

#else

class StrToChar : NoCopy
 {
   StrLen text;

  public:

   explicit StrToChar(StrLen text_) : text(text_) {}

   StrLen operator + () const { return text; }

   operator StrLen() const { return text; }
 };

#endif

/* class CharToStr */

#ifdef CCORE_UTF8

class CharToStr : NoCopy
 {
   DynArray<char> buf;

  public:

   explicit CharToStr(PtrLen<const Char> text);

   ~CharToStr() {}

   StrLen operator + () const { return Range(buf); }

   operator StrLen() const { return Range(buf); }
 };

#else

class CharToStr : NoCopy
 {
   StrLen text;

  public:

   explicit CharToStr(StrLen text_) : text(text_) {}

   StrLen operator + () const { return text; }

   operator StrLen() const { return text; }
 };

#endif

} // namespace CCore

#endif

