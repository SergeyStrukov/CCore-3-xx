/* FrameOf.h */
//----------------------------------------------------------------------------------------
//
//  Project: Book 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef FrameOf_h
#define FrameOf_h

#include <inc/App.h>

namespace App {

/* classes */

struct FramePlace;

template <class W>
class FrameOf;

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
 };

/* class FrameOf<W> */

template <class W>
class FrameOf : public DragFrame
 {
  public:

   struct Config : W::FrameConfigApp
    {
     // user

     RefVal<Ratio> pos_ry = Div(5,12) ;

     CtorRefVal<DragFrame::ConfigType> frame_cfg;

     // app

     typename W::ConfigType client_cfg;

     template <class AppPref>
     Config(const UserPreference &user_pref,const AppPref &app_pref) noexcept
      : client_cfg(user_pref,app_pref)
      {
       bindUser(user_pref.get(),user_pref.getSmartConfig());
       this->bindApp(app_pref.get());
      }

     template <class Bag,class Proxy>
     void bindUser(const Bag &bag,Proxy proxy)
      {
       pos_ry.bind(bag.frame_pos_ry);

       frame_cfg.bind(proxy);
      }
    };

   using ConfigType = Config ;

  protected:

   const Config &cfg;

   W client;

   FramePlace place;

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

   // base

   virtual void dying()
    {
     DragFrame::dying();

     place.set(host->getPlace());
    }

   // create

   Pane getPane(StrLen title) const
    {
     if( place.ok ) return place.place;

     Point size=getMinSize(false,title,client.getMinSize());

     return GetWindowPlace(desktop,+cfg.pos_ry,size);
    }

   void create(FrameWindow *parent)
    {
     DefString title=+cfg.title;

     DragFrame::create(parent,getPane(title.str()),title);
    }
 };

} // namespace App

#endif
