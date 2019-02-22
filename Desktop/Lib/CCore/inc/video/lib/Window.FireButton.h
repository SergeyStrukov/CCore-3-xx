/* Window.FireButton.h */
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

#ifndef CCore_inc_video_lib_Window_FireButton_h
#define CCore_inc_video_lib_Window_FireButton_h

#include <CCore/inc/video/SubWindow.h>

#include <CCore/inc/video/lib/Shape.Button.h>

namespace CCore {
namespace Video {

/* classes */

template <class Shape> class FireButtonWindowOf;

/* class FireButtonWindowOf<Shape> */

template <class Shape>
class FireButtonWindowOf : public SubWindow
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

        fire.assert(false);
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
   explicit FireButtonWindowOf(SubWindowHost &host,TT && ... tt)
    : SubWindow(host),
      shape( std::forward<TT>(tt)... )
    {
    }

   virtual ~FireButtonWindowOf() {}

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

        fire.assert(false);
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

        fire.assert(false);
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

             fire.assert(true);
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

             fire.assert(false);
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

        fire.assert(true);
       }
    }

   void react_LeftUp(Point,MouseKey)
    {
     if( shape.down && shape.mouse )
       {
        shape.down=false;

        releaseMouse();

        redraw();

        fire.assert(false);
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

   Signal<bool> fire;   // on/off
   Signal<bool> tabbed; // shift
 };

/* type FireButtonWindow */

using FireButtonWindow = FireButtonWindowOf<ButtonShape> ;

/* type RefFireButtonWindow */

using RefFireButtonWindow = FireButtonWindowOf<RefButtonShape> ;

/* type FireKnobWindow */

using FireKnobWindow = FireButtonWindowOf<KnobShape> ;

} // namespace Video
} // namespace CCore

#endif

