/* FontInfo.TypeDef.gen.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.01
//
//  Tag: Desktop
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

/* struct TypeDefCore */

struct TypeDefCore
 {
  // types

  struct S1; // #FontInfo 

  using A1 = DDL::MapRange< S1 > ; // #FontDatabase
  using A2 = sint16 ; // #Coord
  using A3 = uint8 ; // #Bool


  using XXX8226D906_9898_43AA_B1BE_D60B0A6E31C8 = TypeDefCore ;

  // structures

  struct S1
   {
    DDL::MapText file_name;
    DDL::MapText family;
    DDL::MapText style;
    A3 scalable;
    A3 monospace;
    A3 italic;
    A3 bold;

    struct Ext;
   };

  // extra

 };

using XXX212CD757_09B3_4D89_BE20_65C1E4E5A819 = TypeDefCore ;

namespace TypeDef {

    using FontDatabase = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::A1 ;
    using Bool = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::A3 ;
    using Coord = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::A2 ;
    using FontInfo = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S1 ;

} // namespace TypeDef

