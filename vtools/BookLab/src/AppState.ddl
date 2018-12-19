/* AppState.ddl */

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
  Place temp_place;
  Place edit_place;
 };
 