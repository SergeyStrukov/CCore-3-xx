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

struct Point
 {
  Coord x;
  Coord y;
 };
 
struct Ratio
 {
  sint32 ratio;
 }; 

 