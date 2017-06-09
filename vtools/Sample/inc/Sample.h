/* Sample.h */
//----------------------------------------------------------------------------------------
//
//  Project: Sample 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef Sample_h
#define Sample_h

#include <inc/Application.h>

namespace App {

/* classes */

class SampleWindow;

/* class SampleWindow */

class SampleWindow : public SubWindow
 {
  public:

   struct Config
    {
     Config() noexcept {}

     template <class AppPref>
     Config(const UserPreference &pref,const AppPref &app_pref) noexcept
      {
       bind(pref.get(),pref.getSmartConfig());
       bindApp(app_pref.get());
      }

     template <class Bag,class Proxy>
     void bind(const Bag &bag,Proxy proxy)
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

   SampleWindow(SubWindowHost &host,const Config &cfg);

   virtual ~SampleWindow();

   // methods

   Point getMinSize() const;
 };

} // namespace App

#endif
