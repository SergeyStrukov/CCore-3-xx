/* PTPSecureConfig.types.ddl */
//----------------------------------------------------------------------------------------
//
//  Project: PTPSecureClient 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

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
 
struct PTPSecureConfig
 {
  uint16 server_pke_port  = 52102 ;
  uint16 server_psec_port = 52103 ;
  
  uint16 pke_port  = 52100 ;
  uint16 psec_port = 52101 ;
  
  uint16 keyset_len = 10 ;
  uint32 ttl        = 3600 ;
  uint32 utl        = 100000000 ;
  
  ip server_ip = 127.0.0.1 ;
  Key server_key;
  
  text name;
  Key key;
 };
 
 