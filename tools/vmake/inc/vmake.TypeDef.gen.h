/* struct TypeDefCore */

struct TypeDefCore
 {
  // types

  struct S1; // #MenuItem 
  struct S2; // #Menu 
  struct S3; // #Dep 
  struct S4; // #Rule 
  struct S5; // #VMake 
  struct S6; // #Env 
  struct S7; // #Cmd 
  struct S8; // #Exe 
  struct S9; // #Target 



  using XXX8226D906_9898_43AA_B1BE_D60B0A6E31C8 = TypeDefCore ;

  // structures

  struct S1
   {
    DDL::MapPtr< S9 > dst;
    DDL::MapText desc;
    DDL::MapRange< DDL::MapPtr< S1 > > sub;

    struct Ext;

    ulen ext;
   };

  struct S2
   {
    DDL::MapRange< S1 > list;

    struct Ext;
   };

  struct S3
   {
    DDL::MapRange< DDL::MapPtr< S9 > > src;
    DDL::MapRange< DDL::MapPtr< S9 > > dst;

    struct Ext;
   };

  struct S4
   {
    DDL::MapRange< DDL::MapPtr< S9 > > src;
    DDL::MapRange< DDL::MapPtr< S9 > > dst;
    DDL::MapRange< DDL::MapPolyPtr< S8 , S7 , S5 > > cmd;

    struct Ext;

    ulen ext;
   };

  struct S5
   {
    DDL::MapText echo;
    DDL::MapText file;
    DDL::MapText target;
    DDL::MapText wdir;

    struct Ext;
   };

  struct S6
   {
    DDL::MapText name;
    DDL::MapText value;

    struct Ext;
   };

  struct S7
   {
    DDL::MapText echo;
    DDL::MapText cmdline;
    DDL::MapText wdir;
    DDL::MapRange< S6 > env;

    struct Ext;
   };

  struct S8
   {
    DDL::MapText echo;
    DDL::MapText exe;
    DDL::MapText cmdline;
    DDL::MapText wdir;
    DDL::MapRange< S6 > env;

    struct Ext;
   };

  struct S9
   {
    DDL::MapText desc;
    DDL::MapText file;

    struct Ext;

    ulen ext;
   };

  // extra

 };

using XXX212CD757_09B3_4D89_BE20_65C1E4E5A819 = TypeDefCore ;

namespace TypeDef {

    using Cmd = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S7 ;
    using Dep = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S3 ;
    using Env = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S6 ;
    using Exe = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S8 ;
    using Menu = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S2 ;
    using Rule = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S4 ;
    using Target = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S9 ;
    using VMake = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S5 ;
    using MenuItem = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S1 ;

} // namespace TypeDef

