/* Window.Check.h */
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

#ifndef CCore_inc_video_lib_Window_Check_h
#define CCore_inc_video_lib_Window_Check_h

#include <CCore/inc/video/SubWindow.h>

#include <CCore/inc/video/lib/Shape.Check.h>
#include <CCore/inc/video/lib/Shape.Switch.h>
#include <CCore/inc/video/lib/Shape.ShiftSwitch.h>

namespace CCore {
namespace Video {

/* classes */

template <class Shape> class CheckWindowOf;

template <class Shape> class AltWindowOf;

/* class CheckWindowOf<Shape> */

template <class Shape>
class CheckWindowOf : public SubWindow
 {
   Shape shape;

  private:

   void inside()
    {
     if( Change(shape.mover,true) ) redraw();
    }

   void outside()
    {
     if( Change(shape.mover,false) ) redraw();
    }

   void change()
    {
     shape.check=!shape.check;

     redraw();

     changed.assert(shape.check);
    }

  public:

   using ShapeType = Shape ;
   using ConfigType = typename Shape::Config ;

   template <class ... TT>
   explicit CheckWindowOf(SubWindowHost &host,TT && ... tt)
    : SubWindow(host),
      shape( std::forward<TT>(tt)... )
    {
    }

   virtual ~CheckWindowOf() {}

   // methods

   auto getMinSize() const { return shape.getMinSize(); }

   bool isEnabled() const { return shape.enable; }

   void enable(bool enable=true)
    {
     if( Change(shape.enable,enable) ) redraw();
    }

   void disable() { enable(false); }

   bool isChecked() const { return shape.check; }

   void check(bool check=true)
    {
     if( Change(shape.check,check) ) redraw();
    }

   void uncheck() { check(false); }

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

   Signal<bool> changed; // check
   Signal<bool> tabbed;  // shift
 };

/* type CheckWindow */

using CheckWindow = CheckWindowOf<CheckShape> ;

/* type SwitchWindow */

using SwitchWindow = CheckWindowOf<SwitchShape> ;

/* type XShiftSwitchWindow */

using XShiftSwitchWindow = CheckWindowOf<XShiftSwitchShape> ;

/* type YShiftSwitchWindow */

using YShiftSwitchWindow = CheckWindowOf<YShiftSwitchShape> ;

/* class AltWindowOf<Shape> */

template <class Shape>
class AltWindowOf : public SubWindow
 {
  public:

   using CheckType = typename Shape::CheckType ;

  private:

   Shape shape;

  private:

   void inside(CheckType zone)
    {
     if( Change(shape.mover,true) )
       {
        shape.zone=zone;

        redraw();
       }
     else
       {
        if( Change(shape.zone,zone) ) redraw();
       }
    }

   void outside()
    {
     if( Change(shape.mover,false) ) redraw();
    }

   void change()
    {
     shape.check=Shape::Next(shape.check);

     redraw();

     changed.assert(shape.check);
    }

   void change(CheckType zone)
    {
     if( Change(shape.check,zone) )
       {
        redraw();

        changed.assert(shape.check);
       }
    }

  public:

   using ShapeType = Shape ;
   using ConfigType = typename Shape::Config ;

   template <class ... TT>
   explicit AltWindowOf(SubWindowHost &host,TT && ... tt)
    : SubWindow(host),
      shape( std::forward<TT>(tt)... )
    {
    }

   virtual ~AltWindowOf() {}

   // methods

   auto getMinSize() const { return shape.getMinSize(); }

   virtual bool isGoodSize(Point size) const { return shape.isGoodSize(size); }

   bool isEnabled() const { return shape.enable; }

   void enable(bool enable=true)
    {
     if( Change(shape.enable,enable) ) redraw();
    }

   void disable() { enable(false); }

   CheckType getCheck() const { return shape.check; }

   void check(CheckType check)
    {
     if( Change(shape.check,check) ) redraw();
    }

   // bool

   bool isChecked() const requires ( IsType<CheckType,bool> ) { return shape.check; }

   void check() requires ( IsType<CheckType,bool> ) { check(true); }

   void uncheck() requires ( IsType<CheckType,bool> ) { check(false); }

   // drawing

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
     if( shape.enable && shape.pane.contains(point) ) change(shape.getZone(point));
    }

   void react_Move(Point point,MouseKey)
    {
     if( shape.pane.contains(point) )
       {
        inside(shape.getZone(point));
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

   Signal<CheckType> changed; // check
   Signal<bool> tabbed;       // shift
 };

} // namespace Video
} // namespace CCore

#endif

