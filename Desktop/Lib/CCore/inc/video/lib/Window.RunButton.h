/* Window.RunButton.h */
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

#ifndef CCore_inc_video_lib_Window_RunButton_h
#define CCore_inc_video_lib_Window_RunButton_h

#include <CCore/inc/video/SubWindow.h>

#include <CCore/inc/video/lib/Shape.RunButton.h>

namespace CCore {
namespace Video {

/* classes */

template <class Shape> class RunButtonWindowOf;

/* class RunButtonWindowOf<Shape> */

template <class Shape>
class RunButtonWindowOf : public SubWindow
 {
   Shape shape;

   DeferInput<RunButtonWindowOf<Shape> > input;

   DeferTick defer_tick;

  private:

   void inside()
    {
     if( Change(shape.mover,true) ) redraw();
    }

   void outside()
    {
     if( Change(shape.mover,false) ) redraw();
    }

   void commit()
    {
     if( shape.on )
       {
        defer_tick.start();

        shape.startRun();
       }
     else
       {
        defer_tick.stop();

        shape.stopRun();
       }

     redraw();
    }

   void change()
    {
     shape.on=!shape.on;

     commit();

     changed.assert(shape.on);
    }

   void tick()
    {
     if( shape.tick() )
       {
        shape.nextRun();

        redraw();
       }
    }

  public:

   using ShapeType = Shape ;
   using ConfigType = typename Shape::Config ;

   template <class ... TT>
   explicit RunButtonWindowOf(SubWindowHost &host,TT && ... tt)
    : SubWindow(host),
      shape( std::forward<TT>(tt)... ),
      input(this)
    {
     defer_tick=input.create(&RunButtonWindowOf<Shape>::tick);
    }

   virtual ~RunButtonWindowOf() {}

   // methods

   auto getMinSize() const { return shape.getMinSize(); }

   bool isEnabled() const { return shape.enable; }

   bool isOn() const { return shape.on; }

   void enable(bool enable=true)
    {
     if( Change(shape.enable,enable) ) redraw();
    }

   void disable() { enable(false); }

   void turn(bool on)
    {
     if( Change(shape.on,on) ) commit();
    }

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

   // base

   virtual void open()
    {
     shape.focus=false;
     shape.mover=false;
     shape.on=false;

     defer_tick.stop();

     shape.stopRun();
    }

   virtual void close()
    {
     defer_tick.stop();

     shape.stopRun();
    }

   // keyboard

   virtual FocusType askFocus() const
    {
     return shape.enable?FocusOk:NoFocus;
    }

   virtual void gainFocus()
    {
     if( Change(shape.focus,true) ) redraw();
    }

   virtual void looseFocus()
    {
     if( Change(shape.focus,false) ) redraw();
    }

   // mouse

   virtual MouseShape getMouseShape(Point,KeyMod) const
    {
     return shape.enable?Mouse_Hand:Mouse_Arrow;
    }

   // user input

   virtual void react(UserAction action)
    {
     action.dispatch(*this);
    }

   void react_Key(VKey vkey,KeyMod kmod)
    {
     switch( vkey )
       {
        case VKey_Enter :
        case VKey_Space :
         {
          if( shape.enable ) change();
         }
        break;

        case VKey_Tab :
         {
          tabbed.assert(kmod&KeyMod_Shift);
         }
        break;
       }
    }

   void react_LeftClick(Point point,MouseKey)
    {
     if( shape.enable && shape.pane.contains(point) ) change();
    }

   void react_Move(Point point,MouseKey)
    {
     if( shape.pane.contains(point) )
       {
        inside();
       }
     else
       {
        outside();
       }
    }

   void react_Leave()
    {
     outside();
    }

   // signals

   Signal<bool> changed; // on
   Signal<bool> tabbed;  // shift
 };

/* type RunButtonWindow */

using RunButtonWindow = RunButtonWindowOf<RunButtonShape> ;

/* type RefRunButtonWindow */

using RefRunButtonWindow = RunButtonWindowOf<RefRunButtonShape> ;

} // namespace Video
} // namespace CCore

#endif

