/* Window.Progress.h */
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
     shape.stopActive();

     redraw();
    }

   void setPos(unsigned pos)
    {
     if( Change(shape.pos,pos) )
       {
        shape.adjustPos();

        redraw();
       }
    }

   void setPosPing(unsigned pos)
    {
     if( Change(shape.pos,pos) )
       {
        shape.adjustPos();

        shape.resetTime();

        defer_tick.start();

        shape.startActive();

        redraw();
       }
    }

   void ping()
    {
     shape.resetTime();

     defer_tick.start();

     if( shape.startActive() ) redraw();
    }

   void stopPing()
    {
     defer_tick.stop();

     shape.stopActive();

     redraw();
    }

   // drawing

   virtual bool isGoodSize(Point size) const
    {
     return shape.isGoodSize(size);
    }

   virtual void layout()
    {
     shape.pane=Pane(Null,getSize());
    }

   virtual void draw(DrawBuf buf,bool) const
    {
     shape.draw(buf);
    }

   // base

   virtual void open()
    {
     shape.has_active=false;
    }

   virtual void close()
    {
     defer_tick.stop();
    }

   // keyboard

   virtual FocusType askFocus() const
    {
     return NoFocus;
    }
 };

/* type ProgressWindow */

using ProgressWindow = ProgressWindowOf<ProgressShape> ;

} // namespace Video
} // namespace CCore

#endif

