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
  struct S9; // #FixedSpan 
  struct S10; // #FixedText 
  struct S11; // #Span 
  struct S12; // #Text 
  struct S13; // #MultiLine 
  struct S14; // #OneLine 
  struct S15; // #Format 
  struct S16; // #Font 

  using A1 = DDL::MapRange< DDL::MapRange< uint32 > > ; // #Bitmap
  using A2 = DDL::MapRange< S9 > ; // #Line
  using A3 = uint8 ; // #OneLine#Align
  using A4 = uint8 ; // #Format#Effect
  using A5 = sint16 ; // #Coord
  using A6 = uint32 ; // #VColor
  using A7 = uint8 ; // #Bool


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
    A6 back;
    A6 fore;

    struct Ext;
   };

  struct S3
   {
    A5 x;
    A5 y;

    struct Ext;
   };

  struct S4
   {
    DDL::MapPolyPtr< S12 , S10 , A1 > body;
    DDL::MapPolyPtr< S8 , S7 > line;
    S3 inner;
    S3 outer;
    A6 col;

    struct Ext;
   };

  struct S5
   {
    DDL::MapText name;
    DDL::MapRange< S4 > list;
    A6 back;
    A6 fore;
    DDL::MapPtr< S5 > top;
    DDL::MapPtr< S5 > prev;
    DDL::MapPtr< S5 > next;

    struct Ext;
   };

  struct S6
   {
    A5 a;
    A5 b;

    struct Ext;
   };

  struct S7
   {
    S6 width;
    A6 gray;
    A6 snow;

    struct Ext;
   };

  struct S8
   {
    S6 width;
    A6 line;

    struct Ext;
   };

  struct S9
   {
    DDL::MapText body;
    DDL::MapPtr< S15 > fmt;
    DDL::MapPolyPtr< S1 , S5 > ref;

    struct Ext;
   };

  struct S10
   {
    DDL::MapRange< A2 > list;
    DDL::MapPtr< S15 > fmt;

    struct Ext;
   };

  struct S11
   {
    DDL::MapText body;
    DDL::MapPtr< S15 > fmt;
    DDL::MapPolyPtr< S1 , S5 > ref;

    struct Ext;
   };

  struct S12
   {
    DDL::MapRange< S11 > list;
    DDL::MapPtr< S15 > fmt;
    DDL::MapPolyPtr< S14 , S13 > placement;

    struct Ext;
   };

  struct S13
   {
    S6 line_space;
    S6 first_line_space;

    struct Ext;
   };

  struct S14
   {
    A3 align;

    using Align = XXX8226D906_9898_43AA_B1BE_D60B0A6E31C8::A3 ;

    struct Ext;
   };

  struct S15
   {
    DDL::MapPtr< S16 > font;
    A6 back;
    A6 fore;
    A4 effect;

    using Effect = XXX8226D906_9898_43AA_B1BE_D60B0A6E31C8::A4 ;

    struct Ext;
   };

  struct S16
   {
    DDL::MapText face;
    A5 size;
    A7 bold;
    A7 italic;
    DDL::sint_type strength;

    struct Ext;

    ulen ext;
   };

  // extra

 };

using XXX212CD757_09B3_4D89_BE20_65C1E4E5A819 = TypeDefCore ;

namespace TypeDef {

    using Bool = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::A7 ;
    using Line = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::A2 ;
    using Bitmap = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::A1 ;
    using VColor = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::A6 ;
    using Coord = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::A5 ;
    using OneLine = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S14 ;
    using Book = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S2 ;
    using Font = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S16 ;
    using Link = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S1 ;
    using SingleLine = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S8 ;
    using Page = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S5 ;
    using Span = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S11 ;
    using Text = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S12 ;
    using DoubleLine = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S7 ;
    using FixedText = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S10 ;
    using FixedSpan = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S9 ;
    using Format = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S15 ;
    using Ratio = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S6 ;
    using MultiLine = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S13 ;
    using Point = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S3 ;
    using Frame = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S4 ;

} // namespace TypeDef

