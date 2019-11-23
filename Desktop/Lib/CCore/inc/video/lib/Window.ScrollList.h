/* Window.ScrollList.h */
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

#ifndef CCore_inc_video_lib_Window_ScrollList_h
#define CCore_inc_video_lib_Window_ScrollList_h

#include <CCore/inc/video/lib/Window.Scrollable.h>

#include <CCore/inc/video/lib/Shape.ScrollList.h>

namespace CCore {
namespace Video {

/* classes */

struct ScrollListWindowBase;

template <class Shape> class ScrollListInnerWindowOf;

template <class Shape,class XShape,class YShape> class ScrollListWindowOf;

/* struct ScrollListWindowBase */

struct ScrollListWindowBase
 {
  // signals

  Signal<> entered;
  Signal<> dclicked;
  Signal<ulen> selected; // select, always valid
  Signal<bool> tabbed;   // shift
 };

/* class ScrollListInnerWindowOf<Shape> */

template <class Shape>
class ScrollListInnerWindowOf : public SubWindow
 {
   Shape shape;

   SignalConnector<Shape,unsigned> connector_updated;

   ScrollListWindowBase *outer;

  private:

   void setXOff(Coord xoff)
    {
     if( Change(shape.xoff,Cap<Coord>(0,xoff,shape.xoff_max)) )
       {
        redraw();

        scroll_x.assert((ulen)shape.xoff);
       }
    }

   void addXOff(Coord count)
    {
     Coord xoff=shape.xoff+count*shape.dxoff;

     setXOff(xoff);
    }

   void setYOff(ulen yoff)
    {
     if( Change(shape.yoff,Min(yoff,shape.yoff_max)) )
       {
        redraw();

        scroll_y.assert(shape.yoff);
       }
    }

   void addYOff(ulen delta)
    {
     setYOff(AddToCap(shape.yoff,delta,shape.yoff_max));
    }

   void subYOff(ulen delta)
    {
     setYOff(PosSub(shape.yoff,delta));
    }

   void showSelect()
    {
     if( shape.showSelect() ) scroll_y.assert(shape.yoff);
    }

   void selectFirst()
    {
     if( shape.setSelectDown(0) )
       {
        shape.yoff=0;

        showSelect();

        redraw();

        outer->selected.assert(shape.select);
       }
    }

   void selectLast()
    {
     ulen count=shape.getLineCount();

     if( count && shape.setSelectUp(count-1) )
       {
        showSelect();

        redraw();

        outer->selected.assert(shape.select);
       }
    }

   void addSelect(ulen delta)
    {
     if( shape.select==MaxULen ) return;

     if( ulen count=shape.getLineCount() )
       {
        if( shape.setSelectDown( AddToCap(shape.select,delta,count-1) ) )
          {
           showSelect();

           redraw();

           outer->selected.assert(shape.select);
          }
        else
          {
           addYOff(delta);
          }
       }
    }

   void subSelect(ulen delta)
    {
     if( shape.select==MaxULen ) return;

     if( shape.setSelectUp( PosSub(shape.select,delta) ) )
       {
        showSelect();

        redraw();

        outer->selected.assert(shape.select);
       }
     else
       {
        subYOff(delta);
       }
    }

   void setSelect(ulen index)
    {
     if( ulen count=shape.getLineCount() )
       {
        if( shape.setSelectDown( Min_cast(index,count-1) ) )
          {
           showSelect();

           redraw();

           outer->selected.assert(shape.select);
          }
       }
    }

  private:

   void posX(ulen pos)
    {
     shape.xoff=(Coord)pos;

     redraw();
    }

   void posY(ulen pos)
    {
     shape.yoff=pos;

     redraw();
    }

   SignalConnector<ScrollListInnerWindowOf<Shape>,ulen> connector_posX;
   SignalConnector<ScrollListInnerWindowOf<Shape>,ulen> connector_posY;

  public:

   using ShapeType = Shape ;
   using ConfigType = typename ShapeType::Config ;

   using InfoType = typename Shape::InfoType ;

   template <class ... TT>
   ScrollListInnerWindowOf(SubWindowHost &host,const ConfigType &cfg,ScrollListWindowBase *outer_,TT && ... tt)
    : SubWindow(host),
      shape(cfg, std::forward<TT>(tt)... ),
      connector_updated(&shape,&Shape::update,host.getUpdated()),
      outer(outer_),
      connector_posX(this,&ScrollListInnerWindowOf<Shape>::posX),
      connector_posY(this,&ScrollListInnerWindowOf<Shape>::posY)
    {
    }

   virtual ~ScrollListInnerWindowOf() {}

   // special methods

   bool shortDX() const { return shape.xoff_max>0; }

   bool shortDY() const { return shape.yoff_max>0; }

   ScrollPos getScrollXRange() const
    {
     Coord page=getSize().x;

     return {(ulen)shape.xoff_max+(ulen)page,(ulen)page,(ulen)shape.xoff};
    }

   ScrollPos getScrollYRange() const
    {
     return {shape.yoff_max+shape.page,shape.page,shape.yoff};
    }

   void adjustScrollPos()
    {
     shape.adjustScrollPos();
    }

   void connect(Signal<ulen> &scroll_x,Signal<ulen> &scroll_y)
    {
     connector_posX.connect(scroll_x);
     connector_posY.connect(scroll_y);
    }

   // methods

