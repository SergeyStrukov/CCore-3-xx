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

struct TempSlot;

class SlotWindow;

class TempWindow;

class TempFrame;

/* struct TempSlot */

struct TempSlot
 {
  BookLab::TempData data;
  String name;
 };

/* class SlotWindow */

class SlotWindow : public SubWindow
 {
  public:

   struct Config
    {
     // user


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
       Used(bag);
       Used(proxy);
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

  public:

   SlotWindow(SubWindowHost &host,const Config &cfg);

   virtual ~SlotWindow();

   // methods

   Point getMinSize() const;

   // drawing

   virtual void layout();

   virtual void draw(DrawBuf buf,bool drag_active) const;
 };

/* class TempWindow */

class TempWindow : public ComboWindow
 {
  public:

   struct Config
    {
     // user

     RefVal<Coord> space_dxy = 10 ;

     RefVal<VColor> back = Silver ;

     CtorRefVal<RefButtonWindow::ConfigType> btn_cfg;
     CtorRefVal<LineEditWindow::ConfigType> edit_cfg;
     CtorRefVal<YScrollWindow::ConfigType> scroll_cfg;

     // app

     RefVal<DefString> text_Copy = "Copy"_def ;
     RefVal<DefString> text_Past = "Past"_def ;
     RefVal<DefString> text_Del  =  "Del"_def ;
     RefVal<DefString> text_Name = "Name"_def ;

     SlotWindow::ConfigType slot_cfg;

     template <class AppPref>
     Config(const UserPreference &user_pref,const AppPref &app_pref) noexcept
      : slot_cfg(user_pref,app_pref)
      {
       bindUser(user_pref.get(),user_pref.getSmartConfig());
       bindApp(app_pref.get());
      }

     template <class Bag,class Proxy>
     void bindUser(const Bag &bag,Proxy proxy)
      {
       space_dxy.bind(bag.space_dxy);

       back.bind(bag.back);

       btn_cfg.bind(proxy);
       edit_cfg.bind(proxy);
       scroll_cfg.bind(proxy);
      }

     template <class Bag>
     void bindApp(const Bag &bag)
      {
       text_Copy.bind(bag.text_Copy);
       text_Past.bind(bag.text_Past);
       text_Del.bind(bag.text_Del);
       text_Name.bind(bag.text_Name);
      }
    };

   using ConfigType = Config ;

  private:

   const Config &cfg;

   // subs

   RefButtonWindow btn_copy;
   RefButtonWindow btn_past;
   RefButtonWindow btn_del;
   RefButtonWindow btn_name;

   LineEditWindow edit;

   YScrollWindow scroll;
   SlotWindow slots;

  private:

   void copy_pressed();

   void past_pressed();

   void del_pressed();

   void name_pressed();

   SignalConnector<TempWindow> connector_copy_pressed;

   SignalConnector<TempWindow> connector_past_pressed;

   SignalConnector<TempWindow> connector_del_pressed;

   SignalConnector<TempWindow> connector_name_pressed;

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


