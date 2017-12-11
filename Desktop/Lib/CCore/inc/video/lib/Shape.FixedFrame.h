/* Shape.FixedFrame.h */
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

#ifndef CCore_inc_video_lib_Shape_FixedFrame_h
#define CCore_inc_video_lib_Shape_FixedFrame_h

#include <CCore/inc/video/lib/Shape.FrameBase.h>

namespace CCore {
namespace Video {

/* classes */

class FixedFrameShape;

/* class FixedFrameShape */

class FixedFrameShape : public FrameShapeBase
 {
  public:

   struct Config : ConfigBase
    {
     RefVal<VColor> frame        =      Snow ;
     RefVal<VColor> frameHilight = PaleGreen ;
     RefVal<VColor> frameDrag    =      Pink ;

     RefVal<VColor> dragSmall    =     Wheat ;

     RefVal<Coord> frame_dxy = 12 ;
     RefVal<Coord> title_dy  = 32 ;

     RefVal<Coord> btn_dx    = 26 ;
     RefVal<Coord> btn_dy    = 24 ;

     RefVal<DefString> hint_Alert    = "Open/close alert view"_def ;
     RefVal<DefString> hint_Help     = "Help on/off"_def ;
     RefVal<DefString> hint_Minimize = "Minimize"_def ;
     RefVal<DefString> hint_Close    = "Close"_def ;

     Config() noexcept {}

     template <class Bag>
     void bind(const Bag &bag)
      {
       ConfigBase::bind(bag);

       frame.bind(bag.frame);
       frameHilight.bind(bag.frameHilight);
       frameDrag.bind(bag.frameDrag);

       dragSmall.bind(bag.dragSmall);

       frame_dxy.bind(bag.frame_dxy);
       title_dy.bind(bag.title_dy);

       btn_dx.bind(bag.btn_dx);
       btn_dy.bind(bag.btn_dy);

       hint_Alert.bind(bag.hint_Alert);
       hint_Help.bind(bag.hint_Help);
       hint_Minimize.bind(bag.hint_Minimize);
       hint_Close.bind(bag.hint_Close);
      }
    };

   const Config &cfg;

  private:

   Point size;

   Pane titleBar;

   Pane btnAlert;
   Pane btnHelp;
   Pane btnMin;
   Pane btnClose;

   Pane client;

  private:

   void draw_Frame(const DrawBuf &buf,Pane part) const;

   void draw_Frame(const DrawBuf &buf) const;

   void draw_Frame(const DrawBuf &buf,DragType drag_type) const;

   void draw_Bar(const DrawBuf &buf) const;

   void draw_Alert(const DrawBuf &buf) const;

   void draw_Help(const DrawBuf &buf) const;

   void draw_Min(const DrawBuf &buf) const;

   void draw_Close(const DrawBuf &buf) const;

  public:

   static constexpr bool EnableAlert = true ;
   static constexpr bool EnableMinimize = true ;
   static constexpr bool EnableMaximize = false ;
   static constexpr bool EnableFixed = true ;

   static VKey Filter(VKey vkey,KeyMod kmod)
    {
     if( kmod&KeyMod_Alt )
       {
        switch( vkey )
          {
           case VKey_Left  :
           case VKey_Right :
           case VKey_Up    :
           case VKey_Down  : return (kmod&KeyMod_Shift)?VKey_Null:vkey;

           case VKey_F2    :
           case VKey_F4    :
           case VKey_F12   : return vkey;

           default: return VKey_Null;
          }
       }
     else
       {
        switch( vkey )
          {
           case VKey_F1    : return vkey;

           default: return VKey_Null;
          }
       }
    }

   // methods

   explicit FixedFrameShape(const Config &cfg_) : FrameShapeBase(cfg_),cfg(cfg_) {}

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

#ifdef CCORE_UTF8

     TrimUtf8End(str);

#endif

     return getMinSize(is_main,str,size);
    }

   Pane getClient() const { return client; }

   DragType dragTest(Point point) const;

   DragType hilightTest(Point point) const
    {
     return dragTest(point);
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

