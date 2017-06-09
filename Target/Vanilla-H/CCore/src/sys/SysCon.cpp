/* SysCon.cpp */
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

#include <CCore/inc/sys/SysCon.h>

namespace CCore {
namespace Sys {

/* functions */

void ConWrite(StrLen /*str*/) noexcept
 {
  // TODO
 }

/* struct ConRead */

ErrorType ConRead::init() noexcept
 {
  // TODO

  return NoError;
 }

ErrorType ConRead::exit() noexcept
 {
  // TODO

  return NoError;
 }

auto ConRead::read(char * /*buf*/,ulen /*len*/) noexcept -> IOResult
 {
  // TODO

  return IOResult{};
 }

auto ConRead::read(char * /*buf*/,ulen /*len*/,MSec /*timeout*/) noexcept -> IOResult
 {
  // TODO

  return IOResult{};
 }

auto ConRead::read(char * /*buf*/,ulen /*len*/,TimeScope /*time_scope*/) noexcept -> IOResult
 {
  // TODO

  return IOResult{};
 }

} // namespace Sys
} // namespace CCore


