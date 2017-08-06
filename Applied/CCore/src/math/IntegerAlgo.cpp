/* IntegerAlgo.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.01
//
//  Tag: Applied
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/math/IntegerAlgo.h>

#include <CCore/inc/Exception.h>

namespace CCore {
namespace Math {

/* guards */

void GuardAddLenOverflow_ulen(ulen a,ulen b)
 {
  Printf(Exception,"CCore::Math::AddLen(#;,#;) : overflow",a,b);
 }

void GuardAddLenOverflow_ulen()
 {
  Printf(Exception,"CCore::Math::AddLen(a,...) : a is not in ulen value range");
 }

} // namespace Math
} // namespace CCore

