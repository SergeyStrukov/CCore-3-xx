/* Application.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: TruePrime 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/Application.h>

namespace App {

/* struct AppPreferenceBag */

void AppPreferenceBag::bindItems(ConfigItemBind &binder)
 {
  binder.group("Common"_str);

    binder.item("title"_str,title);

  binder.group("Menu"_str);

    binder.item("File"_str,menu_File);
    binder.item("Options"_str,menu_Options);
    binder.item("Exit"_str,menu_Exit);
    binder.item("Global"_str,menu_Global);
    binder.item("App"_str,menu_App);

  binder.group("Text"_str);

 }

} // namespace App


