/* FavFrame.cpp */
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

//#include <CCore/inc/video/FavFrame.h>
#include <inc/FavFrame.h>

namespace CCore {
namespace Video {

/* class FavListShape */

Point FavListShape::getMinSize() const
 {
  return Point(100,100);
 }

void FavListShape::layout()
 {
 }

void FavListShape::draw(const DrawBuf &buf,DrawParam draw_param) const
 {
  Used(buf);
  Used(draw_param);
 }

} // namespace Video
} // namespace CCore

