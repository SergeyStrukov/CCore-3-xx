/* struct TypeDefCore */

struct TypeDefCore
 {
  // types

  struct S1; // #PlacementPtr 
  struct S2; // #FormatPtr 
  struct S3; // #RefPtr 
  struct S4; // #Span 
  struct S5; // #Text 
  struct S6; // #Ratio 
  struct S7; // #OptRatio 
  struct S8; // #MultiLine 
  struct S9; // #OptAlign 
  struct S10; // #OneLine 
  struct S11; // #FixedText 
  struct S12; // #Link 
  struct S13; // #BorderPtr 
  struct S14; // #OptBool 
  struct S15; // #CellPtr 
  struct S16; // #Table 
  struct S17; // #OptULen 
  struct S18; // #Point 
  struct S19; // #OptPoint 
  struct S20; // #OptColor 
  struct S21; // #LinePtr 
  struct S22; // #BodyPtr 
  struct S23; // #Frame 
  struct S24; // #FrameList 
  struct S25; // #Cell 
  struct S26; // #OptCoord 
  struct S27; // #Border 
  struct S28; // #Item 
  struct S29; // #ItemList 
  struct S30; // #TextList 
  struct S31; // #Collapse 
  struct S32; // #Bitmap 
  struct S33; // #Section 
  struct S34; // #Defaults 
  struct S35; // #Scope 
  struct S36; // #PagePtr 
  struct S37; // #Page 
  struct S38; // #DoubleLine 
  struct S39; // #SingleLine 
  struct S40; // #FontPtr 
  struct S41; // #OptEffect 
  struct S42; // #Format 
  struct S43; // #OptInt 
  struct S44; // #Font 
  struct S45; // #Doc 

  using A1 = DDL::MapRange< S4 > ; // #TextLine
  using A2 = DDL::MapPolyPtr< S44 , S42 , S39 , S38 , S37 , S35 , S33 , S32 , S31 , S30 , S27 , S25 , S16 , S12 , S11 , S10 , S8 , S5 > ; // #Element
  using A3 = uint8 ; // #Align
  using A4 = uint8 ; // #Effect
  using A5 = sint32 ; // #Coord
  using A6 = uint32 ; // #VColor
  using A7 = uint8 ; // #Bool


  using XXX8226D906_9898_43AA_B1BE_D60B0A6E31C8 = TypeDefCore ;

  // structures

  struct S1
   {
    DDL::MapText name;
    DDL::MapPolyPtr< S10 , S8 > ptr;

    struct Ext;
   };

  struct S2
   {
    DDL::MapText name;
    DDL::MapPtr< S42 > ptr;

    struct Ext;
   };

  struct S3
   {
    DDL::MapText name;
    DDL::MapPolyPtr< S12 , S37 > ptr;

    struct Ext;
   };

  struct S4
   {
    DDL::MapText body;
    S2 format;
    S3 ref;

    struct Ext;
   };

  struct S5
   {
    DDL::MapText name;
    A7 open;
    S1 placement;
    S2 format;
    DDL::MapRange< S4 > list;

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
    A7 def;
    S6 data;

    struct Ext;
   };

  struct S8
   {
    DDL::MapText name;
    A7 open;
    S7 line_space;
    S7 first_line_space;

    struct Ext;
   };

  struct S9
   {
    A7 def;
    A3 data;

    struct Ext;
   };

  struct S10
   {
    DDL::MapText name;
    A7 open;
    S9 align;

    struct Ext;
   };

  struct S11
   {
    DDL::MapText name;
    A7 open;
    S2 format;
    DDL::MapRange< A1 > list;

    struct Ext;
   };

  struct S12
   {
    DDL::MapText name;
    A7 open;
    DDL::MapPtr< S23 > frame;

    struct Ext;
   };

  struct S13
   {
    DDL::MapText name;
    DDL::MapPtr< S27 > ptr;

    struct Ext;
   };

  struct S14
   {
    A7 def;
    A7 data;

    struct Ext;
   };

  struct S15
   {
    DDL::MapText name;
    DDL::MapPtr< S25 > ptr;

    struct Ext;
   };

  struct S16
   {
    DDL::MapText name;
    A7 open;
    S13 border;
    S14 hard;
    DDL::MapRange< A5 > width;
    DDL::MapRange< S15 > table;

    struct Ext;
   };

  struct S17
   {
    A7 def;
    DDL::ulen_type data;

    struct Ext;
   };

  struct S18
   {
    A5 x;
    A5 y;

    struct Ext;
   };

  struct S19
   {
    A7 def;
    S18 data;

    struct Ext;
   };

  struct S20
   {
    A7 def;
    A6 data;

    struct Ext;
   };

  struct S21
   {
    DDL::MapText name;
    DDL::MapPolyPtr< S39 , S38 > ptr;

    struct Ext;
   };

  struct S22
   {
    DDL::MapText name;
    DDL::MapPolyPtr< S32 , S31 , S30 , S16 , S5 , S11 > ptr;

    struct Ext;
   };

  struct S23
   {
    S19 inner;
    S19 outer;
    S20 col;
    S21 line;
    S22 body;

    struct Ext;

    ulen ext;
   };

  struct S24
   {
    DDL::MapRange< S23 > list;
    DDL::ulen_type cur;

    struct Ext;
   };

  struct S25
   {
    DDL::MapText name;
    A7 open;
    S17 span_x;
    S17 span_y;
    S24 list;

    struct Ext;
   };

  struct S26
   {
    A7 def;
    A5 data;

    struct Ext;
   };

  struct S27
   {
    DDL::MapText name;
    A7 open;
    S26 space;
    S7 width;
    S20 line;

    struct Ext;
   };

  struct S28
   {
    DDL::MapText bullet;
    S24 list;

    struct Ext;
   };

  struct S29
   {
    DDL::MapRange< S28 > list;
    DDL::ulen_type cur;

    struct Ext;
   };

  struct S30
   {
    DDL::MapText name;
    A7 open;
    S2 format;
    S26 bullet_space;
    S26 item_space;
    S29 list;

    struct Ext;
   };

  struct S31
   {
    DDL::MapText name;
    A7 open;
    DDL::MapText title;
    S2 format;
    A7 openlist;
    S14 hide;
    S24 list;

    struct Ext;
   };

  struct S32
   {
    DDL::MapText name;
    DDL::MapText file_name;

    struct Ext;
   };

  struct S33
   {
    A7 open;
    DDL::MapText comment;
    DDL::MapRange< A2 > list;

    struct Ext;
   };

  struct S34
   {
    S19 inner;
    S19 outer;
    S26 bulletSpace;
    S26 itemSpace;
    DDL::MapPtr< S39 > singleLine;
    DDL::MapPtr< S38 > doubleLine;
    DDL::MapPtr< S42 > collapseFormat;
    DDL::MapPtr< S42 > bulletFormat;
    DDL::MapPtr< S27 > border;
    DDL::MapPtr< S42 > textFormat;
    DDL::MapPtr< S42 > fixedFormat;
    DDL::MapPolyPtr< S10 , S8 > placement;

    struct Ext;
   };

  struct S35
   {
    DDL::MapText name;
    A7 open;
    S34 defs;
    DDL::MapRange< A2 > list;

    struct Ext;
   };

  struct S36
   {
    DDL::MapText name;
    DDL::MapPtr< S37 > ptr;

    struct Ext;
   };

  struct S37
   {
    DDL::MapText name;
    A7 open;
    DDL::MapText title;
    S20 back;
    S20 fore;
    S36 up;
    S36 prev;
    S36 next;
    S24 list;

    struct Ext;
   };

  struct S38
   {
    DDL::MapText name;
    A7 open;
    S7 width;
    S20 gray;
    S20 snow;

    struct Ext;
   };

  struct S39
   {
    DDL::MapText name;
    A7 open;
    S7 width;
    S20 line;

    struct Ext;
   };

  struct S40
   {
    DDL::MapText name;
    DDL::MapPtr< S44 > ptr;

    struct Ext;
   };

  struct S41
   {
    A7 def;
    A4 data;

    struct Ext;
   };

  struct S42
   {
    DDL::MapText name;
    A7 open;
    S40 font;
    S20 back;
    S20 fore;
    S41 effect;

    struct Ext;
   };

  struct S43
   {
    A7 def;
    DDL::sint_type data;

    struct Ext;
   };

  struct S44
   {
    DDL::MapText name;
    A7 open;
    DDL::MapText face;
    A5 size;
    S14 bold;
    S14 italic;
    S43 strength;

    struct Ext;
   };

  struct S45
   {
    DDL::MapText title;
    S20 back;
    S20 fore;
    S36 start;
    S34 defs;
    DDL::MapRange< A2 > list;

    struct Ext;
   };

  // extra

 };

