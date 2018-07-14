/* DrawBookLab.h */
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

#ifndef DrawBookLab_h
#define DrawBookLab_h

#include <inc/BookLab.h>

namespace App {
namespace BookLab {

/* classes */

struct Config;

/* struct Config */

struct Config
 {
  // user

  RefVal<Fraction> width = Fraction(6,2) ;

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
    width.bind(bag.width);

    Used(proxy);
   }

  template <class Bag>
  void bindApp(const Bag &bag)
   {
    Used(bag);
   }
 };

} // namespace BookLab
} // namespace App

#endif
