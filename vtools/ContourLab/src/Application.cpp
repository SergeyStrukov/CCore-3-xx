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

void AppPreferenceBag::bindItems(ConfigItemBind &binder)
 {
  binder.group("Common"_str);

    binder.item("title"_str,title);
    binder.item("arrow size"_str,arrow_size);
    binder.item("shade dxy"_str,shade_dxy);
    binder.space();
    binder.item("back"_str,back);
    binder.item("border"_str,border);
    binder.item("face"_str,face);
    binder.item("gray"_str,gray);
    binder.item("text"_str,text);
    binder.item("hilight"_str,hilight);
    binder.item("focus"_str,focus);
    binder.space();
    binder.item("font"_str,font);

  binder.group("Edit"_str);

    binder.item("angle dxy"_str,edit_angle_dxy);
    binder.item("length dx"_str,edit_length_dx);
    binder.item("length dy"_str,edit_length_dy);
    binder.item("ratio dx"_str,edit_ratio_dx);
    binder.item("ratio dy"_str,edit_ratio_dy);
    binder.item("text"_str,edit_text);
    binder.item("error text"_str,edit_error_text);
    binder.item("number text"_str,edit_number_text);
    binder.item("length text"_str,edit_length_text);
    binder.item("angle text"_str,edit_angle_text);
    binder.item("name text"_str,edit_name_text);
    binder.item("punct text"_str,edit_punct_text);
    binder.item("delay"_str,edit_delay);
    binder.item("geometry dxy"_str,geometry_dxy);

  binder.group("Item list"_str);

    binder.item("'show'"_str,text_show);
    binder.item("'gray'"_str,text_gray);
    binder.item("'name'"_str,text_name);

    binder.item("'Ins'"_str,title_Ins);

  binder.group("Menu"_str);

    binder.item("File"_str,menu_File);
    binder.item("Options"_str,menu_Options);
    binder.item("New"_str,menu_New);
    binder.item("Open"_str,menu_Open);
    binder.item("Save"_str,menu_Save);
    binder.item("SaveAs"_str,menu_SaveAs);
    binder.item("Exit"_str,menu_Exit);
    binder.item("Global"_str,menu_Global);
    binder.item("App"_str,menu_App);

  binder.group("Hints"_str);

    binder.item("?'File'"_str,hint_File);
    binder.item("?'Angle'"_str,hint_Angle);
    binder.item("?'Length'"_str,hint_Length);
    binder.item("?'Ration'"_str,hint_Ratio);
    binder.item("?'Geom'"_str,hint_Geom);
    binder.item("?'Function List'"_str,hint_function_List);
    binder.item("?'List'"_str,hint_item_List);
    binder.item("?'Edit'"_str,hint_item_Edit);
    binder.item("?'Down'"_str,hint_item_Down);
    binder.item("?'Up'"_str,hint_item_Up);
    binder.item("?'Del'"_str,hint_item_Del);
    binder.item("?'Add'"_str,hint_item_Add);
    binder.item("?'Ins'"_str,hint_item_Ins);
    binder.item("?'Show'"_str,hint_item_Show);
    binder.item("?'Gray'"_str,hint_item_Gray);
    binder.item("?'Name'"_str,hint_item_Name);
 }

} // namespace App


