/* Symbol.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Simple Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_Symbol_h
#define CCore_inc_Symbol_h

#include <CCore/inc/Gadget.h>

#ifdef CCORE_UTF8
# include <CCore/inc/Utf8.h>
#endif

namespace CCore {

/* type Symbol */

#ifdef CCORE_UTF8

using Symbol = Utf8Code ;

#else

using Symbol = char ;

#endif

} // namespace CCore

#endif

