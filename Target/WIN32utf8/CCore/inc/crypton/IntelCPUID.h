/* IntelCPUID.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Target/WIN32utf8
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_crypton_IntelCPUID_h
#define CCore_inc_crypton_IntelCPUID_h

#include <CCore/inc/Gadget.h>

namespace CCore {
namespace Crypton {

/* classes */

struct IntelCPUID1;

/* struct IntelCPUID1 */

struct IntelCPUID1
 {
  uint32 EAX;
  uint32 EBX;
  uint32 ECX;
  uint32 EDX;

  IntelCPUID1() noexcept;

  static uint32 Bit(unsigned num) { return UIntBit<uint32>(num); }

  uint32 capableAES() const { return ECX&Bit(25); }

  uint32 capableRDRAND() const { return ECX&Bit(30); }
 };

} // namespace Crypton
} // namespace CCore

#endif


