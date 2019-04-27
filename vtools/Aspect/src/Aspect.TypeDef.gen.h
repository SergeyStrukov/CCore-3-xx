/* struct TypeDefCore */

struct TypeDefCore
 {
  // types

  struct S1; // #File 
  struct S2; // #Dir 
  struct S3; // #Aspect 

  using A1 = uint8 ; // #Status


  using XXX8226D906_9898_43AA_B1BE_D60B0A6E31C8 = TypeDefCore ;

  // structures

  struct S1
   {
    DDL::MapText name;
    A1 status;

    struct Ext;
   };

  struct S2
   {
    DDL::MapText name;
    A1 status;
    DDL::MapRange< DDL::MapPtr< S2 > > dirs;
    DDL::MapRange< S1 > files;

    struct Ext;
   };

  struct S3
   {
    DDL::MapText path;
    S2 root;

    struct Ext;
   };

  // extra

 };

using XXX212CD757_09B3_4D89_BE20_65C1E4E5A819 = TypeDefCore ;

namespace TypeDef {

    using Status = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::A1 ;
    using Dir = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S2 ;
    using File = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S1 ;
    using Aspect = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S3 ;

} // namespace TypeDef

