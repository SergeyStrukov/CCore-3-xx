/* LaunchPath.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.01
//
//  Tag: HCore
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/LaunchPath.h>

#include <CCore/inc/sys/SysLaunchPath.h>

#include <CCore/inc/PrintError.h>
#include <CCore/inc/Exception.h>

namespace CCore {

/* class LaunchPath */

LaunchPath::LaunchPath()
 {
  auto res=Sys::LaunchPath(buf);

  if( res.error )
    {
     Printf(Exception,"CCore::LaunchPath::LaunchPath() : #;",PrintError(res.error));
    }

  path=res.path;
 }

} // namespace CCore

