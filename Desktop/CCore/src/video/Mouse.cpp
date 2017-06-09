/* Mouse.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Desktop
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/video/Mouse.h>

namespace CCore {
namespace Video {

/* enum MouseShape */

const char * GetTextDesc(MouseShape mshape)
 {
  switch( mshape )
    {
     case Mouse_Null          : return "Null";
     case Mouse_Arrow         : return "Arrow";
     case Mouse_IBeem         : return "IBeem";
     case Mouse_Wait          : return "Wait";
     case Mouse_Cross         : return "Cross";
     case Mouse_Hand          : return "Hand";
     case Mouse_Stop          : return "Stop";
     case Mouse_Help          : return "Help";
     case Mouse_SizeLeftRight : return "SizeLeftRight";
     case Mouse_SizeUpDown    : return "SizeUpDown";
     case Mouse_SizeUpLeft    : return "SizeUpLeft";
     case Mouse_SizeUpRight   : return "SizeUpRight";
     case Mouse_SizeAll       : return "SizeAll";
     case Mouse_UpArrow       : return "UpArrow";
     case Mouse_Progress      : return "Progress";

     default: return "???";
    }
 }

} // namespace Video
} // namespace CCore


