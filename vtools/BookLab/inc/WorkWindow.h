/* WorkWindow.h */
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

#ifndef WorkWindow_h
#define WorkWindow_h

#include <inc/BookWindow.h>

namespace App {

/* classes */

class WorkWindow;

/* class WorkWindow */

class WorkWindow : public ComboWindow
 {
  public:

   struct Config
    {
     // app

     BookWindow::ConfigType book_cfg;

     template <class AppPref>
     Config(const UserPreference &user_pref,const AppPref &app_pref) noexcept
      : book_cfg(user_pref,app_pref)
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

   BookWindow book;

  public:

   WorkWindow(SubWindowHost &host,const Config &cfg,Signal<> &update);

   virtual ~WorkWindow();

   // methods

   Point getMinSize() const;

   bool isModified() const;

   void blank();

   void load(StrLen file_name);

   bool save();

   void save(StrLen file_name);

   // drawing

   virtual void layout();
 };

} // namespace App

#endif

