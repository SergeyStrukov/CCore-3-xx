/* ButtonId.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
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

#ifndef CCore_inc_video_ButtonId_h
#define CCore_inc_video_ButtonId_h

#include <CCore/inc/Gadget.h>

namespace CCore {
namespace Video {

/* enum ButtonId */

enum ButtonId : int
 {
  Button_Cancel = -1 ,
  Button_Ok     =  0 ,

  Button_Yes    =  1 ,
  Button_No     =  2
 };

} // namespace Video
} // namespace CCore

#endif

