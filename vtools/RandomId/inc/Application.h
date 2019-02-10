/* Application.h */
//----------------------------------------------------------------------------------------
//
//  Project: RandomId 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
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
  // common

  String title = "RandomId"_def ;

  // menu

  String menu_File    = "@File"_def ;
  String menu_Options = "@Options"_def ;
  String menu_Exit    = "E@xit"_def ;
  String menu_Global  = "@Global"_def ;
  String menu_App     = "@Application"_def ;

  // text

  String text_Unid = "Unid"_def ;
  String text_Raw  = "Raw"_def ;
  String text_Roll = "Roll"_def ;
  String text_Copy = "Copy"_def ;

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
  func("menu_File"_c,ptr->menu_File);
  func("menu_Options"_c,ptr->menu_Options);
  func("menu_Exit"_c,ptr->menu_Exit);
  func("menu_Global"_c,ptr->menu_Global);
  func("menu_App"_c,ptr->menu_App);
  func("text_Unid"_c,ptr->text_Unid);
  func("text_Raw"_c,ptr->text_Raw);
  func("text_Roll"_c,ptr->text_Roll);
  func("text_Copy"_c,ptr->text_Copy);
 }

/* struct AppProp */

struct AppProp
 {
  static StrLen Key() { return AppKey(); }

  static Picture Icon() { return DefaultAppIcon(); }

  using PreferenceBag = AppPreferenceBag ;

  using ClientWindow = App::ClientWindow ;

  using Opt = OptNone ;

  static constexpr PrepareOpt Prepare = PrepareCenter ;
 };

} // namespace App

#endif

