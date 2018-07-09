/* SelectFrames.h */
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

#ifndef SelectFrames_h
#define SelectFrames_h

#include <inc/App.h>

namespace App {

/* classes */

struct SelectFrames;

/* struct SelectFrames */

struct SelectFrames
 {
  ulen ind;
  ulen lim;

  SelectFrames(PtrLen<const Coord> downs,Coord base,Coord clip,Coord clipLen);
 };

} // namespace App

#endif


