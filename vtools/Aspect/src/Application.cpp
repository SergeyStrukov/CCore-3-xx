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
  binder.group("Common"_def);

    binder.item("title"_def,title);
    binder.space();
    binder.item("path"_def,text_Path);
    binder.item("aspect"_def,text_Aspect);
    binder.space();
    binder.item("nothing"_def,text_Nothing);
    binder.item("save"_def,text_Save);

  binder.group("Menu"_def);

    binder.item("path title"_def,text_SelectPath);
    binder.space();
    binder.item("'File'"_def,menu_File);
    binder.item("'Actions'"_def,menu_Actions);
    binder.item("'Options'"_def,menu_Options);
    binder.item("'Recent'"_def,menu_Recent);
    binder.item("'New'"_def,menu_New);
    binder.item("'Open'"_def,menu_Open);
    binder.item("'Save'"_def,menu_Save);
    binder.item("'SaveAs'"_def,menu_SaveAs);
    binder.item("'Exit'"_def,menu_Exit);
    binder.item("'Collect'"_def,menu_Collect);
    binder.item("'Global'"_def,menu_Global);
    binder.item("'App'"_def,menu_App);

  binder.group("Hide"_def);

    binder.item("status dxy"_def,status_dxy);
    binder.space();
    binder.item("'Hide'"_def,text_Hide);
    binder.item("'ShowAll'"_def,text_ShowAll);

  binder.group("Count"_def);

    binder.item("count_status_dxy"_def,count_status_dxy);

  binder.group("Item"_def);

    binder.item("cell size"_def,item_dxy);
    binder.item("radio size"_def,item_rxy);
    binder.item("radio inner"_def,item_rin);
    binder.item("knob size"_def,item_kxy);
    binder.item("text"_def,item_text);
    binder.item("font"_def,item_font);
    binder.item("face1"_def,item_face1);
    binder.item("face2"_def,item_face2);
    binder.item("line"_def,item_line);

  binder.group("Status"_def);

    binder.item("New"_def,status_New);
    binder.item("Ignore"_def,status_Ignore);
    binder.item("Red"_def,status_Red);
    binder.item("Yellow"_def,status_Yellow);
    binder.item("Green"_def,status_Green);
 }

void AppPreferenceBag::createFonts()
 {
  item_font.create();
 }

} // namespace App


