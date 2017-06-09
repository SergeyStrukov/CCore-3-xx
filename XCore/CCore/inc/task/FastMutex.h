/* FastMutex.h */
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

#ifndef CCore_inc_task_FastMutex_h
#define CCore_inc_task_FastMutex_h

#include <CCore/inc/dev/DevInt.h>

namespace CCore {

/* classes */

struct FastMutexBase;

/* struct FastMutexBase */

struct FastMutexBase : NoCopy
 {
  class Lock : NoCopy
   {
     Dev::IntLock lock;

    public:

     explicit Lock(FastMutexBase &) {}

     ~Lock() {}
   };
 };

} // namespace CCore

#endif


