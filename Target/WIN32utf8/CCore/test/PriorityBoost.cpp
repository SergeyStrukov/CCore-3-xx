/* PriorityBoost.cpp */
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

#include <CCore/test/PriorityBoost.h>

#include <CCore/inc/Print.h>

#include <windows.h>

namespace App {

/* using */

using namespace CCore;

/* PriorityBoost() */

void PriorityBoost()
 {
  if( !SetThreadPriority(GetCurrentThread(),THREAD_PRIORITY_TIME_CRITICAL) )
    {
     Printf(Con,"No priority boost!\n");
    }
 }

} // namespace App

