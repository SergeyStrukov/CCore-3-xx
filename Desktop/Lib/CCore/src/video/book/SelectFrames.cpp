/* SelectFrames.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.60
//
//  Tag: Desktop
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/video/book/SelectFrames.h>

#include <CCore/inc/algon/BinarySearch.h>

namespace CCore {
namespace Video {
namespace Book {
namespace DrawBook {

/* struct SelectFrames */

SelectFrames::SelectFrames(PtrLen<const Coord> downs,Coord base,Coord clip,Coord clip_len)
 {
  //
  // ind <= downs.len
  //
  // ind -> min : base+downs[ind] > clip
  //

  Coord cut=clip-base;

  auto ret1=Algon::BinarySearch_if(downs, [cut] (Coord down) { return down > cut ; } );

  ind=ret1.len;

  //
  // ind <= lim <= downs.len
  //

  //
  // lim -> min : base+downs[lim-1] >= clip+clipLen
  //

  cut+=clip_len;

  auto ret2=Algon::BinarySearch_if(downs, [cut] (Coord down) { return down >= cut ; } );

  if( +downs )
    {
     lim=ind+ret2.len+1;
    }
  else
    {
     lim=ind+ret2.len;
    }
 }

} // namespace DrawBook
} // namespace Book
} // namespace Video
} // namespace CCore


