/* SysTime.cpp */
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

#include <CCore/inc/sys/SysTime.h>

#include <CCore/inc/Task.h>

#include <CCore/inc/dev/DevPlanInit.h>

namespace CCore {
namespace Sys {

/* GetPlanInitNode_...() */

namespace Private_SysTime {

/* class StartStop */

class StartStop : NoCopy
 {
   static void Timer_int()
    {
     Task::Internal::Tick_int();
    }

  public:

   StartStop()
    {
     // TODO
    }

   ~StartStop()
    {
     // TODO
    }

   static MSecTimeType GetMSecTime() noexcept
    {
     // TODO

     return 0;
    }

   static SecTimeType GetSecTime() noexcept
    {
     // TODO

     return 0;
    }

   static ClockTimeType GetClockTime() noexcept
    {
     // TODO

     return 0;
    }

   static const char * GetTag() { return "SysTime"; }
 };

PlanInitObject<StartStop,PlanInitReq<Dev::GetPlanInitNode_Dev> > Object CCORE_INITPRI_1 ;

} // namespace Private_SysTime

using namespace Private_SysTime;

PlanInitNode * GetPlanInitNode_SysTime() { return &Object; }

/* functions */

MSecTimeType GetMSecTime() noexcept
 {
  return StartStop::GetMSecTime();
 }

SecTimeType GetSecTime() noexcept
 {
  return StartStop::GetSecTime();
 }

ClockTimeType GetClockTime() noexcept
 {
  return StartStop::GetClockTime();
 }

void ClockDelay(ClockTimeType clocks) noexcept
 {
  for(auto start=GetClockTime(); GetClockTime()-start<=clocks ;);
 }

} // namespace Sys
} // namespace CCore

