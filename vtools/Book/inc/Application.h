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

#include <inc/App.h>

#include <CCore/inc/video/AppMain.h>

#include <CCore/inc/video/book/BookClient.h>

namespace App {

/* classes */

struct AppPreferenceBag;

struct AppProp;

/* struct AppPreferenceBag */

struct AppPreferenceBag : ConfigItemHost
 {
  // common

  String title = "Book"_str ;

  // menu

  String menu_File    = "@File"_str ;
  String menu_Options = "@Options"_str ;
  String menu_New     = "@New"_str ;
  String menu_Open    = "@Open"_str ;
  String menu_Exit    = "E@xit"_str ;
  String menu_Global  = "@Global"_str ;
  String menu_App     = "@Application"_str ;

  // book

  VColor back = Silver ;
  VColor fore = Black ;

  FontCouple font;
  FontCouple codefont;
  FontCouple decorfont;

  String text_Title = "Title"_str ;
  String text_Page = "Page"_str ;
  String text_NotReady = "Font database is not ready yet"_str ;
  String text_Font = "Fonts"_str ;

  Ratio defscale = Ratio(1,0) ;

  String hint_PrevPage   = "Go to the previous page"_str ;
  String hint_ParentPage = "Go to the parent page"_str ;
  String hint_NextPage   = "Go to the next page"_str ;
  String hint_Scale      = "Set the display scale"_str ;
  String hint_Font       = "Font replacement table"_str ;
  String hint_Reload     = "Reload book"_str ;
  String hint_GotoBack   = "Jump back"_str ;
  String hint_GotoFore   = "Jump fore"_str ;

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
  func("decorfont"_c,ptr->decorfont);
  func("text_Title"_c,ptr->text_Title);
  func("text_Page"_c,ptr->text_Page);
  func("text_NotReady"_c,ptr->text_NotReady);
  func("text_Font"_c,ptr->text_Font);
  func("defscale"_c,ptr->defscale);
  func("back_pict"_c,ptr->back_pict);
  func("back_dy"_c,ptr->back_dy);
  func("hint_PrevPage"_c,ptr->hint_PrevPage);
  func("hint_ParentPage"_c,ptr->hint_ParentPage);
  func("hint_NextPage"_c,ptr->hint_NextPage);
  func("hint_Scale"_c,ptr->hint_Scale);
  func("hint_Font"_c,ptr->hint_Font);
  func("hint_Reload"_c,ptr->hint_Reload);
  func("hint_GotoBack"_c,ptr->hint_GotoBack);
  func("hint_GotoFore"_c,ptr->hint_GotoFore);
 }

/* struct AppProp */

struct AppProp
 {
  static StrLen Key() { return AppKey(); }

  static Picture Icon() { return DefaultAppIcon(); }

  using PreferenceBag = AppPreferenceBag ;

  using ClientWindow = Book::ClientWindow ;

  using Opt = OptFileName ;

  static constexpr PrepareOpt Prepare = PrepareRandom ;
 };

} // namespace App

#endif

