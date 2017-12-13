/* Client.h */
//----------------------------------------------------------------------------------------
//
//  Project: Aspect 1.01
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef Client_h
#define Client_h

#include <inc/Aspect.h>
#include <inc/AppState.h>

namespace App {

/* classes */

struct RecentList;

class ClientWindow;

/* struct RecentList */

struct RecentList : MenuData
 {
  int first_id;
  int max_count;

  void setInd(ulen ind);

  RecentList(int first_id,int max_count);

  ~RecentList();

  void erase() { list.erase(); }

  void add(String file_name);

  void del(int id);

  StrLen get(int id) const;

  void save(DynArray<String> &ret) const;
 };

/* class ClientWindow */

class ClientWindow : public ComboWindow , public AliveControl
 {
  public:

   struct Config
    {
     // user

     RefVal<DefString> text_LoadFile = "Select a file to load from"_def ;
     RefVal<DefString> text_SaveFile = "Select a file to save to"_def ;

     RefVal<DefString> text_Alert   = "Alert"_def ;
     RefVal<DefString> text_AskSave = "Save modifications?"_def ;

     RefVal<DefString> text_Yes    = "Yes"_def ;
     RefVal<DefString> text_No     = "No"_def ;
     RefVal<DefString> text_Cancel = "Cancel"_def ;

     CtorRefVal<FileFrame::ConfigType> file_cfg;
     CtorRefVal<DirFrame::ConfigType> dir_cfg;
     CtorRefVal<MessageFrame::AlertConfigType> msg_cfg;
     CtorRefVal<SimpleTopMenuWindow::ConfigType> menu_cfg;
     CtorRefVal<SimpleCascadeMenu::ConfigType> cascade_menu_cfg;

     // app

     RefVal<DefString> text_SelectPath = "Select a project path"_def ;

     RefVal<DefString> menu_File    = "@File"_def ;
     RefVal<DefString> menu_Actions = "@Actions"_def ;
     RefVal<DefString> menu_Options = "@Options"_def ;
     RefVal<DefString> menu_Recent  = "@Recent"_def ;

     RefVal<DefString> menu_New     = "@New ..."_def ;
     RefVal<DefString> menu_Open    = "@Open ..."_def ;
     RefVal<DefString> menu_Save    = "@Save"_def ;
     RefVal<DefString> menu_SaveAs  = "Save @as ..."_def ;
     RefVal<DefString> menu_Exit    = "E@xit"_def ;
     RefVal<DefString> menu_Collect = "@Collect"_def ;
     RefVal<DefString> menu_Global  = "@Global ..."_def ;
     RefVal<DefString> menu_App     = "@Application ..."_def ;

     AspectWindow::ConfigType aspect_cfg;

     Config() noexcept {}

     template <class AppPref>
     Config(const UserPreference &user_pref,const AppPref &app_pref) noexcept
      : aspect_cfg(user_pref,app_pref)
      {
       bindUser(user_pref.get(),user_pref.getSmartConfig());
       bindApp(app_pref.get());
      }

     template <class Bag,class Proxy>
     void bindUser(const Bag &bag,Proxy proxy)
      {
       text_LoadFile.bind(bag.text_LoadFile);
       text_SaveFile.bind(bag.text_SaveFile);

       text_Alert.bind(bag.text_Alert);
       text_AskSave.bind(bag.text_AskSave);

       text_Yes.bind(bag.text_Yes);
       text_No.bind(bag.text_No);
       text_Cancel.bind(bag.text_Cancel);

       file_cfg.bind(proxy);
       dir_cfg.bind(proxy);
       msg_cfg.bind(proxy);
       menu_cfg.bind(proxy);
       cascade_menu_cfg.bind(proxy);
      }

