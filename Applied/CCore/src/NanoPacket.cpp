/* NanoPacket.cpp */
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

#include <CCore/inc/NanoPacket.h>

#include <CCore/inc/Abort.h>

namespace CCore {

/* functions */

void NanoPacketListExitAbort()
 {
  Abort("Fatal error : CCore::NanoPacketList is not empty on exit");
 }

void NanoPacketPoolExitAbort()
 {
  Abort("Fatal error : CCore::NanoPacketPool is used on exit");
 }

} // namespace CCore


