/* AppState.ddl */
//----------------------------------------------------------------------------------------
//
//  Project: Book 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

type Coord = sint32 ;

type Bool = uint8 ;

Bool True = 1 ;

Bool False = 0 ;

struct Pane
 {
  Coord x;
  Coord y;
  Coord dx;
  Coord dy;
 };

struct Place
 {
  Coord x;
  Coord y;
  Coord dx;
  Coord dy;
  
  Bool ok = False ;
 };
 
struct AppState
 {
  Pane place;
  Place fav_place;
 };
