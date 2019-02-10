/* Application.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: Sample 1.00
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
 }

} // namespace App


