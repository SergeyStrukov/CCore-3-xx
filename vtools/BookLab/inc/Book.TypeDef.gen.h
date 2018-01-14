/* struct TypeDefCore */

struct TypeDefCore
 {
  // types

  struct S1; // #Link 
  struct S2; // #Book 
  struct S3; // #Point 
  struct S4; // #Frame 
  struct S5; // #Page 
  struct S6; // #Ratio 
  struct S7; // #DoubleLine 
  struct S8; // #SingleLine 
  struct S9; // #Bitmap 
  struct S10; // #FixedSpan 
  struct S11; // #Line 
  struct S12; // #FixedText 
  struct S13; // #Span 
  struct S14; // #Text 
  struct S15; // #MultiLine 
  struct S16; // #OneLine 
  struct S17; // #Format 
  struct S18; // #Font 

  using A1 = uint8 ; // #OneLine#Align
  using A2 = uint8 ; // #Format#Effect
  using A3 = sint16 ; // #Coord
  using A4 = uint32 ; // #VColor
  using A5 = uint8 ; // #Bool


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
    A4 back;
    A4 fore;

    struct Ext;
   };

  struct S3
   {
    A3 x;
    A3 y;

    struct Ext;
   };

  struct S4
   {
    DDL::MapPolyPtr< S14 , S12 , S9 > body;
    DDL::MapPolyPtr< S8 , S7 > line;
    S3 inner;
    S3 outer;
    A4 col;

    struct Ext;
   };

  struct S5
   {
    DDL::MapText name;
    DDL::MapRange< S4 > list;
    A4 back;
    A4 fore;

    struct Ext;
   };

  struct S6
   {
    A3 a;
    A3 b;

    struct Ext;
   };

  struct S7
   {
    S6 width;
    A4 gray;
    A4 snow;

    struct Ext;
   };

  struct S8
   {
    S6 width;
    A4 line;

    struct Ext;
   };

  struct S9
   {
    DDL::MapRange< DDL::MapRange< A4 > > map;

    struct Ext;
   };

  struct S10
   {
    DDL::MapText body;
    DDL::MapPtr< S17 > fmt;
    DDL::MapPolyPtr< S1 , S5 > ref;

    struct Ext;
   };

  struct S11
   {
    DDL::MapRange< S10 > list;

    struct Ext;
   };

  struct S12
   {
    DDL::MapRange< S11 > list;
    DDL::MapPtr< S17 > fmt;

    struct Ext;
   };

  struct S13
   {
    DDL::MapRange< DDL::MapText > list;
    DDL::MapPtr< S17 > fmt;
    DDL::MapPolyPtr< S1 , S5 > ref;

    struct Ext;
   };

  struct S14
   {
    DDL::MapRange< S13 > list;
    DDL::MapPtr< S17 > fmt;
    DDL::MapPolyPtr< S16 , S15 > placement;

    struct Ext;
   };

  struct S15
   {
    S6 line_space;
    S6 first_line_space;

    struct Ext;
   };

  struct S16
   {
    A1 align;

    using Align = XXX8226D906_9898_43AA_B1BE_D60B0A6E31C8::A1 ;

    struct Ext;
   };

  struct S17
   {
    DDL::MapPtr< S18 > font;
    A4 back;
    A4 fore;
    A2 effect;

    using Effect = XXX8226D906_9898_43AA_B1BE_D60B0A6E31C8::A2 ;

    struct Ext;
   };

  struct S18
   {
    DDL::MapText face;
    A3 size;
    A5 bold;
    A5 italic;
    DDL::sint_type strength;

    struct Ext;

    ulen ext;
   };

  // extra

 };

using XXX212CD757_09B3_4D89_BE20_65C1E4E5A819 = TypeDefCore ;

namespace TypeDef {

    using Bool = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::A5 ;
    using VColor = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::A4 ;
    using Coord = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::A3 ;
    using OneLine = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S16 ;
    using Book = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S2 ;
    using Font = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S18 ;
    using Line = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S11 ;
    using Link = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S1 ;
    using SingleLine = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S8 ;
    using Page = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S5 ;
    using Bitmap = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S9 ;
    using Span = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S13 ;
    using Text = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S14 ;
    using DoubleLine = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S7 ;
    using FixedText = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S12 ;
    using FixedSpan = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S10 ;
    using Format = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S17 ;
    using Ratio = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S6 ;
    using MultiLine = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S15 ;
    using Point = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S3 ;
    using Frame = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S4 ;

} // namespace TypeDef

