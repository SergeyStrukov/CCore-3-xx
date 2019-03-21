/* struct TypeDefCore */

struct TypeDefCore
 {
  // types

  struct S1; // #Dep 
  struct S2; // #Rule 
  struct S3; // #VMake 
  struct S4; // #Cmd 
  struct S5; // #Exe 
  struct S6; // #Target 



  using XXX8226D906_9898_43AA_B1BE_D60B0A6E31C8 = TypeDefCore ;

  // structures

  struct S1
   {
    DDL::MapRange< DDL::MapPtr< S6 > > src;
    DDL::MapRange< DDL::MapPtr< S6 > > dst;

    struct Ext;
   };

  struct S2
   {
    DDL::MapRange< DDL::MapPtr< S6 > > src;
    DDL::MapRange< DDL::MapPtr< S6 > > dst;
    DDL::MapRange< DDL::MapPolyPtr< S5 , S4 , S3 > > cmd;

    struct Ext;
   };

  struct S3
   {
    DDL::MapText file;
    DDL::MapText target;

    struct Ext;
   };

  struct S4
   {
    DDL::MapText cmdline;

    struct Ext;
   };

  struct S5
   {
    DDL::MapText exe;
    DDL::MapText cmdline;

    struct Ext;
   };

  struct S6
   {
    DDL::MapText file;

    struct Ext;
   };

  // extra

 };

using XXX212CD757_09B3_4D89_BE20_65C1E4E5A819 = TypeDefCore ;

namespace TypeDef {

    using Cmd = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S4 ;
    using Dep = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S1 ;
    using Exe = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S5 ;
    using Rule = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S2 ;
    using Target = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S6 ;
    using VMake = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S3 ;

} // namespace TypeDef

