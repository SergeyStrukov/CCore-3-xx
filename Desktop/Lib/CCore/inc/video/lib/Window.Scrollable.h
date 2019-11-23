/* Window.Scrollable.h */
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
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_video_lib_Window_Scrollable_h
#define CCore_inc_video_lib_Window_Scrollable_h

#include <CCore/inc/video/BindBagProxy.h>

#include <CCore/inc/video/lib/Window.Scroll.h>

namespace CCore {
namespace Video {

/* consts */

enum DockYBar
 {
  DockLeft,
  DockRight,

  DockYBarDefault = DockRight
 };

enum DockXBar
 {
  DockTop,
  DockBottom,

  DockXBarDefault = DockBottom
 };

/* classes */

template <class Window,class XShape=XScrollShape,class YShape=YScrollShape> class ScrollableWindow;

/* class ScrollableWindow<Window,XShape,YShape> */

#if 0

class Window
 {
   ....

  public:

   using ConfigType = .... ;

   Window(SubWindowHost &host,const ConfigType &cfg, .... );

   ....

   // special methods

   bool shortDX() const;

   bool shortDY() const;

   ScrollPos getScrollXRange() const;

   ScrollPos getScrollYRange() const;

   void adjustScrollPos();

   void connect(Signal<ulen> &scroll_x,Signal<ulen> &scroll_y);

   // methods

   Point getMinSize(Point cap=Point::Max()) const;

   [ Point getMinSize(T arg) const; ]

   // signals

   Signal<ulen> scroll_x;
   Signal<ulen> scroll_y;
 };

#endif

template <class Window,class XShape,class YShape>
class ScrollableWindow : public ComboWindow
 {
  public:

   struct Config
    {
     typename Window::ConfigType window_cfg;

     CtorRefVal<typename XShape::Config> x_cfg;
     CtorRefVal<typename YShape::Config> y_cfg;

     // lib

     Config() noexcept {}

     template <class Bag,class Proxy>
     void bindUser(const Bag &,Proxy proxy)
      {
       x_cfg.bind(proxy);
       y_cfg.bind(proxy);
      }

     template <class Bag,class Proxy>
     void bind(const Bag &bag,Proxy proxy)
      {
       BindBagProxy(window_cfg,bag,proxy);

       bindUser(bag,proxy);
      }

     // app

     template <class UserPref,class AppPref>
     Config(const UserPref &user_pref,const AppPref &app_pref) noexcept
      : window_cfg(user_pref,app_pref)
      {
       bindUser(user_pref.get(),user_pref.getSmartConfig());
      }
    };

  protected:

   const Config &cfg;

   Window window;
   ScrollWindowOf<XShape> scroll_x;
   ScrollWindowOf<YShape> scroll_y;

   DockXBar dockX = DockXBarDefault ;
   DockYBar dockY = DockYBarDefault ;

  private:

   void setScroll()
    {
     window.adjustScrollPos();

     if( scroll_x.isListed() ) scroll_x.setRange(window.getScrollXRange());

     if( scroll_y.isListed() ) scroll_y.setRange(window.getScrollYRange());
    }

   Pane splitX(Pane &pane,Coord delta) const
    {
     if( dockY==DockRight )
       return SplitX(pane,delta);
     else
       return SplitX(delta,pane);
    }

   Pane splitY(Pane &pane,Coord delta) const
    {
     if( dockX==DockBottom )
       return SplitY(pane,delta);
     else
       return SplitY(delta,pane);
    }

  private:

   SignalConnector<ScrollWindowOf<XShape>,ulen> connector_posx;
   SignalConnector<ScrollWindowOf<YShape>,ulen> connector_posy;

  public:

   using ConfigType = Config ;

   template <class ... TT>
   ScrollableWindow(SubWindowHost &host,const Config &cfg_,TT && ... tt)
    : ComboWindow(host),
      cfg(cfg_),

      window(wlist,cfg_.window_cfg, std::forward<TT>(tt)... ),
      scroll_x(wlist,cfg_.x_cfg),
      scroll_y(wlist,cfg_.y_cfg),

      connector_posx(&scroll_x,&ScrollWindowOf<XShape>::setPos,window.scroll_x),
      connector_posy(&scroll_y,&ScrollWindowOf<YShape>::setPos,window.scroll_y)
    {
     wlist.insTop(window);

     window.connect(scroll_x.changed,scroll_y.changed);
    }

   virtual ~ScrollableWindow() {}

   // methods

   unsigned getUpdateMask() const { return window.getUpdateMask(); }

   void setUpdateMask(unsigned flags) { window.setUpdateMask(flags); }

   Point getMinSize(Point cap=Point::Max()) const
    {
     Point delta(scroll_y.getMinSize().dx,0);

     return window.getMinSize(cap-delta)+delta;
    }

   template <class T>
   Point getMinSize(T arg) const
    {
     Point delta(scroll_y.getMinSize().dx,0);

     return window.getMinSize(arg)+delta;
    }

   // dock

   DockXBar getDockX() const { return dockX; }

   DockYBar getDockY() const { return dockY; }

   void setDockX(DockXBar val,bool update=true)
    {
     if( Change(dockX,val) && update )
       {
        layout();

        redraw();
       }
    }

   void setDockY(DockYBar val,bool update=true)
    {
     if( Change(dockY,val) && update )
       {
        layout();

        redraw();
       }
    }

   // drawing

   virtual void layout()
    {
     Pane all=getPane();
     Pane pane(all);

     Coord delta_x=scroll_y.getMinSize().dx;
     Coord delta_y=scroll_x.getMinSize().dy;

     window.setPlace(pane);

     if( window.shortDY() )
       {
        Pane py=splitX(pane,delta_x);

        window.setPlace(pane);
        scroll_y.setPlace(py);

        wlist.insBottom(scroll_y);

        if( window.shortDX() )
          {
           Pane px=splitY(pane,delta_y);

           window.setPlace(pane);
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
        if( window.shortDX() )
          {
           Pane px=splitY(pane,delta_y);

           window.setPlace(pane);

           if( window.shortDY() )
             {
              pane=all;
              Pane py=splitX(pane,delta_x);
              Pane px=splitY(pane,delta_y);

              window.setPlace(pane);
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

} // namespace Video
} // namespace CCore

#endif

