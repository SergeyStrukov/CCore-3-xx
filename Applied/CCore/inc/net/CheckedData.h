/* CheckedData.h */
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

#ifndef CCore_inc_net_CheckedData_h
#define CCore_inc_net_CheckedData_h

#include <CCore/inc/PlatformRandom.h>

namespace CCore {
namespace Net {

/* classes */

class CheckedData;

/* class CheckedData */

class CheckedData
 {
   PlatformRandom random;
   uint8 start_sum;

  public:

   CheckedData();

   ulen getLen(ulen max_len);

   bool fill(PtrLen<uint8> data);

   bool check(PtrLen<const uint8> data) const; // random is not used
 };

} // namespace Net
} // namespace CCore

#endif


