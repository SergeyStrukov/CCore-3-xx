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

void AppPreferenceBag::bindItems(ConfigItemBind &binder)
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

  binder.group("Book"_str);

    binder.item("'No file'"_str,text_NoFile);
    binder.item("'File'"_str,text_File);
    binder.item("'Save'"_str,text_Save);
    binder.item("'Link'"_str,text_Link);
    binder.item("'Book'"_str,text_Book);
    binder.item("'Extern'"_str,text_Extern);
    binder.item("'Temp'"_str,text_Temp);
    binder.item("'Copy'"_str,text_Copy);
    binder.item("'Past'"_str,text_Past);
    binder.item("'Del'"_str,text_Del);
    binder.item("'Name'"_str,text_Name);

    binder.item("table line width"_str,line_width);
    binder.item("border width"_str,border_dxy);
    binder.item("table width"_str,table_dxy);
    binder.item("element space"_str,element_space);
    binder.item("knob len"_str,knob_dxy);
    binder.item("back"_str,back);
    binder.item("cursor"_str,cursor);
    binder.item("gray cursor"_str,gray_cursor);
    binder.item("table"_str,table);
    binder.item("text"_str,text);
    binder.item("element"_str,element);
    binder.item("comment"_str,comment);
    binder.item("text font"_str,text_font);
    binder.item("element font"_str,element_font);
    binder.item("comment font"_str,comment_font);

    binder.item("ins title"_str,ins_title);
    binder.item("field title"_str,field_title);
    binder.item("temp title"_str,temp_title);

  binder.group("Text editor"_str);

    binder.item("font"_str,textedit_font);
    binder.item("line width"_str,textedit_width);
    binder.item("text"_str,textedit_text);
    binder.item("endspan"_str,textedit_endspan);
    binder.item("line"_str,textedit_line);
    binder.item("alert"_str,textedit_alert);
    binder.item("cursor"_str,textedit_cursor);
    binder.item("select"_str,textedit_select);
 }

void AppPreferenceBag::findFonts()
 {
  DialogFontLookup dev;

  text_font=dev.build("Anonymous Pro"_c,22);
  element_font=dev.build("Anonymous Pro"_c|Italic,26);
  comment_font=dev.build("Bookman Old Style"_c|Italic,20);
  textedit_font=dev.build("Anonymous Pro"_c,22);
 }

} // namespace App


