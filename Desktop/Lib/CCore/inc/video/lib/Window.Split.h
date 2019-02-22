/* Window.Split.h */
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

#ifndef CCore_inc_video_lib_Window_Split_h
#define CCore_inc_video_lib_Window_Split_h

#include <CCore/inc/video/SubWindow.h>

#include <CCore/inc/video/lib/Shape.Split.h>

namespace CCore {
namespace Video {

/* classes */

template <class Shape> class SplitWindowOf;

/* class SplitWindowOf<Shape> */

template <class Shape>
class SplitWindowOf : public SubWindow
 {
   Shape shape;

  private:

   void startDrag(Point point)
    {
     shape.drag_base=toScreen(point);
    }

   void dragTo(Point point)
    {
     Point delta=Diff(shape.drag_base,toScreen(point));

     dragged.assert(delta);
    }

   void endDrag()
    {
     shape.down=false;

     releaseMouse();

     redraw();
    }

   void endDrag(Point point)
    {
     endDrag();

     dragTo(point);
    }

   void inside()
    {
     if( Change(shape.mover,true) ) redraw();
    }

   void outside()
    {
     if( Change(shape.mover,false) ) redraw();
    }

  public:

   using ShapeType = Shape ;
   using ConfigType = typename Shape::Config ;

   template <class ... TT>
   SplitWindowOf(SubWindowHost &host,TT && ... tt)
    : SubWindow(host),
      shape( std::forward<TT>(tt)... )
    {
    }

   virtual ~SplitWindowOf() {}

   // methods

   auto getMinSize() const { return shape.getMinSize(); }

   bool isEnabled() const { return shape.enable; }

   void enable(bool enable=true)
    {
     if( Change(shape.enable,enable) ) redraw();
    }

   void disable() { enable(false); }

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
     shape.mover=false;
     shape.down=false;
    }

   // keyboard

   virtual FocusType askFocus() const
    {
     return NoFocus;
    }

   // mouse

   virtual void looseCapture()
    {
     if( shape.down )
       {
        shape.mover=false;
        shape.down=false;

        redraw();
       }
    }

   virtual MouseShape getMouseShape(Point,KeyMod) const
    {
     return Mouse_Arrow;
    }

   // user input

   virtual void react(UserAction action)
    {
     action.dispatch(*this);
    }

   void react_LeftClick(Point point,MouseKey)
    {
     if( shape.enable && !shape.down && shape.pane.contains(point) )
       {
        shape.down=true;

        startDrag(point);

        captureMouse();

        redraw();
       }
    }

   void react_LeftUp(Point point,MouseKey)
    {
     if( shape.down )
       {
        endDrag(point);
       }
    }

   void react_Move(Point point,MouseKey mkey)
    {
     if( shape.pane.contains(point) )
       {
        inside();
       }
     else
       {
        outside();
       }

     if( shape.down )
       {
        if( mkey&MouseKey_Left )
          {
           dragTo(point);
          }
        else
          {
           endDrag();
          }
       }
    }

   void react_Leave()
    {
     outside();
    }

   // signals

   Signal<Point> dragged; // delta
};

/* type XSplitWindow */

using XSplitWindow = SplitWindowOf<XSplitShape> ;

/* type YSplitWindow */

using YSplitWindow = SplitWindowOf<YSplitShape> ;

} // namespace Video
} // namespace CCore

#endif

