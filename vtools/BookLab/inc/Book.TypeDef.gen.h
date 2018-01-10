/* struct TypeDefCore */

struct TypeDefCore
 {
  // types

  struct S1; // #Link 
  struct S2; // #Book 
  struct S3; // #Point 
  struct S4; // #Frame 
  struct S5; // #Page 
  struct S6; // #Bitmap 
  struct S7; // #FixedSpan 
  struct S8; // #Line 
  struct S9; // #FixedText 
  struct S10; // #Span 
  struct S11; // #Text 
  struct S12; // #Ratio 
  struct S13; // #MultiLine 
  struct S14; // #OneLine 
  struct S15; // #Format 
  struct S16; // #Font 

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
    DDL::ulen_type page_index;
    DDL::ulen_type frame_index;

    struct Ext;
   };

  struct S2
   {
    DDL::MapText title;
    DDL::MapRange< DDL::MapPtr< S5 > > list;
    A5 back;
    A5 fore;

    struct Ext;
   };

  struct S3
   {
    A4 x;
    A4 y;

    struct Ext;
   };

  struct S4
   {
    DDL::MapPolyPtr< S11 , S9 , S6 > body;
    A1 line_type;
    S3 inner;
    S3 outer;
    A5 col;

    using LineType = XXX8226D906_9898_43AA_B1BE_D60B0A6E31C8::A1 ;

    struct Ext;
   };

  struct S5
   {
    DDL::MapText name;
    DDL::MapRange< S4 > list;
    A5 back;
    A5 fore;

    struct Ext;
   };

  struct S6
   {
    DDL::MapRange< DDL::MapRange< A5 > > map;

    struct Ext;
   };

  struct S7
   {
    DDL::MapText body;
    DDL::MapPtr< S15 > fmt;
    DDL::MapPolyPtr< S1 , S5 > ref;

    struct Ext;
   };

  struct S8
   {
    DDL::MapRange< S7 > list;

    struct Ext;
   };

  struct S9
   {
    DDL::MapRange< S8 > list;
    DDL::MapPtr< S15 > fmt;

    struct Ext;
   };

  struct S10
   {
    DDL::MapRange< DDL::MapText > list;
    DDL::MapPtr< S15 > fmt;
    DDL::MapPolyPtr< S1 , S5 > ref;

    struct Ext;
   };

  struct S11
   {
    DDL::MapRange< S10 > list;
    DDL::MapPtr< S15 > fmt;
    DDL::MapPolyPtr< S14 , S13 > placement;

    struct Ext;
   };

  struct S12
   {
    A4 a;
    A4 b;

    struct Ext;
   };

  struct S13
   {
    S12 line_space;
    S12 first_line_space;

    struct Ext;
   };

  struct S14
   {
    A2 align;

    using Align = XXX8226D906_9898_43AA_B1BE_D60B0A6E31C8::A2 ;

    struct Ext;
   };

  struct S15
   {
    DDL::MapPtr< S16 > font;
    A5 back;
    A5 fore;
    A3 effect;

    using Effect = XXX8226D906_9898_43AA_B1BE_D60B0A6E31C8::A3 ;

    struct Ext;
   };

  struct S16
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
    using OneLine = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S14 ;
    using Book = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S2 ;
    using Font = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S16 ;
    using Line = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S8 ;
    using Link = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S1 ;
    using Page = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S5 ;
    using Bitmap = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S6 ;
    using Span = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S10 ;
    using Text = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S11 ;
    using FixedText = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S9 ;
    using FixedSpan = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S7 ;
    using Format = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S15 ;
    using Ratio = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S12 ;
    using MultiLine = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S13 ;
    using Point = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S3 ;
    using Frame = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S4 ;

} // namespace TypeDef

