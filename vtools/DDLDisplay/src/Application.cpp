/* Application.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: DDLDisplay 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/Application.h>

namespace App {

/* struct AppPreferenceBag */

void AppPreferenceBag::bind(ConfigItemBind &binder)
 {
  binder.group("DDL"_def);

   binder.item("title"_def,title);
   binder.item("space length"_def,space_dxy);
   binder.item("text space"_def,space);
   binder.item("text"_def,text);
   binder.item("pointer"_def,ptr);
   binder.item("select"_def,select);
   binder.item("title font"_def,title_font);
   binder.item("text font"_def,font);
 }

void AppPreferenceBag::createFonts()
 {
  title_font.create();
  font.create();
 }

} // namespace App


