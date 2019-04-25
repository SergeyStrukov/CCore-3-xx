/* FrameClient.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.60
//
//  Tag: Desktop
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_video_FrameClient_h
#define CCore_inc_video_FrameClient_h

#include <CCore/inc/video/lib/Window.DragFrame.h>

#include <CCore/inc/video/Layout.h>

namespace CCore {
namespace Video {

/* classes */

struct FramePlace;

template <class W> class FrameClient;

template <class W,class P=FramePlace> class FrameClientPlace;

/* struct FramePlace */

struct FramePlace
 {
  Pane place;
  bool ok = false ;

  void set(Pane pane)
   {
    if( +pane )
      {
       place=pane;
       ok=true;
      }
   }

  template <class T>
  void set(T data)
   {
    if( data.ok )
      {
       place.x=data.x;
       place.y=data.y;
       place.dx=data.dx;
       place.dy=data.dy;

       ok=true;
      }
    else
      {
       ok=false;
      }
   }

  Pane get(Point size) const { Used(size); return place; }

  void print(PrinterType &out) const
   {
    if( ok )
      Printf(out,"{ #; , #; , #; , #; , True }",place.x,place.y,place.dx,place.dy);
    else
      Putobj(out,"{ .ok = False }"_c);
   }
 };

/* concept CapSizeType<W> */

template <class W> // ref extended
concept bool CapSizeType = requires (Meta::ToConst<W> &cobj,Point cap)
 {
  { cobj.getMinSize(cap) } -> Point ;
 } ;

/* class FrameClient<W> */

template <class W>
class FrameClient : public DragFrame
 {
  public:

   struct Config
    {
     RefVal<Ratio> pos_ry = Div(5,12) ;

     CtorRefVal<DragFrame::ConfigType> frame_cfg;
     CtorRefVal<typename W::ConfigType> client_cfg;

     Config() noexcept {}

     template <class Bag,class Proxy>
     void bind(const Bag &bag,Proxy proxy)
      {
       pos_ry.bind(bag.frame_pos_ry);

       frame_cfg.bind(proxy);
       client_cfg.bind(proxy);
      }
    };

   using ConfigType = Config ;

  protected:

   const Config &cfg;

   W client;

  public:

   template <class ... TT>
   FrameClient(Desktop *desktop,const Config &cfg_,TT && ... tt)
    : DragFrame(desktop,cfg_.frame_cfg),
      cfg(cfg_),
      client(*this,cfg_.client_cfg, std::forward<TT>(tt)... )
    {
     bindClient(client);
    }

   template <class ... TT>
   FrameClient(Desktop *desktop,const Config &cfg,Signal<> &update,TT && ... tt)
    : FrameClient(desktop,cfg, std::forward<TT>(tt)... )
    {
     connectUpdate(update);
    }

   virtual ~FrameClient()
    {
    }

   // create

   Pane getPane(StrLen title,Point base) const requires ( !CapSizeType<W> )
    {
     Point size=getMinSize(false,title,client.getMinSize());

     return FitToScreen(base,size,getScreenSize());
    }

   Pane getPane(StrLen title) const requires ( !CapSizeType<W> )
    {
     Point size=getMinSize(false,title,client.getMinSize());

     return GetWindowPlace(getDesktop(),+cfg.pos_ry,size);
    }

   Pane getPane(StrLen title,Point base) const requires ( CapSizeType<W> )
    {
     Point screen_size=getScreenSize();
     Point cap=Div(9,10)*screen_size;
     Point size=getMinSize(false,title,client.getMinSize(cap));

     return FitToScreen(base,size,screen_size);
    }

   Pane getPane(StrLen title) const requires ( CapSizeType<W> )
    {
     Point cap=Div(9,10)*getScreenSize();
     Point size=getMinSize(false,title,client.getMinSize(cap));

     return GetWindowPlace(getDesktop(),+cfg.pos_ry,size);
    }

   void create(Point base,const String &title)
    {
     DragFrame::create(getPane(Range(title),base),title);
    }

   void create(FrameWindow *parent,Point base,const String &title)
    {
     DragFrame::create(parent,getPane(Range(title),base),title);
    }

   void create(const String &title)
    {
     DragFrame::create(getPane(Range(title)),title);
    }

   void create(FrameWindow *parent,const String &title)
    {
     DragFrame::create(parent,getPane(Range(title)),title);
    }
 };

/* class FrameClientPlace<W,P> */

template <class W,class P>
class FrameClientPlace : public DragFrame
 {
  public:

   struct Config : W::FrameConfig
    {
     RefVal<Ratio> pos_ry = Div(5,12) ;

     CtorRefVal<DragFrame::ConfigType> frame_cfg;

     typename W::ConfigType client_cfg;

     // lib

     Config() noexcept {}

     template <class Bag,class Proxy>
     void bindUser(const Bag &bag,Proxy proxy)
      {
       pos_ry.bind(bag.frame_pos_ry);

       frame_cfg.bind(proxy);
      }

     template <class Bag,class Proxy>
     void bind(const Bag &bag,Proxy proxy)
      {
       BindBagProxy(client_cfg,bag,proxy);

       bindUser(bag,proxy);

       this->bindUserFrame(bag,proxy);
      }

     // app

     template <class UserPref,class AppPref>
     Config(const UserPref &user_pref,const AppPref &app_pref) noexcept
      : client_cfg(user_pref,app_pref)
      {
       bindUser(user_pref.get(),user_pref.getSmartConfig());

       this->bindAppFrame(app_pref.get());
      }
    };

   using ConfigType = Config ;

  protected:

   const Config &cfg;

   W client;
   P place;

  private:

   void setPlace()
    {
     if( notMaximized() )
       {
        place.set(host->getPlace());
       }
    }

  public:

   template <class ... TT>
   FrameClientPlace(Desktop *desktop,const Config &cfg_,TT && ... tt)
    : DragFrame(desktop,cfg_.frame_cfg),
      cfg(cfg_),

      client(*this,cfg_.client_cfg, std::forward<TT>(tt)... )
    {
     bindClient(client);
    }

   template <class ... TT>
   FrameClientPlace(Desktop *desktop,const Config &cfg,Signal<> &update,TT && ... tt)
    : FrameClientPlace(desktop,cfg, std::forward<TT>(tt)... )
    {
     connectUpdate(update);
    }

   virtual ~FrameClientPlace()
    {
    }

   // methods

   void prepare(const P &state)
    {
     place=state;
    }

   void save(P &state)
    {
     if( isAlive() ) setPlace();

     state=place;
    }

   // base

   virtual void dying()
    {
     DragFrame::dying();

     setPlace();
    }

   // create

   Pane getPane(StrLen title) const
    {
     Point size=getMinSize(false,title,client.getMinSize());

     if( place.ok ) return place.get(size);

     return GetWindowPlace(desktop,+cfg.pos_ry,size);
    }

   void create(FrameWindow *parent)
    {
     String title=+cfg.title;

     DragFrame::create(parent,getPane(Range(title)),title);
    }
 };

} // namespace Video
} // namespace CCore

#endif

