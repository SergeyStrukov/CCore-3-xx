/* SysCon.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Target/WIN64utf8
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_sys_SysCon_h
#define CCore_inc_sys_SysCon_h

#include <CCore/inc/sys/SysError.h>

#include <CCore/inc/TimeScope.h>

namespace CCore {
namespace Sys {

/* functions */

void ConWrite(StrLen str) noexcept;

/* classes */

struct ConRead;

/* struct ConRead */

struct ConRead
 {
  // public

  struct IOResult
   {
    ulen len;
    ErrorType error;
   };

  // private data

  using Type = long ;
  using ModeType = unsigned ;

  Type handle;
  ModeType modes;

  struct Symbol
   {
    uint16 hi;

    char buf[8];
    ulen len;

    ulen operator + () const { return len; }

    void reset() { len=0; hi=0; }

    void put(uint32 sym);

    bool pushUnicode(uint32 sym);

    bool push(uint16 wch);

    void shift(ulen delta);

    IOResult get(char *out,ulen out_len);
   };

  Symbol symbol;

  // private

  struct InitType
   {
    Type handle;
    ModeType modes;
    ErrorType error;
   };

  static InitType Init() noexcept;

  static ErrorType Exit(Type handle,ModeType modes) noexcept;

  // public

  ErrorType init()
   {
    InitType result=Init();

    handle=result.handle;
    modes=result.modes;

    symbol.reset();

    return result.error;
   }

  ErrorType exit() { return Exit(handle,modes); }

  IOResult read(char *buf,ulen len) noexcept;

  IOResult read(char *buf,ulen len,MSec timeout)
   {
    return read(buf,len,TimeScope(timeout));
   }

  IOResult read(char *buf,ulen len,TimeScope time_scope) noexcept;
 };

} // namespace Sys
} // namespace CCore

#endif


