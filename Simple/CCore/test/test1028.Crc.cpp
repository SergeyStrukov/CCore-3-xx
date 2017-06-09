/* test1028.Crc.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Simple Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/Crc.h>

namespace App {

/* Testit<1028> */

template<>
const char *const Testit<1028>::Name="Test1028 Crc";

template<>
bool Testit<1028>::Main()
 {
  {
   CrcTable<uint16,0xFFFF,0x1021> table;

   if( table.check(AlgoCrc16::Table) )
     {
      Printf(Con,"\n#;\n\n",table);

      Printf(Con,"Crc16 Ok\n");
     }
   else
     {
      Printf(Con,"Crc16 Failed\n");

      return false;
     }
  }

  {
   CrcTable<uint32,0xFFFFFF,0x864CFB> table;

   if( table.check(AlgoCrc24::Table) )
     {
      Printf(Con,"\n#;\n\n",table);

      Printf(Con,"Crc24 Ok\n");
     }
   else
     {
      Printf(Con,"Crc24 Failed\n");

      return false;
     }
  }

  {
   CrcTable<uint32,0xFFFFFFFF,0x00A00805> table;

   if( table.check(AlgoCrc32::Table) )
     {
      Printf(Con,"\n#;\n\n",table);

      Printf(Con,"Crc32 Ok\n");
     }
   else
     {
      Printf(Con,"Crc32 Failed\n");

      return false;
     }
  }

  return true;
 }

} // namespace App

