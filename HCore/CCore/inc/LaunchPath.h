/* LaunchPath.h */
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

#ifndef CCore_inc_LaunchPath_h
#define CCore_inc_LaunchPath_h

#include <CCore/inc/Path.h>

namespace CCore {

/* classes */

class LaunchPath;

/* class LaunchPath */

class LaunchPath : NoCopy
 {
   char buf[MaxPathLen+1];
   StrLen path;

  public:

   LaunchPath();

   StrLen getPath() const { return path; }

   StrLen getDir() const { return PrefixPath(path); }
 };

} // namespace CCore

#endif

