/* struct TypeDefCore */

struct TypeDefCore
 {
  // types

  struct S1; // #Book 
  struct S2; // #Point 
  struct S3; // #Frame 
  struct S4; // #Page 
  struct S5; // #Ratio 
  struct S6; // #DoubleLine 
  struct S7; // #SingleLine 
  struct S8; // #Table 
  struct S9; // #Border 
  struct S10; // #Cell 
  struct S11; // #Collapse 
  struct S12; // #ListItem 
  struct S13; // #TextList 
  struct S14; // #Bitmap 
  struct S15; // #Span 
  struct S16; // #FixedText 
  struct S17; // #Text 
  struct S18; // #MultiLine 
  struct S19; // #OneLine 
  struct S20; // #Link 
  struct S21; // #Format 
  struct S22; // #Font 

  using A1 = DDL::MapRange< S15 > ; // #Line
  using A2 = uint8 ; // #OneLine#Align
  using A3 = uint8 ; // #Format#Effect
  using A4 = sint32 ; // #Coord
  using A5 = uint32 ; // #VColor
  using A6 = uint8 ; // #Bool


  using XXX8226D906_9898_43AA_B1BE_D60B0A6E31C8 = TypeDefCore ;

  // structures

  struct S1
   {
    DDL::MapText title;
    DDL::MapPtr< S4 > start;
    A5 back;
    A5 fore;

    struct Ext;
   };

  struct S2
   {
    A4 x;
    A4 y;

    struct Ext;
   };

  struct S3
   {
    DDL::MapPolyPtr< S17 , S16 , S14 , S13 , S11 , S8 > body;
    DDL::MapPolyPtr< S7 , S6 > line;
    S2 inner;
    S2 outer;
    A5 col;

    struct Ext;

    ulen ext;
   };

  struct S4
   {
    DDL::MapText name;
    DDL::MapRange< S3 > list;
    A5 back;
    A5 fore;
    DDL::MapPtr< S4 > up;
    DDL::MapPtr< S4 > prev;
    DDL::MapPtr< S4 > next;

    struct Ext;
   };

  struct S5
   {
    A4 a;
    A4 b;

    struct Ext;
   };

  struct S6
   {
    S5 width;
    A5 gray;
    A5 snow;

    struct Ext;
   };

  struct S7
   {
    S5 width;
    A5 line;

    struct Ext;
   };

  struct S8
   {
    DDL::MapRange< A4 > width;
    DDL::MapRange< DDL::MapRange< DDL::MapPtr< S10 > > > rows;
    DDL::MapPtr< S9 > border;
    A6 hard;

    struct Ext;
   };

  struct S9
   {
    A4 space;
    S5 width;
    A5 line;

    struct Ext;
   };

  struct S10
   {
    DDL::MapRange< S3 > list;
    DDL::ulen_type span_x;
    DDL::ulen_type span_y;

    struct Ext;
   };

  struct S11
   {
    DDL::MapText title;
    DDL::MapRange< S3 > list;
    DDL::MapPtr< S21 > collapse_fmt;
    A6 open;
    A6 hide;

    struct Ext;
   };

  struct S12
   {
    DDL::MapText bullet;
    DDL::MapRange< S3 > list;

    struct Ext;
   };

  struct S13
   {
    DDL::MapRange< S12 > list;
    DDL::MapPtr< S21 > bullet_fmt;
    A4 bullet_space;
    A4 item_space;

    struct Ext;
   };

  struct S14
   {
    DDL::MapText file_name;

    struct Ext;

    ulen ext;
   };

  struct S15
   {
    DDL::MapText body;
    DDL::MapPtr< S21 > fmt;
    DDL::MapPolyPtr< S20 , S4 > ref;

    struct Ext;
   };

  struct S16
   {
    DDL::MapRange< A1 > list;
    DDL::MapPtr< S21 > fmt;

    struct Ext;
   };

  struct S17
   {
    DDL::MapRange< S15 > list;
    DDL::MapPtr< S21 > fmt;
    DDL::MapPolyPtr< S19 , S18 > placement;

    struct Ext;
   };

  struct S18
   {
    S5 line_space;
    S5 first_line_space;

    struct Ext;
   };

  struct S19
   {
    A2 align;

    using Align = XXX8226D906_9898_43AA_B1BE_D60B0A6E31C8::A2 ;

    struct Ext;
   };

  struct S20
   {
    DDL::MapPtr< S4 > page;
    DDL::MapRange< DDL::ulen_type > index_list;

    struct Ext;
   };

  struct S21
   {
    DDL::MapPtr< S22 > font;
    A5 back;
    A5 fore;
    A3 effect;

    using Effect = XXX8226D906_9898_43AA_B1BE_D60B0A6E31C8::A3 ;

    struct Ext;
   };

  struct S22
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
    using OneLine = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S19 ;
    using Book = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S1 ;
    using Cell = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S10 ;
    using Font = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S22 ;
    using Link = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S20 ;
    using SingleLine = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S7 ;
    using Page = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S4 ;
    using Bitmap = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S14 ;
    using Span = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S15 ;
    using Text = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S17 ;
    using Border = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S9 ;
    using DoubleLine = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S6 ;
    using ListItem = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S12 ;
    using TextList = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S13 ;
    using FixedText = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S16 ;
    using Collapse = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S11 ;
    using Format = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S21 ;
    using Table = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S8 ;
    using Ratio = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S5 ;
    using MultiLine = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S18 ;
    using Point = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S2 ;
    using Frame = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S3 ;

} // namespace TypeDef

