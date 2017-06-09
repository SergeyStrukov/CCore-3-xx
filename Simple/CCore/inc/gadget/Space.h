/* Space.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Simple Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_gadget_Space_h
#define CCore_inc_gadget_Space_h

#include <CCore/inc/gadget/Len.h>
#include <CCore/inc/gadget/Nothing.h>

namespace CCore {

/* classes */

struct DeltaLen;

struct Space;

/* struct DeltaLen */

struct DeltaLen
 {
  ulen delta;
  bool ok;

  DeltaLen(NothingType) : delta(0),ok(false) {}

  DeltaLen(ulen delta_) : delta(delta_),ok(true) {}
 };

/* struct Space */

struct Space
 {
  void *mem;
  ulen len;

  Space() noexcept : mem(0),len(0) {}

  Space(NothingType) : Space() {}

  Space(void *mem_,ulen len_) : mem(mem_),len(len_) {}
 };

} // namespace CCore

#endif


