/* PTPSecureConfig.types.ddl */
//----------------------------------------------------------------------------------------
//
//  Project: PTPSecureServer 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

type Bool = uint8 ;
  
Bool Yes = 1 ;
Bool No  = 0 ;  
  
struct Key
 {
  const uint8 SHA1   = 0 ; 
  const uint8 SHA224 = 1 ;
  const uint8 SHA256 = 2 ;
  const uint8 SHA384 = 3 ;
  const uint8 SHA512 = 4 ;
 
  uint8 hash_id;
  
  uint8[] key;
 };
 
struct Client
 {
  text name;
  Key key;
  
  // access rights
  
  Bool access_read;
  Bool access_write;
  Bool has_home;
 }; 

struct PTPSecureConfig
 {
  uint16 pke_port  = 52102 ;
  uint16 psec_port = 52103 ;
  
  uint16 keyset_len = 10 ;
  uint32 ttl        = 3600 ;
  uint32 utl        = 100000000 ;
  
  uint32 max_clients = 10000 ;
  
  text root = './root' ;
  
  Key server_key;
  
  text admin_name = 'admin' ;
  Key admin_key;
  
  Client[] clients;   
 };
 
 