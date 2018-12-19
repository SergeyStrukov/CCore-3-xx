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

struct FramePlace;

struct AppState;

/* struct FramePlace */

struct FramePlace
 {
  Pane place;
  bool ok = false ;

  void set(Pane pane)
   {
    place=pane;
    ok=true;
   }

  template <class T>
  void set(T data)
   {
    if( data.ok )
      {
       place.x=data.x;
       place.y=data.y;
       place.dx=data.dx;
       place.dy=data.dy;

       ok=true;
      }
    else
      {
       ok=false;
      }
   }

  Pane get(Point size) const { Used(size); return place; }

  void print(PrinterType &out) const
   {
    if( ok )
      Printf(out,"{ #; , #; , #; , #; , True }",place.x,place.y,place.dx,place.dy);
    else
      Putobj(out,"{ .ok = False }"_c);
   }
 };

/* struct AppState */

struct AppState
 {
  Pane place;
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


