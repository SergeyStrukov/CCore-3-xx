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

int Version = 1 ;

//--- basic types ------------------------------------------------------------------------

type Bool = uint8 ;

Bool True = 1 ;

Bool False = 0 ;

type VColor = uint32 ;

VColor NoColor = 0FFFFFFFFh ;

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

//--- Text -------------------------------------------------------------------------------

struct Font
 {
  text face;
  Coord size;
  
  Bool bold = False ;
  Bool italic = False ;
  
  int strength = 0 ;
 };

struct Format
 {
  Font *font = null ;
  
  VColor back = NoColor ;
  VColor fore = NoColor ;
  
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
  text body;
  
  Format *fmt = null ;
  
  {Link,Page} * ref = null ;
 };

Format DefaultFormat = {} ;

MultiLine DefaultPlacement = {} ;

struct Text
 {
  Span[] list;
  
  Format *fmt = & ?DefaultFormat ;
  
  {OneLine,MultiLine} *placement = & ?DefaultPlacement ;
 };
 
struct FixedSpan
 {
  text body;
  
  Format *fmt = null ;
  
  {Link,Page} * ref = null ;
 };
 
type Line = FixedSpan[] ; 
 
Format DefaultFixedFormat = {} ;

struct FixedText
 {
  Line[] list;
 
  Format *fmt = & ?DefaultFixedFormat ;
 }; 

//--- Bitmap -----------------------------------------------------------------------------

struct Bitmap
 {
  text file_name;
 };

//--- TextList ---------------------------------------------------------------------------

struct ListItem
 {
  text bullet;
  Frame[] list;
 };

Format DefaultBulletFormat = {} ;

Coord DefaultBulletSpace = 5 ;
Coord DefaultItemSpace = 0 ;

struct TextList
 {
  ListItem[] list;
  
  Format *bullet_fmt = & ?DefaultBulletFormat ;
  
  Coord bullet_space = ?DefaultBulletSpace ;
  Coord item_space = ?DefaultItemSpace ;
 };

//--- Frame ------------------------------------------------------------------------------

struct SingleLine
 {
  Ratio width = {1,1} ; 
  VColor line = NoColor ;
 };
 
struct DoubleLine
 {
  Ratio width = {1,1} ;
  VColor gray = NoColor ;
  VColor snow = NoColor ; 
 };
 
SingleLine DefaultSingleLine = {} ;

DoubleLine DefaultDoubleLine = {} ;  

Point DefaultInner = { 0 , 0 } ;

Point DefaultOuter = { 0 , 0 } ;

struct Frame
 {
  {Text,FixedText,Bitmap,TextList} *body;
  
  {SingleLine,DoubleLine} *line = null ;
  
  Point inner = ?DefaultInner ;
  Point outer = ?DefaultOuter ;
  
  VColor col = NoColor ;
 };
 
//--- Book -------------------------------------------------------------------------------

struct Page
 {
  text name;
  
  Frame[] list;
  
  VColor back = NoColor ;
  VColor fore = NoColor ;
  
  Page *up = null ;
  Page *prev = null ;
  Page *next = null ;
 };
 
struct Book
 {
  text title;
  
  Page *start;
  
  VColor back = NoColor ;
  VColor fore = NoColor ;
 }; 

struct Link
 {
  Page *page;
  ulen frame_index = 0 ;
 };


