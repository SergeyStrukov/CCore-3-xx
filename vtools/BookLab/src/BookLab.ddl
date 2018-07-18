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
 
//--- Ptrs ------------------------------------------------------------------------------- 
 
struct PagePtr
 {
  text name;
  Page *page;
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

//---  --------------------------------------------------------------------------------

struct Font;

struct Format;

struct SingleLine;

struct DoubleLine;

struct Frame;

struct FrameList;

struct Page;

struct Bitmap;

struct Collapse;

struct Item;

struct ItemList;

struct TextList;

struct Border;

struct Cell;

struct Table;

struct Link;

struct Span;

struct TextLine;

struct FixedText;

struct OneLine;

struct MultiLine;

struct Text;
 