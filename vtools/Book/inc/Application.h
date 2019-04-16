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

struct AppState;

class ClientWindow;

struct AppProp;

/* struct AppState */

struct AppState
 {
  Pane place;

  FramePlace fav_place;

  // methods

  static StrLen File();

  static StrLen Pretext();

  AppState();

  ~AppState();

  bool load(StrLen file_name);

  void save(StrLen file_name) const;

  bool load() noexcept;

  void save() const noexcept;
 };

/* class ClientWindow */

class ClientWindow : public Book::ClientWindow , public AliveControl
 {
  public:

   ClientWindow(SubWindowHost &host,const Config &cfg,OptFileName opt,Signal<> &update);

   virtual ~ClientWindow();

   // AliveControl

   virtual void dying();
 };

/* struct AppProp */

struct AppProp
 {
  static StrLen Key() { return HomeKey(); }

  static StrLen File() { return BookPreference::File(); }

  static Picture Icon() { return DefaultAppIcon(); }

  using PreferenceBag = Book::ClientWindow::AppBag ;

  using ClientWindow = App::ClientWindow ;

  using Opt = OptFileName ;

  using Persist = AppState ;

  static constexpr PrepareOpt Prepare = PreparePersist ;
 };

} // namespace App

#endif

