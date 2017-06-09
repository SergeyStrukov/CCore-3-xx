/* FastMutex.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: HCore Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/task/FastMutex.h>

#include <CCore/inc/Abort.h>

namespace CCore {

/* class Mutex */

FastMutex::FastMutex(unsigned spin_count_)
 : spin_count(spin_count_)
 {
 }

FastMutex::~FastMutex()
 {
  if( entry ) Abort("Fatal error : CCore::FastMutex is locked on exit");
 }

} // namespace CCore


