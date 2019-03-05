/* struct TypeDefCore */

struct TypeDefCore
 {
  // types

  struct S1; // #Include 
  struct S2; // #PlacementPtr 
  struct S3; // #FormatPtr 
  struct S4; // #RefPtr 
  struct S5; // #Span 
  struct S6; // #Text 
  struct S7; // #Ratio 
  struct S8; // #OptRatio 
  struct S9; // #MultiLine 
  struct S10; // #OptAlign 
  struct S11; // #OneLine 
  struct S12; // #FixedText 
  struct S13; // #Link 
  struct S14; // #BorderPtr 
  struct S15; // #OptBool 
  struct S16; // #CellPtr 
  struct S17; // #Table 
  struct S18; // #OptULen 
  struct S19; // #Point 
  struct S20; // #OptPoint 
  struct S21; // #OptColor 
  struct S22; // #LinePtr 
  struct S23; // #BodyPtr 
  struct S24; // #Frame 
  struct S25; // #FrameList 
  struct S26; // #Cell 
  struct S27; // #OptCoord 
  struct S28; // #Border 
  struct S29; // #Item 
  struct S30; // #ItemList 
  struct S31; // #TextList 
  struct S32; // #Collapse 
  struct S33; // #Bitmap 
  struct S34; // #Section 
  struct S35; // #Defaults 
  struct S36; // #Scope 
  struct S37; // #PagePtr 
  struct S38; // #Page 
  struct S39; // #DoubleLine 
  struct S40; // #SingleLine 
  struct S41; // #FontPtr 
  struct S42; // #OptEffect 
  struct S43; // #Format 
  struct S44; // #OptInt 
  struct S45; // #Font 
  struct S46; // #Doc 

  using A1 = DDL::MapRange< S5 > ; // #TextLine
  using A2 = DDL::MapPolyPtr< S45 , S43 , S40 , S39 , S38 , S36 , S34 , S33 , S32 , S31 , S28 , S26 , S17 , S13 , S12 , S11 , S9 , S6 , S1 > ; // #Element
  using A3 = uint8 ; // #Align
  using A4 = uint8 ; // #Effect
  using A5 = sint32 ; // #Coord
  using A6 = uint32 ; // #VColor
  using A7 = uint8 ; // #Bool


  using XXX8226D906_9898_43AA_B1BE_D60B0A6E31C8 = TypeDefCore ;

  // structures

  struct S1
   {
    DDL::MapText file_name;

    struct Ext;
   };

  struct S2
   {
    DDL::MapText name;
    DDL::MapPolyPtr< S11 , S9 > ptr;

    struct Ext;
   };

  struct S3
   {
    DDL::MapText name;
    DDL::MapPtr< S43 > ptr;

    struct Ext;
   };

  struct S4
   {
    DDL::MapText name;
    DDL::MapPolyPtr< S13 , S38 > ptr;

    struct Ext;
   };

  struct S5
   {
    DDL::MapText body;
    S3 format;
    S4 ref;

    struct Ext;
   };

  struct S6
   {
    DDL::MapText name;
    A7 open;
    S2 placement;
    S3 format;
    DDL::MapRange< A1 > list;

    struct Ext;
   };

  struct S7
   {
    A5 a;
    A5 b;

    struct Ext;
   };

  struct S8
   {
    A7 def;
    S7 data;

    struct Ext;
   };

  struct S9
   {
    DDL::MapText name;
    A7 open;
    S8 line_space;
    S8 first_line_space;

    struct Ext;
   };

  struct S10
   {
    A7 def;
    A3 data;

    struct Ext;
   };

  struct S11
   {
    DDL::MapText name;
    A7 open;
    S10 align;

    struct Ext;
   };

  struct S12
   {
    DDL::MapText name;
    A7 open;
    S3 format;
    DDL::MapRange< A1 > list;

    struct Ext;
   };

  struct S13
   {
    DDL::MapText name;
    A7 open;
    DDL::MapPtr< S24 > frame;

    struct Ext;
   };

  struct S14
   {
    DDL::MapText name;
    DDL::MapPtr< S28 > ptr;

    struct Ext;
   };

  struct S15
   {
    A7 def;
    A7 data;

    struct Ext;
   };

  struct S16
   {
    DDL::MapText name;
    DDL::MapPtr< S26 > ptr;

    struct Ext;
   };

  struct S17
   {
    DDL::MapText name;
    A7 open;
    S14 border;
    S15 hard;
    DDL::MapRange< A5 > width;
    DDL::MapRange< S16 > table;

    struct Ext;
   };

  struct S18
   {
    A7 def;
    DDL::ulen_type data;

    struct Ext;
   };

  struct S19
   {
    A5 x;
    A5 y;

    struct Ext;
   };

  struct S20
   {
    A7 def;
    S19 data;

    struct Ext;
   };

  struct S21
   {
    A7 def;
    A6 data;

    struct Ext;
   };

  struct S22
   {
    DDL::MapText name;
    DDL::MapPolyPtr< S40 , S39 > ptr;

    struct Ext;
   };

  struct S23
   {
    DDL::MapText name;
    DDL::MapPolyPtr< S33 , S32 , S31 , S17 , S6 , S12 > ptr;

    struct Ext;
   };

  struct S24
   {
    S20 inner;
    S20 outer;
    S21 col;
    S22 line;
    S23 body;

    struct Ext;

    ulen ext;
   };

  struct S25
   {
    DDL::MapRange< S24 > list;
    DDL::ulen_type cur;

    struct Ext;
   };

  struct S26
   {
    DDL::MapText name;
    A7 open;
    S18 span_x;
    S18 span_y;
    S25 list;

    struct Ext;
   };

  struct S27
   {
    A7 def;
    A5 data;

    struct Ext;
   };

  struct S28
   {
    DDL::MapText name;
    A7 open;
    S27 space;
    S8 width;
    S21 line;

    struct Ext;
   };

  struct S29
   {
    DDL::MapText bullet;
    S25 list;

    struct Ext;
   };

  struct S30
   {
    DDL::MapRange< S29 > list;
    DDL::ulen_type cur;

    struct Ext;
   };

  struct S31
   {
    DDL::MapText name;
    A7 open;
    S3 format;
    S27 bullet_space;
    S27 item_space;
    S30 list;

    struct Ext;
   };

  struct S32
   {
    DDL::MapText name;
    A7 open;
    DDL::MapText title;
    S3 format;
    A7 openlist;
    S15 hide;
    S25 list;

    struct Ext;
   };

  struct S33
   {
    DDL::MapText name;
    DDL::MapText file_name;

    struct Ext;
   };

  struct S34
   {
    A7 open;
    DDL::MapText comment;
    DDL::MapRange< A2 > list;

    struct Ext;
   };

  struct S35
   {
    S20 inner;
    S20 outer;
    S27 bulletSpace;
    S27 itemSpace;
    DDL::MapPtr< S43 > collapseFormat;
    DDL::MapPtr< S43 > bulletFormat;
    DDL::MapPtr< S28 > border;
    DDL::MapPtr< S43 > textFormat;
    DDL::MapPtr< S43 > fixedFormat;
    DDL::MapPolyPtr< S11 , S9 > placement;

    struct Ext;
   };

  struct S36
   {
    DDL::MapText name;
    A7 open;
    S35 defs;
    DDL::MapRange< A2 > list;

    struct Ext;
   };

  struct S37
   {
    DDL::MapText name;
    DDL::MapPtr< S38 > ptr;

    struct Ext;
   };

  struct S38
   {
    DDL::MapText name;
    A7 open;
    DDL::MapText title;
    S21 back;
    S21 fore;
    S37 up;
    S37 prev;
    S37 next;
    S25 list;

    struct Ext;
   };

  struct S39
   {
    DDL::MapText name;
    A7 open;
    S8 width;
    S21 gray;
    S21 snow;

    struct Ext;
   };

  struct S40
   {
    DDL::MapText name;
    A7 open;
    S8 width;
    S21 line;

    struct Ext;
   };

  struct S41
   {
    DDL::MapText name;
    DDL::MapPtr< S45 > ptr;

    struct Ext;
   };

  struct S42
   {
    A7 def;
    A4 data;

    struct Ext;
   };

  struct S43
   {
    DDL::MapText name;
    A7 open;
    S41 font;
    S21 back;
    S21 fore;
    S42 effect;

    struct Ext;
   };

  struct S44
   {
    A7 def;
    DDL::sint_type data;

    struct Ext;
   };

  struct S45
   {
    DDL::MapText name;
    A7 open;
    DDL::MapText face;
    A5 size;
    S15 bold;
    S15 italic;
    S44 strength;

    struct Ext;
   };

  struct S46
   {
    DDL::MapText title;
    S21 back;
    S21 fore;
    S37 start;
    S35 defs;
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
    using Doc = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S46 ;
    using PagePtr = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S37 ;
    using OneLine = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S11 ;
    using ItemList = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S30 ;
    using Section = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S34 ;
    using RefPtr = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S4 ;
    using Cell = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S26 ;
    using Font = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S45 ;
    using Item = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S29 ;
    using Link = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S13 ;
    using SingleLine = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S40 ;
    using Page = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S38 ;
    using OptColor = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S21 ;
    using OptCoord = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S27 ;
    using PlacementPtr = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S2 ;
    using Bitmap = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S33 ;
    using Span = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S5 ;
    using OptAlign = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S10 ;
    using Text = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S6 ;
    using OptRatio = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S8 ;
    using Border = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S28 ;
    using OptPoint = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S20 ;
    using BorderPtr = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S14 ;
    using OptEffect = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S42 ;
    using DoubleLine = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S39 ;
    using OptInt = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S44 ;
    using Include = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S1 ;
    using BodyPtr = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S23 ;
    using FormatPtr = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S3 ;
    using LinePtr = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S22 ;
    using CellPtr = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S16 ;
    using TextList = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S31 ;
    using Defaults = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S35 ;
    using FixedText = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S12 ;
    using FrameList = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S25 ;
    using FontPtr = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S41 ;
    using OptBool = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S15 ;
    using Collapse = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S32 ;
    using Format = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S43 ;
    using OptULen = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S18 ;
    using Scope = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S36 ;
    using Table = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S17 ;
    using Ratio = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S7 ;
    using MultiLine = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S9 ;
    using Point = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S19 ;
    using Frame = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S24 ;

} // namespace TypeDef

