/* InfoSize.cpp */
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

#include <CCore/inc/video/InfoSize.h>

namespace CCore {
namespace Video {

/* functions */

Point InfoSize(Font font,Info info)
 {
  Coord dx=0;
  CoordAcc dy;

  for(ulen index=0,count=info->getLineCount(); index<count ;index++)
    {
     TextSize ts=font->text(info->getLine(index));

     Replace_max(dx,ts.full_dx);

     dy.add(ts.dy);
    }

  return Point(dx,dy.value);
 }

} // namespace Video
} // namespace CCore

