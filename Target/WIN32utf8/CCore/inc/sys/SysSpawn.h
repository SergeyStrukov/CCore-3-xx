/* SysSpawn.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.60
//
//  Tag: Target/WIN32utf8
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

StrLen GetShell(char buf[MaxPathLen+1]);

/* GetEnviron() */

void GetEnviron(Function<void (StrLen)> func);

/* classes */

struct SpawnChild;

struct SpawnWaitList;

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

  using Type = int ;

  Type handle;

  // public

  static void * MemAlloc(ulen len);

  static void MemFree(void *mem);

  ErrorType spawn(char *wdir,char *path,char **argv,char **envp); // path!=0 , argv!=0 , envp!=0

  WaitResult wait();
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

  ErrorType init(ulen reserve);

  ErrorType exit();

  ErrorType add(SpawnChild *spawn,void *arg); // makes spawn reusable

  WaitResult wait();
 };

} // namespace Sys
} // namespace CCore

#endif

