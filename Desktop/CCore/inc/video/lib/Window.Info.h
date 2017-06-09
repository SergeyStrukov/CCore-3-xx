/* Window.Info.h */
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

#ifndef CCore_inc_video_lib_Window_Info_h
#define CCore_inc_video_lib_Window_Info_h

#include <CCore/inc/video/SubWindow.h>

#include <CCore/inc/video/lib/Shape.Info.h>

namespace CCore {
namespace Video {

/* classes */

template <class Shape> class InfoWindowOf;

/* class InfoWindowOf<Shape> */

template <class Shape>
class InfoWindowOf : public SubWindow
 {
   Shape shape;

  private:

   void setXOff(Coord xoff)
    {
     if( Change(shape.xoff,Cap<Coord>(0,xoff,shape.xoffMax)) ) redraw();
    }

   void addXOff(Coordinate count)
    {
     Coordinate xoff=shape.xoff+count*shape.dxoff;

     setXOff(+xoff);
    }

   void setYOff(ulen yoff)
    {
     if( Change(shape.yoff,Min(yoff,shape.yoffMax)) ) redraw();
    }

   void addYOff(ulen delta)
    {
     setYOff(AddToCap(shape.yoff,delta,shape.yoffMax));
    }

   void subYOff(ulen delta)
    {
     setYOff(PosSub(shape.yoff,delta));
    }

   void startDrag(Point point)
    {
     if( Change(shape.drag,true) )
       {
        shape.drag_base=point;
        shape.xoff_base=shape.xoff;

        captureMouse();
       }
    }

   void dragTo(Point point)
    {
     Coordinate xoff=shape.xoff_base-(Coordinate(point.x)-shape.drag_base.x);

     setXOff(+xoff);
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

  public:

   using ShapeType = Shape ;
   using ConfigType = typename Shape::Config ;

   template <class ... TT>
   InfoWindowOf(SubWindowHost &host,TT && ... tt)
    : SubWindow(host),
      shape( std::forward<TT>(tt)... )
    {
    }

   virtual ~InfoWindowOf()
    {
    }

   // methods

   auto getMinSize(Point cap=Point::Max()) const { return shape.getMinSize(cap); }

   bool isEnabled() const { return shape.enable; }

   void enable(bool enable=true)
    {
     if( Change(shape.enable,enable) ) redraw();
    }

   void disable() { enable(false); }

   void setInfo(const Info &info)
    {
     shape.info=info;
     shape.yoff=0;
     shape.xoff=0;

     shape.setMax();

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

     shape.setMax();
    }

   virtual void draw(DrawBuf buf,bool) const
    {
     shape.draw(buf);
    }

   // base

   virtual void open()
    {
     shape.focus=false;
     shape.drag=false;

     shape.xoff=0;
     shape.yoff=0;
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
    }

   virtual MouseShape getMouseShape(Point,KeyMod) const
    {
     if( !shape.enable ) return Mouse_Arrow;

     if( shape.xoffMax>0 || shape.xoff>0 ) return Mouse_SizeLeftRight;

     return Mouse_Arrow;
    }

   // user input

   virtual void react(UserAction action)
    {
     action.dispatch(*this);
    }

   void react_Key(VKey vkey,KeyMod,unsigned repeat)
    {
     switch( vkey )
       {
        case VKey_Left :
         {
          addXOff(-CountToCoordinate(repeat));
         }
        break;

        case VKey_Right :
         {
          addXOff(CountToCoordinate(repeat));
         }
        break;

        case VKey_Up :
         {
          subYOff(repeat);
         }
        break;

        case VKey_Down :
         {
          addYOff(repeat);
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

   void react_Wheel(Point,MouseKey,Coord delta)
    {
     if( delta>0 )
       {
        addYOff(IntAbs(delta));
       }
     else
       {
        subYOff(IntAbs(delta));
       }
    }
 };

/* type InfoWindow */

using InfoWindow = InfoWindowOf<InfoShape> ;

} // namespace Video
} // namespace CCore

#endif

