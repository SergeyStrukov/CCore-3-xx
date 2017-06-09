/* CheckPlatformBase.cpp */
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

#include <CCore/inc/base/PlatformBase.h>

namespace CCore {

namespace Private_CheckPlatformBase {

#if 0

template <class UInt,UInt Val=UInt(-1)>
const unsigned BitsOf = (Val>1)? 1+BitsOf<UInt,(Val>>1)> : Val ;

#else

template <class UInt>
constexpr unsigned BitsOfFunc(UInt val)
 {
  return (val>1)? 1+BitsOfFunc<UInt>(val>>1) : val ;
 }

template <class UInt,UInt Val=UInt(-1)>
const unsigned BitsOf = BitsOfFunc<UInt>(Val) ;

#endif

} // namespace Private_CheckPlatformBase

using namespace Private_CheckPlatformBase;

/* asserts */

static_assert( std::is_same<uint8,unsigned char>::value ,"CCore::uint8 : must be unsigned char");

static_assert( BitsOf<uint8 > == 8 ,"CCore::uint8 : broken definition");
static_assert( BitsOf<uint16> == 16 ,"CCore::uint16 : broken definition");
static_assert( BitsOf<uint32> == 32 ,"CCore::uint32 : broken definition");
static_assert( BitsOf<uint64> == 64 ,"CCore::uint64 : broken definition");

static_assert( BitsOf<unsigned char     > == Bits::unsigned_char      ,"CCore::Bits::unsigned_char : broken definition");
static_assert( BitsOf<unsigned short    > == Bits::unsigned_short     ,"CCore::Bits::unsigned_short : broken definition");
static_assert( BitsOf<unsigned int      > == Bits::unsigned_int       ,"CCore::Bits::unsigned_int : broken definition");
static_assert( BitsOf<unsigned long     > == Bits::unsigned_long      ,"CCore::Bits::unsigned_long : broken definition");
static_assert( BitsOf<unsigned long long> == Bits::unsigned_long_long ,"CCore::Bits::unsigned_long_long : broken definition");

static_assert( BitsOf<ulen> >= BitsOf<std::size_t> ,"CCore::ulen : broken definition");

static_assert( MaxBitLen >= BitsOf<unsigned long long> ,"CCore::MaxBitLen : broken definition");

} // namespace CCore


