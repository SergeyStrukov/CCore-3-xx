/* SmallPrimes.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: Applied
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_math_SmallPrimes_h
#define CCore_inc_math_SmallPrimes_h

#include <CCore/inc/Gadget.h>

namespace CCore {
namespace Math {

/* global data */

 //
 // All primes < 1'000'000
 //

inline constexpr unsigned SmallPrimesCap = 1'000'000 ;

extern const unsigned SmallPrimes[78'498];

} // namespace Math
} // namespace CCore

#endif


