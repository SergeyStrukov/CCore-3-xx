/* AppState.h */
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

#ifndef AppState_h
#define AppState_h

#include <inc/App.h>

namespace App {

/* classes */

struct AppState;

/* struct AppState */

struct AppState
 {
  FramePlace place;
  FramePlace temp_place;
  FramePlace edit_place;

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

} // namespace App

#endif


