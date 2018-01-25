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
  struct S9; // #ListItem 
  struct S10; // #TextList 
  struct S11; // #Bitmap 
  struct S12; // #FixedSpan 
  struct S13; // #FixedText 
  struct S14; // #Span 
  struct S15; // #Text 
  struct S16; // #MultiLine 
  struct S17; // #OneLine 
  struct S18; // #Format 
  struct S19; // #Font 

  using A1 = DDL::MapRange< S12 > ; // #Line
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
    DDL::MapPolyPtr< S15 , S13 , S11 , S10 > body;
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
    DDL::MapPtr< S5 > top;
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
    DDL::MapText bullet;
    DDL::MapRange< S4 > list;

    struct Ext;
   };

  struct S10
   {
    DDL::MapRange< S9 > list;
    DDL::MapPtr< S18 > bullet_fmt;
    A4 bullet_space;
    A4 item_space;

    struct Ext;
   };

  struct S11
   {
    DDL::MapText file_name;

    struct Ext;

    ulen ext;
   };

  struct S12
   {
    DDL::MapText body;
    DDL::MapPtr< S18 > fmt;
    DDL::MapPolyPtr< S1 , S5 > ref;

    struct Ext;
   };

  struct S13
   {
    DDL::MapRange< A1 > list;
    DDL::MapPtr< S18 > fmt;

    struct Ext;
   };

  struct S14
   {
    DDL::MapText body;
    DDL::MapPtr< S18 > fmt;
    DDL::MapPolyPtr< S1 , S5 > ref;

    struct Ext;
   };

  struct S15
   {
    DDL::MapRange< S14 > list;
    DDL::MapPtr< S18 > fmt;
    DDL::MapPolyPtr< S17 , S16 > placement;

    struct Ext;
   };

  struct S16
   {
    S6 line_space;
    S6 first_line_space;

    struct Ext;
   };

  struct S17
   {
    A2 align;

    using Align = XXX8226D906_9898_43AA_B1BE_D60B0A6E31C8::A2 ;

    struct Ext;
   };

  struct S18
   {
    DDL::MapPtr< S19 > font;
    A5 back;
    A5 fore;
    A3 effect;

    using Effect = XXX8226D906_9898_43AA_B1BE_D60B0A6E31C8::A3 ;

    struct Ext;
   };

  struct S19
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
    using OneLine = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S17 ;
    using Book = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S2 ;
    using Font = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S19 ;
    using Link = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S1 ;
    using SingleLine = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S8 ;
    using Page = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S5 ;
    using Bitmap = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S11 ;
    using Span = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S14 ;
    using Text = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S15 ;
    using DoubleLine = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S7 ;
    using ListItem = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S9 ;
    using TextList = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S10 ;
    using FixedText = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S13 ;
    using FixedSpan = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S12 ;
    using Format = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S18 ;
    using Ratio = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S6 ;
    using MultiLine = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S16 ;
    using Point = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S3 ;
    using Frame = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S4 ;

} // namespace TypeDef

