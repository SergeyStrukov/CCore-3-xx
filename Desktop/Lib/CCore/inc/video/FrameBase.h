/* FrameBase.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.01
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

#ifndef CCore_inc_video_FrameBase_h
#define CCore_inc_video_FrameBase_h

#include <CCore/inc/video/Point.h>

namespace CCore {
namespace Video {

/* consts */

enum DragType
 {
  DragType_None = 0,

  DragType_Top,
  DragType_TopLeft,
  DragType_Left,
  DragType_BottomLeft,
  DragType_Bottom,
  DragType_BottomRight,
  DragType_Right,
  DragType_TopRight,

  DragType_Bar,

  DragType_Alert,
  DragType_Help,
  DragType_Min,
  DragType_Max,
  DragType_Close
 };

inline bool IsButton(DragType drag_type) { return drag_type>DragType_Bar; }

enum AlertType
 {
  AlertType_No = 0,

  AlertType_Closed,
  AlertType_Opened
 };

/* guard functions */

void GuardNoClient();

void GuardNotDead();

/* DragPane() */

void DragPane(Pane &place,Point delta,DragType drag_type);

/* classes */

class RedrawSet;

/* class RedrawSet */

class RedrawSet : NoCopy
 {
   static constexpr ulen Len = 10 ;

   Pane set[Len];
   ulen count = 0 ;

  private:

   static AreaType Excess(Pane a,Pane b,Pane c);

   void compress(Pane pane);

  public:

   RedrawSet() {}

   bool add(Pane pane);

   PtrLen<Pane> pop();
 };

} // namespace Video
} // namespace CCore

#endif

