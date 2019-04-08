/* SysLaunchPath.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.01
//
//  Tag: Target/WIN64utf8
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_sys_SysLaunchPath_h
#define CCore_inc_sys_SysLaunchPath_h

#include <CCore/inc/GenFile.h>

#include <CCore/inc/sys/SysError.h>

namespace CCore {
namespace Sys {

/* classes */

struct LaunchPath;

/* struct LaunchPath */

struct LaunchPath
 {
  StrLen path;
  ErrorType error;

  explicit LaunchPath(char buf[MaxPathLen+1]);
 };

} // namespace Sys
} // namespace CCore

#endif



