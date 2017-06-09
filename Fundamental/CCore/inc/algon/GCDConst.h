/* GCDConst.h */
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

#ifndef CCore_inc_algon_GCDConst_h
#define CCore_inc_algon_GCDConst_h

#include <CCore/inc/Gadget.h>

namespace CCore {
namespace Algon {

/* EuclidAlgo<UInt,UInt A,UInt B>() */

template <UIntType UInt,UInt A,UInt B>
constexpr UInt EuclidAlgo()
 {
  return A? EuclidAlgo<UInt,B%(A?A:1),A>() : B ;
 }

/* const GCDConst<UInt,UInt A,UInt B> */

template <UIntType UInt,UInt A,UInt B>
inline constexpr UInt GCDConst = EuclidAlgo<UInt,A,B>() ;

/* const LCMConst<UInt,UInt A,UInt B> */

template <UIntType UInt,UInt A,UInt B> requires ( A!=0 || B!=0 )
inline constexpr UInt LCMConst = UIntConstMul<UInt, A/GCDConst<UInt,A,B> , B > ;

} // namespace Algon
} // namespace CCore

#endif


