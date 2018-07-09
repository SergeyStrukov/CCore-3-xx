/* Application.h */
//----------------------------------------------------------------------------------------
//
//  Project: Book 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
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

  DefString title = "Book"_def ;

  // menu

  DefString menu_File    = "@File"_def ;
  DefString menu_Options = "@Options"_def ;
  DefString menu_New     = "@New"_def ;
  DefString menu_Open    = "@Open"_def ;
  DefString menu_Exit    = "E@xit"_def ;
  DefString menu_Global  = "@Global"_def ;
  DefString menu_App     = "@Application"_def ;

  // book

  VColor back = Silver ;
  VColor fore = Black ;

  FontCouple font;
  FontCouple codefont;

  DefString text_Title = "Title"_def ;
  DefString text_Page = "Page"_def ;
  DefString text_NotReady = "Font database is not ready yet"_def ;

  Ratio defscale = Ratio(1,0) ;

  DefString hint_PrevPage   = "Go to the previous page"_def ;
  DefString hint_ParentPage = "Go to the parent page"_def ;
  DefString hint_NextPage   = "Go to the next page"_def ;
  DefString hint_Scale      = "Set the display scale"_def ;
  DefString hint_GotoBack   = "Jump back"_def ;
  DefString hint_GotoFore   = "Jump fore"_def ;

  // back

  VColor back_pict = Black ;

  Coord back_dy = 30 ;

  // constructors

  AppPreferenceBag() noexcept {}

  // methods

  template <class Ptr,class Func>
  static void Members(Ptr ptr,Func func);

  virtual void bind(ConfigItemBind &binder);

  void findFonts();
 };

template <class Ptr,class Func>
void AppPreferenceBag::Members(Ptr ptr,Func func)
 {
  func("title"_c,ptr->title);
  func("menu_File"_c,ptr->menu_File);
  func("menu_Options"_c,ptr->menu_Options);
  func("menu_New"_c,ptr->menu_New);
  func("menu_Open"_c,ptr->menu_Open);
  func("menu_Exit"_c,ptr->menu_Exit);
  func("menu_Global"_c,ptr->menu_Global);
  func("menu_App"_c,ptr->menu_App);
  func("back"_c,ptr->back);
  func("fore"_c,ptr->fore);
  func("font"_c,ptr->font);
  func("codefont"_c,ptr->codefont);
  func("text_Title"_c,ptr->text_Title);
  func("text_Page"_c,ptr->text_Page);
  func("text_NotReady"_c,ptr->text_NotReady);
  func("defscale"_c,ptr->defscale);
  func("back_pict"_c,ptr->back_pict);
  func("back_dy"_c,ptr->back_dy);
  func("hint_PrevPage"_c,ptr->hint_PrevPage);
  func("hint_ParentPage"_c,ptr->hint_ParentPage);
  func("hint_NextPage"_c,ptr->hint_NextPage);
  func("hint_Scale"_c,ptr->hint_Scale);
  func("hint_GotoBack"_c,ptr->hint_GotoBack);
  func("hint_GotoFore"_c,ptr->hint_GotoFore);
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
