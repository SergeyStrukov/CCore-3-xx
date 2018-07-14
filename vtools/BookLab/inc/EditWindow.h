/* EditWindow.h */
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

#ifndef EditWindow_h
#define EditWindow_h

#include <inc/DrawBookLab.h>

namespace App {

/* classes */

class InnerBookLabWindow;

class BookLabWindow;

class EditWindow;

/* class InnerBookLabWindow */

class InnerBookLabWindow : public SubWindow
 {
  public:

   struct Config : BookLab::Config
    {
     // user

     RefVal<VColor> focus = OrangeRed ;

     // app

     RefVal<Coord> border_dxy = 5 ;

     RefVal<VColor> back = Silver ;

     template <class AppPref>
     Config(const UserPreference &user_pref,const AppPref &app_pref) noexcept
      : BookLab::Config(user_pref,app_pref)
      {
       bindUser(user_pref.get(),user_pref.getSmartConfig());
       bindApp(app_pref.get());
      }

     template <class Bag,class Proxy>
     void bindUser(const Bag &bag,Proxy proxy)
      {
       focus.bind(bag.focus);
      }

     template <class Bag>
     void bindApp(const Bag &bag)
      {
       border_dxy.bind(bag.border_dxy);
       back.bind(bag.back);
      }
    };

   using ConfigType = Config ;

  private:

   const Config &cfg;

   BookLab::Book book;

   bool focus = false ;

   // scroll

   ScrollPos sx;
   ScrollPos sy;

   // layout

   mutable Point size; // without border

   mutable bool ok = false ;

  private:

   void cache() const;

  private:

   void posX(ulen pos);

   void posY(ulen pos);

   SignalConnector<InnerBookLabWindow,ulen> connector_posX;
   SignalConnector<InnerBookLabWindow,ulen> connector_posY;

   void updated(unsigned flags);

   SignalConnector<InnerBookLabWindow,unsigned> connector_updated;

  public:

   InnerBookLabWindow(SubWindowHost &host,const Config &cfg);

   virtual ~InnerBookLabWindow();

   // methods

   Point getMinSize(Point cap=Point::Max()) const;

   void blank();

   ErrorText load(StrLen file_name,PtrLen<char> ebuf);

   ErrorText save(StrLen file_name,PtrLen<char> ebuf) const;

   // special methods

   bool shortDX() const { return sx.tooShort(); }

   bool shortDY() const { return sy.tooShort();  }

   ScrollPos getScrollXRange() const { return sx; }

   ScrollPos getScrollYRange() const { return sy; }

   void connect(Signal<ulen> &scroll_x,Signal<ulen> &scroll_y)
    {
     connector_posX.connect(scroll_x);
     connector_posY.connect(scroll_y);
    }

   // drawing

   virtual void layout();

   virtual void draw(DrawBuf buf,bool drag_active) const;

   // base

   virtual void open();

   // keyboard

   virtual void gainFocus();

   virtual void looseFocus();

   // mouse

   virtual MouseShape getMouseShape(Point point,KeyMod kmod) const;

   // user input

   virtual void react(UserAction action);

   void react_Key(VKey vkey,KeyMod kmod,unsigned repeat);

   void react_LeftClick(Point point,MouseKey mkey);

   void react_RightClick(Point point,MouseKey mkey);

   void react_Wheel(Point point,MouseKey mkey,Coord delta);

   // signals

   Signal<ulen> scroll_x;
   Signal<ulen> scroll_y;

   Signal<> changed;
   Signal<> modified;
 };

/* class BookLabWindow */

class BookLabWindow
 {
 };

/* class EditWindow */

class EditWindow : public ComboWindow
 {
  public:

   struct Config
    {
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

   EditWindow(SubWindowHost &host,const Config &cfg,Signal<> &update);

   virtual ~EditWindow();

   // methods

   Point getMinSize() const;

   bool isModified() const;

   void blank();

   void load(StrLen file_name);

   bool save();

   void save(StrLen file_name);

   // drawing

   virtual void layout();

   virtual void drawBack(DrawBuf buf,bool drag_active) const;
 };

} // namespace App

#endif

