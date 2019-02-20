/* LabWindow.h */
//----------------------------------------------------------------------------------------
//
//  Project: WinLab 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef LabWindow_h
#define LabWindow_h

#include <inc/App.h>

namespace App {

/* classes */

class LabWindow;

/* class LabWindow */

class LabWindow : public SubWindow
 {
  public:

   struct Config
    {
     Config() noexcept {}

     template <class UserPref,class AppPref>
     Config(const UserPref &user_pref,const AppPref &app_pref) noexcept
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

   LabWindow(SubWindowHost &host,const Config &cfg);

   virtual ~LabWindow();

   // methods

   Point getMinSize() const;

   // drawing

   virtual void layout();
 };

} // namespace App

#endif
