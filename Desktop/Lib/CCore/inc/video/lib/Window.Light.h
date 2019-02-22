/* Window.Light.h */
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
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_video_lib_Window_Light_h
#define CCore_inc_video_lib_Window_Light_h

#include <CCore/inc/video/SubWindow.h>

#include <CCore/inc/video/lib/Shape.Light.h>

namespace CCore {
namespace Video {

/* classes */

template <class Shape> class LightWindowOf;

/* class LightWindowOf<Shape> */

template <class Shape>
class LightWindowOf : public SubWindow
 {
   Shape shape;

  public:

   using ShapeType = Shape ;
   using ConfigType = typename Shape::Config ;

   template <class ... TT>
   LightWindowOf(SubWindowHost &host,TT && ... tt)
    : SubWindow(host),
      shape( std::forward<TT>(tt)... )
    {
    }

   virtual ~LightWindowOf() {}

   // methods

   auto getMinSize() const { return shape.getMinSize(); }

   VColor getFace() const { return shape.face; }

   void setFace(VColor face)
    {
     if( Change(shape.face,face) ) redraw();
    }

   bool isOn() const { return shape.on; }

   void turn(bool on)
    {
     if( Change(shape.on,on) ) redraw();
    }

   void turnOn() { turn(true); }

   void turnOff() { turn(false); }

   // drawing

   virtual bool isGoodSize(Point size) const
    {
     return shape.isGoodSize(size);
    }

   virtual void layout()
    {
     shape.pane=getPane();
    }

   virtual void draw(DrawBuf buf,DrawParam draw_param) const
    {
     shape.draw(buf,draw_param);
    }

   // keyboard

   virtual FocusType askFocus() const
    {
     return NoFocus;
    }
 };

/* type LightWindow */

using LightWindow = LightWindowOf<LightShape> ;

} // namespace Video
} // namespace CCore

#endif

