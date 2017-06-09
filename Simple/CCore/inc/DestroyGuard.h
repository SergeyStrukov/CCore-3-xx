/* DestroyGuard.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: Simple
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_DestroyGuard_h
#define CCore_inc_DestroyGuard_h

#include <CCore/inc/Gadget.h>

namespace CCore {

/* DestroyGuardAbort() */

void DestroyGuardAbort();

void DestroyGuardAbort(StrLen name);

/* classes */

class DestroyGuard;

/* class DestroyGuard */

class DestroyGuard : NoCopy
 {
   bool locked = false ;

  public:

   DestroyGuard() {}

   ~DestroyGuard() { guard(); }

   // methods

   void lock() { locked=true; }

   void unlock() { locked=false; }

   void guard() { if( locked ) DestroyGuardAbort(); }

   void guard(StrLen name) { if( locked ) DestroyGuardAbort(name); }

   using Lock = LockObject<DestroyGuard> ;
 };

} // namespace CCore

#endif

