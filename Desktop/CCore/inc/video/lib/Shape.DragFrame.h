/* Shape.DragFrame.h */
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

#ifndef CCore_inc_video_lib_Shape_DragFrame_h
#define CCore_inc_video_lib_Shape_DragFrame_h

#include <CCore/inc/video/lib/Shape.FrameBase.h>

namespace CCore {
namespace Video {

/* classes */

class DragFrameShape;

/* class DragFrameShape */

class DragFrameShape : public FrameShapeBase
 {
  public:

   struct Config : ConfigBase
    {
     RefVal<VColor> frame       =   Snow ;

     RefVal<VColor> drag        = Silver ;
     RefVal<VColor> dragHilight =  Green ;
     RefVal<VColor> dragActive  =    Red ;
     RefVal<VColor> dragSmall   =  Wheat ;

     RefVal<Coord> frame_dxy = 12 ;
     RefVal<Coord> title_dy  = 32 ;

     RefVal<Coord> btn_dx    = 26 ;
     RefVal<Coord> btn_dy    = 24 ;

     RefVal<DefString> hint_ResizeTopLeft     = "Resize top-left"_def ;
     RefVal<DefString> hint_ResizeLeft        = "Resize left"_def ;
     RefVal<DefString> hint_ResizeBottomLeft  = "Resize bottom-left"_def ;
     RefVal<DefString> hint_ResizeBottom      = "Resize bottom"_def ;
     RefVal<DefString> hint_ResizeBottomRight = "Resize bottom-right"_def ;
     RefVal<DefString> hint_ResizeRight       = "Resize right"_def ;
     RefVal<DefString> hint_ResizeTopRight    = "Resize top-right"_def ;

     RefVal<DefString> hint_Alert    = "Open/close alert view"_def ;
     RefVal<DefString> hint_Help     = "Help on/off"_def ;
     RefVal<DefString> hint_Minimize = "Minimize"_def ;
     RefVal<DefString> hint_Maximize = "Maximize"_def ;
     RefVal<DefString> hint_Restore  = "Restore"_def ;
     RefVal<DefString> hint_Close    = "Close"_def ;

     Config() noexcept {}

     template <class Bag>
     void bind(const Bag &bag)
      {
       ConfigBase::bind(bag);

       frame.bind(bag.frame);

       drag.bind(bag.drag);
       dragHilight.bind(bag.dragHilight);
       dragActive.bind(bag.dragActive);
       dragSmall.bind(bag.dragSmall);

       frame_dxy.bind(bag.frame_dxy);
       title_dy.bind(bag.title_dy);

       btn_dx.bind(bag.btn_dx);
       btn_dy.bind(bag.btn_dy);

       hint_ResizeTopLeft.bind(bag.hint_ResizeTopLeft);
       hint_ResizeLeft.bind(bag.hint_ResizeLeft);
       hint_ResizeBottomLeft.bind(bag.hint_ResizeBottomLeft);
       hint_ResizeBottom.bind(bag.hint_ResizeBottom);
       hint_ResizeBottomRight.bind(bag.hint_ResizeBottomRight);
       hint_ResizeRight.bind(bag.hint_ResizeRight);
       hint_ResizeTopRight.bind(bag.hint_ResizeTopRight);

       hint_Alert.bind(bag.hint_Alert);
       hint_Help.bind(bag.hint_Help);
       hint_Minimize.bind(bag.hint_Minimize);
       hint_Maximize.bind(bag.hint_Maximize);
       hint_Restore.bind(bag.hint_Restore);
       hint_Close.bind(bag.hint_Close);
      }
    };

   const Config &cfg;

  private:

   Point size;

   Pane dragTopLeft;
   Pane dragLeft;
   Pane dragBottomLeft;
   Pane dragBottom;
   Pane dragBottomRight;
   Pane dragRight;
   Pane dragTopRight;

   Pane dragBar;
   Pane titleBar;

   Pane btnAlert;
   Pane btnHelp;
   Pane btnMin;
   Pane btnMax;
   Pane btnClose;

   Pane client;

  private:

   VColor dragColor(DragType zone) const;

   void draw_Frame(const DrawBuf &buf,Pane part) const;

   void draw_Frame(const DrawBuf &buf) const;

   void draw_Frame(const DrawBuf &buf,DragType drag_type) const;

   void draw_TopLeft(const DrawBuf &buf) const;

   void draw_Left(const DrawBuf &buf) const;

   void draw_BottomLeft(const DrawBuf &buf) const;

   void draw_Bottom(const DrawBuf &buf) const;

   void draw_BottomRight(const DrawBuf &buf) const;

   void draw_Right(const DrawBuf &buf) const;

   void draw_TopRight(const DrawBuf &buf) const;

   void draw_Bar(const DrawBuf &buf) const;

   void draw_Alert(const DrawBuf &buf) const;

   void draw_Help(const DrawBuf &buf) const;

   void draw_Min(const DrawBuf &buf) const;

   void draw_Max(const DrawBuf &buf) const;

   void draw_Close(const DrawBuf &buf) const;

  public:

   static const bool EnableAlert = true ;
   static const bool EnableMinimize = true ;
   static const bool EnableMaximize = true ;
   static const bool EnableFixed = false ;

   static VKey Filter(VKey vkey,KeyMod kmod)
    {
     Used(kmod);

     return vkey;
    }

   // state

   bool max_button = true ;

   // methods

   explicit DragFrameShape(const Config &cfg_) : FrameShapeBase(cfg_),cfg(cfg_) {}

   void reset(const DefString &title,bool is_main,bool max_button);

   void layout(Point size);

   Point getDeltaSize() const;

   Coord getMinDX(bool is_main,StrLen title) const;

   Point getMinSize(bool is_main,StrLen title,Point size) const
    {
     size+=getDeltaSize();

     return Point( Max(size.x,getMinDX(is_main,title)) , size.y );
    }

   Point getMinSize(Point size=Point(10,10)) const
    {
     StrLen str=title.str();

     Replace_min(str.len,10);

     return getMinSize(is_main,str,size);
    }

   Pane getClient() const { return client; }

   DragType dragTest(Point point) const;

   DragType hilightTest(Point point) const
    {
     DragType ret=dragTest(point);

     if( ret==DragType_Bar ) return DragType_None;

     return ret;
    }

   Pane getPane(DragType drag_type) const;

   Hint getHint(Point point) const;

   void draw(const DrawBuf &buf) const;

   void draw(const DrawBuf &buf,DragType drag_type) const;

   void drawHint(const DrawBuf &buf,Hint hint) const;
 };

} // namespace Video
} // namespace CCore

#endif

