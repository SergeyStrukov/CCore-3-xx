/* FieldEditor.h */
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

#ifndef FieldEditor_h
#define FieldEditor_h

#include <inc/BookLab.h>

namespace App {

/* classes */

class FieldWindow;

class FieldFrame;

/* class FieldWindow */

class FieldWindow : public ComboWindow
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

       back.bind(bag.back);

       space_dxy.bind(bag.space_dxy);
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

   BookLab::Book &book;
   BookLab::PadType pad;

  public:

   FieldWindow(SubWindowHost &host,const Config &cfg,BookLab::Book &book);

   virtual ~FieldWindow();

   // methods

   Point getMinSize() const;

   void setField(BookLab::PadType pad);

   // base

   virtual void open();

   // drawing

   virtual void layout();

   virtual void drawBack(DrawBuf buf,bool drag_active) const;

   // signals

   Signal<> modified;
 };

/* class FieldFrame */

class FieldFrame : public DragFrame
 {
  public:

   struct Config
    {
     // user

     RefVal<Ratio> pos_ry = Div(5,12) ;

     CtorRefVal<DragFrame::ConfigType> frame_cfg;

     // app

     RefVal<DefString> title = "Edit field"_def ;

     FieldWindow::ConfigType client_cfg;

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
       title.bind(bag.field_title);
      }
    };

   using ConfigType = Config ;

  private:

   const Config &cfg;

   FieldWindow client;

   Pane place;
   bool has_place = false ;

  public:

   FieldFrame(Desktop *desktop,const Config &cfg,BookLab::Book &book,Signal<> &update);

   virtual ~FieldFrame();

   // methods

   void setField(BookLab::PadType pad) { client.setField(pad); }

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

   Signal<> &modified;
 };

} // namespace App

#endif

