/* Application.h */
//----------------------------------------------------------------------------------------
//
//  Project: ContourLab 1.00
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

#include <CCore/inc/video/BookAppMain.h>

#include <inc/Client.h>

namespace App {

/* classes */

struct AppPreferenceBag;

struct AppProp;

/* struct AppPreferenceBag */

struct AppPreferenceBag
 {
  // common

  String title = "ContourLab"_str ;

  Fraction arrow_size = Fraction(5) ;

  Coord shade_dxy = 8 ;

  VColor back    =     White ;
  VColor border  =     Black ;
  VColor face    =     Black ;
  VColor gray    =      Gray ;
  VColor text    =      Blue ;
  VColor hilight =     Green ;
  VColor focus   = OrangeRed ;

  FontCouple font;

  // edit angle

  Coord edit_angle_dxy = 100 ;

  // edit length

  Coord edit_length_dx = 500 ;
  Coord edit_length_dy = 100 ;

  // edit ratio

  Coord edit_ratio_dx = 500 ;
  Coord edit_ratio_dy = 100 ;

  // edit formula

  VColor edit_text        =     Black ;
  VColor edit_error_text  =       Red ;
  VColor edit_number_text = DarkGreen ;
  VColor edit_length_text = DarkGreen ;
  VColor edit_angle_text  = DarkGreen ;
  VColor edit_name_text   =      Blue ;
  VColor edit_punct_text  =     Black ;

  unsigned edit_delay = 1_sectick ;

  // geometry

  Coord geometry_dxy = 300 ;

  // item list

  String text_show = "show"_str ;
  String text_gray = "gray"_str ;
  String text_name = "name"_str ;

  String title_Ins = "Function list"_str ;

  // menu

  String menu_File    = "@File"_str ;
  String menu_Options = "@Options"_str ;
  String menu_Help    = "@Help"_str ;
  String menu_New     = "@New"_str ;
  String menu_Open    = "@Open ..."_str ;
  String menu_Save    = "@Save"_str ;
  String menu_SaveAs  = "Save @as ..."_str ;
  String menu_Exit    = "E@xit"_str ;
  String menu_Global  = "@Global ..."_str ;
  String menu_App     = "@Application ..."_str ;
  String menu_Book    = "@Book ..."_str ;
  String menu_Manual  = "@Manual ..."_str ;

  String title_Manual  = "Book: ContourLab manual"_str ;

  // hints

  String hint_File   = "The current file"_str ;
  String hint_Angle  = "Set the selected angle"_str ;
  String hint_Length = "Set the selected length"_str ;
  String hint_Ratio  = "Set the selected ratio"_str ;
  String hint_Geom   = "Draw of elements, use to set the selected point"_str ;

  String hint_function_List = "Select a function to be inserted into the cursor position"_str ;

  String hint_item_List = "Geometry object list"_str ;
  String hint_item_Edit = "Enter a formula to create a new object"_str ;

  String hint_item_Down = "Move the object down in the list"_str ;
  String hint_item_Up   = "Move the object up in the list"_str ;
  String hint_item_Del  = "Delete the object"_str ;
  String hint_item_Add  = "Add a new object"_str ;
  String hint_item_Ins  = "Open the Function list window"_str ;

  String hint_item_Show = "Show this object"_str ;
  String hint_item_Gray = "Gray this object if not selected"_str ;
  String hint_item_Name = "Show the name of this object"_str ;

  // constructors

  AppPreferenceBag() noexcept {}

  // methods

  template <class Ptr,class Func>
  static void Members(Ptr ptr,Func func);

  void bindItems(ConfigItemBind &binder);
 };

template <class Ptr,class Func>
void AppPreferenceBag::Members(Ptr ptr,Func func)
 {
  func("title"_c,ptr->title);

  func("arrow_size"_c,ptr->arrow_size);

  func("shade_dxy"_c,ptr->shade_dxy);

  func("back"_c,ptr->back);
  func("border"_c,ptr->border);
  func("face"_c,ptr->face);
  func("gray"_c,ptr->gray);
  func("vtext"_c,ptr->text);
  func("hilight"_c,ptr->hilight);
  func("focus"_c,ptr->focus);

  func("font"_c,ptr->font);

  func("edit_angle_dxy"_c,ptr->edit_angle_dxy);

  func("edit_length_dx"_c,ptr->edit_length_dx);
  func("edit_length_dy"_c,ptr->edit_length_dy);

  func("edit_ratio_dx"_c,ptr->edit_ratio_dx);
  func("edit_ratio_dy"_c,ptr->edit_ratio_dy);

  func("edit_text"_c,ptr->edit_text);
  func("edit_error_text"_c,ptr->edit_error_text);
  func("edit_number_text"_c,ptr->edit_number_text);
  func("edit_length_text"_c,ptr->edit_length_text);
  func("edit_angle_text"_c,ptr->edit_angle_text);
  func("edit_name_text"_c,ptr->edit_name_text);
  func("edit_punct_text"_c,ptr->edit_punct_text);

  func("edit_delay"_c,ptr->edit_delay);

  func("geometry_dxy"_c,ptr->geometry_dxy);

  func("text_show"_c,ptr->text_show);
  func("text_gray"_c,ptr->text_gray);
  func("text_name"_c,ptr->text_name);

  func("title_Ins"_c,ptr->title_Ins);

  func("menu_File"_c,ptr->menu_File);
  func("menu_Options"_c,ptr->menu_Options);
  func("menu_Help"_c,ptr->menu_Help);
  func("menu_New"_c,ptr->menu_New);
  func("menu_Open"_c,ptr->menu_Open);
  func("menu_Save"_c,ptr->menu_Save);
  func("menu_SaveAs"_c,ptr->menu_SaveAs);
  func("menu_Exit"_c,ptr->menu_Exit);
  func("menu_Global"_c,ptr->menu_Global);
  func("menu_App"_c,ptr->menu_App);
  func("menu_Book"_c,ptr->menu_Book);
  func("menu_Manual"_c,ptr->menu_Manual);

  func("title_Manual"_c,ptr->title_Manual);

  func("hint_File"_c,ptr->hint_File);
  func("hint_Angle"_c,ptr->hint_Angle);
  func("hint_Length"_c,ptr->hint_Length);
  func("hint_Ratio"_c,ptr->hint_Ratio);
  func("hint_Geom"_c,ptr->hint_Geom);

  func("hint_function_List"_c,ptr->hint_function_List);

  func("hint_item_List"_c,ptr->hint_item_List);
  func("hint_item_Edit"_c,ptr->hint_item_Edit);

  func("hint_item_Down"_c,ptr->hint_item_Down);
  func("hint_item_Up"_c,ptr->hint_item_Up);
  func("hint_item_Del"_c,ptr->hint_item_Del);
  func("hint_item_Add"_c,ptr->hint_item_Add);
  func("hint_item_Ins"_c,ptr->hint_item_Ins);

  func("hint_item_Show"_c,ptr->hint_item_Show);
  func("hint_item_Gray"_c,ptr->hint_item_Gray);
  func("hint_item_Name"_c,ptr->hint_item_Name);
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

