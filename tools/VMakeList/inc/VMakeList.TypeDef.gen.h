/* struct TypeDefCore */

struct TypeDefCore
 {
  // types

  struct S1; // #Tools 
  struct S2; // #Param 



  using XXX8226D906_9898_43AA_B1BE_D60B0A6E31C8 = TypeDefCore ;

  // structures

  struct S1
   {
    DDL::MapText CC;
    DDL::MapText AS;
    DDL::MapText LD;
    DDL::MapText AR;
    DDL::MapText RM;
    DDL::MapText MKDIR;
    DDL::MapText MKEMPTY;
    DDL::MapRange< DDL::MapText > CCOPT;
    DDL::MapRange< DDL::MapText > ASOPT;
    DDL::MapRange< DDL::MapText > LDOPT;
    DDL::MapRange< DDL::MapText > LDOPT_DESKTOP;
    DDL::MapText CORELIB;

    struct Ext;
   };

  struct S2
   {
    DDL::MapText CCORE_ROOT;
    DDL::MapText CCORE_TARGET;
    DDL::MapText OBJ_PATH;
    DDL::MapRange< DDL::MapText > SRC_PATH_LIST;
    DDL::MapRange< DDL::MapText > CCOPT_EXTRA;
    DDL::MapRange< DDL::MapText > ASOPT_EXTRA;
    DDL::MapRange< DDL::MapText > LDOPT_EXTRA;
    DDL::MapText TARGET;
    DDL::sint_type target;
    DDL::MapPtr< S1 > tools;

    struct Ext;
   };

  // extra

 };

using XXX212CD757_09B3_4D89_BE20_65C1E4E5A819 = TypeDefCore ;

namespace TypeDef {

    using Param = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S2 ;
    using Tools = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S1 ;

} // namespace TypeDef

