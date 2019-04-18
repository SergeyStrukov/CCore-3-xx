/* Window.Progress.h */
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

#ifndef CCore_inc_video_lib_Window_Progress_h
#define CCore_inc_video_lib_Window_Progress_h

#include <CCore/inc/video/SubWindow.h>

#include <CCore/inc/video/lib/Shape.Progress.h>

namespace CCore {
namespace Video {

/* classes */

template <class Shape> class ProgressWindowOf;

/* class ProgressWindowOf<Shape> */

template <class Shape>
class ProgressWindowOf : public SubWindow
 {
   Shape shape;

   DeferInput<ProgressWindowOf<Shape> > input;

   DeferTick defer_tick;

  private:

   void tick()
    {
     if( shape.checkTime() )
       {
        if( shape.tick() )
          {
           shape.nextActive();

           redraw();
          }
       }
     else
       {
        stopPing();
       }
    }

  public:

   using ShapeType = Shape ;
   using ConfigType = typename Shape::Config ;

   template <class ... TT>
   ProgressWindowOf(SubWindowHost &host,TT && ... tt)
    : SubWindow(host),
      shape( std::forward<TT>(tt)... ),
      input(this)
    {
     defer_tick=input.create(&ProgressWindowOf<Shape>::tick);
    }

   virtual ~ProgressWindowOf() {}

   // methods

   auto getMinSize() const { return shape.getMinSize(); }

   unsigned getPos() const { return shape.pos; }

   unsigned getTotal() const { return shape.total; }

   void setTotal(unsigned total)
    {
     shape.total=total;
     shape.pos=0;

     stopPing();
    }

   void setPos(unsigned pos)
    {
     if( shape.setPos(pos) )
       {
        redraw();
       }
    }

   void setPosPing(unsigned pos)
    {
     if( shape.setPos(pos) )
       {
        shape.resetTime();

        if( shape.startActive() ) defer_tick.start();

        redraw();
       }
    }

   void ping()
    {
     shape.resetTime();

     if( shape.startActive() )
       {
        defer_tick.start();

        redraw();
       }
    }

   void stopPing()
    {
     defer_tick.stop();

     shape.stopActive();

     redraw();
    }

   void setEnd() { setPos(getTotal()); }

   void setEndPing() { setPosPing(getTotal()); }

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
     defer_tick.stop();

     shape.stopActive();
    }

   virtual void close()
    {
     defer_tick.stop();

     shape.stopActive();
    }

   // keyboard

   virtual FocusType askFocus() const
    {
     return NoFocus;
    }
 };

/* type ProgressWindow */

using ProgressWindow = ProgressWindowOf<ProgressShape> ;

/* type ArrowProgressWindow */

using ArrowProgressWindow = ProgressWindowOf<ArrowProgressShape> ;

} // namespace Video
} // namespace CCore

#endif

