/* App.h */
//----------------------------------------------------------------------------------------
//
//  Project: ContourLab 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef App_h
#define App_h

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

/* AppKey() */

StrLen AppKey();

} // namespace App

#endif


