/* Window.Spinor.h */
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

#ifndef CCore_inc_video_lib_Window_Spinor_h
#define CCore_inc_video_lib_Window_Spinor_h

#include <CCore/inc/video/SubWindow.h>

#include <CCore/inc/video/lib/Shape.Spinor.h>

namespace CCore {
namespace Video {

/* classes */

template <class Shape> class SpinorWindowOf;

/* class SpinorWindowOf<Shape> */

template <class Shape>
class SpinorWindowOf : public SubWindow
 {
   Shape shape;

   DeferInput<SpinorWindowOf<Shape> > input;

   DeferTick defer_tick;

  private:

   static int MinSub(unsigned delta,unsigned a,unsigned b) { return (int)Min(delta,b-a); }

   void incVal(int delta)
    {
     if( delta<=0 ) return;

     shape.val+=MinSub(delta,shape.val,shape.max_val);
    }

   void decVal(int delta)
    {
     if( delta<=0 ) return;

     shape.val-=MinSub(delta,shape.min_val,shape.val);
    }

   void spin()
    {
     switch( shape.down )
       {
        case SpinType_Plus :
         {
          if( shape.val<shape.max_val )
            {
             incVal(shape.delta);

             changed.assert(shape.val);
            }
          else
            {
             defer_tick.stop();
            }
         }
        break;

        case SpinType_Minus :
         {
          if( shape.val>shape.min_val )
            {
             decVal(shape.delta);

             changed.assert(shape.val);
            }
          else
            {
             defer_tick.stop();
            }
         }
        break;
       }
    }

   void btnDown()
    {
     redraw();

     defer_tick.start();

     shape.tickStart();

     spin();
    }

   void btnUp()
    {
     defer_tick.stop();

     redraw();
    }

   void hilight(SpinType zone)
    {
     if( shape.down && shape.mouse )
       {
        if( zone!=shape.down )
          {
           shape.down=SpinType_None;
           shape.mover=SpinType_None;

           releaseMouse();

           btnUp();
          }
       }
     else
       {
        if( Change(shape.mover,zone) ) redraw();
       }
    }

   void tick()
    {
     if( shape.tick() )
       {
        redraw();

        spin();
       }
    }

   void deltaUp()
    {
     if( shape.delta<Shape::DeltaCap )
       {
        shape.delta*=10;

        redraw();
       }
    }

   void deltaDown()
    {
     if( shape.delta>=10 )
       {
        shape.delta/=10;

        redraw();
       }
    }

  public:

   using ShapeType = Shape ;
   using ConfigType = typename Shape::Config ;

   template <class ... TT>
   explicit SpinorWindowOf(SubWindowHost &host,TT && ... tt)
    : SubWindow(host),
      shape( std::forward<TT>(tt)... ),
      input(this)
    {
     defer_tick=input.create(&SpinorWindowOf<Shape>::tick);
    }

   virtual ~SpinorWindowOf() {}

   // methods

   auto getMinSize() const { return shape.getMinSize(); }

   bool isEnabled() const { return shape.enable; }

   void enable(bool enable=true)
    {
     if( Change(shape.enable,enable) ) redraw();
    }

   void disable() { enable(false); }

   int getValue() const { return shape.val; }

   void setValue(int val)
    {
     shape.val=Cap(shape.min_val,val,shape.max_val);

     redraw();
    }

   void setRange(int min_val,int max_val)
    {
     shape.min_val=min_val;
     shape.max_val=max_val;
     shape.val=Cap(min_val,shape.val,max_val);

     redraw();
    }

   void setOptions(const IntPrintOpt &opt)
    {
     shape.opt=opt;

     redraw();
    }

   void setOptions(StrLen str)
    {
     IntPrintOpt opt(str.ptr,str.ptr+str.len);

     setOptions(opt);
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
     shape.mover=SpinType_None;
     shape.down=SpinType_None;

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
        shape.focus=false;
        shape.down=SpinType_None;

        btnUp();
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
        shape.mover=SpinType_None;
        shape.down=SpinType_None;

        btnUp();
       }
    }

   virtual MouseShape getMouseShape(Point point,KeyMod) const
    {
     return ( shape.enable && shape.getZone(point) )?Mouse_Hand:Mouse_Arrow;
    }

   // user input

   virtual void react(UserAction action)
    {
     action.dispatch(*this);
    }

   void react_Key(VKey vkey,KeyMod kmod)
    {
     if( vkey==VKey_Tab )
       {
        tabbed.assert(kmod&KeyMod_Shift);

        return;
       }

     if( !shape.enable ) return;

     switch( vkey )
       {
        case VKey_NumPlus :
        case VKey_Equal :
         {
          if( !shape.down )
            {
             shape.down=SpinType_Plus;
             shape.mouse=false;

             btnDown();
            }
         }
        break;

        case VKey_NumMinus :
        case VKey_Minus :
         {
          if( !shape.down )
            {
             shape.down=SpinType_Minus;
             shape.mouse=false;

             btnDown();
            }
         }
        break;

        case VKey_PageUp :
         {
          deltaUp();
         }
        break;

        case VKey_PageDown :
         {
          deltaDown();
         }
        break;

        case VKey_Home :
         {
          if( Change(shape.delta,1) ) redraw();
         }
        break;
       }
    }

   void react_KeyUp(VKey vkey,KeyMod)
    {
     switch( vkey )
       {
        case VKey_NumPlus :
        case VKey_Equal :
        case VKey_NumMinus :
        case VKey_Minus :
         {
          if( shape.down && !shape.mouse )
            {
             shape.down=SpinType_None;

             btnUp();
            }
         }
        break;
       }
    }

   void react_LeftClick(Point point,MouseKey)
    {
     if( shape.enable && !shape.down && shape.pane.contains(point) )
       {
        if( SpinType zone=shape.getZone(point) )
          {
           shape.down=zone;
           shape.mouse=true;

           captureMouse();

           btnDown();
          }
       }
    }

   void react_LeftUp(Point,MouseKey)
    {
     if( shape.down && shape.mouse )
       {
        shape.down=SpinType_None;

        releaseMouse();

        btnUp();
       }
    }

   void react_Move(Point point,MouseKey)
    {
     if( shape.pane.contains(point) )
       {
        hilight(shape.getZone(point));
       }
     else
       {
        hilight(SpinType_None);
       }
    }

   void react_Leave()
    {
     hilight(SpinType_None);
    }

   void react_Wheel(Point,MouseKey mkey,Coord delta)
    {
     if( shape.enable && !shape.down )
       {
        if( mkey&MouseKey_Shift )
          {
           if( delta>0 )
             {
              deltaUp();
             }
           else
             {
              deltaDown();
             }
          }
        else
          {
           if( delta>0 )
             {
              if( shape.val<shape.max_val )
                {
                 incVal(delta*shape.delta);

                 redraw();

                 changed.assert(shape.val);
                }
             }
           else
             {
              if( shape.val>shape.min_val )
                {
                 decVal((-(int)delta)*shape.delta);

                 redraw();

                 changed.assert(shape.val);
                }
             }
          }
       }
    }

   // signals

   Signal<int> changed; // value
   Signal<bool> tabbed; // shift
 };

/* type SpinorWindow */

using SpinorWindow = SpinorWindowOf<SpinorShape> ;

} // namespace Video
} // namespace CCore

#endif

