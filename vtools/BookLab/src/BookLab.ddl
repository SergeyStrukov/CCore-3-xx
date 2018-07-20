/* BookLab.ddl */
//----------------------------------------------------------------------------------------
//
//  Project: BookLab 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

//--- basic types ------------------------------------------------------------------------

type Bool = uint8 ;

Bool True = 1 ;

Bool False = 0 ;

type VColor = uint32 ;

type Coord = sint32 ;

type Effect = uint8 ;

type Align = uint8 ;

struct Point
 {
  Coord x;
  Coord y;
 };
 
struct Ratio
 {
  Coord a;
  Coord b;
 }; 

//--- Opts -------------------------------------------------------------------------------

struct OptColor
 {
  Bool def;
  VColor data;
 };
 
struct OptPoint
 {
  Bool def;
  Point data;
 };
 
struct OptCoord
 {
  Bool def;
  Coord data;
 };  
 
struct OptRatio
 {
  Bool def;
  Ratio data;
 }; 
 
struct OptEffect
 {
  Bool def;
  Effect data;
 };
 
struct OptAlign
 {
  Bool def;
  Align data;
 };  
 
struct OptBool
 {
  Bool def;
  Bool data;
 };
  
struct OptInt
 {
  Bool def;
  int data;
 };
 
struct OptULen
 {
  Bool def;
  ulen data;
 }; 
 
//--- Ptrs ------------------------------------------------------------------------------- 
 
struct PagePtr
 {
  text name;
  Page *ptr;
 }; 
 
struct FontPtr
 {
  text name;
  Font *ptr;
 };
 
struct LinePtr
 {
  text name;
  {SingleLine,DoubleLine} *ptr;
 };  
 
struct BodyPtr
 {
  text name;
  {Bitmap,Collapse,TextList,Table,Text,FixedText} *ptr;
 }; 
 
struct FormatPtr
 {
  text name;
  Format *ptr;
 };
 
struct BorderPtr
 {
  text name;
  Border *ptr;
 };
 
struct CellPtr
 {
  text name;
  Cell *ptr;
 };
 
struct RefPtr
 {
  text name;
  {Link,Page} *ptr;
 };
 
struct PlacementPtr
 {
  text name;
  {OneLine,MultiLine} *ptr;
 };     
 
//--- Doc --------------------------------------------------------------------------------
 
struct Defaults
 {
  OptPoint inner;
  OptPoint outer;
  OptCoord bulletSpace;
  OptCoord itemSpace;

  SingleLine *singleLine;
  DoubleLine *doubleLine;
  Format *collapseFormat;
  Format *bulletFormat;
  Border *border;
  Format *textFormat;
  Format *fixedFormat;
  {OneLine,MultiLine} *placement;
 }; 

type Element = {Font,Format,SingleLine,DoubleLine,Page,Scope,Section,Bitmap,Collapse,TextList,Table,Text,FixedText} * ;

struct Doc
 {
  text title;
  OptColor back;
  OptColor fore;
  PagePtr start;
  Defaults defs;
  
  Element[] list;
 };

//--- Meat -------------------------------------------------------------------------------

struct Font
 {
  text name;
  Bool open;
  
  text face;
  Coord size;
  OptBool bold;
  OptBool italic;
  OptInt strength;
 };

struct Format
 {
  text name;
  Bool open;
  
  FontPtr font;
  OptColor back;
  OptColor fore;
  OptEffect effect;  
 };

struct SingleLine
 {
  text name;
  Bool open;
  
  OptRatio width;
  OptColor line;
 };

struct DoubleLine
 {
  text name;
  Bool open;
  
  OptRatio width;
  OptColor gray;
  OptColor snow;
 };

struct Frame
 {
  OptPoint inner;
  OptPoint outer;
  OptColor col;
  
  LinePtr line;
  BodyPtr body;
 };

struct FrameList
 {
  Frame[] list;
  ulen cur;
 };

struct Page
 {
  text name;
  Bool open;
  
  text title;
  OptColor back;
  OptColor fore;
  
  PagePtr up;
  PagePtr prev;
  PagePtr next;
  
  FrameList list;
 };

struct Scope
 {
  text name;
  Bool open;
  
  Defaults defs;
  
  Element[] list;
 };

struct Section
 {
  Bool open;
  
  text comment;
  
  Element[] list;
 };

struct Bitmap
 {
  text name;
  
  text file_name;
 };

struct Collapse
 {
  text name;
  Bool open;
  
  text title;
  FormatPtr format;
  Bool openlist;
  OptBool hide;
  
  FrameList list;
 };

struct Item
 {
  text bullet;
  
  FrameList list;
 };

struct ItemList
 {
  Item[] list;
  ulen cur;
 };

struct TextList
 {
  text name;
  Bool open;
  
  FormatPtr format;
  OptCoord bullet_space;
  OptCoord item_space;
  
  ItemList list;
 };

struct Border
 {
  text name;
  Bool open;
  
  OptCoord space;
  OptRatio width;
  OptColor line;
 };

struct Cell
 {
  text name;
  Bool open;
  
  OptULen span_x;
  OptULen span_y;
   
  FrameList list;
 };

struct Table
 {
  text name;
  Bool open;
  
  BorderPtr border;
  OptBool hard;
  
  Coord[] width;
  CellPtr[] table;
 };

struct Link
 {
  text name;
  Bool open;
  
  PagePtr page;
  ulen[] index_list;
 };

struct Span
 {
  text body;
  FormatPtr format;
  RefPtr ref;
 };

type TextLine = Span[] ;

struct FixedText
 {
  text name;
  Bool open;
  
  FormatPtr format;
  
  TextLine[] list;
 };

struct OneLine
 {
  text name;
  Bool open;
  
  OptAlign align;
 };

struct MultiLine
 {
  text name;
  Bool open;
  
  OptRatio line_space;
  OptRatio first_line_space; 
 };

struct Text
 {
  text name;
  Bool open;
  
  PlacementPtr placement;
  FormatPtr format;
  
  Span[] list;  
 };
 
 