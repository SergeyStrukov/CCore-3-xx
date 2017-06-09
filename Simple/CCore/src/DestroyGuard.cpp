/* DestroyGuard.cpp */
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
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/DestroyGuard.h>

#include <CCore/inc/PrintAbort.h>

namespace CCore {

/* DestroyGuardAbort() */

void DestroyGuardAbort()
 {
  Abort("Fatal error: destroy guard abort");
 }

void DestroyGuardAbort(StrLen name)
 {
  PrintAbort("Fatal error: destroy guard #.q; abort",name);
 }

} // namespace CCore

