/* AppState.ddl */
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

type Coord = sint32 ;

struct Pane
 {
  Coord x;
  Coord y;
  Coord dx;
  Coord dy;
 };

struct AppState
 {
  Pane place;

  text[] recent_files;
 };
