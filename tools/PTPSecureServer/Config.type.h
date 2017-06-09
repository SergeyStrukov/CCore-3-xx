/* struct TypeDefCore */

struct TypeDefCore
 {
  // types

  struct S1; // #Key 
  struct S2; // #Client 
  struct S3; // #PTPSecureConfig 

  using A1 = uint8 ; // #Bool


  using XXX8226D906_9898_43AA_B1BE_D60B0A6E31C8 = TypeDefCore ;

  // structures

  struct S1
   {
    uint8 hash_id;
    DDL::MapRange< uint8 > key;

    struct Ext;
   };

  struct S2
   {
    DDL::MapText name;
    S1 key;
    A1 access_read;
    A1 access_write;
    A1 has_home;

    struct Ext;
   };

  struct S3
   {
    uint16 pke_port;
    uint16 psec_port;
    uint16 keyset_len;
    uint32 ttl;
    uint32 utl;
    uint32 max_clients;
    DDL::MapText root;
    S1 server_key;
    DDL::MapText admin_name;
    S1 admin_key;
    DDL::MapRange< S2 > clients;

    struct Ext;
   };

  // extra

 };

using XXX212CD757_09B3_4D89_BE20_65C1E4E5A819 = TypeDefCore ;

namespace TypeDef {

    using Bool = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::A1 ;
    using Key = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S1 ;
    using PTPSecureConfig = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S3 ;
    using Client = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S2 ;

} // namespace TypeDef

