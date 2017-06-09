/* EthDevice.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Applied
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/net/EthDevice.h>

namespace CCore {
namespace Net {

/* enum EthEvent */

const char * GetTextDesc(EthEvent ev)
 {
  static const char *const Table[]=
   {
    "Link up",       //  EthLink_Up
    "Link down",     //  EthLink_Down

    "Tx",            //  EthTx_Done
    "Rx",            //  EthRx_Done

    "Tx bad length", //  EthTx_BadPacketLen
    "Tx error",      //  EthTx_Error

    "Rx bad length", //  EthRx_BadPacketLen
    "Rx drop",       //  EthRx_Drop
    "Rx broadcast",  //  EthRx_Broadcast
    "Rx error"       //  EthRx_Error

    ""
   };

  return Table[ev];
 }

/* struct EthDevice */

const Unid EthDevice::TypeUnid={{0x0CDC'D18A,0x7486'9ECE,0xDFDD'0BB2,0xE4CE'7C25,0xC8EB'C2D5,0x3CA3'F9C7,0x84D2'9B8C,0x672E'3636}};

} // namespace Net
} // namespace CCore


