/* Window.TextLine.h */
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

   SignalConnector<Shape,unsigned> connector_updated;

  private:

   void setXOff(Coord xoff)
    {
     if( Change(shape.xoff,Cap<Coord>(0,xoff,shape.xoff_max)) ) redraw();
    }

   void addXOff(Coord count)
    {
     Coord xoff=shape.xoff+count*shape.dxoff;

     setXOff(xoff);
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
     Coord xoff=shape.xoff_base-(point.x-shape.drag_base.x);

     setXOff(xoff);
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
      shape( std::forward<TT>(tt)... ),
      connector_updated(&shape,&Shape::update,host.getUpdated())
    {
    }

   virtual ~TextLineWindowOf() {}

   // methods

   unsigned getUpdateMask() const { return shape.update_mask; }

   void setUpdateMask(unsigned flags) { shape.update_mask=flags|LayoutUpdate; }

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

   void alertCode(auto code)
    {
     if( Change(shape.code,code) ) redraw();
    }

   String getText() const { return shape.text; }

   void setText(const String &text)
    {
     shape.text=text;

     shape.update(LayoutUpdate);
     shape.layout();

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
     shape.pane=getPane();

     shape.layout();
    }

   virtual void draw(DrawBuf buf,DrawParam draw_param) const
    {
     shape.draw(buf,draw_param);
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

     if( shape.xoff_max>0 || shape.xoff>0 ) return Mouse_SizeLeftRight;

     return Mouse_Arrow;
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
        case VKey_Left :
         {
          addXOff(-CountToCoord(repeat));
         }
        break;

        case VKey_Right :
         {
          addXOff(CountToCoord(repeat));
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
     if( !shape.enable ) return;

     addXOff(delta);
    }

   // signals

   Signal<bool> tabbed; // shift
 };

/* type TextLineWindow */

using TextLineWindow = TextLineWindowOf<TextLineShape> ;

/* type TextLineCodeWindow */

using TextLineCodeWindow = TextLineWindowOf<TextLineCodeShape> ;

} // namespace Video
} // namespace CCore

#endif

