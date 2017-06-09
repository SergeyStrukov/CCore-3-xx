/* PtrLen.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Simple Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/gadget/PtrLen.h>

#include <cstring>

namespace CCore {

/* struct StrLen */

StrLen::StrLen(const char *zstr) : PtrLen<const char>(zstr,std::strlen(zstr)) {}

} // namespace CCore


