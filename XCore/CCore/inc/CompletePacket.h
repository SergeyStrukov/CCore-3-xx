/* CompletePacket.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: XCore
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_CompletePacket_h
#define CCore_inc_CompletePacket_h

#include <CCore/inc/Packet.h>

namespace CCore {

/* functions */

void CompletePacket_int(PacketHeader *packet);

void CompletePacket_int(PacketType packet) { CompletePacket_int(GetPacketHeader(packet)); }

} // namespace CCore

#endif


