/* Window.Button.h */
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

#ifndef CCore_inc_video_lib_Window_Button_h
#define CCore_inc_video_lib_Window_Button_h

#include <CCore/inc/video/SubWindow.h>

#include <CCore/inc/video/lib/Shape.Button.h>
#include <CCore/inc/video/lib/Shape.MoveButton.h>
#include <CCore/inc/video/lib/Shape.AllButton.h>

namespace CCore {
namespace Video {

/* classes */

template <class Shape> class ButtonWindowOf;

/* class ButtonWindowOf<Shape> */

template <class Shape>
class ButtonWindowOf : public SubWindow
 {
   Shape shape;

  private:

   void inside()
    {
     if( Change(shape.mover,true) ) redraw();
    }

   void outside()
    {
     if( shape.down && shape.mouse )
       {
        shape.mover=false;
        shape.down=false;

        releaseMouse();

        redraw();
       }
     else
       {
        if( Change(shape.mover,false) ) redraw();
       }
    }

  public:

   using ShapeType = Shape ;
   using ConfigType = typename Shape::Config ;

   template <class ... TT>
   explicit ButtonWindowOf(SubWindowHost &host,TT && ... tt)
    : SubWindow(host),
      shape( std::forward<TT>(tt)... )
    {
    }

   virtual ~ButtonWindowOf() {}

   // methods

   auto getMinSize() const { return shape.getMinSize(); }

   bool isEnabled() const { return shape.enable; }

   void enable(bool enable=true)
    {
     if( Change(shape.enable,enable) ) redraw();
    }

   void disable() { enable(false); }

   using FaceType = typename Shape::FaceType ;

   FaceType getFace() const { return shape.face; }

   void setFace(const FaceType &face)
    {
     shape.face=face;

     redraw();
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
     shape.down=false;
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
     if( shape.down && !shape.mouse )
       {
        shape.focus=false;
        shape.down=false;

        redraw();
       }
     else
       {
        if( Change(shape.focus,false) ) redraw();
       }
    }

   // mouse

   virtual void looseCapture()
    {
     if( shape.down && shape.mouse )
       {
        shape.mover=false;
        shape.down=false;

        redraw();
       }
    }

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
          if( shape.enable && !shape.down )
            {
             shape.down=true;
             shape.mouse=false;

             redraw();
            }
         }
        break;

        case VKey_Tab :
         {
          tabbed.assert(kmod&KeyMod_Shift);
         }
        break;
       }
    }

   void react_KeyUp(VKey vkey,KeyMod)
    {
     switch( vkey )
       {
        case VKey_Enter :
        case VKey_Space :
         {
          if( shape.down && !shape.mouse )
            {
             shape.down=false;

             redraw();

             pressed.assert();
            }
         }
        break;
       }
    }

   void react_LeftClick(Point point,MouseKey)
    {
     if( shape.enable && !shape.down && shape.pane.contains(point) )
       {
        shape.down=true;
        shape.mouse=true;

        captureMouse();

        redraw();
       }
    }

   void react_LeftUp(Point point,MouseKey)
    {
     if( shape.down && shape.mouse )
       {
        shape.down=false;

        releaseMouse();

        redraw();

        if( shape.pane.contains(point) ) pressed.assert();
       }
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

   Signal<> pressed;
   Signal<bool> tabbed; // shift
 };

/* type ButtonWindow */

using ButtonWindow = ButtonWindowOf<ButtonShape> ;

/* type RefButtonWindow */

using RefButtonWindow = ButtonWindowOf<RefButtonShape> ;

/* type KnobWindow */

using KnobWindow = ButtonWindowOf<KnobShape> ;

/* type MoveButtonWindow */

using MoveButtonWindow = ButtonWindowOf<MoveButtonShape> ;

/* type AllButtonWindow */

using AllButtonWindow = ButtonWindowOf<AllButtonShape> ;

} // namespace Video
} // namespace CCore

#endif

