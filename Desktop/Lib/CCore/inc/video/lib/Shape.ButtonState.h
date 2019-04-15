/* Shape.ButtonState.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.60
//
//  Tag: Desktop
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_video_lib_Shape_ButtonState_h
#define CCore_inc_video_lib_Shape_ButtonState_h

#include <CCore/inc/Gadget.h>

namespace CCore {
namespace Video {

/* classes */

struct ButtonState;

/* struct ButtonState */

struct ButtonState
 {
  bool enable =  true ;
  bool focus  = false ;
  bool mover  = false ;
  bool down   = false ;

  bool mouse  = false ;

  ButtonState() {}
 };

} // namespace Video
} // namespace CCore

#endif

