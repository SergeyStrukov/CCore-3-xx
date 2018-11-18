/* TempWindow.h */
//----------------------------------------------------------------------------------------
//
//  Project: BookLab 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef TempWindow_h
#define TempWindow_h

#include <inc/BookLab.h>

namespace App {

/* classes */

class TempWindow;

class TempFrame;

/* class TempWindow */

class TempWindow : public ComboWindow
 {
  public:

   struct Config
    {
     // user

     RefVal<Coord> space_dxy = 10 ;

     RefVal<VColor> back = Silver ;

     // app

     template <class AppPref>
     Config(const UserPreference &user_pref,const AppPref &app_pref) noexcept
      {
       bindUser(user_pref.get(),user_pref.getSmartConfig());
       bindApp(app_pref.get());
      }

     template <class Bag,class Proxy>
     void bindUser(const Bag &bag,Proxy proxy)
      {
       Used(proxy);

       space_dxy.bind(bag.space_dxy);

       back.bind(bag.back);
      }

     template <class Bag>
     void bindApp(const Bag &bag)
      {
       Used(bag);
      }
    };

   using ConfigType = Config ;

  private:

   const Config &cfg;

   // subs

  public:

   TempWindow(SubWindowHost &host,const Config &cfg);

   virtual ~TempWindow();

   // methods

   Point getMinSize() const;

   bool copy(BookLab::Ref cursor);

   bool copy(ulen slot,BookLab::Ref cursor);

   bool past(ulen slot,BookLab::Ref cursor);

   // drawing

   virtual void layout();

   virtual void drawBack(DrawBuf buf,bool drag_active) const;

   // user input

   virtual void react(UserAction action);

   // signals

   Signal<ulen> askCopy;
   Signal<ulen> askPast;
 };

/* class TempFrame */

class TempFrame : public DragFrame
 {
  public:

   struct Config
    {
     // user

     RefVal<Ratio> pos_ry = Div(5,12) ;

     CtorRefVal<DragFrame::ConfigType> frame_cfg;

     // app

     RefVal<DefString> title = "Temp pad"_def ;

     TempWindow::ConfigType client_cfg;

     template <class AppPref>
     Config(const UserPreference &user_pref,const AppPref &app_pref) noexcept
      : client_cfg(user_pref,app_pref)
      {
       bindUser(user_pref.get(),user_pref.getSmartConfig());
       bindApp(app_pref.get());
      }

     template <class Bag,class Proxy>
     void bindUser(const Bag &bag,Proxy proxy)
      {
       pos_ry.bind(bag.frame_pos_ry);

       frame_cfg.bind(proxy);
      }

     template <class Bag>
     void bindApp(const Bag &bag)
      {
       title.bind(bag.temp_title);
      }
    };

   using ConfigType = Config ;

  private:

   const Config &cfg;

   TempWindow client;

   Pane place;
   bool has_place = false ;

  public:

   TempFrame(Desktop *desktop,const Config &cfg,Signal<> &update);

   virtual ~TempFrame();

   // methods

   bool copy(BookLab::Ref cursor) { return client.copy(cursor); }

   bool copy(ulen slot,BookLab::Ref cursor) { return client.copy(slot,cursor); }

   bool past(ulen slot,BookLab::Ref cursor) { return client.past(slot,cursor); }

   // base

   virtual void dying();

   // create

   Pane getPane(StrLen title) const;

   void create(FrameWindow *parent)
    {
     DefString title=+cfg.title;

     DragFrame::create(parent,getPane(title.str()),title);
    }

   // signals

   Signal<ulen> &askCopy;
   Signal<ulen> &askPast;
 };

} // namespace App

#endif


