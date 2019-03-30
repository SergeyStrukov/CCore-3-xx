/* struct TypeDefCore */

struct TypeDefCore
 {
  // types

  struct S1; // #Param 



  using XXX8226D906_9898_43AA_B1BE_D60B0A6E31C8 = TypeDefCore ;

  // structures

  struct S1
   {
    DDL::MapText CCORE_ROOT;
    DDL::MapText CCORE_TARGET;
    DDL::MapText OBJ_PATH;
    DDL::MapRange< DDL::MapText > SRC_PATH_LIST;
    DDL::MapRange< DDL::MapText > CCOPT_EXTRA;
    DDL::MapRange< DDL::MapText > LDOPT_EXTRA;
    DDL::MapText TARGET;

    struct Ext;
   };

  // extra

 };

using XXX212CD757_09B3_4D89_BE20_65C1E4E5A819 = TypeDefCore ;

namespace TypeDef {

    using Param = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S1 ;

} // namespace TypeDef

