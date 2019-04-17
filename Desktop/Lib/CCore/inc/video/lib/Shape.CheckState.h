/* Shape.CheckState.h */
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

#ifndef CCore_inc_video_lib_Shape_CheckState_h
#define CCore_inc_video_lib_Shape_CheckState_h

#include <CCore/inc/Gadget.h>

namespace CCore {
namespace Video {

/* classes */

struct CheckState;

/* struct CheckState */

struct CheckState
 {
  bool enable =  true ;
  bool focus  = false ;
  bool mover  = false ;
  bool check  = false ;

  CheckState() {}
 };

} // namespace Video
} // namespace CCore

#endif

