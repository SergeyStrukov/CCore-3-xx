/* DefaultFileDevice.h */
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
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_DefaultFileDevice_h
#define CCore_inc_DefaultFileDevice_h

#include <CCore/inc/GenFile.h>

namespace CCore {

/* functions */

void SetDefaultFileDevice(StrLen dev);

ulen CopyDefaultFileDevice(char buf[MaxPathLen]);

/* classes */

struct GetDefaultFileDevice;

/* struct GetDefaultFileDevice */

struct GetDefaultFileDevice : NoCopy
 {
  char buf[MaxPathLen];
  ulen len;

  GetDefaultFileDevice() { len=CopyDefaultFileDevice(buf); }

  operator StrLen() const { return Range(buf,len); }
 };

} // namespace CCore

#endif

