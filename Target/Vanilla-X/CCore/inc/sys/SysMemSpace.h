/* SysMemSpace.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Target/Vanilla-X
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_sys_SysMemSpace_h
#define CCore_inc_sys_SysMemSpace_h

#include <CCore/inc/Gadget.h>

namespace CCore {
namespace Sys {

/* functions */

 // one-time call , aligned

Space AllocHeapSpace();

Space AllocHeapSpace_int();

Space AllocHeapSpace_shared();

Space AllocLogSpace();

Space AllocVideoSpace();

} // namespace Sys
} // namespace CCore

#endif


