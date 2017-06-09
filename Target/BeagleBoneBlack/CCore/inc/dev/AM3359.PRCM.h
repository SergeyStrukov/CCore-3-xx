/* AM3359.PRCM.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Target/BeagleBoneBlack
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_dev_AM3359_PRCM_h
#define CCore_inc_dev_AM3359_PRCM_h

#include <CCore/inc/dev/AM3359.h>
#include <CCore/inc/dev/DevRW.h>
#include <CCore/inc/dev/DevControlMutex.h>

namespace AM3359 {
namespace PRCM {

//
// Use Dev::ControlMutex to protect against race-condition.
//

/* AM3359.PRCM.desc -> AM3359.PRCM.gen.h */

#include <CCore/inc/dev/AM3359.PRCM.gen.h>

/* struct BarPER */

struct BarPER : PERBar<CCore::Dev::RegRW>
 {
  BarPER() : PERBar<CCore::Dev::RegRW>(0x44E0'0000) {}
 };

/* struct BarDPLL */

struct BarDPLL : DPLLBar<CCore::Dev::RegRW>
 {
  BarDPLL() : DPLLBar<CCore::Dev::RegRW>(0x44E0'0500) {}
 };

/* struct BarWKUP */

struct BarWKUP : WKUPBar<CCore::Dev::RegRW>
 {
  BarWKUP() : WKUPBar<CCore::Dev::RegRW>(0x44E0'0400) {}
 };

} // namespace PRCM
} // namespace AM3359

#endif

