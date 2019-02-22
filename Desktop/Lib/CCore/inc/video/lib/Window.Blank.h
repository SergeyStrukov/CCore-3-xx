/* Window.Blank.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Desktop
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_video_lib_Window_Blank_h
#define CCore_inc_video_lib_Window_Blank_h

#include <CCore/inc/video/SubWindow.h>

namespace CCore {
namespace Video {

/* classes */

class BlankWindow;

/* class BlankWindow */

class BlankWindow : public SubWindow
 {
   VColor back;

  public:

   BlankWindow(SubWindowHost &host,VColor back);

   virtual ~BlankWindow();

   // methods

   Point getMinSize() const { return {10,10}; }

   // drawing

   virtual bool isGoodSize(Point size) const;

   virtual void layout();

   virtual void draw(DrawBuf buf,DrawParam draw_param) const;

   // keyboard

   virtual FocusType askFocus() const;
 };

} // namespace Video
} // namespace CCore

#endif

