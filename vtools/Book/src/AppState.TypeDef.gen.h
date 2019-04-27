/* struct TypeDefCore */

struct TypeDefCore
 {
  // types

  struct S1; // #Place 
  struct S2; // #AppState 

  using A1 = uint8 ; // #Bool
  using A2 = sint32 ; // #Coord


  using XXX8226D906_9898_43AA_B1BE_D60B0A6E31C8 = TypeDefCore ;

  // structures

  struct S1
   {
    A2 x;
    A2 y;
    A2 dx;
    A2 dy;
    A1 ok;

    struct Ext;
   };

  struct S2
   {
    S1 place;
    S1 fav_place;

    struct Ext;
   };

  // extra

 };

using XXX212CD757_09B3_4D89_BE20_65C1E4E5A819 = TypeDefCore ;

namespace TypeDef {

    using Bool = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::A1 ;
    using Coord = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::A2 ;
    using AppState = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S2 ;
    using Place = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S1 ;

} // namespace TypeDef

