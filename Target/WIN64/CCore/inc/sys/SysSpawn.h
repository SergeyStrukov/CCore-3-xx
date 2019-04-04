/* SysSpawn.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.60
//
//  Tag: Target/WIN64
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_sys_SysSpawn_h
#define CCore_inc_sys_SysSpawn_h

#include <CCore/inc/GenFile.h>

#include <CCore/inc/sys/SysError.h>

namespace CCore {
namespace Sys {

/* GetShell() */

StrLen GetShell(char buf[MaxPathLen+1]) noexcept;

/* classes */

struct GetEnviron;

struct SpawnChild;

struct SpawnWaitList;

/* struct GetEnviron */

struct GetEnviron
 {
  // public

  struct NextResult
   {
    StrLen env;
    ErrorType error;
    bool eof;
   };

  // private data

  using WChar = unsigned short ;

  WChar *envblock;
  const WChar *ptr;
  char *str;
  ulen len;

  char small[TextBufLen];

  // private

  const WChar * ZScan(const WChar *ztext);

  struct TransformResult
   {
    ulen len;
    ErrorType error;
   };

  TransformResult transform(PtrLen<const WChar> text) noexcept;

  // public

  ErrorType init() noexcept;

  ErrorType exit() noexcept;

  NextResult next() noexcept;
 };

/* struct SpawnChild */

struct SpawnChild
 {
  // public

  struct WaitResult
   {
    int status;
    ErrorType error;
   };

  // private data

  using Type = long ;

  Type handle;

  // public

  ErrorType spawn(char *wdir,char *path,char **argv,char **envp) noexcept; // path!=0 , argv!=0 , envp!=0

  WaitResult wait() noexcept;
 };

/* struct SpawnWaitList */

struct SpawnWaitList
 {
  // public

  struct WaitResult
   {
    void *arg;
    int status;
    ErrorType error;
   };

  // private data

  class Engine;

  Engine *engine;

  // public

  ErrorType init(ulen reserve) noexcept;

  ErrorType exit() noexcept;

  ErrorType add(SpawnChild *spawn,void *arg) noexcept; // makes spawn reusable

  WaitResult wait() noexcept;
 };

} // namespace Sys
} // namespace CCore

#endif

