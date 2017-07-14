/* AppState.TypeDef.gen.h */
//----------------------------------------------------------------------------------------
//
//  Project: Aspect 1.01
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

  struct S1; // #Pane 
  struct S2; // #AppState 

  using A1 = sint16 ; // #Coord


  using XXX8226D906_9898_43AA_B1BE_D60B0A6E31C8 = TypeDefCore ;

  // structures

  struct S1
   {
    A1 x;
    A1 y;
    A1 dx;
    A1 dy;

    struct Ext;
   };

  struct S2
   {
    S1 place;
    DDL::MapRange< DDL::MapText > recent_files;

    struct Ext;
   };

  // extra

 };

using XXX212CD757_09B3_4D89_BE20_65C1E4E5A819 = TypeDefCore ;

namespace TypeDef {

    using Coord = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::A1 ;
    using Pane = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S1 ;
    using AppState = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S2 ;

} // namespace TypeDef

