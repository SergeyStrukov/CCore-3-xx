/* Window.Scroll.h */
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

#ifndef CCore_inc_video_lib_Window_Scroll_h
#define CCore_inc_video_lib_Window_Scroll_h

#include <CCore/inc/video/SubWindow.h>

#include <CCore/inc/video/lib/Shape.Scroll.h>

namespace CCore {
namespace Video {

/* classes */

template <class Shape> class ScrollWindowOf;

/* class ScrollWindowOf<Shape> */

template <class Shape>
class ScrollWindowOf : public SubWindow
 {
   Shape shape;

   DeferInput<ScrollWindowOf<Shape> > input;

   DeferTick defer_tick;

   bool invert_wheel = false ;

  private:

   void pressOn()
    {
     shape.change_count=0;

     shape.posChange();

     defer_tick.start();

     redraw();

     changed.assert(shape.pos);
    }

   void pressOn(ScrollType type,Point point)
    {
     shape.press_type=type;

     if( type==ScrollType_Drag )
       {
        shape.drag_base=point;
        shape.drag_pos=shape.pos;

        redraw();
       }
     else
       {
        pressOn();
       }
    }

   void pressOn(ScrollType type)
    {
     shape.press_type=type;

     pressOn();
    }

   void drag(Point point)
    {
     shape.drag(point);

     redraw();

     changed.assert(shape.pos);
    }

   void pressOff(Point point)
    {
     if( shape.press_type==ScrollType_Drag )
       {
        shape.drag(point);

        redraw();

        changed.assert(shape.pos);
       }
     else
       {
        defer_tick.stop();

        redraw();
       }
    }

   void pressOff()
    {
     if( shape.press_type!=ScrollType_Drag ) defer_tick.stop();

     redraw();
    }

   void inside(ScrollType type)
    {
     if( shape.down && shape.mouse )
       {
        if( Change(shape.mover,type) )
          {
           shape.down=ScrollType_None;

           releaseMouse();

           pressOff();
          }
       }
     else
       {
        if( Change(shape.mover,type) ) redraw();
       }
    }

   void outside()
    {
     if( shape.down && shape.mouse )
       {
        shape.down=ScrollType_None;
        shape.mover=ScrollType_None;

        releaseMouse();

        pressOff();
       }
     else
       {
        if( Change(shape.mover,ScrollType_None) ) redraw();
       }
    }

   void tick()
    {
     if( shape.posChange() )
       {
        redraw();

        changed.assert(shape.pos);
       }
    }

   void stopDown()
    {
     if( shape.down )
       {
        shape.down=ScrollType_None;

        if( shape.mouse )
          {
           shape.mover=ScrollType_None;

           releaseMouse();
          }

        pressOff();
       }
    }

  public:

   using ShapeType = Shape ;
   using ConfigType = typename Shape::Config ;

   template <class ... TT>
   ScrollWindowOf(SubWindowHost &host,TT && ... tt)
    : SubWindow(host),
      shape( std::forward<TT>(tt)... ),
      input(this)
    {
     defer_tick=input.create(&ScrollWindowOf<Shape>::tick);
    }

   virtual ~ScrollWindowOf() {}

   // methods

   auto getMinSize() const { return shape.getMinSize(); }

   bool isEnabled() const { return shape.enable; }

   void enable(bool enable=true)
    {
     if( Change(shape.enable,enable) ) redraw();
    }

   void disable() { enable(false); }

   void invertWheel(bool invert=true) { invert_wheel=invert; }

   ulen getTotal() const { return shape.total; }

   ulen getPage() const { return shape.page; }

   ulen getPos() const { return shape.pos; }

   void setRange(ulen total,ulen page,ulen pos)
    {
     stopDown();

     shape.total=total;
     shape.page=page;
     shape.pos=pos;

     shape.adjustPos();

     redraw();
    }

   void setRange(ScrollPos spos)
    {
     setRange(spos.total,spos.page,spos.pos);
    }

   void setRange(ulen total,ulen page)
    {
     stopDown();

     shape.total=total;
     shape.page=page;

     shape.adjustPos();

     redraw();
    }

   void setPos(ulen pos)
    {
     stopDown();

     shape.pos=pos;

     shape.adjustPos();

     redraw();
    }

   void setStep(ulen step) { shape.step=step; }

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
     shape.down=ScrollType_None;
     shape.mover=ScrollType_None;

     defer_tick.stop();
    }