     template <class Bag>
     void bindApp(const Bag &bag)
      {
       text_SelectPath.bind(bag.text_SelectPath);

       menu_File.bind(bag.menu_File);
       menu_Actions.bind(bag.menu_Actions);
       menu_Options.bind(bag.menu_Options);
       menu_Recent.bind(bag.menu_Recent);
       menu_New.bind(bag.menu_New);
       menu_Open.bind(bag.menu_Open);
       menu_Save.bind(bag.menu_Save);
       menu_SaveAs.bind(bag.menu_SaveAs);
       menu_Exit.bind(bag.menu_Exit);
       menu_Collect.bind(bag.menu_Collect);
       menu_Global.bind(bag.menu_Global);
       menu_App.bind(bag.menu_App);
      }
    };

   using ConfigType = Config ;

  private:

   const Config &cfg;

   // menu

   MenuData menu_data;

   MenuData menu_file_data;
   MenuData menu_act_data;
   MenuData menu_opt_data;
   RecentList menu_recent_data;

   SimpleTopMenuWindow menu;
   SimpleCascadeMenu cascade_menu;

   // aspect

   AspectWindow aspect;

   // frames

   FileFrame file_frame;
   DirFrame dir_frame;
   MessageFrame msg_frame;

   // continuation

   enum Continue
    {
     ContinueNone = 0,

     ContinueNew,
     ContinueNew2,
     ContinueOpen,
     ContinueStartOpen,
     ContinueSave,
     ContinueSaveAs,
     ContinueExit,
     ContinueOpenRecent
    };

   Continue cont = ContinueNone ;
   Point file_point;
   int recent_id = 0 ;

   Point action_base = Point(10,10) ;

  private:

   void menuOff();

   void fileOff();

   void dirOff();

   void msgOff();

   void askSave(Continue cont);

   void startNew(Point point);

   void startOpen(Point point);

   void startSave(Point point);

   void openRecent(int id);

   enum MenuId
    {
     MenuFile = 1,

      MenuFileNew    = 101,
      MenuFileOpen   = 102,
      MenuFileSave   = 103,
      MenuFileSaveAs = 104,
      MenuFileExit   = 110,

     MenuActions = 2,

      MenuCollect = 201,

     MenuOptions = 3,

      MenuOptionsUserPref = 301,
      MenuOptionsAppPref  = 302,

     MenuRecent = 4,

      MenuRecentFirst = 401,
      MenuRecentLim   = 421
    };

   void menuAction(int id,Point point);

   void menuAction(int id);

  private:

   void menu_selected(int id,Point point);

   void cascade_menu_selected(int id,Point point);

   void cascade_menu_deleted(int id);

   void cascade_menu_pressed(VKey vkey,KeyMod kmod);

   SignalConnector<ClientWindow,int,Point> connector_menu_selected;
   SignalConnector<ClientWindow,int,Point> connector_cascade_menu_selected;
   SignalConnector<ClientWindow,int> connector_cascade_menu_deleted;
   SignalConnector<ClientWindow,VKey,KeyMod> connector_cascade_menu_pressed;

   void file_destroyed();

   void dir_destroyed();

   void msg_destroyed();

   SignalConnector<ClientWindow> connector_file_destroyed;
   SignalConnector<ClientWindow> connector_dir_destroyed;
   SignalConnector<ClientWindow> connector_msg_destroyed;

  public:

   ClientWindow(SubWindowHost &host,const Config &cfg,const char *open_file_name);

   virtual ~ClientWindow();

   // methods

   void update(bool new_data) { aspect.update(new_data); }

   void prepare(const AppState &app_state);

   // base

   virtual void open();

   // drawing

   virtual void layout(unsigned flags);

   // user input

   virtual void react(UserAction action);

   void react_Key(VKey vkey,KeyMod kmod);

   void react_LeftClick(Point point,MouseKey mkey);

   void react_RightClick(Point point,MouseKey mkey);

   void react_other(UserAction action);

   // AliveControl

   virtual void dying();

   virtual bool askDestroy();

   // signals

   Signal<Point> doUserPref;
   Signal<Point> doAppPref;
 };

} // namespace App

#endif

