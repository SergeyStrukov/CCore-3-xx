/* Window.TextLine.h */
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

#ifndef CCore_inc_video_lib_Window_TextLine_h
#define CCore_inc_video_lib_Window_TextLine_h

#include <CCore/inc/video/SubWindow.h>

#include <CCore/inc/video/lib/Shape.TextLine.h>

namespace CCore {
namespace Video {

/* classes */

template <class Shape> class TextLineWindowOf;

/* class TextLineWindowOf<Shape> */

template <class Shape>
class TextLineWindowOf : public SubWindow
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
   TextLineWindowOf(SubWindowHost &host,TT && ... tt)
    : SubWindow(host),
      shape( std::forward<TT>(tt)... )
    {
    }

   virtual ~TextLineWindowOf()
    {
    }

   // methods

   auto getMinSize() const { return shape.getMinSize(); }

   Point getMinSize(StrLen sample_text) const { return shape.getMinSize(sample_text); }

   bool isEnabled() const { return shape.enable; }

   bool isAlerted() const { return shape.alert; }

   void enable(bool enable=true)
    {
     if( Change(shape.enable,enable) ) redraw();
    }

   void disable() { enable(false); }

   void alert(bool on=true)
    {
     if( Change(shape.alert,on) ) redraw();
    }

   DefString getText() const { return shape.text; }

   void setText(const DefString &text)
    {
     shape.text=text;

     shape.setMax();

     shape.xoff=0;

     redraw();
    }

   template <class ... TT>
   void printf(const char *format,const TT & ... tt)
    {
     setText( Stringf(format,tt...) );
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

     if( ( shape.xoffMax>0 || shape.xoff>0 ) ) return Mouse_SizeLeftRight;

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
     addXOff(delta);
    }
 };

/* type TextLineWindow */

using TextLineWindow = TextLineWindowOf<TextLineShape> ;

} // namespace Video
} // namespace CCore

#endif

