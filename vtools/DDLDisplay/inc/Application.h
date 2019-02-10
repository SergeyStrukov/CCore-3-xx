/* Application.h */
//----------------------------------------------------------------------------------------
//
//  Project: DDLDisplay 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef Application_h
#define Application_h

#include <CCore/inc/video/AppMain.h>

#include <inc/Client.h>

namespace App {

/* classes */

struct AppPreferenceBag;

struct AppProp;

/* struct AppPreferenceBag */

struct AppPreferenceBag : ConfigItemHost
 {
  String title = "DDLDisplay"_str ;

  Coord space_dxy = 3 ;

  Point space = Point(6,4) ;

  VColor text   =     Black ;
  VColor ptr    =      Blue ;
  VColor select = OrangeRed ;

  FontCouple title_font;
  FontCouple font;

  // constructors

  AppPreferenceBag() noexcept {}

  // methods

  template <class Ptr,class Func>
  static void Members(Ptr ptr,Func func);

  virtual void bind(ConfigItemBind &binder);
 };

template <class Ptr,class Func>
void AppPreferenceBag::Members(Ptr ptr,Func func)
 {
  func("title"_c,ptr->title);
  func("space_dxy"_c,ptr->space_dxy);
  func("space"_c,ptr->space);
  func("vc_text"_c,ptr->text);
  func("vc_ptr"_c,ptr->ptr);
  func("select"_c,ptr->select);
  func("title_font"_c,ptr->title_font);
  func("font"_c,ptr->font);
 }

/* struct AppProp */

struct AppProp
 {
  static StrLen Key() { return AppKey(); }

  static Picture Icon() { return DefaultAppIcon(); }

  using PreferenceBag = AppPreferenceBag ;

  using ClientWindow = App::ClientWindow ;

  using Opt = OptNone ;

  static constexpr PrepareOpt Prepare = PrepareRandom ;
 };

} // namespace App

#endif

