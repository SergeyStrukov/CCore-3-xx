/* Application.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: BookLab 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/Application.h>

#include <CCore/inc/video/FontLookup.h>

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
    binder.item("Save"_def,menu_Save);
    binder.item("SaveAs"_def,menu_SaveAs);
    binder.item("Exit"_def,menu_Exit);
    binder.item("Global"_def,menu_Global);
    binder.item("App"_def,menu_App);

  binder.group("Book"_def);

    binder.item("'No file'"_def,text_NoFile);
    binder.item("'File'"_def,text_File);
    binder.item("'Link'"_def,text_Link);
    binder.item("'Book'"_def,text_Book);

    binder.item("table line width"_def,line_width);
    binder.item("border width"_def,border_dxy);
    binder.item("table width"_def,table_dxy);
    binder.item("element space"_def,element_space);
    binder.item("knob len"_def,knob_dxy);
    binder.item("back"_def,back);
    binder.item("cursor"_def,cursor);
    binder.item("table"_def,table);
    binder.item("text"_def,text);
    binder.item("element"_def,element);
    binder.item("comment"_def,comment);
    binder.item("text font"_def,text_font);
    binder.item("element font"_def,element_font);
    binder.item("comment font"_def,comment_font);

    binder.item("ins title"_def,ins_title);
    binder.item("field title"_def,field_title);
 }

void AppPreferenceBag::findFonts()
 {
  DialogFontLookup dev;

  text_font=dev.build("Anonymous Pro"_c,22);
  element_font=dev.build("Anonymous Pro"_c|Italic,26);
  comment_font=dev.build("Bookman Old Style"_c|Italic,20);
 }

} // namespace App


