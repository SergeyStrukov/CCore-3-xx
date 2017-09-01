/* SysUtf8.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Target/WIN32utf8
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/sys/SysUtf8.h>

namespace CCore {
namespace Sys {

/* functions */

const WChar * ZScan(const WChar *ztext)
 {
  for(; *ztext ;ztext++);

  return ztext;
 }

ulen ZLen(const WChar *ztext)
 {
  return Dist(ztext,ZScan(ztext));
 }

/* functions */

ulen Truncate(PtrLen<const WChar> text,PtrLen<char> out)
 {
  ulen len=out.len;

  FeedUnicode(text, [&] (Unicode sym)
                        {
                         Utf8Code code=ToUtf8(sym);

                         if( code.getLen()>out.len ) return false;

                         code.getRange().copyTo(out.ptr);

                         out+=code.getLen();

                         return true;

                        } );

  return len-out.len;
 }

ulen Full(PtrLen<const WChar> text,PtrLen<char> out)
 {
  ulen len=out.len;

  bool ok=FeedUnicode(text, [&] (Unicode sym)
                                {
                                 Utf8Code code=ToUtf8(sym);

                                 if( code.getLen()>out.len ) return false;

                                 code.getRange().copyTo(out.ptr);

                                 out+=code.getLen();

                                 return true;

                                } );

  if( ok ) return len-out.len;

  return MaxULen;
 }

ulen Full(const WChar *ztext,PtrLen<char> out)
 {
  return Full(Range(ztext,ZLen(ztext)),out);
 }

} // namespace Sys
} // namespace CCore

