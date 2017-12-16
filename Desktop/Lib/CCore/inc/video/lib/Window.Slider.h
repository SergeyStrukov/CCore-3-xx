/* Window.Slider.h */
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

#ifndef CCore_inc_video_lib_Window_Slider_h
#define CCore_inc_video_lib_Window_Slider_h

#include <CCore/inc/video/SubWindow.h>

#include <CCore/inc/video/lib/Shape.Slider.h>

namespace CCore {
namespace Video {

/* classes */

template <class Shape> class SliderWindowOf;

/* class SliderWindowOf<Shape> */

template <class Shape>
class SliderWindowOf : public SubWindow
 {
   Shape shape;

  private:

   void movePos(unsigned pos)
    {
     if( Change(shape.pos,Min(pos,shape.cap)) )
       {
        redraw();

        changed.assert(shape.pos);
       }
    }

   void addPos(unsigned delta)
    {
     movePos(AddToCap<unsigned>(shape.pos,delta,shape.cap));
    }

   void subPos(unsigned delta)
    {
     movePos(PosSub(shape.pos,delta));
    }

   void startDrag(Point point)
    {
     if( Change(shape.drag,true) )
       {
        captureMouse();

        dragTo(point);
       }
    }

   void dragTo(Point point)
    {
     movePos(shape.getPos(point));
    }

   void endDrag()
    {
     shape.drag=false;

     releaseMouse();
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
   explicit SliderWindowOf(SubWindowHost &host,TT && ... tt)
    : SubWindow(host),
      shape( std::forward<TT>(tt)... )
    {
    }

   virtual ~SliderWindowOf() {}

   // methods

   auto getMinSize(unsigned) const { return shape.getMinSize(); }

   bool isEnabled() const { return shape.enable; }

   void enable(bool enable=true)
    {
     if( Change(shape.enable,enable) ) redraw();
    }

   void disable() { enable(false); }

   unsigned getPos() const { return shape.pos; }

   unsigned getCap() const { return shape.cap; }

   void setPos(unsigned pos)
    {
     shape.pos=Min(pos,shape.cap);

     redraw();
    }

   void setCap(unsigned cap)
    {
     shape.cap=cap;

     shape.pos=Min(shape.pos,cap);

     redraw();
    }

   // drawing

   virtual bool isGoodSize(Point size) const
    {
     return shape.isGoodSize(size);
    }

   virtual void layout(unsigned)
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
     shape.focus=false;
     shape.mover=false;
     shape.drag=false;
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

   virtual void looseCapture()
    {
     shape.drag=false;

     outside();
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

   void react_Key(VKey vkey,KeyMod kmod,unsigned repeat)
    {
     if( vkey==VKey_Tab )
       {
        tabbed.assert(kmod&KeyMod_Shift);

        return;
       }

     if( !shape.enable ) return;

     switch( vkey )
       {
        case Shape::KeyDown :
         {
          if( shape.enable ) subPos(repeat);
         }
        break;

        case Shape::KeyUp :
         {
          if( shape.enable ) addPos(repeat);
         }
        break;

        case VKey_Home :
         {
          if( shape.enable ) movePos(0);
         }
        break;

        case VKey_End :
         {
          if( shape.enable ) movePos(shape.cap);
         }
        break;

        case VKey_PageUp :
         {
          if( shape.enable ) addPos(shape.cap/10);
         }
        break;

        case VKey_PageDown :
         {
          if( shape.enable ) subPos(shape.cap/10);
         }
        break;
       }
    }

   void react_LeftClick(Point point,MouseKey)
    {
     if( !shape.enable ) return;

     startDrag(point);
    }

   void react_LeftUp(Point point,MouseKey)
    {
     if( shape.drag ) endDrag(point);
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

     if( shape.drag )
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

   void react_Wheel(Point,MouseKey,Coord delta)
    {
     if( !shape.enable ) return;

     if( delta>0 )
       {
        addPos(IntAbs(delta));
       }
     else
       {
        subPos(IntAbs(delta));
       }
    }

   // signals

   Signal<unsigned> changed; // pos
   Signal<bool> tabbed;      // shift
 };

/* type XSliderWindow */

using XSliderWindow = SliderWindowOf<XSliderShape> ;

/* type YSliderWindow */

using YSliderWindow = SliderWindowOf<YSliderShape> ;

} // namespace Video
} // namespace CCore

#endif

