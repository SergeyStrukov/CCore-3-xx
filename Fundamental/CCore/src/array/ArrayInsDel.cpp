/* ArrayInsDel.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.60
//
//  Tag: Fundamental
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/array/ArrayInsDel.h>

#include <CCore/inc/Exception.h>

namespace CCore {

/* guard functions */

void ArrayInsRangeGuardOutOfBorder(ulen ind,ulen len)
 {
  Printf(Exception,"CCore::ArrayInsRangeGuard(#;,#;) : out of range",ind,len);
 }

} // namespace CCore

