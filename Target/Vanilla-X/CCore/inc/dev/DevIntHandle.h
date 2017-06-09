/* DevIntHandle.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Target/Vanilla-X
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_dev_DevIntHandle_h
#define CCore_inc_dev_DevIntHandle_h

#include <CCore/inc/PlanInit.h>

namespace CCore {
namespace Dev {

/* GetPlanInitNode_...() */

PlanInitNode * GetPlanInitNode_DevIntHandle();

/* enum IntSource */

enum IntSource
 {
  Int_TINTx    = 92,

  Int_TableLen = 128
 };

/* functions */

void SetupIntHandler(IntSource int_source,Function<void (void)> handle_int);

void CleanupIntHandler(IntSource int_source);

void EnableInt(IntSource int_source);

void DisableInt(IntSource int_source);

} // namespace Dev
} // namespace CCore

#endif

