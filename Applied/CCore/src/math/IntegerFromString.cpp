/* IntegerFromString.cpp */
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

#include <CCore/inc/math/IntegerFromString.h>

#include <CCore/inc/Exception.h>

namespace CCore {
namespace Math {

/* functions */

void GuardIntegerBadString()
 {
  Printf(Exception,"CCore::Math::IntegerFromString<...> : bad string");
 }

} // namespace Math
} // namespace CCore

