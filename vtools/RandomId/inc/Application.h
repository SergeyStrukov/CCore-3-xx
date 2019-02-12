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

struct AppPreferenceBag
 {
  // common

  String title = "RandomId"_str ;

  // menu

  String menu_File    = "@File"_str ;
  String menu_Options = "@Options"_str ;
  String menu_Exit    = "E@xit"_str ;
  String menu_Global  = "@Global"_str ;
  String menu_App     = "@Application"_str ;

  // text

  String text_Unid = "Unid"_str ;
  String text_Raw  = "Raw"_str ;
  String text_Roll = "Roll"_str ;
  String text_Copy = "Copy"_str ;

  // constructors

  AppPreferenceBag() noexcept {}

  // methods

  template <class Ptr,class Func>
  static void Members(Ptr ptr,Func func);

  virtual void bindItems(ConfigItemBind &binder);
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

