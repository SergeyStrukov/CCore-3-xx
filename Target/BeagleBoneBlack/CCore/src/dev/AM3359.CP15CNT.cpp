/* AM3359.CP15CNT.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.01
//
//  Tag: Target/BeagleBoneBlack
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/dev/AM3359.CP15CNT.h>

namespace AM3359 {
namespace CP15CNT {

#if 0

 // Fake code

Type_Control GetControl() noexcept { return Type_Control(0); }

void SetControl(Type_Control) noexcept {}

Type_UserCountEnable GetUserCountEnable() noexcept { return Type_UserCountEnable(0); }

void SetUserCountEnable(Type_UserCountEnable) noexcept {}

Type_ClockCount GetClockCount() noexcept { return Type_ClockCount(0); }

Type_Count GetCount() noexcept { return Type_Count(0); }

void SetCounterSelect(Type_CounterSelect) noexcept {}

void SetEventSelect(Type_EventSelect) noexcept {}

void SetCountEnableSet(Type_CounterBits) noexcept {}

void SetCountEnableClear(Type_CounterBits) noexcept {}

Type_CounterBits GetCountOverflowStatus() noexcept { return Type_CounterBits(0); }

void SetCountOverflowStatus(Type_CounterBits) noexcept {}

void SetIntEnableSet(Type_CounterBits) noexcept {}

void SetIntEnableClear(Type_CounterBits) noexcept {}

void SetCountInc(Type_CounterBits) noexcept {}

void SetCount(Type_Count) noexcept {}

#endif

} // namespace CP15CNT
} // namespace AM3359
