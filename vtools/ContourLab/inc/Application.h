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

  DefString title = "ContourLab"_def ;

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

  DefString text_show = "show"_def ;
  DefString text_gray = "gray"_def ;
  DefString text_name = "name"_def ;

  DefString title_Ins = "Function list"_def ;

  // menu

  DefString menu_File    = "@File"_def ;
  DefString menu_Options = "@Options"_def ;
  DefString menu_New     = "@New"_def ;
  DefString menu_Open    = "@Open ..."_def ;
  DefString menu_Save    = "@Save"_def ;
  DefString menu_SaveAs  = "Save @as ..."_def ;
  DefString menu_Exit    = "E@xit"_def ;
  DefString menu_Global  = "@Global ..."_def ;
  DefString menu_App     = "@Application ..."_def ;

  // hints

  DefString hint_File   = "The current file"_def ;
  DefString hint_Angle  = "Set the selected angle"_def ;
  DefString hint_Length = "Set the selected length"_def ;
  DefString hint_Ratio  = "Set the selected ratio"_def ;
  DefString hint_Geom   = "Draw of elements, use to set the selected point"_def ;

  DefString hint_function_List = "Select a function to be inserted into the cursor position"_def ;

  DefString hint_item_List = "Geometry object list"_def ;
  DefString hint_item_Edit = "Enter a formula to create a new object"_def ;

  DefString hint_item_Down = "Move the object down in the list"_def ;
  DefString hint_item_Up   = "Move the object up in the list"_def ;
  DefString hint_item_Del  = "Delete the object"_def ;
  DefString hint_item_Add  = "Add a new object"_def ;
  DefString hint_item_Ins  = "Open the Function list window"_def ;

  DefString hint_item_Show = "Show this object"_def ;
  DefString hint_item_Gray = "Gray this object if not selected"_def ;
  DefString hint_item_Name = "Show the name of this object"_def ;

  // constructors

  AppPreferenceBag() noexcept {}

  // methods

  template <class Ptr,class Func>
  static void Members(Ptr ptr,Func func);

  virtual void bind(ConfigItemBind &binder);

  void createFonts();
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

  func("font"_c,ptr->font.param);

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
  func("menu_New"_c,ptr->menu_New);
  func("menu_Open"_c,ptr->menu_Open);
  func("menu_Save"_c,ptr->menu_Save);
  func("menu_SaveAs"_c,ptr->menu_SaveAs);
  func("menu_Exit"_c,ptr->menu_Exit);
  func("menu_Global"_c,ptr->menu_Global);
  func("menu_App"_c,ptr->menu_App);

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

