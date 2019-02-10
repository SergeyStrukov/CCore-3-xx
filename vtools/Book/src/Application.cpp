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
  binder.group("Common"_def);

    binder.item("title"_def,title);

  binder.group("Menu"_def);

    binder.item("File"_def,menu_File);
    binder.item("Options"_def,menu_Options);
    binder.item("New"_def,menu_New);
    binder.item("Open"_def,menu_Open);
    binder.item("Exit"_def,menu_Exit);
    binder.item("Global"_def,menu_Global);
    binder.item("App"_def,menu_App);

  binder.group("Book"_def);

    binder.item("back"_def,back);
    binder.item("fore"_def,fore);
    binder.item("font"_def,font);
    binder.item("codefont"_def,codefont);
    binder.item("decorfont"_def,decorfont);
    binder.item("'Title'"_def,text_Title);
    binder.item("'Page'"_def,text_Page);
    binder.item("'Not ready'"_def,text_NotReady);
    binder.item("'Fonts'"_def,text_Font);
    binder.item("default scale"_def,defscale);
    binder.item("'Previuos page'"_def,hint_PrevPage);
    binder.item("'Parent page'"_def,hint_ParentPage);
    binder.item("'Next page'"_def,hint_NextPage);
    binder.item("'Scale'"_def,hint_Scale);
    binder.item("'Font'"_def,hint_Font);
    binder.item("'Reload'"_def,hint_Reload);
    binder.item("'Back'"_def,hint_GotoBack);
    binder.item("'Fore'"_def,hint_GotoFore);

  binder.group("Back button"_def);

    binder.item("picture"_def,back_pict);
    binder.item("height"_def,back_dy);

  binder.group("Font replace"_def);

    binder.item("title"_def,replace_title);
    binder.item("'Find'"_def,text_Find);
    binder.item("'Replace'"_def,text_Replace);
    binder.item("'Save'"_def,text_Save);
    binder.item("'Apply'"_def,text_Apply);

  binder.group("Font selection"_def);

    binder.item("title"_def,font_selection_title);
    binder.item("'Select'"_def,text_Select);
 }

void AppPreferenceBag::findFonts()
 {
  DialogFontLookup dev;

  font=dev.build("Times New Roman"_c,22);
  codefont=dev.build("Anonymous Pro"_c,22);
  decorfont=dev.build("Georgia"_c|Bold|Italic,20);
 }

} // namespace App


