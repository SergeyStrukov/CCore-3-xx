/* Config.ddl */
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

//include <PTPSecureConfig.types.ddl>

PTPSecureConfig config = 
 {
  .server_key = { Key#SHA512 , { 000h, 019h, 09Bh, 0FAh, 013h, 064h, 0D0h, 0F4h, 061h, 01Eh, 055h, 050h, 057h, 052h, 0FBh, 00Ch,
                                 04Ah, 0A0h, 04Ah, 0F2h, 083h, 037h, 06Eh, 001h, 050h, 013h, 06Dh, 0B1h, 004h, 0A7h, 082h, 010h } },
                                  
  .admin_key = { Key#SHA512 , { 09Eh, 03Fh, 083h, 09Bh, 0E3h, 0EAh, 04Ah, 0D9h, 0EEh, 0A1h, 049h, 005h, 046h, 0E6h, 0C8h, 07Ch, 
                                0A7h, 00Dh, 0F2h, 01Ch, 030h, 0F5h, 091h, 08Bh, 03Dh, 0CFh, 090h, 00Ah, 0EAh, 0B4h, 0A8h, 025h } },
                                 
  .clients = {
              Ivan,
              Boris,
              Sergey
             }                                                                  
 };
 
Client Ivan = 
 {
  .name = 'Ivan',
  .key = { Key#SHA512 , { 016h, 006h, 008h, 001h, 0A7h, 0D2h, 020h, 06Ah, 0AAh, 003h } },
  
  .access_read = Yes ,
  .access_write = No ,
  .has_home = No   
 }; 
 
Client Boris = 
 {
  .name = 'Boris',
  .key = { Key#SHA512 , { 05Eh, 031h, 076h, 04Ah, 05Dh, 02Fh, 062h, 0A8h, 0ACh, 0ABh } },
  
  .access_read = Yes ,
  .access_write = Yes ,
  .has_home = No   
 }; 
 
Client Sergey = 
 {
  .name = 'Sergey',
  .key = { Key#SHA512 , { 032h, 0E3h, 095h, 080h, 0D7h, 029h, 06Ch, 0F5h, 00Fh, 027h } },
  
  .access_read = Yes ,
  .access_write = Yes ,
  .has_home = Yes   
 }; 


