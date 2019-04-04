/* struct TypeDefCore */

struct TypeDefCore
 {
  // types

  struct S1; // #MenuItem 
  struct S2; // #Menu 
  struct S3; // #Dep 
  struct S4; // #Rule 
  struct S5; // #IntCmd 
  struct S6; // #Mkdir 
  struct S7; // #Rm 
  struct S8; // #Cat 
  struct S9; // #Echo 
  struct S10; // #VMake 
  struct S11; // #Env 
  struct S12; // #Cmd 
  struct S13; // #Exe 
  struct S14; // #Target 



  using XXX8226D906_9898_43AA_B1BE_D60B0A6E31C8 = TypeDefCore ;

  // structures

  struct S1
   {
    DDL::MapPtr< S14 > dst;
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
    DDL::MapRange< DDL::MapPtr< S14 > > src;
    DDL::MapRange< DDL::MapPtr< S14 > > dst;

    struct Ext;
   };

  struct S4
   {
    DDL::MapRange< DDL::MapPtr< S14 > > src;
    DDL::MapRange< DDL::MapPtr< S14 > > dst;
    DDL::MapRange< DDL::MapPolyPtr< S13 , S12 , S10 , S5 > > cmd;

    struct Ext;

    ulen ext;
   };

  struct S5
   {
    DDL::MapText echo;
    DDL::MapPolyPtr< S9 , S8 , S7 , S6 > cmd;
    DDL::MapText wdir;

    struct Ext;
   };

  struct S6
   {
    DDL::MapText path;

    struct Ext;
   };

  struct S7
   {
    DDL::MapRange< DDL::MapText > files;

    struct Ext;
   };

  struct S8
   {
    DDL::MapRange< DDL::MapText > files;
    DDL::MapText outfile;

    struct Ext;
   };

  struct S9
   {
    DDL::MapText str;
    DDL::MapText outfile;

    struct Ext;
   };

  struct S10
   {
    DDL::MapText echo;
    DDL::MapText file;
    DDL::MapText target;
    DDL::MapText wdir;

    struct Ext;
   };

  struct S11
   {
    DDL::MapText name;
    DDL::MapText value;

    struct Ext;
   };

  struct S12
   {
    DDL::MapText echo;
    DDL::MapText cmdline;
    DDL::MapText wdir;
    DDL::MapRange< S11 > env;

    struct Ext;
   };

  struct S13
   {
    DDL::MapText echo;
    DDL::MapText exe;
    DDL::MapRange< DDL::MapText > args;
    DDL::MapText wdir;
    DDL::MapRange< S11 > env;

    struct Ext;
   };

  struct S14
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

    using Rm = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S7 ;
    using Cat = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S8 ;
    using Cmd = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S12 ;
    using Dep = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S3 ;
    using Env = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S11 ;
    using Exe = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S13 ;
    using Echo = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S9 ;
    using Menu = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S2 ;
    using Rule = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S4 ;
    using Target = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S14 ;
    using IntCmd = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S5 ;
    using VMake = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S10 ;
    using MenuItem = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S1 ;
    using Mkdir = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S6 ;

} // namespace TypeDef

