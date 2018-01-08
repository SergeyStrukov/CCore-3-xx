/* struct TypeDefCore */

struct TypeDefCore
 {
  // types

  struct S1; // #Span 
  struct S2; // #Text 
  struct S3; // #Ratio 
  struct S4; // #Placement 
  struct S5; // #Font 
  struct S6; // #Format 
  struct S7; // #Point 

  using A1 = uint8 ; // #Placement#Align
  using A2 = uint8 ; // #Format#Effect
  using A3 = uint32 ; // #VColor
  using A4 = sint16 ; // #Coord
  using A5 = uint8 ; // #Bool


  using XXX8226D906_9898_43AA_B1BE_D60B0A6E31C8 = TypeDefCore ;

  // structures

  struct S1
   {
    DDL::MapRange< DDL::MapText > list;
    DDL::MapPtr< S6 > fmt;

    struct Ext;
   };

  struct S2
   {
    DDL::MapRange< S1 > list;
    DDL::MapPtr< S6 > fmt;
    DDL::MapPtr< S4 > placement;

    struct Ext;
   };

  struct S3
   {
    A4 a;
    A4 b;

    struct Ext;
   };

  struct S4
   {
    A5 one_line;
    S3 line_space;
    S3 first_line_space;
    A1 align;

    using Align = XXX8226D906_9898_43AA_B1BE_D60B0A6E31C8::A1 ;

    struct Ext;
   };

  struct S5
   {
    DDL::MapText face;
    A4 size;
    A5 bold;
    A5 italic;

    struct Ext;
   };

  struct S6
   {
    S5 font;
    A3 back;
    A3 fore;
    A2 effect;

    using Effect = XXX8226D906_9898_43AA_B1BE_D60B0A6E31C8::A2 ;

    struct Ext;
   };

  struct S7
   {
    A4 x;
    A4 y;

    struct Ext;
   };

  // extra

 };

using XXX212CD757_09B3_4D89_BE20_65C1E4E5A819 = TypeDefCore ;

namespace TypeDef {

    using Bool = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::A5 ;
    using VColor = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::A3 ;
    using Coord = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::A4 ;
    using Font = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S5 ;
    using Span = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S1 ;
    using Text = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S2 ;
    using Placement = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S4 ;
    using Format = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S6 ;
    using Ratio = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S3 ;
    using Point = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S7 ;

} // namespace TypeDef

