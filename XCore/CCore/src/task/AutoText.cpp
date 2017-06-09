/* AutoText.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
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

#include <CCore/inc/task/AutoText.h>

namespace CCore {

/* class AutoTextNumber */

unsigned AutoTextNumber::get()
 {
  Lock lock(*this);

  return GetTextLabelNumber(next);
 }

} // namespace CCore


