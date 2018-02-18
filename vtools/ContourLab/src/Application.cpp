/* Application.cpp */
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

#include <inc/Application.h>

namespace App {

/* struct AppPreferenceBag */

void AppPreferenceBag::bind(ConfigItemBind &binder)
 {
  binder.group("Common"_def);

    binder.item("title"_def,title);
    binder.item("arrow size"_def,arrow_size);
    binder.item("shade dxy"_def,shade_dxy);
    binder.space();
    binder.item("back"_def,back);
    binder.item("border"_def,border);
    binder.item("face"_def,face);
    binder.item("gray"_def,gray);
    binder.item("text"_def,text);
    binder.item("hilight"_def,hilight);
    binder.item("focus"_def,focus);
    binder.space();
    binder.item("font"_def,font);

  binder.group("Edit"_def);

    binder.item("angle dxy"_def,edit_angle_dxy);
    binder.item("length dx"_def,edit_length_dx);
    binder.item("length dy"_def,edit_length_dy);
    binder.item("ratio dx"_def,edit_ratio_dx);
    binder.item("ratio dy"_def,edit_ratio_dy);
    binder.item("text"_def,edit_text);
    binder.item("error text"_def,edit_error_text);
    binder.item("number text"_def,edit_number_text);
    binder.item("length text"_def,edit_length_text);
    binder.item("angle text"_def,edit_angle_text);
    binder.item("name text"_def,edit_name_text);
    binder.item("punct text"_def,edit_punct_text);
    binder.item("delay"_def,edit_delay);
    binder.item("geometry dxy"_def,geometry_dxy);

  binder.group("Item list"_def);

    binder.item("'show'"_def,text_show);
    binder.item("'gray'"_def,text_gray);
    binder.item("'name'"_def,text_name);

    binder.item("'Ins'"_def,title_Ins);

  binder.group("Menu"_def);

    binder.item("File"_def,menu_File);
    binder.item("Options"_def,menu_Options);
    binder.item("New"_def,menu_New);
    binder.item("Open"_def,menu_Open);
    binder.item("Save"_def,menu_Save);
    binder.item("SaveAs"_def,menu_SaveAs);
    binder.item("Exit"_def,menu_Exit);
    binder.item("Global"_def,menu_Global);
    binder.item("App"_def,menu_App);

  binder.group("Hints"_def);

    binder.item("?'File'"_def,hint_File);
    binder.item("?'Angle'"_def,hint_Angle);
    binder.item("?'Length'"_def,hint_Length);
    binder.item("?'Ration'"_def,hint_Ratio);
    binder.item("?'Geom'"_def,hint_Geom);
    binder.item("?'Function List'"_def,hint_function_List);
    binder.item("?'List'"_def,hint_item_List);
    binder.item("?'Edit'"_def,hint_item_Edit);
    binder.item("?'Down'"_def,hint_item_Down);
    binder.item("?'Up'"_def,hint_item_Up);
    binder.item("?'Del'"_def,hint_item_Del);
    binder.item("?'Add'"_def,hint_item_Add);
    binder.item("?'Ins'"_def,hint_item_Ins);
    binder.item("?'Show'"_def,hint_item_Show);
    binder.item("?'Gray'"_def,hint_item_Gray);
    binder.item("?'Name'"_def,hint_item_Name);
 }

void AppPreferenceBag::createFonts()
 {
  font.create();
 }

} // namespace App


