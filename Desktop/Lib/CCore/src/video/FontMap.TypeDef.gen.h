/* FontMap.TypeDef.gen.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.60
//
//  Tag: Desktop
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

/* struct TypeDefCore */

struct TypeDefCore
 {
  // types

  struct S1; // #Entry
  struct S2; // #Map



  using XXX8226D906_9898_43AA_B1BE_D60B0A6E31C8 = TypeDefCore ;

  // structures

  struct S1
   {
    DDL::MapText face;
    DDL::MapText replace;

    struct Ext;
   };

  struct S2
   {
    DDL::MapRange< S1 > list;

    struct Ext;
   };

  // extra

 };

using XXX212CD757_09B3_4D89_BE20_65C1E4E5A819 = TypeDefCore ;

namespace TypeDef {

    using Map = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S2 ;
    using Entry = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S1 ;

} // namespace TypeDef

