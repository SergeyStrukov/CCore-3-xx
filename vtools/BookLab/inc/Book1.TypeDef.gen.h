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
  struct S9; // #Table 
  struct S10; // #Border 
  struct S11; // #Cell 
  struct S12; // #Collapse 
  struct S13; // #ListItem 
  struct S14; // #TextList 
  struct S15; // #Bitmap 
  struct S16; // #FixedSpan 
  struct S17; // #FixedText 
  struct S18; // #Span 
  struct S19; // #Text 
  struct S20; // #MultiLine 
  struct S21; // #OneLine 
  struct S22; // #Format 
  struct S23; // #Font 

  using A1 = DDL::MapRange< S16 > ; // #Line
  using A2 = uint8 ; // #OneLine#Align
  using A3 = uint8 ; // #Format#Effect
  using A4 = sint32 ; // #Coord
  using A5 = uint32 ; // #VColor
  using A6 = uint8 ; // #Bool


  using XXX8226D906_9898_43AA_B1BE_D60B0A6E31C8 = TypeDefCore ;

  // structures

  struct S1
   {
    DDL::MapPtr< S5 > page;
    DDL::ulen_type frame_index;

    struct Ext;
   };

  struct S2
   {
    DDL::MapText title;
    DDL::MapPtr< S5 > start;
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
    DDL::MapPolyPtr< S19 , S17 , S15 , S14 , S12 , S9 > body;
    DDL::MapPolyPtr< S8 , S7 > line;
    S3 inner;
    S3 outer;
    A5 col;

    struct Ext;
   };

  struct S5
   {
    DDL::MapText name;
    DDL::MapRange< S4 > list;
    A5 back;
    A5 fore;
    DDL::MapPtr< S5 > up;
    DDL::MapPtr< S5 > prev;
    DDL::MapPtr< S5 > next;

    struct Ext;
   };

  struct S6
   {
    A4 a;
    A4 b;

    struct Ext;
   };

  struct S7
   {
    S6 width;
    A5 gray;
    A5 snow;

    struct Ext;
   };

  struct S8
   {
    S6 width;
    A5 line;

    struct Ext;
   };

  struct S9
   {
    DDL::MapRange< A4 > width;
    DDL::MapRange< DDL::MapRange< DDL::MapPtr< S11 > > > rows;
    DDL::MapPtr< S10 > border;
    A6 hard;

    struct Ext;
   };

  struct S10
   {
    A4 space;
    S6 width;
    A5 line;

    struct Ext;
   };

  struct S11
   {
    DDL::MapRange< S4 > list;
    DDL::ulen_type span_x;
    DDL::ulen_type span_y;

    struct Ext;
   };

  struct S12
   {
    DDL::MapText title;
    DDL::MapRange< S4 > list;
    DDL::MapPtr< S22 > collapse_fmt;
    A6 open;
    A6 hide;

    struct Ext;
   };

  struct S13
   {
    DDL::MapText bullet;
    DDL::MapRange< S4 > list;

    struct Ext;
   };

  struct S14
   {
    DDL::MapRange< S13 > list;
    DDL::MapPtr< S22 > bullet_fmt;
    A4 bullet_space;
    A4 item_space;

    struct Ext;
   };

  struct S15
   {
    DDL::MapText file_name;

    struct Ext;

    ulen ext;
   };

  struct S16
   {
    DDL::MapText body;
    DDL::MapPtr< S22 > fmt;
    DDL::MapPolyPtr< S1 , S5 > ref;

    struct Ext;
   };

  struct S17
   {
    DDL::MapRange< A1 > list;
    DDL::MapPtr< S22 > fmt;

    struct Ext;
   };

  struct S18
   {
    DDL::MapText body;
    DDL::MapPtr< S22 > fmt;
    DDL::MapPolyPtr< S1 , S5 > ref;

    struct Ext;
   };

  struct S19
   {
    DDL::MapRange< S18 > list;
    DDL::MapPtr< S22 > fmt;
    DDL::MapPolyPtr< S21 , S20 > placement;

    struct Ext;
   };

  struct S20
   {
    S6 line_space;
    S6 first_line_space;

    struct Ext;
   };

  struct S21
   {
    A2 align;

    using Align = XXX8226D906_9898_43AA_B1BE_D60B0A6E31C8::A2 ;

    struct Ext;
   };

  struct S22
   {
    DDL::MapPtr< S23 > font;
    A5 back;
    A5 fore;
    A3 effect;

    using Effect = XXX8226D906_9898_43AA_B1BE_D60B0A6E31C8::A3 ;

    struct Ext;
   };

  struct S23
   {
    DDL::MapText face;
    A4 size;
    A6 bold;
    A6 italic;
    DDL::sint_type strength;

    struct Ext;

    ulen ext;
   };

  // extra

 };

using XXX212CD757_09B3_4D89_BE20_65C1E4E5A819 = TypeDefCore ;

namespace TypeDef {

    using Bool = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::A6 ;
    using Line = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::A1 ;
    using VColor = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::A5 ;
    using Coord = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::A4 ;
    using OneLine = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S21 ;
    using Book = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S2 ;
    using Cell = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S11 ;
    using Font = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S23 ;
    using Link = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S1 ;
    using SingleLine = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S8 ;
    using Page = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S5 ;
    using Bitmap = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S15 ;
    using Span = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S18 ;
    using Text = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S19 ;
    using Border = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S10 ;
    using DoubleLine = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S7 ;
    using ListItem = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S13 ;
    using TextList = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S14 ;
    using FixedText = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S17 ;
    using FixedSpan = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S16 ;
    using Collapse = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S12 ;
    using Format = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S22 ;
    using Table = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S9 ;
    using Ratio = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S6 ;
    using MultiLine = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S20 ;
    using Point = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S3 ;
    using Frame = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S4 ;

} // namespace TypeDef

