/* BookWindow.h */
//----------------------------------------------------------------------------------------
//
//  Project: BookLab 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef BookWindow_h
#define BookWindow_h

#include <inc/Book.h>

namespace App {

/* classes */

class InnerBookWindow;

class DisplayBookWindow;

class BookWindow;

/* class InnerBookWindow */

class InnerBookWindow : public SubWindow
 {
  public:

   struct Config
    {
     // user

     RefVal<MCoord> width = Fraction(6,2) ;

     RefVal<VColor> line = Gray ;
     RefVal<VColor> gray = Gray ;
     RefVal<VColor> snow = Snow ;

     // app

     VColor back = Silver ;
     VColor fore = Black ;

     Font font;
     Font codefont;

     Config() noexcept {}

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

   Book::TypeDef::Page *page = 0 ;
   VColor back = Book::NoColor ;
   VColor fore = Book::NoColor ;

   bool focus = false ;

  public:

   InnerBookWindow(SubWindowHost &host,const Config &cfg);

   virtual ~InnerBookWindow();

   // methods

   Point getMinSize(unsigned flags,Point cap=Point::Max()) const;

   void setPage(Book::TypeDef::Page *page,VColor back,VColor fore);

   // special methods

   bool shortDX() const;

   bool shortDY() const;

   template <class W>
   void setScrollXRange(W &window) const;

   template <class W>
   void setScrollYRange(W &window) const;

   void connect(Signal<ulen> &scroll_x,Signal<ulen> &scroll_y);

   // drawing

   virtual void layout(unsigned flags);

   virtual void draw(DrawBuf buf,bool drag_active) const;

   // base

   virtual void open();

   // keyboard

   virtual void gainFocus();

   virtual void looseFocus();

   // mouse

   virtual MouseShape getMouseShape(Point point,KeyMod kmod) const;

   // signals

   Signal<ulen> scroll_x;
   Signal<ulen> scroll_y;

   Signal<Book::TypeDef::Link> link;
   Signal<Book::TypeDef::Page *> hint;
 };

/* class BookWindow */

class BookWindow : public SubWindow
 {
  public:

   struct Config
    {
     Config() noexcept {}

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

   BookWindow(SubWindowHost &host,const Config &cfg);

   virtual ~BookWindow();

   // methods

   Point getMinSize(unsigned flags) const;

   void blank();

   void load(StrLen file_name);

   // drawing

   virtual void layout(unsigned flags);
 };

} // namespace App

#endif

