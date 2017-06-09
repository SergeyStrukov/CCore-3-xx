/* StrKey.cpp */
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

#include <CCore/inc/StrKey.h>

#include <CCore/inc/Crc.h>

namespace CCore {

/* struct StrKey */

auto StrKey::Hash(StrLen str) -> HashType
 {
  Crc32 crc;

  crc.addRange(str);

  return crc;
 }

} // namespace CCore


