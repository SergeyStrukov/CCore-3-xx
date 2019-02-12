/* Application.h */
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

#ifndef Application_h
#define Application_h

#include <inc/App.h>

#include <CCore/inc/video/AppMain.h>

#include <CCore/inc/video/BookFrame.h>

#include <CCore/inc/video/DesktopKey.h>

namespace App {

/* classes */

struct AppProp;

/* struct AppProp */

struct AppProp
 {
  static StrLen Key() { return HomeKey(); }

  static StrLen File() { return BookPreference::File(); }

  static Picture Icon() { return DefaultAppIcon(); }

  using PreferenceBag = Book::ClientWindow::AppBag ;

  using ClientWindow = Book::ClientWindow ;

  using Opt = OptFileName ;

  static constexpr PrepareOpt Prepare = PrepareRandom ;
 };

} // namespace App

#endif

