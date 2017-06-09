/* InstanceLock.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: Simple
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/InstanceLock.h>

#include <CCore/inc/Exception.h>

namespace CCore {

/* functions */

void GuardInstanceLockTaken(StrLen name,ulen index)
 {
  Printf(Exception,"CCore::InstanceLock<...>::InstanceLock(#.q;,#;) : instance is locked",name,index);
 }

} // namespace CCore


