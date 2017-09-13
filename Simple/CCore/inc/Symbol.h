/* Symbol.h */
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

#ifndef CCore_inc_Symbol_h
#define CCore_inc_Symbol_h

#include <CCore/inc/Gadget.h>

#ifdef CCORE_UTF8
# include <CCore/inc/Utf8.h>
#endif

namespace CCore {

/* type Symbol */

#ifdef CCORE_UTF8

using Symbol = Utf8Code ;

#else

using Symbol = char ;

#endif

/* const MaxSymbolLen */

#ifdef CCORE_UTF8

inline constexpr unsigned MaxSymbolLen = 4 ;

#else

inline constexpr unsigned MaxSymbolLen = 1 ;

#endif

/* functions */

#ifdef CCORE_UTF8

inline int ToChar(Utf8Code ch) { return (ch.getLen()==1)?ch[0]:(-1); }

inline ulen SymbolLen(Utf8Code ch) { return ch.getLen(); }

inline StrLen SymbolRange(const Utf8Code &ch) { return ch.getRange(); }

inline Utf8Code PeekSymbol(StrLen text) // +text
 {
  return PeekUtf8(text);
 }

#else

inline char PeekSymbol(StrLen text) // +text
 {
  return *text;
 }

#endif

inline int ToChar(char ch) { return ch; }

inline ulen SymbolLen(char ch) { Used(ch); return 1; }

inline StrLen SymbolRange(const char &ch) { return Single(ch); }

} // namespace CCore

#endif

