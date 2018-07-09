/* SelectFrames.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: Book 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/SelectFrames.h>

#include <CCore/inc/algon/BinarySearch.h>

namespace App {

/* struct SelectFrames */

SelectFrames::SelectFrames(PtrLen<const Coord> downs,Coord base,Coord clip,Coord clipLen)
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

  cut+=clipLen;

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

} // namespace App


