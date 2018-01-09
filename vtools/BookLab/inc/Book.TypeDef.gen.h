/* struct TypeDefCore */

struct TypeDefCore
 {
  // types

  struct S1; // #Point 
  struct S2; // #Frame 
  struct S3; // #Book 
  struct S4; // #Bitmap 
  struct S5; // #Span 
  struct S6; // #Text 
  struct S7; // #Ratio 
  struct S8; // #MultiLine 
  struct S9; // #OneLine 
  struct S10; // #Format 
  struct S11; // #Font 

  using A1 = uint8 ; // #Frame#LineType
  using A2 = uint8 ; // #OneLine#Align
  using A3 = uint8 ; // #Format#Effect
  using A4 = sint16 ; // #Coord
  using A5 = uint32 ; // #VColor
  using A6 = uint8 ; // #Bool


  using XXX8226D906_9898_43AA_B1BE_D60B0A6E31C8 = TypeDefCore ;

  // structures

  struct S1
   {
    A4 x;
    A4 y;

    struct Ext;
   };

  struct S2
   {
    A1 line_type;
    S1 inner;
    S1 outer;
    A5 col;
    DDL::MapPolyPtr< S6 , S4 > body;

    using LineType = XXX8226D906_9898_43AA_B1BE_D60B0A6E31C8::A1 ;

    struct Ext;
   };

  struct S3
   {
    A5 back;
    A5 fore;
    DDL::MapRange< S2 > body;

    struct Ext;
   };

  struct S4
   {
    DDL::MapRange< DDL::MapRange< A5 > > map;

    struct Ext;
   };

  struct S5
   {
    DDL::MapRange< DDL::MapText > list;
    DDL::MapPtr< S10 > fmt;

    struct Ext;
   };

  struct S6
   {
    DDL::MapRange< S5 > list;
    DDL::MapPtr< S10 > fmt;
    DDL::MapPolyPtr< S9 , S8 > placement;

    struct Ext;
   };

  struct S7
   {
    A4 a;
    A4 b;

    struct Ext;
   };

  struct S8
   {
    S7 line_space;
    S7 first_line_space;

    struct Ext;
   };

  struct S9
   {
    A2 align;

    using Align = XXX8226D906_9898_43AA_B1BE_D60B0A6E31C8::A2 ;

    struct Ext;
   };

  struct S10
   {
    DDL::MapPtr< S11 > font;
    A5 back;
    A5 fore;
    A3 effect;

    using Effect = XXX8226D906_9898_43AA_B1BE_D60B0A6E31C8::A3 ;

    struct Ext;
   };

  struct S11
   {
    DDL::MapText face;
    A4 size;
    A6 bold;
    A6 italic;

    struct Ext;
   };

  // extra

 };

using XXX212CD757_09B3_4D89_BE20_65C1E4E5A819 = TypeDefCore ;

namespace TypeDef {

    using Bool = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::A6 ;
    using VColor = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::A5 ;
    using Coord = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::A4 ;
    using OneLine = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S9 ;
    using Book = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S3 ;
    using Font = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S11 ;
    using Bitmap = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S4 ;
    using Span = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S5 ;
    using Text = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S6 ;
    using Format = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S10 ;
    using Ratio = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S7 ;
    using MultiLine = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S8 ;
    using Point = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S1 ;
    using Frame = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S2 ;

} // namespace TypeDef