using XXX212CD757_09B3_4D89_BE20_65C1E4E5A819 = TypeDefCore ;

namespace TypeDef {

    using Effect = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::A4 ;
    using Bool = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::A7 ;
    using Element = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::A2 ;
    using TextLine = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::A1 ;
    using VColor = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::A6 ;
    using Align = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::A3 ;
    using Coord = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::A5 ;
    using Doc = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S45 ;
    using PagePtr = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S36 ;
    using OneLine = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S10 ;
    using ItemList = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S29 ;
    using Section = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S33 ;
    using RefPtr = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S3 ;
    using Cell = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S25 ;
    using Font = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S44 ;
    using Item = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S28 ;
    using Link = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S12 ;
    using SingleLine = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S39 ;
    using Page = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S37 ;
    using OptColor = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S20 ;
    using OptCoord = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S26 ;
    using PlacementPtr = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S1 ;
    using Bitmap = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S32 ;
    using Span = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S4 ;
    using OptAlign = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S9 ;
    using Text = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S5 ;
    using OptRatio = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S7 ;
    using Border = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S27 ;
    using OptPoint = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S19 ;
    using BorderPtr = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S13 ;
    using OptEffect = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S41 ;
    using DoubleLine = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S38 ;
    using OptInt = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S43 ;
    using BodyPtr = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S22 ;
    using FormatPtr = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S2 ;
    using LinePtr = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S21 ;
    using CellPtr = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S15 ;
    using TextList = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S30 ;
    using Defaults = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S34 ;
    using FixedText = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S11 ;
    using FrameList = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S24 ;
    using FontPtr = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S40 ;
    using OptBool = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S14 ;
    using Collapse = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S31 ;
    using Format = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S42 ;
    using OptULen = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S17 ;
    using Scope = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S35 ;
    using Table = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S16 ;
    using Ratio = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S6 ;
    using MultiLine = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S8 ;
    using Point = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S18 ;
    using Frame = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S23 ;

} // namespace TypeDef

