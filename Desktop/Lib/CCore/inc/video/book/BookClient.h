/* BookClient.h */
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

#ifndef CCore_inc_video_book_Client_h
#define CCore_inc_video_book_Client_h

#include <CCore/inc/video/book/BookWindow.h>

#include <CCore/inc/video/FileFrame.h>

namespace CCore {
namespace Video {
namespace Book {

/* classes */

class ClientWindow;

/* class ClientWindow */

class ClientWindow : public ComboWindow
 {
  public:

   using SubWinType = BookWindow ;

   struct ClientBag
    {
     // common

     String title = "Book"_str ;

     // menu

     String menu_File    = "@File"_str ;
     String menu_Options = "@Options"_str ;
     String menu_New     = "@New"_str ;
     String menu_Open    = "@Open"_str ;
     String menu_Exit    = "E@xit"_str ;
     String menu_Global  = "@Global"_str ;
     String menu_App     = "@Application"_str ;

     // constructors

     ClientBag() noexcept {}

     // methods

     template <class Ptr,class Func>
     static void Members(Ptr ptr,Func func)
      {
       func("title"_c,ptr->title);
       func("menu_File"_c,ptr->menu_File);
       func("menu_Options"_c,ptr->menu_Options);
       func("menu_New"_c,ptr->menu_New);
       func("menu_Open"_c,ptr->menu_Open);
       func("menu_Exit"_c,ptr->menu_Exit);
       func("menu_Global"_c,ptr->menu_Global);
       func("menu_App"_c,ptr->menu_App);
      }

     void bindItems(ConfigItemBind &binder);

     void findFonts() {}
    };

   using AppBag = CombineBags<BookWindow::AppBag,ClientBag> ;

   struct Config
    {
     // user

     RefVal<String> text_LoadFile = "Select a file to load from"_str ;
     RefVal<String> text_SaveFile = "Select a file to save to"_str ;

     RefVal<String> text_Alert   = "Alert"_str ;
     RefVal<String> text_AskSave = "Save modifications?"_str ;

     RefVal<String> text_Yes    = "Yes"_str ;
     RefVal<String> text_No     = "No"_str ;
     RefVal<String> text_Cancel = "Cancel"_str ;

     CtorRefVal<FileFrame::ConfigType> file_cfg;
     CtorRefVal<SimpleTopMenuWindow::ConfigType> menu_cfg;
     CtorRefVal<SimpleCascadeMenu::ConfigType> cascade_menu_cfg;

     // app

     RefVal<String> menu_File    = "@File"_str ;
     RefVal<String> menu_Options = "@Options"_str ;
     RefVal<String> menu_New     = "@New"_str ;
     RefVal<String> menu_Open    = "@Open"_str ;
     RefVal<String> menu_Exit    = "E@xit"_str ;
     RefVal<String> menu_Global  = "@Global"_str ;
     RefVal<String> menu_App     = "@Application"_str ;

     SubWinType::ConfigType sub_win_cfg;

     template <class UserPref,class AppPref>
     Config(const UserPref &user_pref,const AppPref &app_pref) noexcept
      : sub_win_cfg(user_pref,app_pref)
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
       menu_cfg.bind(proxy);
       cascade_menu_cfg.bind(proxy);
      }

     template <class Bag>
     void bindApp(const Bag &bag)
      {
       menu_File.bind(bag.menu_File);
       menu_Options.bind(bag.menu_Options);
       menu_New.bind(bag.menu_New);
       menu_Open.bind(bag.menu_Open);
       menu_Exit.bind(bag.menu_Exit);
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
   MenuData menu_opt_data;

   SimpleTopMenuWindow menu;
   SimpleCascadeMenu cascade_menu;

   // inner

   SubWinType sub_win;

   // frames

   FileFrame file_frame;

   // continuation

   enum Continue
    {
     ContinueNone = 0,

     ContinueOpen
    };

   Continue cont = ContinueNone ;
   Point file_point;

   Point action_base = Point(10,10) ;

  private:

   void menuOff();

   void fileOff();

   void startOpen(Point point);

   enum MenuId
    {
     MenuFile = 1,

     MenuFileNew    = 101,
     MenuFileOpen   = 102,
     MenuFileExit   = 110,

     MenuOptions = 2,

     MenuOptionsUserPref = 201,
     MenuOptionsAppPref  = 202
    };

   void menuAction(int id,Point point);

   void menuAction(int id);

  private:

   void menu_selected(int id,Point point);

   void cascade_menu_selected(int id,Point point);

   void cascade_menu_pressed(VKey vkey,KeyMod kmod);

   void file_destroyed();

   SignalConnector<ClientWindow,int,Point> connector_menu_selected;
   SignalConnector<ClientWindow,int,Point> connector_cascade_menu_selected;
   SignalConnector<ClientWindow,VKey,KeyMod> connector_cascade_menu_pressed;
   SignalConnector<ClientWindow> connector_file_destroyed;

  public:

   ClientWindow(SubWindowHost &host,const Config &cfg,OptFileName opt,Signal<> &update);

   virtual ~ClientWindow();

   // methods

   Point getMinSize() const;

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

   Signal<Point> doUserPref;
   Signal<Point> doAppPref;
 };

} // namespace Book
} // namespace Video
} // namespace CCore

#endif

