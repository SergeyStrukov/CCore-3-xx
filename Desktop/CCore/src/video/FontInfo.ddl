/* FontInfo.ddl */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: Desktop
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

type Bool = uint8 ;

Bool True = 1 ;
Bool False = 0 ;

type Coord = sint16 ;

struct FontSize
 {
  Coord min_dx;
  Coord max_dx;
  Coord dy;
  Coord by;
  Coord dx0;
  Coord dx1;
  Coord skew;
 };

struct FontInfo
 {
  text file_name;

  text family;
  text style;

  Bool scalable;
  Bool monospace;
  Bool italic;
  Bool bold;

  FontSize def_size;
 };

type FontDatabase = FontInfo[] ;
