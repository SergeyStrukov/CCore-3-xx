/* AM3359.I2C.h */
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

#ifndef CCore_inc_dev_AM3359_I2C_h
#define CCore_inc_dev_AM3359_I2C_h

#include <CCore/inc/dev/AM3359.h>
#include <CCore/inc/dev/DevRW.h>

namespace AM3359 {
namespace I2C {

/* AM3359.I2C.desc -> AM3359.I2C.gen.h */

#include <CCore/inc/dev/AM3359.I2C.gen.h>

/* Instances */

enum Instance : uint32
 {
  I2C_0 = 0x44E0'B000,
  I2C_1 = 0x4802'A000,
  I2C_2 = 0x4819'C000
 };

/* struct Bar */

struct Bar : I2CBar<CCore::Dev::RegRW>
 {
  explicit Bar(Instance instance) : I2CBar<CCore::Dev::RegRW>(instance) {}
 };

} // namespace I2C
} // namespace AM3359

#endif

