/* SysProp.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Target/Vanilla-H
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/sys/SysProp.h>

namespace CCore {
namespace Sys {

/* functions */

unsigned GetCpuCount() noexcept
 {
  // TODO

  return 1;
 }

unsigned GetSpinCount() noexcept
 {
  // TODO

  return 1000;
 }

} // namespace Sys
} // namespace CCore


