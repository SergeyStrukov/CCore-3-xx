/* FavData.TypeDef.gen.h */
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

  struct S1; // #FavElement 
  struct S2; // #FavData 

  using A1 = uint8 ; // #Bool


  using XXX8226D906_9898_43AA_B1BE_D60B0A6E31C8 = TypeDefCore ;

  // structures

  struct S1
   {
    DDL::MapText title;
    DDL::MapText path;
    A1 section;
    A1 open;

    struct Ext;
   };

  struct S2
   {
    DDL::MapRange< S1 > list;
    DDL::ulen_type off;
    DDL::ulen_type cur;

    struct Ext;
   };

  // extra

 };

using XXX212CD757_09B3_4D89_BE20_65C1E4E5A819 = TypeDefCore ;

namespace TypeDef {

    using Bool = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::A1 ;
    using FavElement = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S1 ;
    using FavData = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S2 ;

} // namespace TypeDef

