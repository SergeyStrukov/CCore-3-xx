/* AM3359.ETH.h */
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

#ifndef CCore_inc_dev_AM3359_ETH_h
#define CCore_inc_dev_AM3359_ETH_h

#include <CCore/inc/dev/AM3359.h>
#include <CCore/inc/dev/DevRW.h>

namespace AM3359 {
namespace ETH {

/* AM3359.ETH.desc -> AM3359.ETH.gen.h */

#include <CCore/inc/dev/AM3359.ETH.gen.h>

/* struct BarSwitch */

struct BarSwitch : SwitchBar<CCore::Dev::RegRW>
 {
  BarSwitch() : SwitchBar<CCore::Dev::RegRW>(0x4A10'0000u) {}
 };

/* struct BarPort0 */

struct BarPort0 : Port0Bar<CCore::Dev::RegRW>
 {
  BarPort0() : Port0Bar<CCore::Dev::RegRW>(0x4A10'0100u) {}
 };

/* struct BarPort1 */

struct BarPort1 : Port1Bar<CCore::Dev::RegRW>
 {
  BarPort1() : Port1Bar<CCore::Dev::RegRW>(0x4A10'0200u) {}
 };

/* struct BarPort2 */

struct BarPort2 : Port2Bar<CCore::Dev::RegRW>
 {
  BarPort2() : Port2Bar<CCore::Dev::RegRW>(0x4A10'0300u) {}
 };

/* struct BarDMA */

struct BarDMA : DMABar<CCore::Dev::RegRW>
 {
  BarDMA() : DMABar<CCore::Dev::RegRW>(0x4A10'0800u) {}
 };

/* struct BarStat */

struct BarStat : StatBar<CCore::Dev::RegRW>
 {
  BarStat() : StatBar<CCore::Dev::RegRW>(0x4A10'0900u) {}
 };

/* struct BarDesc */

struct BarDesc : DescBar<CCore::Dev::RegRW>
 {
  BarDesc() : DescBar<CCore::Dev::RegRW>(0x4A10'0A00u) {}
 };

/* struct BarTimeSync */

struct BarTimeSync : TimeSyncBar<CCore::Dev::RegRW>
 {
  BarTimeSync() : TimeSyncBar<CCore::Dev::RegRW>(0x4A10'0C00u) {}
 };

/* struct BarALE */

struct BarALE : ALEBar<CCore::Dev::RegRW>
 {
  BarALE() : ALEBar<CCore::Dev::RegRW>(0x4A10'0D00u) {}
 };

/* struct BarSliver1 */

struct BarSliver1 : SliverBar<CCore::Dev::RegRW>
 {
  BarSliver1() : SliverBar<CCore::Dev::RegRW>(0x4A10'0D80u) {}
 };

/* struct BarSliver2 */

struct BarSliver2 : SliverBar<CCore::Dev::RegRW>
 {
  BarSliver2() : SliverBar<CCore::Dev::RegRW>(0x4A10'0DC0u) {}
 };

/* struct BarWR */

struct BarWR : WRBar<CCore::Dev::RegRW>
 {
  BarWR() : WRBar<CCore::Dev::RegRW>(0x4A10'1200u) {}
 };

/* struct BarMDIO */

struct BarMDIO : MDIOBar<CCore::Dev::RegRW>
 {
  BarMDIO() : MDIOBar<CCore::Dev::RegRW>(0x4A10'1000u) {}
 };

} // namespace ETH
} // namespace AM3359

#endif