   unsigned getUpdateMask() const { return shape.update_mask; }

   void setUpdateMask(unsigned flags) { shape.update_mask=flags|LayoutUpdate; }

   Point getMinSize(Point cap=Point::Max()) const { return shape.getMinSize(cap); }

   Point getMinSize(unsigned lines) const { return shape.getMinSize(lines); }

   bool isEnabled() const { return shape.enable; }

   void enable(bool enable=true)
    {
     if( Change(shape.enable,enable) ) redraw();
    }

   void disable() { enable(false); }

   const InfoType & getInfo() const { return shape.info; }

   void setInfo(const InfoType &info)
    {
     shape.info=info;

     update();
    }

   void update()
    {
     shape.yoff=0;
     shape.xoff=0;

     shape.initSelect();

     shape.update(LayoutUpdate);
     shape.layout();

     redraw();
    }

   ulen getSelect() const { return shape.select; } // valid OR MaxULen, if there is no positions

   bool select(ulen index)
    {
     if( ulen count=shape.getLineCount() )
       {
        if( shape.setSelectDown( Min_cast(index,count-1) ) )
          {
           showSelect();

           redraw();

           return true;
          }
        else
          {
           if( shape.select<count && shape.isSelectable(shape.select) )
             {
              return true;
             }
          }
       }

     shape.select=MaxULen;

     return false;
    }

   bool reselect()
    {
     return select(shape.select);
    }

   void ping()
    {
     ulen count=shape.getLineCount();

     if( shape.select<count && shape.isSelectable(shape.select) )
       {
        outer->selected.assert(shape.select);
       }
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
     // do nothing
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

   void react_Key(VKey vkey,KeyMod kmod,unsigned repeat)
    {
     if( vkey==VKey_Tab )
       {
        outer->tabbed.assert(kmod&KeyMod_Shift);

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

        case VKey_Up :
         {
          if( kmod&KeyMod_Shift )
            {
             subYOff(repeat);
            }
          else
            {
             subSelect(repeat);
            }
         }
        break;

        case VKey_Down :
         {
          if( kmod&KeyMod_Shift )
            {
             addYOff(repeat);
            }
          else
            {
             addSelect(repeat);
            }
         }
        break;

        case VKey_PageUp :
         {
          ulen delta=shape.page*repeat;

          subYOff(delta);
          subSelect(delta);
         }
        break;

        case VKey_PageDown :
         {
          ulen delta=shape.page*repeat;

          addYOff(delta);
          addSelect(delta);
         }
        break;

        case VKey_Home :
         {
          selectFirst();
         }
        break;

        case VKey_End :
         {
          selectLast();
         }
        break;

        case VKey_Enter :
         {
          outer->entered.assert();
         }
        break;
       }
    }

   void react_LeftClick(Point point,MouseKey)
    {
     if( !shape.enable ) return;

     setSelect(shape.getPosition(point));
    }

   void react_LeftDClick(Point,MouseKey)
    {
     if( !shape.enable ) return;

     outer->dclicked.assert();
    }

   void react_Wheel(Point,MouseKey mkey,Coord delta_)
    {
     if( !shape.enable ) return;

     ulen delta=IntAbs(delta_);

     if( delta_<0 )
       {
        if( mkey&MouseKey_Shift )
          {
           addYOff(delta);
          }
        else
          {
           addSelect(delta);
          }
       }
     else
       {
        if( mkey&MouseKey_Shift )
          {
           subYOff(delta);
          }
        else
          {
           subSelect(delta);
          }
       }
    }

   // signals

   Signal<ulen> scroll_x;
   Signal<ulen> scroll_y;
 };

/* class ScrollListWindowOf<Shape,XShape,YShape> */

template <class Shape,class XShape,class YShape>
class ScrollListWindowOf : public ScrollListWindowBase , public ScrollableWindow<ScrollListInnerWindowOf<Shape>,XShape,YShape>
 {
   using Base = ScrollableWindow<ScrollListInnerWindowOf<Shape>,XShape,YShape> ;

   using Base::window;
   using Base::scroll_x;
   using Base::scroll_y;
   using Base::layout;
   using Base::redraw;

  public:

   using ShapeType = Shape ;

   using InfoType = typename Shape::InfoType ;

   template <class ... TT>
   ScrollListWindowOf(SubWindowHost &host,const typename Base::ConfigType &cfg,TT && ... tt)
    : Base(host,cfg,(ScrollListWindowBase *)this, std::forward<TT>(tt)... )
    {
    }

   virtual ~ScrollListWindowOf() {}

   // methods

   bool isEnabled() const { return window.isEnabled(); }

   void enable(bool enable=true)
    {
     window.enable(enable);
     scroll_x.enable(enable);
     scroll_y.enable(enable);
    }

   void disable() { enable(false); }

   const InfoType & getInfo() const { return window.getInfo(); }

   void setInfo(const InfoType &info)
    {
     window.setInfo(info);

     layout();

     redraw();
    }

   void update()
    {
     window.update();

     layout();

     redraw();
    }

   ulen getSelect() const { return window.getSelect(); }

   bool select(ulen index) { return window.select(index); }

   bool reselect() { return window.reselect(); }

   void ping() { window.ping(); }
 };

/* type ScrollListWindow */

using ScrollListWindow = ScrollListWindowOf<ScrollListShape,XScrollShape,YScrollShape> ;

} // namespace Video
} // namespace CCore

#endif

