/* LockUse.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.60
//
//  Tag: Simple Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_gadget_LockUse_h
#define CCore_inc_gadget_LockUse_h

#include <CCore/inc/gadget/Classification.h>
#include <CCore/inc/gadget/NoCopy.h>

namespace CCore {

/* functions */

void GuardUseLocked();

/* classes */

template <UIntType UInt> class LockUse;

/* class LockUse<UInt> */

template <UIntType UInt>
class LockUse : NoCopy
 {
   UInt &count;

  public:

   explicit LockUse(UInt &count_) : count(count_) { if( !count_ ) GuardUseLocked(); count_--; }

   ~LockUse() { count++; }
 };

} // namespace CCore

#endif

