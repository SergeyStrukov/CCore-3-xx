/* FrameOf.h */
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

#ifndef CCore_inc_video_FrameOf_h
#define CCore_inc_video_FrameOf_h

#include <CCore/inc/video/WindowLib.h>

namespace CCore {
namespace Video {

/* classes */

struct FramePlace;

template <class W,class P=FramePlace> class FrameOf;

/* struct FramePlace */

struct FramePlace
 {
  Pane place;
  bool ok = false ;

  void set(Pane pane)
   {
    place=pane;
    ok=true;
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

/* class FrameOf<W,P> */

template <class W,class P>
class FrameOf : public DragFrame
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
     if( notMaximized() ) place.set(host->getPlace());
    }

  public:

   template <class ... SS>
   FrameOf(Desktop *desktop,const Config &cfg_,SS && ... ss)
    : DragFrame(desktop,cfg_.frame_cfg),
      cfg(cfg_),

      client(*this,cfg.client_cfg, std::forward<SS>(ss)... )
    {
     bindClient(client);
    }

   template <class ... SS>
   FrameOf(Desktop *desktop,const Config &cfg_,Signal<> &update,SS && ... ss)
    : DragFrame(desktop,cfg_.frame_cfg,update),
      cfg(cfg_),

      client(*this,cfg.client_cfg, std::forward<SS>(ss)... )
    {
     bindClient(client);
    }

   virtual ~FrameOf()
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
