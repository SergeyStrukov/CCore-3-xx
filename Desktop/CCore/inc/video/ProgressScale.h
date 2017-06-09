/* ProgressScale.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: Desktop
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_video_ProgressScale_h
#define CCore_inc_video_ProgressScale_h

#include <CCore/inc/Gadget.h>

namespace CCore {
namespace Video {

/* classes */

template <UIntType UInt> class ProgressScale;

/* class ProgressScale<UInt> */

template <UIntType UInt>
class ProgressScale
 {
   unsigned shift;

  public:

   ProgressScale() : shift(0) {}

   unsigned set(UInt total)
    {
     shift=PosSub(UIntBitsOf(total),Meta::UIntBits<unsigned>);

     return unsigned(total>>shift);
    }

   unsigned operator () (UInt pos) const { return unsigned(pos>>shift); }
 };

} // namespace Video
} // namespace CCore

#endif

