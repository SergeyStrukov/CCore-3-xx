/* Application.h */
//----------------------------------------------------------------------------------------
//
//  Project: ContourLab 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef Application_h
#define Application_h

#include <CCore/inc/video/UserPreference.h>

namespace App {

/* using */

using namespace CCore;
using namespace CCore::Video;

/* enum CharAccent */

enum CharAccent : char
 {
  CharNormal = 0,

  CharNumber,
  CharLength,
  CharAngle,
  CharName,
  CharPunct,

  CharError
 };

/* Main() */

int Main(CmdDisplay cmd_display);

} // namespace App

#endif

