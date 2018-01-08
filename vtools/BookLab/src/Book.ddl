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

/* basic types */

type Bool = uint8 ;

Bool True = 1 ;

Bool False = 0 ;

type Coord = sint16 ;

type VColor = uint32 ;

VColor NoColor = 0FFFFFFFFh ;

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

//----------------------------------------------------------------------------------------

/* Text */

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
  Font font;
  
  VColor back = ?DefaultBack ;
  VColor fore = ?DefaultFore ;
  
  type Effect = uint8 ;
  
  const Effect None = 0 ;
  const Effect Underline = 1 ;
  const Effect Strikeout = 2 ;
  
  Effect effect = None ;
 };
 
struct Placement
 {
  Bool one_line = False ;
  
  Ratio line_space = {1,1} ;
  Ratio first_line_space = {2,1} ;
  
  type Align = uint8 ;
  
  const Align Left   = 0 ;  
  const Align Right  = 1 ;  
  const Align Center = 2 ;
  
  Align align = Left ;  
 }; 

struct Span
 {
  text[] list;
  Format *fmt = null ;
 };

struct Text
 {
  Span[] list;
  Format *fmt = & ?DefaultFormat ;
  Placement *placement = & ?DefaultPlacement ;
 };


 