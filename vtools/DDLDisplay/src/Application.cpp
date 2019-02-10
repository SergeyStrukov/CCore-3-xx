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
  binder.group("DDL"_str);

   binder.item("title"_str,title);
   binder.item("space length"_str,space_dxy);
   binder.item("text space"_str,space);
   binder.item("text"_str,text);
   binder.item("pointer"_str,ptr);
   binder.item("select"_str,select);
   binder.item("title font"_str,title_font);
   binder.item("text font"_str,font);
 }

} // namespace App


