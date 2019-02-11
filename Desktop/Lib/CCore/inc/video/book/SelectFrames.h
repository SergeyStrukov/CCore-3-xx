/* SelectFrames.h */
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

#ifndef CCore_inc_video_book_SelectFrames_h
#define CCore_inc_video_book_SelectFrames_h

#include <CCore/inc/video/Point.h>

namespace CCore {
namespace Video {
namespace Book {
namespace DrawBook {

/* classes */

struct SelectFrames;

/* struct SelectFrames */

struct SelectFrames
 {
  ulen ind;
  ulen lim;

  SelectFrames(PtrLen<const Coord> downs,Coord base,Coord clip,Coord clip_len);
 };

} // namespace DrawBook
} // namespace Book
} // namespace Video
} // namespace CCore

#endif


