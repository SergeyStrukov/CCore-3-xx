/* IntegerDivider.cpp */
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

#include <CCore/inc/math/IntegerDivider.h>

#include <CCore/inc/Exception.h>

namespace CCore {
namespace Math {

/* guards */

void GuardIntegerInverseNotNormalized()
 {
  Printf(Exception,"CCore::Math::IntegerInverse<...> : not normalized");
 }

void GuardIntegerInverseOverflow()
 {
  Printf(Exception,"CCore::Math::IntegerInverse<...> : overflow");
 }

void GuardIntegerZeroDivide()
 {
  Printf(Exception,"CCore::Math::IntegerDivider<...> : zero divide");
 }

} // namespace Math
} // namespace CCore

