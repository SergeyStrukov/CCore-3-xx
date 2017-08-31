/* SysUtf8.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Target/WIN323utf8
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_sys_SysUtf8_h
#define CCore_inc_sys_SysUtf8_h

#include <CCore/inc/Gadget.h>

namespace CCore {
namespace Sys {

/* type WChar */

using WChar = unsigned short ;

/* functions */

ulen Truncate(PtrLen<const WChar> text,PtrLen<char> out);

/* classes */

template <ulen Len_>
struct WCharToUtf8 : NoCopy
 {
  static constexpr ulen Len = Len_ ;

  WChar buf[Len];
  ulen len;

  ulen truncate(PtrLen<char> out) const { return Truncate(Range(buf,len),out); }
 };

} // namespace Sys
} // namespace CCore

#endif

