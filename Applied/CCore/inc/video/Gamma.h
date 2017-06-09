/* Gamma.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Applied
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_video_Gamma_h
#define CCore_inc_video_Gamma_h

#include <CCore/inc/Gadget.h>

namespace CCore {
namespace Video {

/* classes */

struct GammaFunc;

class GammaCorrect;

/* struct GammaFunc */

struct GammaFunc
 {
  const uint16 *direct;
  const uint8 *inverse;
 };

/* class GammaCorrect */

class GammaCorrect
 {
   static const uint16 DirectTable[256];

   static const uint8 InverseTable[65536];

  public:

   static uint16 Direct(uint8 val) { return DirectTable[val]; }

   static uint8 Inverse(uint16 val) { return InverseTable[val]; }

   static GammaFunc Default() { return {DirectTable,InverseTable}; }
 };

} // namespace Video
} // namespace CCore

#endif

