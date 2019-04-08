/* SysTime.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Target/LIN64utf8
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_sys_SysTime_h
#define CCore_inc_sys_SysTime_h

#include <CCore/inc/Gadget.h>

namespace CCore {
namespace Sys {

/* types */

using MSecTimeType = uint64 ;  // unsigned integral type

using SecTimeType = uint64 ;   // unsigned integral type

using ClockTimeType = uint64 ; // unsigned integral type

/* functions */

MSecTimeType GetMSecTime() noexcept;

SecTimeType GetSecTime() noexcept;

ClockTimeType GetClockTime() noexcept;

} // namespace Sys
} // namespace CCore

#endif


