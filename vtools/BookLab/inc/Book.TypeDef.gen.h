/* struct TypeDefCore */

struct TypeDefCore
 {
  // types

  struct S1; // #Ratio 
  struct S2; // #Point 

  using A1 = uint32 ; // #VColor
  using A2 = sint16 ; // #Coord
  using A3 = uint8 ; // #Bool


  using XXX8226D906_9898_43AA_B1BE_D60B0A6E31C8 = TypeDefCore ;

  // structures

  struct S1
   {
    sint32 ratio;

    struct Ext;
   };

  struct S2
   {
    A2 x;
    A2 y;

    struct Ext;
   };

  // extra

 };

using XXX212CD757_09B3_4D89_BE20_65C1E4E5A819 = TypeDefCore ;

namespace TypeDef {

    using Bool = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::A3 ;
    using VColor = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::A1 ;
    using Coord = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::A2 ;
    using Ratio = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S1 ;
    using Point = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S2 ;

} // namespace TypeDef

