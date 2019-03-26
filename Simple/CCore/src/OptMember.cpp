/* OptMember.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.60
//
//  Tag: Simple
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/OptMember.h>

#include <CCore/inc/Exception.h>

namespace CCore {

/* guard functions */

void GuardOptMemberNoObject()
 {
  Printf(Exception,"CCore::OptMember<...>::getPtr() : no object");
 }

} // namespace CCore

