/* SysSpawn.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.60
//
//  Tag: Target/Vanilla-H
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/sys/SysSpawn.h>

namespace CCore {
namespace Sys {

/* GetShell() */

StrLen GetShell(char /*buf*/[MaxPathLen+1])
 {
  // TODO

  return "C:\\WINDOWS\\system32\\cmd.exe"_c;
 }

/* GetEnviron() */

void GetEnviron(Function<void (StrLen)> /*func*/)
 {
  // TODO
 }

/* struct SpawnChild */

ErrorType SpawnChild::spawn(char * /*wdir*/,char * /*path*/,char ** /*argv*/,char ** /*envp*/)
 {
  // TODO

  return NoError;
 }

auto SpawnChild::wait() -> WaitResult
 {
  // TODO

  return {};
 }

/* struct SpawnWaitList */

ErrorType SpawnWaitList::init(ulen /*reserve*/)
 {
  // TODO

  return NoError;
 }

ErrorType SpawnWaitList::exit()
 {
  // TODO

  return NoError;
 }

ErrorType SpawnWaitList::add(SpawnChild * /*spawn*/,void * /*arg*/)
 {
  // TODO

  return NoError;
 }

auto SpawnWaitList::wait() -> WaitResult
 {
  // TODO

  return {};
 }

} // namespace Sys
} // namespace CCore