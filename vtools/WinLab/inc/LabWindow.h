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

//#include <CCore/inc/video/FavFrame.h>
#include <inc/FavFrame.h>

namespace App {

/* classes */

class LabWindow;

/* class LabWindow */

class LabWindow : public FavWindow
 {
  public:

   struct Config : public FavWindow::ConfigType
    {
     template <class UserPref,class AppPref>
     Config(const UserPref &user_pref,const AppPref &) noexcept
      {
       bind(user_pref.get(),user_pref.getSmartConfig());
      }
    };

   using ConfigType = Config ;

  public:

   LabWindow(SubWindowHost &host,const Config &cfg);

   virtual ~LabWindow();
 };

} // namespace App

#endif
