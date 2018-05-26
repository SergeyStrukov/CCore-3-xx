/* SysSem.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: Target/LIN64
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_sys_SysSem_h
#define CCore_inc_sys_SysSem_h

#include <CCore/inc/sys/SysError.h>
#include <CCore/inc/sys/SysData.h>

#include <CCore/inc/TimeScope.h>

namespace CCore {
namespace Sys {

/* classes */

struct Sem;

/* struct Sem */

struct Sem
 {
  // private

  SysData<64> sem;

  // public

  ErrorType init(ulen count=0) noexcept;

  void exit() noexcept;

  void give() noexcept;

  void give_many(ulen count) noexcept;

  bool try_take() noexcept;

  void take() noexcept;

  bool take(MSec timeout) noexcept;

  bool take(TimeScope time_scope)
   {
    auto timeout=time_scope.get();

    if( !timeout ) return false;

    return take(timeout);
   }
 };

} // namespace Sys
} // namespace CCore

#endif


