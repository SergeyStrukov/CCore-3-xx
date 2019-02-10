/* Application.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: Aspect 1.01
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
  binder.group("Common"_str);

    binder.item("title"_str,title);
    binder.space();
    binder.item("path"_str,text_Path);
    binder.item("aspect"_str,text_Aspect);
    binder.space();
    binder.item("nothing"_str,text_Nothing);
    binder.item("save"_str,text_Save);

  binder.group("Menu"_str);

    binder.item("path title"_str,text_SelectPath);
    binder.space();
    binder.item("'File'"_str,menu_File);
    binder.item("'Actions'"_str,menu_Actions);
    binder.item("'Options'"_str,menu_Options);
    binder.item("'Recent'"_str,menu_Recent);
    binder.item("'New'"_str,menu_New);
    binder.item("'Open'"_str,menu_Open);
    binder.item("'Save'"_str,menu_Save);
    binder.item("'SaveAs'"_str,menu_SaveAs);
    binder.item("'Exit'"_str,menu_Exit);
    binder.item("'Collect'"_str,menu_Collect);
    binder.item("'Global'"_str,menu_Global);
    binder.item("'App'"_str,menu_App);

  binder.group("Hide"_str);

    binder.item("status dxy"_str,status_dxy);
    binder.space();
    binder.item("'Hide'"_str,text_Hide);
    binder.item("'ShowAll'"_str,text_ShowAll);

  binder.group("Count"_str);

    binder.item("count_status_dxy"_str,count_status_dxy);

  binder.group("Item"_str);

    binder.item("cell size"_str,item_dxy);
    binder.item("radio size"_str,item_rxy);
    binder.item("radio inner"_str,item_rin);
    binder.item("knob size"_str,item_kxy);
    binder.item("text"_str,item_text);
    binder.item("font"_str,item_font);
    binder.item("face1"_str,item_face1);
    binder.item("face2"_str,item_face2);
    binder.item("line"_str,item_line);

  binder.group("Status"_str);

    binder.item("New"_str,status_New);
    binder.item("Ignore"_str,status_Ignore);
    binder.item("Red"_str,status_Red);
    binder.item("Yellow"_str,status_Yellow);
    binder.item("Green"_str,status_Green);
 }

} // namespace App


