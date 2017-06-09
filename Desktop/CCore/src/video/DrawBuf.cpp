/* DrawBuf.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
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

#include <CCore/inc/video/DrawBuf.h>

namespace CCore {
namespace Video {

/* class DrawBuf */

DrawBuf DrawBuf::cut(Pane pane) const
 {
  pane=Inf(map(pane),buf.getPane());

  if( !pane ) return DrawBuf();

  return DrawBuf(buf.cutFrame_unsafe(pane),origin-pane.getBase());
 }

DrawBuf DrawBuf::cutRebase(Pane pane) const
 {
  DrawBuf ret=cut(pane);

  ret.origin+=pane.getBase();

  return ret;
 }

} // namespace Video
} // namespace CCore


