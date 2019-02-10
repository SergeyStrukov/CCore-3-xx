/* Application.cpp */
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
    binder.item("Exit"_str,menu_Exit);
    binder.item("Global"_str,menu_Global);
    binder.item("App"_str,menu_App);

  binder.group("Book"_str);

    binder.item("back"_str,back);
    binder.item("fore"_str,fore);
    binder.item("font"_str,font);
    binder.item("codefont"_str,codefont);
    binder.item("decorfont"_str,decorfont);
    binder.item("'Title'"_str,text_Title);
    binder.item("'Page'"_str,text_Page);
    binder.item("'Not ready'"_str,text_NotReady);
    binder.item("'Fonts'"_str,text_Font);
    binder.item("default scale"_str,defscale);
    binder.item("'Previuos page'"_str,hint_PrevPage);
    binder.item("'Parent page'"_str,hint_ParentPage);
    binder.item("'Next page'"_str,hint_NextPage);
    binder.item("'Scale'"_str,hint_Scale);
    binder.item("'Font'"_str,hint_Font);
    binder.item("'Reload'"_str,hint_Reload);
    binder.item("'Back'"_str,hint_GotoBack);
    binder.item("'Fore'"_str,hint_GotoFore);

  binder.group("Back button"_str);

    binder.item("picture"_str,back_pict);
    binder.item("height"_str,back_dy);

  binder.group("Font replace"_str);

    binder.item("title"_str,replace_title);
    binder.item("'Find'"_str,text_Find);
    binder.item("'Replace'"_str,text_Replace);
    binder.item("'Save'"_str,text_Save);
    binder.item("'Apply'"_str,text_Apply);

  binder.group("Font selection"_str);

    binder.item("title"_str,font_selection_title);
    binder.item("'Select'"_str,text_Select);
 }

void AppPreferenceBag::findFonts()
 {
  DialogFontLookup dev;

  font=dev.build("Times New Roman"_c,22);
  codefont=dev.build("Anonymous Pro"_c,22);
  decorfont=dev.build("Georgia"_c|Bold|Italic,20);
 }

} // namespace App


