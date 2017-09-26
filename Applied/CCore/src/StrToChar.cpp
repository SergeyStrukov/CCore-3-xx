/* StrToChar.cpp */
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

#include <CCore/inc/StrToChar.h>

namespace CCore {

/* class StrToChar */

#ifdef CCORE_UTF8

StrToChar::StrToChar(StrLen text)
 : buf(DoReserve,text.len)
 {
  while( +text )
    {
     Unicode ch=CutUtf8_unicode(text);

     if( ch==Unicode(-1) ) GuardUtf8Broken("CCore::StrToChar::StrToChar(...)");

     buf.append_copy(ch);
    }
 }

#endif

/* class CharToStr */

#ifdef CCORE_UTF8

CharToStr::CharToStr(PtrLen<const Char> text)
 : buf(DoReserve,2*text.len)
 {
  for(Char ch : text )
    {
     Utf8Code code=ToUtf8(ch);

     buf.extend_copy(code.getRange());
    }
 }

#endif

} // namespace CCore

