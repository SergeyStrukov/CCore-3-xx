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

struct Scope;

struct Section;

//--- Meat -------------------------------------------------------------------------------

struct Font
 {
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

struct Frame;

struct FrameList;

struct Page;

struct Bitmap;

struct Collapse;

struct Item;

struct ItemList;

struct TextList;

struct Border
 {
  text name;
  Bool open;
  
  OptCoord space;
  OptRatio width;
  OptColor line;
 };

struct Cell;

struct Table;

struct Link;

struct Span;

struct TextLine;

struct FixedText;

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

struct Text;
 