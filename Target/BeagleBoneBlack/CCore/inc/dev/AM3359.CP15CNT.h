/* AM3359.CP15CNT.h */
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

#ifndef CCore_inc_dev_AM3359_CP15CNT_h
#define CCore_inc_dev_AM3359_CP15CNT_h

#include <CCore/inc/dev/AM3359.h>

namespace AM3359 {
namespace CP15CNT {

/* AM3359.CP15CNT.desc -> AM3359.CP15CNT.gen.h */

#include <CCore/inc/dev/AM3359.CP15CNT.gen.h>

/* functions */

Type_Control GetControl() noexcept;

void SetControl(Type_Control) noexcept;

Type_UserCountEnable GetUserCountEnable() noexcept;

void SetUserCountEnable(Type_UserCountEnable) noexcept;

Type_ClockCount GetClockCount() noexcept;

Type_Count GetCount() noexcept;

void SetCount(Type_Count) noexcept;

void SetCounterSelect(Type_CounterSelect) noexcept;

void SetEventSelect(Type_EventSelect) noexcept;

void SetCountEnableSet(Type_CounterBits) noexcept;

void SetCountEnableClear(Type_CounterBits) noexcept;

Type_CounterBits GetCountOverflowStatus() noexcept;

void SetCountOverflowStatus(Type_CounterBits) noexcept;

void SetIntEnableSet(Type_CounterBits) noexcept;

void SetIntEnableClear(Type_CounterBits) noexcept;

void SetCountInc(Type_CounterBits) noexcept;

} // namespace CP15CNT
} // namespace AM3359

#endif

