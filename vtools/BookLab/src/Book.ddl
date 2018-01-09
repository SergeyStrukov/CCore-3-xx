/* Book.ddl */
//----------------------------------------------------------------------------------------
//
//  Project: BookLab 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

//--- basic types ------------------------------------------------------------------------

type Bool = uint8 ;

Bool True = 1 ;

Bool False = 0 ;

type VColor = uint32 ;

VColor NoColor = 0FFFFFFFFh ;

type Coord = sint16 ;

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

//--- Text -------------------------------------------------------------------------------

struct Font
 {
  text face;
  Coord size;
  
  Bool bold = False ;
  Bool italic = False ;
 };

VColor DefaultBack = NoColor ;
VColor DefaultFore = NoColor ;

struct Format
 {
  Font *font = null ;
  
  VColor back = ?DefaultBack ;
  VColor fore = ?DefaultFore ;
  
  type Effect = uint8 ;
  
  const Effect None = 0 ;
  const Effect Underline = 1 ;
  const Effect Strikeout = 2 ;
  
  Effect effect = None ;
 };

struct OneLine
 {
  type Align = uint8 ;
  
  const Align Left   = 0 ;  
  const Align Right  = 1 ;  
  const Align Center = 2 ;
  
  Align align = Left ;
 };
 
struct MultiLine
 {
  Ratio line_space = {1,1} ;
  Ratio first_line_space = {2,1} ;
 }; 

struct Span
 {
  text[] list;
  Format *fmt = null ;
 };

Format DefaultFormat = {} ;

MultiLine DefaultPlacement = {} ;

struct Text
 {
  Span[] list;
  Format *fmt = & ?DefaultFormat ;
  {OneLine,MultiLine} *placement = & ?DefaultPlacement ;
 };

//--- Bitmap -----------------------------------------------------------------------------

struct Bitmap
 {
  VColor[][] map;
 };

//--- Frame ------------------------------------------------------------------------------

struct Frame
 {
  type LineType = uint8 ;
  
  const LineType None = 0 ;
  const LineType Single = 1 ;
  const LineType Double = 2 ;
  
  LineType line_type = None ; 
 
  Point inner = { 0 , 0 } ;
  Point outer = { 0 , 0 } ;
  
  VColor col = NoColor ;
  
  {Text,Bitmap} *body;
 };
 
//--- Book -------------------------------------------------------------------------------

struct Book
 {
  VColor back = NoColor ;
  VColor fore = NoColor ;
  
  Frame[] body;
 };




 