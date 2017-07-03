/* SysLaunchPath.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.01
//
//  Tag: Target/LIN64
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/sys/SysLaunchPath.h>

#include <unistd.h>
#include <errno.h>

namespace CCore {
namespace Sys {

/* struct LaunchPath */

LaunchPath::LaunchPath(char buf[MaxPathLen+1])
 {
  ssize_t ret=readlink("/proc/self/exe",buf,MaxPathLen+1);

  if( ret==-1 )
    {
     path=Null;
     error=NonNullError();
    }
  else if( (size_t)ret>MaxPathLen )
    {
     path=Null;
     error=(ErrorType)ENAMETOOLONG;
    }
  else
    {
     path=StrLen(buf,ret);
     error=NoError;
    }
 }

} // namespace Sys
} // namespace CCore

