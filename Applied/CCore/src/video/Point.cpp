/* Point.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Applied
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/video/Point.h>

#include <CCore/inc/Exception.h>

namespace CCore {
namespace Video {

/* size functions */

void GuardSizeOverflow(const char *name)
 {
  Printf(Exception,"#;(...) : size overflow",name);
 }

/* struct PaneSub */

PaneSub::PaneSub(Pane outer,Pane inner)
 {
  if( !outer ) return;

  if( !inner )
    {
     top=outer;

     return;
    }

  inner=Inf_nonempty(outer,inner);

  if( !inner )
    {
     top=outer;

     return;
    }

  top.x=outer.x;
  top.y=outer.y;
  top.dx=outer.dx;
  top.dy=inner.y-outer.y;

  left.x=outer.x;
  left.y=inner.y;
  left.dx=inner.x-outer.x;
  left.dy=inner.dy;

  right.x=inner.x+inner.dx;
  right.y=inner.y;
  right.dx=outer.x+outer.dx-right.x;
  right.dy=inner.dy;

  bottom.x=outer.x;
  bottom.y=inner.y+inner.dy;
  bottom.dx=outer.dx;
  bottom.dy=outer.y+outer.dy-bottom.y;
 }

} // namespace Video
} // namespace CCore


