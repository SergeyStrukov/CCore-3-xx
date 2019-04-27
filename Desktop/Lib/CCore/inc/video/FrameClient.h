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

/* concept CapSizeType<W> */

template <class W> // ref extended
concept bool CapSizeType = requires (Meta::ToConst<W> &cobj,Point cap)
 {
  { cobj.getMinSize(cap) } -> Point ;
 } ;

/* concept Has_FrameConfig<W> */

template <class W>
concept bool Has_FrameConfig = requires()
 {
  typename W::FrameConfig;
 } ;

/* classes */

struct FramePlace;

template <class W> struct FrameConfig;

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

  bool fit(Point size,Pane outer) const
   {
    return ok && place.getSize()>=size && outer.contains(place) ;
   }

  Pane get() const { return place; }

  void print(PrinterType &out) const
   {
    if( ok )
      Printf(out,"{ #; , #; , #; , #; , True }",place.x,place.y,place.dx,place.dy);
    else
      Putobj(out,"{ .ok = False }"_c);
   }
 };

/* struct FrameConfig<W> */

template <class W> requires ( !Has_FrameConfig<W> )
struct FrameConfig<W>
 {
  RefVal<Ratio> pos_ry = Div(5,12) ;

  CtorRefVal<DragFrame::ConfigType> frame_cfg;

  typename W::ConfigType client_cfg;

  // lib

  FrameConfig() noexcept {}

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
   }

  // app

  template <class UserPref,class AppPref>
  FrameConfig(const UserPref &user_pref,const AppPref &app_pref) noexcept
   : client_cfg(user_pref,app_pref)
   {
    bindUser(user_pref.get(),user_pref.getSmartConfig());
   }
 };

template <class W> requires ( Has_FrameConfig<W> )
struct FrameConfig<W> : W::FrameConfig
 {
  RefVal<Ratio> pos_ry = Div(5,12) ;

  CtorRefVal<DragFrame::ConfigType> frame_cfg;

  typename W::ConfigType client_cfg;

  // lib

  FrameConfig() noexcept {}

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
  FrameConfig(const UserPref &user_pref,const AppPref &app_pref) noexcept
   : client_cfg(user_pref,app_pref)
   {
    bindUser(user_pref.get(),user_pref.getSmartConfig());

    this->bindAppFrame(app_pref.get());
   }
 };

/* class FrameClient<W> */

template <class W>
class FrameClient : public DragFrame
 {
  public:

   using ConfigType = FrameConfig<W> ;

  protected:

   const ConfigType &cfg;

   W client;

  public:

   template <class ... TT>
   FrameClient(Desktop *desktop,const ConfigType &cfg_,TT && ... tt)
    : DragFrame(desktop,cfg_.frame_cfg),
      cfg(cfg_),
      client(*this,cfg_.client_cfg, std::forward<TT>(tt)... )
    {
     bindClient(client);
    }

   template <class ... TT>
   FrameClient(Desktop *desktop,const ConfigType &cfg,Signal<> &update,TT && ... tt)
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

   Pane getMainPane(StrLen title) const requires ( !CapSizeType<W> )
    {
     Point size=getMinSize(true,title,client.getMinSize());

     return GetWindowPlace(getDesktop(),+cfg.pos_ry,size);
    }

   Pane getPane(StrLen title,Point base) const requires ( CapSizeType<W> )
    {
     Point screen_size=getScreenSize();
     Point cap=getCap(Div(9,10)*screen_size);
     Point size=getMinSize(false,title,client.getMinSize(cap));

     return FitToScreen(base,size,screen_size);
    }

   Pane getPane(StrLen title) const requires ( CapSizeType<W> )
    {
     Point cap=getCap(Div(9,10)*getScreenSize());
     Point size=getMinSize(false,title,client.getMinSize(cap));

     return GetWindowPlace(getDesktop(),+cfg.pos_ry,size);
    }

   Pane getMainPane(StrLen title) const requires ( CapSizeType<W> )
    {
     Point cap=getCap(Div(9,10)*getScreenSize());
     Point size=getMinSize(true,title,client.getMinSize(cap));

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

   void createMain(const String &title)
    {
     DragFrame::createMain(CmdDisplay_Normal,getMainPane(Range(title)),title);
    }

   void createMain(CmdDisplay cmd_display,Pane pane,const String &title)
    {
     DragFrame::createMain(cmd_display,pane,title);
    }
 };

/* class FrameClientPlace<W,P> */

template <class W,class P>
class FrameClientPlace : public DragFrame
 {
  public:

   using ConfigType = FrameConfig<W> ;

  protected:

   const ConfigType &cfg;

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
   FrameClientPlace(Desktop *desktop,const ConfigType &cfg_,TT && ... tt)
    : DragFrame(desktop,cfg_.frame_cfg),
      cfg(cfg_),

      client(*this,cfg_.client_cfg, std::forward<TT>(tt)... )
    {
     bindClient(client);
    }

   template <class ... TT>
   FrameClientPlace(Desktop *desktop,const ConfigType &cfg,Signal<> &update,TT && ... tt)
    : FrameClientPlace(desktop,cfg, std::forward<TT>(tt)... )
    {
     connectUpdate(update);
    }

   virtual ~FrameClientPlace()
    {
    }

   // methods

   void preparePlace(const P &state)
    {
     place=state;
    }

   void savePlace(P &state)
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

   Pane getPane(StrLen title) const requires ( !CapSizeType<W> )
    {
     Point size=getMinSize(false,title,client.getMinSize());

     Pane outer=getMaxPane();

     if( place.fit(size,outer) ) return place.get();

     return GetWindowPlace(outer,+cfg.pos_ry,size);
    }

   Pane getPane(StrLen title) const requires ( CapSizeType<W> )
    {
     Point cap=getCap(Div(9,10)*getScreenSize());
     Point size=getMinSize(false,title,client.getMinSize(cap));

     Pane outer=getMaxPane();

     if( place.fit(size,outer) ) return place.get();

     return GetWindowPlace(outer,+cfg.pos_ry,size);
    }

   Pane getPane(StrLen title,Point base) const requires ( !CapSizeType<W> )
    {
     Point size=getMinSize(false,title,client.getMinSize());

     Pane outer=getMaxPane();

     if( place.fit(size,outer) ) return place.get();

     return FitToScreen(base,size,getScreenSize());
    }

   Pane getPane(StrLen title,Point base) const requires ( CapSizeType<W> )
    {
     Point screen_size=getScreenSize();
     Point cap=getCap(Div(9,10)*screen_size);
     Point size=getMinSize(false,title,client.getMinSize(cap));

     Pane outer=getMaxPane();

     if( place.fit(size,outer) ) return place.get();

     return FitToScreen(base,size,screen_size);
    }

   void create()
    {
     String title=+cfg.title;

     DragFrame::create(getPane(Range(title)),title);
    }

   void create(FrameWindow *parent)
    {
     String title=+cfg.title;

     DragFrame::create(parent,getPane(Range(title)),title);
    }

   void create(const String &title)
    {
     DragFrame::create(getPane(Range(title)),title);
    }

   void create(FrameWindow *parent,const String &title)
    {
     DragFrame::create(parent,getPane(Range(title)),title);
    }

   void create(Point base,const String &title)
    {
     DragFrame::create(getPane(Range(title),base),title);
    }

   void create(FrameWindow *parent,Point base,const String &title)
    {
     DragFrame::create(parent,getPane(Range(title),base),title);
    }
 };

} // namespace Video
} // namespace CCore

#endif

