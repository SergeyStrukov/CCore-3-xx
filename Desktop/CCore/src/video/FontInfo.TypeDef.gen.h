/* FontInfo.TypeDef.gen.h */
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

/* struct TypeDefCore */

struct TypeDefCore
 {
  // types

  struct S1; // #FontSize
  struct S2; // #FontInfo

  using A1 = DDL::MapRange< S2 > ; // #FontDatabase
  using A2 = sint16 ; // #Coord
  using A3 = uint8 ; // #Bool


  using XXX8226D906_9898_43AA_B1BE_D60B0A6E31C8 = TypeDefCore ;

  // structures

  struct S1
   {
    A2 min_dx;
    A2 max_dx;
    A2 dy;
    A2 by;
    A2 dx0;
    A2 dx1;
    A2 skew;

    struct Ext;
   };

  struct S2
   {
    DDL::MapText file_name;
    DDL::MapText family;
    DDL::MapText style;
    A3 scalable;
    A3 monospace;
    A3 italic;
    A3 bold;
    S1 def_size;

    struct Ext;
   };

  // extra

 };

using XXX212CD757_09B3_4D89_BE20_65C1E4E5A819 = TypeDefCore ;

namespace TypeDef {

    using FontDatabase = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::A1 ;
    using Bool = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::A3 ;
    using Coord = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::A2 ;
    using FontSize = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S1 ;
    using FontInfo = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S2 ;

} // namespace TypeDef

