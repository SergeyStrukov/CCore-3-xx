/* DevPlanInit.cpp */
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

#include <CCore/inc/dev/DevPlanInit.h>

#include <CCore/inc/dev/DevIntHandle.h>

#include <__std_init.h>

namespace CCore {
namespace Dev {

/* Init_CPU() */

void Init_CPU()
 {
  // TODO
 }

/* GetPlanInitNode_...() */

namespace Private_DevPlanInit {

struct Empty
 {
  static const char * GetTag() { return "Dev"; }
 };

PlanInitObject<Empty,PlanInitReq<GetPlanInitNode_DevIntHandle> > Object CCORE_INITPRI_1 ;

} // namespace Private_DevPlanInit

using namespace Private_DevPlanInit;

PlanInitNode * GetPlanInitNode_Dev() { return &Object; }

} // namespace Dev
} // namespace CCore


