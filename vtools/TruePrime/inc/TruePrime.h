/* TruePrime.h */
//----------------------------------------------------------------------------------------
//
//  Project: TruePrime 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef TruePrime_h
#define TruePrime_h

#include <inc/App.h>

namespace App {

/* classes */

class TruePrimeWindow;

/* class TruePrimeWindow */

class TruePrimeWindow : public ComboWindow
 {
  public:

   struct Config
    {
     // user

     RefVal<Coord> space_dxy = 10 ;

     RefVal<VColor> back = Silver ;

     CtorRefVal<RefButtonWindow::ConfigType> btn_cfg;

     // app


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
       space_dxy.bind(bag.space_dxy);
       back.bind(bag.back);

       btn_cfg.bind(proxy);
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

  private:


  public:

   TruePrimeWindow(SubWindowHost &host,const Config &cfg);

   virtual ~TruePrimeWindow();

   // methods

   Point getMinSize() const;

   // drawing

   virtual void layout();

   virtual void drawBack(DrawBuf buf,DrawParam &draw_param) const;
 };

} // namespace App

#endif
