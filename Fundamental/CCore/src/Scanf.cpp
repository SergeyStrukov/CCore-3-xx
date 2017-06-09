/* Scanf.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: Fundamental Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/Scanf.h>

namespace CCore {

/* struct ScanfDevBase */

const char * ScanfDevBase::Find(const char *format,char ch)
 {
  for(; NotFound(*format,ch) ;format++);

  return format;
 }

} // namespace CCore


