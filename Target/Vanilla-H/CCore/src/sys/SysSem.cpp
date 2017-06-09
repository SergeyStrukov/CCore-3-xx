/* SysSem.cpp */
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

#include <CCore/inc/sys/SysSem.h>

namespace CCore {
namespace Sys {

/* struct Sem */

ErrorType Sem::init(ulen /*count*/) noexcept
 {
  // TODO

  return NoError;
 }

void Sem::exit() noexcept
 {
  // TODO
 }

void Sem::give() noexcept
 {
  // TODO
 }

void Sem::give_many(ulen /*count*/) noexcept
 {
  // TODO
 }

bool Sem::try_take() noexcept
 {
  // TODO

  return false;
 }

void Sem::take() noexcept
 {
  // TODO
 }

bool Sem::take(MSec /*timeout*/) noexcept
 {
  // TODO

  return false;
 }

bool Sem::take(TimeScope /*time_scope*/) noexcept
 {
  // TODO

  return false;
 }

} // namespace Sys
} // namespace CCore


