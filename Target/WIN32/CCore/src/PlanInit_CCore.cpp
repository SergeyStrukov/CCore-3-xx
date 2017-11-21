/* PlanInit_CCore.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Target/WIN32
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/PlanInit.h>

#ifndef CCORE_MINI

#include <CCore/inc/PacketPool.h>
#include <CCore/inc/TaskMemStack.h>
#include <CCore/inc/DeferCall.h>

#endif

#include <CCore/inc/Job.h>
#include <CCore/inc/ObjHost.h>
#include <CCore/inc/PerTask.h>
#include <CCore/inc/Scope.h>

namespace CCore {

/* GetPlanInitNode_...() */

namespace Private_PlanInit_CCore {

struct Empty
 {
  static const char * GetTag() { return "CCore"; }
 };

PlanInitObject<Empty,PlanInitReq<GetPlanInitNode_JobHost>
                    ,PlanInitReq<GetPlanInitNode_PerTask>
                    ,PlanInitReq<GetPlanInitNode_ObjHost>
                    ,PlanInitReq<GetPlanInitNode_Scope>

#ifndef CCORE_MINI

                    ,PlanInitReq<GetPlanInitNode_PacketPool>
                    ,PlanInitReq<GetPlanInitNode_TaskMemStack>
                    ,PlanInitReq<GetPlanInitNode_DeferCall>

#endif

                    > Object CCORE_INITPRI_1 ;

} // namespace Private_PlanInit_CCore

using namespace Private_PlanInit_CCore;

PlanInitNode * GetPlanInitNode_CCore() { return &Object; }

} // namespace CCore


