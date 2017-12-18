/* HitDirs.TypeDef.gen.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
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

  struct S1; // #HitDirData#Rec
  struct S2; // #HitDirData



  using XXX8226D906_9898_43AA_B1BE_D60B0A6E31C8 = TypeDefCore ;

  // structures

  struct S1
   {
    DDL::MapText dir;
    DDL::uint_type count;

    struct Ext;
   };

  struct S2
   {
    DDL::MapRange< DDL::MapText > hit_list;
    DDL::MapRange< S1 > last_list;

    using Rec = XXX8226D906_9898_43AA_B1BE_D60B0A6E31C8::S1 ;

    struct Ext;
   };

  // extra

 };

using XXX212CD757_09B3_4D89_BE20_65C1E4E5A819 = TypeDefCore ;

namespace TypeDef {

    using HitDirData = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S2 ;

} // namespace TypeDef

