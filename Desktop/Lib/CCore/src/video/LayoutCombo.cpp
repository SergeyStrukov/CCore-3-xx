/* LayoutCombo.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Desktop
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/video/LayoutCombo.h>

namespace CCore {
namespace Video {

/* functions */

Coord PosSubMul(Coord a,ulen count,Coord b)
 {
  if( a<=0 ) return 0;

  if( b<=0 ) return a;

  Coord m=a/b;

  if( count>ulen(m) ) return 0;

  return a-Coord(count)*b;
 }

} // namespace Video
} // namespace CCore

