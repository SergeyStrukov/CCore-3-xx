/* GammaTable.h */
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

#ifndef CCore_inc_video_GammaTable_h
#define CCore_inc_video_GammaTable_h

#include <CCore/inc/video/Gamma.h>

#include <CCore/inc/Array.h>

namespace CCore {
namespace Video {

/* classes */

class GammaTable;

/* class GammaTable */

class GammaTable : NoCopy
 {
   SimpleArray<uint16> direct;
   SimpleArray<uint8> inverse;
   double order = 0 ;

  private:

   template <UIntType UInt>
   static void Fill(PtrLen<UInt> table,double order);

  public:

   // constructors

   GammaTable() noexcept;

   explicit GammaTable(double order) : GammaTable() { fill(order); }

   ~GammaTable();

   // methods

   void fill(double order);

   double getOrder() const { return order; }

   GammaFunc getFunc() const
    {
     if( direct.getLen() )
       return {direct.getPtr(),inverse.getPtr()};
     else
       return GammaCorrect::Default();
    }
 };

} // namespace Video
} // namespace CCore

#endif

