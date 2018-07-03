/* LockUse.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.60
//
//  Tag: Simple Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/gadget/LockUse.h>

#include <CCore/inc/Exception.h>

namespace CCore {

/* functions */

void GuardUseLocked()
 {
  Printf(Exception,"CCore::LockUse<...>::LockUse(...) : no more use");
 }

} // namespace CCore

