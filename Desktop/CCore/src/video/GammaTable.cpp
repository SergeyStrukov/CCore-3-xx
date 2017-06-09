/* GammaTable.cpp */
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

#include <CCore/inc/video/GammaTable.h>

#include <math.h>

namespace CCore {
namespace Video {

/* class GammaTable */

template <UIntType UInt>
void GammaTable::Fill(PtrLen<UInt> table,double order)
 {
  double M=table.len-1;
  double V=MaxUInt<UInt>;

  for(ulen i=0; i<table.len ;i++)
    {
     double x=i/M;
     double y=pow(x,order);

     table[i]=UInt( round(V*y) );
    }
 }

GammaTable::GammaTable() noexcept
 {
 }

GammaTable::~GammaTable()
 {
 }

void GammaTable::fill(double order)
 {
  static const ulen DirectLen = ulen(1)<<8 ;
  static const ulen InverseLen = ulen(1)<<16 ;

  if( !direct.getLen() )
    {
     SimpleArray<uint16> direct_(DirectLen);
     SimpleArray<uint8> inverse_(InverseLen);

     direct=std::move(direct_);
     inverse=std::move(inverse_);
    }

  Fill(Range(direct),order);
  Fill(Range(inverse),1/order);

  this->order=order;
 }

} // namespace Video
} // namespace CCore

