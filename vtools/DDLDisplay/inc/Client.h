/* Client.h */
//----------------------------------------------------------------------------------------
//
//  Project: DDLDisplay 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef Client_h
#define Client_h

#include <inc/Display.h>

namespace App {

/* classes */

class ClientWindow;

/* class ClientWindow */

class ClientWindow : public ComboWindow
 {
  public:

   struct Config
    {
     // user

     CtorRefVal<SimpleTopMenuWindow::ConfigType> menu_cfg;
     CtorRefVal<SimpleCascadeMenu::ConfigType> cascade_menu_cfg;
     CtorRefVal<FileFrame::ConfigType> file_cfg;

     // app

     DisplayWindow::ConfigType display_cfg;

     Config() noexcept {}

     template <class AppPref>
     Config(const UserPreference &pref,const AppPref &app_pref)
      : display_cfg(pref,app_pref)
      {
       bind(pref.get(),pref.getSmartConfig());
       bindApp(app_pref.get());
      }

     template <class Bag,class Proxy>
     void bind(const Bag &,Proxy proxy)
      {
       menu_cfg.bind(proxy);
       cascade_menu_cfg.bind(proxy);
       file_cfg.bind(proxy);
      }

     template <class Bag>
     void bindApp(const Bag &)
      {
      }
    };

   using ConfigType = Config ;

  private:

   const Config &cfg;

   enum CommandId
    {
     Cmd_File    =   1,
     Cmd_Options =   2,

     Cmd_Open    = 101,
     Cmd_Exit    = 110,

     Cmd_Pretext   = 201,
     Cmd_NoPretext = 202,
     Cmd_UserPref  = 203,
     Cmd_AppPref   = 204
    };

   MenuData menu_data;

   MenuData menu_file_data;
   MenuData menu_options_data;

   SimpleTopMenuWindow menu;
   SimpleCascadeMenu cascade_menu;

   DisplayWindow display;

   FileFrame open_file;
   FileFrame open_pretext;

  private:

   void menuOff();

  private:

   void menu_selected(int id,Point point);

   void cascade_menu_selected(int id,Point point);

   void cascade_menu_pressed(VKey vkey,KeyMod kmod);

   SignalConnector<ClientWindow,int,Point> connector_menu_selected;
   SignalConnector<ClientWindow,int,Point> connector_cascade_menu_selected;
   SignalConnector<ClientWindow,VKey,KeyMod> connector_cascade_menu_pressed;

   void open_file_destroyed();

   SignalConnector<ClientWindow> connector_open_file_destroyed;

   void open_pretext_destroyed();

   SignalConnector<ClientWindow> connector_open_pretext_destroyed;

  public:

   ClientWindow(SubWindowHost &host,const Config &cfg,Signal<> &update);

   virtual ~ClientWindow();

   // base

   virtual void open();

   // drawing

   virtual void layout();

   // user input

   virtual void react(UserAction action);

   void react_Key(VKey vkey,KeyMod kmod);

   void react_LeftClick(Point point,MouseKey mkey);

   void react_RightClick(Point point,MouseKey mkey);

   void react_other(UserAction action);

   // signals

   Signal<StrLen,bool> &opened;

   // signals

   Signal<Point> doUserPref;
   Signal<Point> doAppPref;
 };

} // namespace App

#endif

