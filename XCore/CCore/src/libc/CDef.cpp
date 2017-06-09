/* CDef.cpp */
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

#include <CCore/inc/libc/CDef.h>

namespace LibC_Internal {

/* struct ParseSize */

ParseSize::ParseSize(const char *s)
 {
  Size result=0;

  for(int d; (d=DecValue(*s))>=0 ;s++) result=10*result+d;

  value=result;
  str=s;
 }

} // namespace LibC_Internal


