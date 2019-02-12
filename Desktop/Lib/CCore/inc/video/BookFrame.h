/* BookFrame.h */
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

#ifndef CCore_inc_video_BookFrame_h
#define CCore_inc_video_BookFrame_h

#include <CCore/inc/video/book/BookClient.h>

namespace CCore {
namespace Video {

/* classes */

class BookPreference;

class ShowBookClient;

class BookFrame;

/* class BookPreference */

class BookPreference : public ConfigBinder<Book::ClientWindow::AppBag>
 {
  public:

   static StrLen File();

   BookPreference() noexcept;

   ~BookPreference();

   void sync() noexcept;

   void update() noexcept;
 };

/* class ShowBookClient */

class ShowBookClient : public ComboWindow
 {
  public:

   using SubWinType = Book::BookWindow ;

   struct Config
    {
     // user

     CtorRefVal<SimpleTopMenuWindow::ConfigType> menu_cfg;
     CtorRefVal<SimpleCascadeMenu::ConfigType> cascade_menu_cfg;

     // app

     RefVal<String> menu_Options = "@Options"_str ;
     RefVal<String> menu_Global  = "@Global"_str ;
     RefVal<String> menu_Book    = "@Book"_str ;

     SubWinType::ConfigType sub_win_cfg;

     template <class UserPref,class BookPref>
     Config(const UserPref &user_pref,const BookPref &book_pref) noexcept
      : sub_win_cfg(user_pref,book_pref)
      {
       bindUser(user_pref.get(),user_pref.getSmartConfig());
       bindApp(book_pref.get());
      }

     template <class Bag,class Proxy>
     void bindUser(const Bag &,Proxy proxy)
      {
       menu_cfg.bind(proxy);
       cascade_menu_cfg.bind(proxy);
      }

     template <class Bag>
     void bindApp(const Bag &bag)
      {
       menu_Options.bind(bag.menu_Options);
       menu_Global.bind(bag.menu_Global);
       menu_Book.bind(bag.menu_Book);
      }
    };

   using ConfigType = Config ;

  private:

   const Config &cfg;

   // menu

   MenuData menu_data;

   MenuData menu_opt_data;

   SimpleTopMenuWindow menu;
   SimpleCascadeMenu cascade_menu;

   // inner

   SubWinType sub_win;

  private:

   void menuOff();

   enum MenuId
    {
     MenuOptions = 2,

     MenuOptionsUserPref = 201,
     MenuOptionsBookPref = 202
    };

   void menuAction(int id,Point point);

  private:

   void menu_selected(int id,Point point);

   void cascade_menu_selected(int id,Point point);

   void cascade_menu_pressed(VKey vkey,KeyMod kmod);

   SignalConnector<ShowBookClient,int,Point> connector_menu_selected;
   SignalConnector<ShowBookClient,int,Point> connector_cascade_menu_selected;
   SignalConnector<ShowBookClient,VKey,KeyMod> connector_cascade_menu_pressed;

  public:

   ShowBookClient(SubWindowHost &host,const Config &cfg,Signal<> &update);

   virtual ~ShowBookClient();

   // methods

   Point getMinSize() const;

   void load(StrLen file_name) { sub_win.load(file_name); }

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
   Signal<Point> doBookPref;
 };

/* class BookFrame */

class BookFrame : public DragFrame
 {
  public:

   struct Config
    {
     // user

     RefVal<Ratio> pos_ry = Div(5,12) ;

     CtorRefVal<DragFrame::ConfigType> frame_cfg;

     // app

     ShowBookClient::ConfigType client_cfg;

     template <class UserPref,class BookPref>
     Config(const UserPref &user_pref,const BookPref &book_pref) noexcept
      : client_cfg(user_pref,book_pref)
      {
       bindUser(user_pref.get(),user_pref.getSmartConfig());
       bindApp(book_pref.get());
      }

     template <class Bag,class Proxy>
     void bindUser(const Bag &bag,Proxy proxy)
      {
       pos_ry.bind(bag.frame_pos_ry);

       frame_cfg.bind(proxy);
      }

     template <class Bag>
     void bindApp(const Bag &)
      {
      }
    };

   using ConfigType = Config ;

  private:

   const Config &cfg;

   ShowBookClient client;

  private:

   Pane getPane(StrLen title) const;

  public:

   BookFrame(Desktop *desktop,const Config &cfg,Signal<> &update);

   virtual ~BookFrame();

   void create(FrameWindow *parent,const String &title);

   void load(StrLen file_name) { client.load(file_name); }

   void loadLaunch(StrLen file_name);

   // signals

   Signal<Point> &doUserPref;
   Signal<Point> &doBookPref;
 };

} // namespace Video
} // namespace CCore

#endif