   virtual void close()
    {
     defer_tick.stop();
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
        shape.down=ScrollType_None;
        shape.focus=false;

        pressOff();
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
        shape.down=ScrollType_None;
        shape.mover=ScrollType_None;

        pressOff();
       }
    }

   virtual MouseShape getMouseShape(Point,KeyMod) const
    {
     if( shape.enable && shape.page<shape.total ) return Mouse_Hand;

     return Mouse_Arrow;
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
        case VKey_Home :
         {
          if( shape.enable && !shape.down )
            {
             shape.beg();

             redraw();

             changed.assert(shape.pos);
            }
         }
        break;

        case VKey_End :
         {
          if( shape.enable && !shape.down )
            {
             shape.end();

             redraw();

             changed.assert(shape.pos);
            }
         }
        break;

        case Shape::DownKey :
         {
          if( shape.enable && !shape.down )
            {
             shape.down=ScrollType_Down;
             shape.mouse=false;

             pressOn(ScrollType_Down);
            }
         }
        break;

        case Shape::UpKey :
         {
          if( shape.enable && !shape.down )
            {
             shape.down=ScrollType_Up;
             shape.mouse=false;

             pressOn(ScrollType_Up);
            }
         }
        break;

        case VKey_PageUp :
         {
          if( shape.enable && !shape.down )
            {
             shape.down=ScrollType_DownPage;
             shape.mouse=false;

             pressOn(ScrollType_DownPage);
            }
         }
        break;

        case VKey_PageDown :
         {
          if( shape.enable && !shape.down )
            {
             shape.down=ScrollType_UpPage;
             shape.mouse=false;

             pressOn(ScrollType_UpPage);
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
        case Shape::DownKey :
         {
          if( shape.down==ScrollType_Down && !shape.mouse )
            {
             shape.down=ScrollType_None;

             pressOff();
            }
         }
        break;

        case Shape::UpKey :
         {
          if( shape.down==ScrollType_Up && !shape.mouse )
            {
             shape.down=ScrollType_None;

             pressOff();
            }
         }
        break;

        case VKey_PageUp :
         {
          if( shape.down==ScrollType_DownPage && !shape.mouse )
            {
             shape.down=ScrollType_None;

             pressOff();
            }
         }
        break;

        case VKey_PageDown :
         {
          if( shape.down==ScrollType_UpPage && !shape.mouse )
            {
             shape.down=ScrollType_None;

             pressOff();
            }
         }
        break;
       }
    }

   void react_LeftClick(Point point,MouseKey)
    {
     if( shape.enable && !shape.down )
       {
        if( ScrollType type=shape.getType(point) )
          {
           shape.mover=type;
           shape.down=type;
           shape.mouse=true;

           captureMouse();

           pressOn(type,point);
          }
       }
    }

   void react_LeftUp(Point point,MouseKey)
    {
     if( shape.down && shape.mouse )
       {
        shape.down=ScrollType_None;
        shape.mover=shape.getType(point);

        releaseMouse();

        pressOff(point);
       }
    }

   void react_Move(Point point,MouseKey mkey)
    {
     if( shape.down==ScrollType_Drag && shape.mouse )
       {
        if( mkey&MouseKey_Left )
          drag(point);
        else
          react_LeftUp(point,mkey);
       }
     else
       {
        if( shape.down && shape.mouse && !(mkey&MouseKey_Left) )
          {
           react_LeftUp(point,mkey);
          }
        else
          {
           if( ScrollType type=shape.getType(point) )
             inside(type);
           else
             outside();
          }
       }
    }

   void react_Leave()
    {
     if( shape.down==ScrollType_Drag && shape.mouse )
       {
        // do nothing
       }
     else
       {
        outside();
       }
    }

   void react_Wheel(Point,MouseKey mkey,Coord delta_)
    {
     if( shape.enable && !shape.down )
       {
        ulen delta=IntAbs(delta_);

        if( invert_wheel? delta_<0 : ( delta_>0 ) )
          {
           if( mkey&MouseKey_Shift )
             shape.subPage(delta);
           else
             shape.sub(delta);
          }
        else
          {
           if( mkey&MouseKey_Shift )
             shape.addPage(delta);
           else
             shape.add(delta);
          }

        redraw();

        changed.assert(shape.pos);
       }
    }

   // signals

   Signal<ulen> changed; // pos
   Signal<bool> tabbed;  // shift
 };

/* type XScrollWindow */

using XScrollWindow = ScrollWindowOf<XScrollShape> ;

/* type YScrollWindow */

using YScrollWindow = ScrollWindowOf<YScrollShape> ;

} // namespace Video
} // namespace CCore

#endif

