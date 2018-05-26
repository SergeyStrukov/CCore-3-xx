/* SysTime.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Target/LIN64
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/sys/SysTime.h>

#include <CCore/inc/sys/SysInternal.h>

namespace CCore {
namespace Sys {

/* functions */

MSecTimeType GetMSecTime() noexcept
 {
  TimeSpec time(CLOCK_REALTIME);

  return time.getMSec();
 }

SecTimeType GetSecTime() noexcept
 {
  TimeSpec time(CLOCK_REALTIME);

  return time.getSec();
 }

#if 0

ClockTimeType GetClockTime() noexcept
 {
  TimeSpec time(CLOCK_REALTIME);

  return time.getNanoSec();
 }

#endif

} // namespace Sys
} // namespace CCore


