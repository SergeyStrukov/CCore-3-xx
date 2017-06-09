/* Window.ScrollList.h */
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

#ifndef CCore_inc_video_lib_Window_ScrollList_h
#define CCore_inc_video_lib_Window_ScrollList_h

#include <CCore/inc/video/lib/Window.Scroll.h>

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
 };

/* class ScrollListInnerWindowOf<Shape> */

template <class Shape>
class ScrollListInnerWindowOf : public SubWindow
 {
   Shape shape;

   ScrollListWindowBase *outer;

  private:

   void setXOff(Coord xoff)
    {
     if( Change(shape.xoff,Cap<Coord>(0,xoff,shape.xoffMax)) )
       {
        redraw();

        scroll_x.assert((ulen)shape.xoff);
       }
    }

   void addXOff(Coordinate count)
    {
     Coordinate xoff=shape.xoff+count*shape.dxoff;

     setXOff(+xoff);
    }

   void setYOff(ulen yoff)
    {
     if( Change(shape.yoff,Min(yoff,shape.yoffMax)) )
       {
        redraw();

        scroll_y.assert(shape.yoff);
       }
    }

   void addYOff(ulen delta)
    {
     setYOff(AddToCap(shape.yoff,delta,shape.yoffMax));
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
        showSelect();

        redraw();

        outer->selected.assert(shape.select);
       }
    }

   void selectLast()
    {
     ulen count=shape.info->getLineCount();

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

     if( ulen count=shape.info->getLineCount() )
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
     if( ulen count=shape.info->getLineCount() )
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

   template <class ... TT>
   ScrollListInnerWindowOf(SubWindowHost &host,ScrollListWindowBase *outer_,TT && ... tt)
    : SubWindow(host),
      shape( std::forward<TT>(tt)... ),
      outer(outer_),
      connector_posX(this,&ScrollListInnerWindowOf<Shape>::posX),
      connector_posY(this,&ScrollListInnerWindowOf<Shape>::posY)
    {
    }

   virtual ~ScrollListInnerWindowOf()
    {
    }

   // special methods

   bool shortDX() const { return shape.xoffMax>0; }

   bool shortDY() const { return shape.yoffMax>0; }

   template <class W>
   void setScrollXRange(W &window)
    {
     window.setRange((ulen)shape.xoffMax+(ulen)shape.dxoff,(ulen)shape.dxoff,(ulen)shape.xoff);
    }

   template <class W>
   void setScrollYRange(W &window)
    {
     window.setRange(shape.yoffMax+shape.page,shape.page,shape.yoff);
    }

   void connect(Signal<ulen> &scroll_x,Signal<ulen> &scroll_y)
    {
     connector_posX.connect(scroll_x);
     connector_posY.connect(scroll_y);
    }

   // methods

   auto getMinSize(Point cap=Point::Max()) const { return shape.getMinSize(cap); }

   bool isEnabled() const { return shape.enable; }

   void enable(bool enable=true)
    {
     if( Change(shape.enable,enable) ) redraw();
    }

   void disable() { enable(false); }

   void setInfo(const ComboInfo &info)
    {
     shape.info=info;
     shape.yoff=0;
     shape.xoff=0;

     shape.initSelect();

     shape.setMax();

     redraw();
    }

   const ComboInfo & getInfo() const { return shape.info; }

   ulen getSelect() const { return shape.select; } // valid OR MaxULen, if there is no positions

   bool select(ulen index)
    {
     if( ulen count=shape.info->getLineCount() )
       {
        if( shape.setSelectDown( Min_cast(index,count-1) ) )
          {
           showSelect();

           redraw();

           return true;
          }
        else
          {
           if( shape.select<count && shape.info->getLine(shape.select).type==ComboInfoText )
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
     ulen count=shape.info->getLineCount();

     if( shape.select<count && shape.info->getLine(shape.select).type==ComboInfoText )
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
     if( !shape.enable ) return;

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
class ScrollListWindowOf : public ComboWindow , public ScrollListWindowBase
 {
  public:

   struct Config : Shape::Config
    {
     CtorRefVal<typename XShape::Config> x_cfg;
     CtorRefVal<typename YShape::Config> y_cfg;

     Config() noexcept {}

     template <class Bag,class Proxy>
     void bind(const Bag &bag,Proxy proxy)
      {
       Shape::Config::bind(bag);

       x_cfg.bind(proxy);
       y_cfg.bind(proxy);
      }
    };

  private:

   const Config &cfg;

   ScrollListInnerWindowOf<Shape> inner;
   ScrollWindowOf<XShape> scroll_x;
   ScrollWindowOf<YShape> scroll_y;

  private:

   void setScroll()
    {
     if( scroll_x.isListed() ) inner.setScrollXRange(scroll_x);

     if( scroll_y.isListed() ) inner.setScrollYRange(scroll_y);
    }

  private:

   SignalConnector<ScrollWindowOf<XShape>,ulen> connector_posx;
   SignalConnector<ScrollWindowOf<YShape>,ulen> connector_posy;

  public:

   using ShapeType = Shape ;
   using ConfigType = Config ;

   template <class ... TT>
   ScrollListWindowOf(SubWindowHost &host,const Config &cfg_,TT && ... tt)
    : ComboWindow(host),
      cfg(cfg_),
      inner(wlist,this,cfg_, std::forward<TT>(tt)... ),
      scroll_x(wlist,cfg_.x_cfg),
      scroll_y(wlist,cfg_.y_cfg),
      connector_posx(&scroll_x,&ScrollWindowOf<XShape>::setPos,inner.scroll_x),
      connector_posy(&scroll_y,&ScrollWindowOf<YShape>::setPos,inner.scroll_y)
    {
     wlist.insTop(inner);

     inner.connect(scroll_x.changed,scroll_y.changed);
    }

   virtual ~ScrollListWindowOf()
    {
    }

   // methods

   auto getMinSize(Point cap=Point::Max()) const
    {
     Point delta(scroll_y.getMinSize().dx,0);

     return inner.getMinSize(cap-delta)+delta;
    }

   bool isEnabled() const { return inner.isEnabled(); }

   void enable(bool enable=true)
    {
     inner.enable(enable);
     scroll_x.enable(enable);
     scroll_y.enable(enable);
    }

   void disable() { enable(false); }

   void setInfo(const ComboInfo &info)
    {
     inner.setInfo(info);

     layout();

     redraw();
    }

   const ComboInfo & getInfo() const { return inner.getInfo(); }

   ulen getSelect() const { return inner.getSelect(); }

   bool select(ulen index) { return inner.select(index); }

   bool reselect() { return inner.reselect(); }

   void ping() { inner.ping(); }

   // drawing

   virtual void layout()
    {
     Pane all(Null,getSize());
     Pane pane(all);

     Coord delta_x=scroll_y.getMinSize().dx;
     Coord delta_y=scroll_x.getMinSize().dy;

     inner.setPlace(pane);

     if( inner.shortDY() )
       {
        Pane py=SplitX(pane,delta_x);

        inner.setPlace(pane);
        scroll_y.setPlace(py);

        wlist.insBottom(scroll_y);

        if( inner.shortDX() )
          {
           Pane px=SplitY(pane,delta_y);

           inner.setPlace(pane);
           scroll_x.setPlace(px);

           wlist.insBottom(scroll_x);
          }
        else
          {
           wlist.del(scroll_x);
          }
       }
     else
       {
        if( inner.shortDX() )
          {
           Pane px=SplitY(pane,delta_y);

           inner.setPlace(pane);

           if( inner.shortDY() )
             {
              pane=all;
              Pane py=SplitX(pane,delta_x);
              Pane px=SplitY(pane,delta_y);

              inner.setPlace(pane);
              scroll_x.setPlace(px);
              scroll_y.setPlace(py);

              wlist.insBottom(scroll_x);

              wlist.insBottom(scroll_y);
             }
           else
             {
              scroll_x.setPlace(px);

              wlist.insBottom(scroll_x);

              wlist.del(scroll_y);
             }
          }
        else
          {
           wlist.del(scroll_x);

           wlist.del(scroll_y);
          }
       }

     setScroll();
    }
 };

/* type ScrollListWindow */

using ScrollListWindow = ScrollListWindowOf<ScrollListShape,XScrollShape,YScrollShape> ;

} // namespace Video
} // namespace CCore

#endif

