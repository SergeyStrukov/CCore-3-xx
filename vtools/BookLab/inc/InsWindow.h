/* InsWindow.h */
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

#ifndef InsWindow_h
#define InsWindow_h

#include <inc/BookLab.h>

namespace App {

/* classes */

class InsWindow;

class InsFrame;

/* class InsWindow */

class InsWindow : public ComboWindow
 {
  public:

   struct Config
    {
     // user

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

   BookLab::InsData data;

  public:

   InsWindow(SubWindowHost &host,const Config &cfg);

   virtual ~InsWindow();

   // methods

   Point getMinSize() const;

   BookLab::InsData getData() const { return data; }

   // drawing

   virtual void layout();

   virtual void drawBack(DrawBuf buf,bool drag_active) const;
 };

/* class InsFrame */

class InsFrame : public DragFrame
 {
  public:

   struct Config
    {
     // user

     RefVal<Ratio> pos_ry = Div(5,12) ;

     CtorRefVal<DragFrame::ConfigType> frame_cfg;

     // app

     RefVal<DefString> title = "Select element"_def ;

     InsWindow::ConfigType client_cfg;

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
       title.bind(bag.ins_title);
      }
    };

   using ConfigType = Config ;

  private:

   const Config &cfg;

   InsWindow client;

   Pane place;
   bool has_place = false ;

  public:

   InsFrame(Desktop *desktop,const Config &cfg,Signal<> &update);

   virtual ~InsFrame();

   // methods

   BookLab::InsData getData() const { return client.getData(); }

   // base

   virtual void dying();

   // create

   Pane getPane(StrLen title) const;

   void create(FrameWindow *parent)
    {
     DefString title=+cfg.title;

     DragFrame::create(parent,getPane(title.str()),title);
    }
 };

} // namespace App

#endif
