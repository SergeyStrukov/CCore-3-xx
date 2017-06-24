/* AppState.h */
//----------------------------------------------------------------------------------------
//
//  Project: Aspect 1.01
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef AppState_h
#define AppState_h

#include <inc/Application.h>

#include <CCore/inc/Array.h>
#include <CCore/inc/String.h>

namespace App {

/* classes */

struct AppState;

/* struct AppState */

struct AppState
 {
  Pane place;

  DynArray<String> recent_list;

  // methods

  AppState();

  ~AppState();

  bool load() noexcept;

  void save() noexcept;
 };

} // namespace App

#endif


