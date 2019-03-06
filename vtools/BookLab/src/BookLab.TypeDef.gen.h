/* struct TypeDefCore */

struct TypeDefCore
 {
  // types

  struct S1; // #Extern 
  struct S2; // #Include 
  struct S3; // #PlacementPtr 
  struct S4; // #FormatPtr 
  struct S5; // #RefPtr 
  struct S6; // #Span 
  struct S7; // #Text 
  struct S8; // #Ratio 
  struct S9; // #OptRatio 
  struct S10; // #MultiLine 
  struct S11; // #OptAlign 
  struct S12; // #OneLine 
  struct S13; // #FixedText 
  struct S14; // #Link 
  struct S15; // #BorderPtr 
  struct S16; // #OptBool 
  struct S17; // #CellPtr 
  struct S18; // #Table 
  struct S19; // #OptULen 
  struct S20; // #Point 
  struct S21; // #OptPoint 
  struct S22; // #OptColor 
  struct S23; // #LinePtr 
  struct S24; // #BodyPtr 
  struct S25; // #Frame 
  struct S26; // #FrameList 
  struct S27; // #Cell 
  struct S28; // #OptCoord 
  struct S29; // #Border 
  struct S30; // #Item 
  struct S31; // #ItemList 
  struct S32; // #TextList 
  struct S33; // #Collapse 
  struct S34; // #Bitmap 
  struct S35; // #Section 
  struct S36; // #Defaults 
  struct S37; // #Scope 
  struct S38; // #PagePtr 
  struct S39; // #Page 
  struct S40; // #DoubleLine 
  struct S41; // #SingleLine 
  struct S42; // #FontPtr 
  struct S43; // #OptEffect 
  struct S44; // #Format 
  struct S45; // #OptInt 
  struct S46; // #Font 
  struct S47; // #Doc 

  using A1 = DDL::MapRange< S6 > ; // #TextLine
  using A2 = DDL::MapPolyPtr< S46 , S44 , S41 , S40 , S39 , S37 , S35 , S34 , S33 , S32 , S29 , S27 , S18 , S14 , S13 , S12 , S10 , S7 , S2 , S1 > ; // #Element
  using A3 = uint8 ; // #Align
  using A4 = uint8 ; // #Effect
  using A5 = sint32 ; // #Coord
  using A6 = uint32 ; // #VColor
  using A7 = uint8 ; // #Bool


  using XXX8226D906_9898_43AA_B1BE_D60B0A6E31C8 = TypeDefCore ;

  // structures

  struct S1
   {
    DDL::MapPolyPtr< S46 , S44 , S41 , S40 , S39 , S33 , S32 , S29 , S27 , S18 , S14 , S13 , S12 , S10 , S7 > ptr;

    struct Ext;
   };

  struct S2
   {
    DDL::MapText file_name;

    struct Ext;
   };

  struct S3
   {
    DDL::MapText name;
    DDL::MapPolyPtr< S12 , S10 > ptr;

    struct Ext;
   };

  struct S4
   {
    DDL::MapText name;
    DDL::MapPtr< S44 > ptr;

    struct Ext;
   };

  struct S5
   {
    DDL::MapText name;
    DDL::MapPolyPtr< S14 , S39 > ptr;

    struct Ext;
   };

  struct S6
   {
    DDL::MapText body;
    S4 format;
    S5 ref;

    struct Ext;
   };

  struct S7
   {
    DDL::MapText name;
    A7 open;
    S3 placement;
    S4 format;
    DDL::MapRange< A1 > list;

    struct Ext;
   };

  struct S8
   {
    A5 a;
    A5 b;

    struct Ext;
   };

  struct S9
   {
    A7 def;
    S8 data;

    struct Ext;
   };

  struct S10
   {
    DDL::MapText name;
    A7 open;
    S9 line_space;
    S9 first_line_space;

    struct Ext;
   };

  struct S11
   {
    A7 def;
    A3 data;

    struct Ext;
   };

  struct S12
   {
    DDL::MapText name;
    A7 open;
    S11 align;

    struct Ext;
   };

  struct S13
   {
    DDL::MapText name;
    A7 open;
    S4 format;
    DDL::MapRange< A1 > list;

    struct Ext;
   };

  struct S14
   {
    DDL::MapText name;
    A7 open;
    DDL::MapPtr< S25 > frame;

    struct Ext;
   };

  struct S15
   {
    DDL::MapText name;
    DDL::MapPtr< S29 > ptr;

    struct Ext;
   };

  struct S16
   {
    A7 def;
    A7 data;

    struct Ext;
   };

  struct S17
   {
    DDL::MapText name;
    DDL::MapPtr< S27 > ptr;

    struct Ext;
   };

  struct S18
   {
    DDL::MapText name;
    A7 open;
    S15 border;
    S16 hard;
    DDL::MapRange< A5 > width;
    DDL::MapRange< S17 > table;

    struct Ext;
   };

  struct S19
   {
    A7 def;
    DDL::ulen_type data;

    struct Ext;
   };

  struct S20
   {
    A5 x;
    A5 y;

    struct Ext;
   };

  struct S21
   {
    A7 def;
    S20 data;

    struct Ext;
   };

  struct S22
   {
    A7 def;
    A6 data;

    struct Ext;
   };

  struct S23
   {
    DDL::MapText name;
    DDL::MapPolyPtr< S41 , S40 > ptr;

    struct Ext;
   };

  struct S24
   {
    DDL::MapText name;
    DDL::MapPolyPtr< S34 , S33 , S32 , S18 , S7 , S13 > ptr;

    struct Ext;
   };

  struct S25
   {
    S21 inner;
    S21 outer;
    S22 col;
    S23 line;
    S24 body;

    struct Ext;

    ulen ext;
   };

  struct S26
   {
    DDL::MapRange< S25 > list;
    DDL::ulen_type cur;

    struct Ext;
   };

  struct S27
   {
    DDL::MapText name;
    A7 open;
    S19 span_x;
    S19 span_y;
    S26 list;

    struct Ext;
   };

  struct S28
   {
    A7 def;
    A5 data;

    struct Ext;
   };

  struct S29
   {
    DDL::MapText name;
    A7 open;
    S28 space;
    S9 width;
    S22 line;

    struct Ext;
   };

  struct S30
   {
    DDL::MapText bullet;
    S26 list;

    struct Ext;
   };

  struct S31
   {
    DDL::MapRange< S30 > list;
    DDL::ulen_type cur;

    struct Ext;
   };

  struct S32
   {
    DDL::MapText name;
    A7 open;
    S4 format;
    S28 bullet_space;
    S28 item_space;
    S21 frame_inner;
    S21 frame_outer;
    S4 text_format;
    S3 placement;
    S31 list;

    struct Ext;
   };

  struct S33
   {
    DDL::MapText name;
    A7 open;
    DDL::MapText title;
    S4 format;
    A7 openlist;
    S16 hide;
    S26 list;

    struct Ext;
   };

  struct S34
   {
    DDL::MapText name;
    DDL::MapText file_name;

    struct Ext;
   };

  struct S35
   {
    A7 open;
    DDL::MapText comment;
    DDL::MapRange< A2 > list;

    struct Ext;
   };

  struct S36
   {
    S21 inner;
    S21 outer;
    S28 bulletSpace;
    S28 itemSpace;
    DDL::MapPtr< S44 > collapseFormat;
    DDL::MapPtr< S44 > bulletFormat;
    DDL::MapPtr< S29 > border;
    DDL::MapPtr< S44 > textFormat;
    DDL::MapPtr< S44 > fixedFormat;
    DDL::MapPolyPtr< S12 , S10 > placement;

    struct Ext;
   };

  struct S37
   {
    DDL::MapText name;
    A7 open;
    S36 defs;
    DDL::MapRange< A2 > list;

    struct Ext;
   };

  struct S38
   {
    DDL::MapText name;
    DDL::MapPtr< S39 > ptr;

    struct Ext;
   };

  struct S39
   {
    DDL::MapText name;
    A7 open;
    DDL::MapText title;
    S22 back;
    S22 fore;
    S38 up;
    S38 prev;
    S38 next;
    S26 list;

    struct Ext;
   };

  struct S40
   {
    DDL::MapText name;
    A7 open;
    S9 width;
    S22 gray;
    S22 snow;

    struct Ext;
   };

  struct S41
   {
    DDL::MapText name;
    A7 open;
    S9 width;
    S22 line;

    struct Ext;
   };

  struct S42
   {
    DDL::MapText name;
    DDL::MapPtr< S46 > ptr;

    struct Ext;
   };

  struct S43
   {
    A7 def;
    A4 data;

    struct Ext;
   };

  struct S44
   {
    DDL::MapText name;
    A7 open;
    S42 font;
    S22 back;
    S22 fore;
    S43 effect;

    struct Ext;
   };

  struct S45
   {
    A7 def;
    DDL::sint_type data;

    struct Ext;
   };

  struct S46
   {
    DDL::MapText name;
    A7 open;
    DDL::MapText face;
    A5 size;
    S16 bold;
    S16 italic;
    S45 strength;

    struct Ext;
   };

  struct S47
   {
    DDL::MapText title;
    S22 back;
    S22 fore;
    S38 start;
    S36 defs;
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
    using Doc = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S47 ;
    using PagePtr = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S38 ;
    using OneLine = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S12 ;
    using ItemList = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S31 ;
    using Extern = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S1 ;
    using Section = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S35 ;
    using RefPtr = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S5 ;
    using Cell = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S27 ;
    using Font = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S46 ;
    using Item = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S30 ;
    using Link = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S14 ;
    using SingleLine = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S41 ;
    using Page = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S39 ;
    using OptColor = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S22 ;
    using OptCoord = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S28 ;
    using PlacementPtr = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S3 ;
    using Bitmap = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S34 ;
    using Span = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S6 ;
    using OptAlign = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S11 ;
    using Text = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S7 ;
    using OptRatio = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S9 ;
    using Border = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S29 ;
    using OptPoint = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S21 ;
    using BorderPtr = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S15 ;
    using OptEffect = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S43 ;
    using DoubleLine = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S40 ;
    using OptInt = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S45 ;
    using Include = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S2 ;
    using BodyPtr = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S24 ;
    using FormatPtr = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S4 ;
    using LinePtr = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S23 ;
    using CellPtr = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S17 ;
    using TextList = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S32 ;
    using Defaults = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S36 ;
    using FixedText = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S13 ;
    using FrameList = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S26 ;
    using FontPtr = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S42 ;
    using OptBool = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S16 ;
    using Collapse = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S33 ;
    using Format = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S44 ;
    using OptULen = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S19 ;
    using Scope = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S37 ;
    using Table = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S18 ;
    using Ratio = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S8 ;
    using MultiLine = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S10 ;
    using Point = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S20 ;
    using Frame = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S25 ;

} // namespace TypeDef

