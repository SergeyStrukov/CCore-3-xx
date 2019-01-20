/* SymPart.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.60
//
//  Tag: Simple
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/Gadget.h>

#ifdef CCORE_UTF8
# include <CCore/inc/Utf8.h>
#endif

#ifndef CCore_inc_SymPart_h
#define CCore_inc_SymPart_h

namespace CCore {

/* functions */

inline StrLen SymPrefix(StrLen str,ulen len)
 {
#ifdef CCORE_UTF8

  return str.prefix(Utf8Move(str,len));

#else

  return str.safe_part(0,len);

#endif
 }

inline StrLen SymPart(StrLen str,ulen off)
 {
#ifdef CCORE_UTF8

  return Utf8Move(str,off);

#else

  return str.safe_part(off);

#endif
 }

inline StrLen SymPart(StrLen str,ulen off,ulen len)
 {
  return SymPrefix(SymPart(str,off),len);
 }

} // namespace CCore

#endif

