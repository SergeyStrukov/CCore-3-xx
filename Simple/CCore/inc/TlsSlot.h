/* TlsSlot.h */
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

#ifndef CCore_inc_TlsSlot_h
#define CCore_inc_TlsSlot_h

#include <CCore/inc/PlanInit.h>

#include <CCore/inc/sys/SysTlsSlot.h>
#include <CCore/inc/sys/SysPlanInit.h>

namespace CCore {

/* classes */

class TlsSlot;

/* class TlsSlot */

class TlsSlot : PlanInitReqList<PlanInitReq<Sys::GetPlanInitNode_Sys> > , public PlanInitNode
 {
   Sys::TlsSlot slot;

  private:

   virtual void init();

   virtual void exit();

  public:

   explicit TlsSlot(const char *tag);

   ~TlsSlot();

   void set(void *value) { slot.set(value); }

   void * get() { return slot.get(); }
 };

} // namespace CCore

#endif


