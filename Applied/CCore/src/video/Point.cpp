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

/* Align...() */

Pane AlignLeft(Pane pane,Coord dx)
 {
  if( dx<=pane.dx )
    {
     return Pane(pane.x,pane.y,dx,pane.dy);
    }
  else
    {
     return pane;
    }
 }

Pane AlignCenterX(Pane pane,Coord dx)
 {
  if( dx<=pane.dx )
    {
     Coord off=(pane.dx-dx)/2;

     return Pane(pane.x+off,pane.y,dx,pane.dy);
    }
  else
    {
     return pane;
    }
 }

Pane AlignRight(Pane pane,Coord dx)
 {
  if( dx<=pane.dx )
    {
     Coord off=pane.dx-dx;

     return Pane(pane.x+off,pane.y,dx,pane.dy);
    }
  else
    {
     return pane;
    }
 }

Pane AlignTop(Pane pane,Coord dy)
 {
  if( dy<=pane.dy )
    {
     return Pane(pane.x,pane.y,pane.dx,dy);
    }
  else
    {
     return pane;
    }
 }

Pane AlignCenterY(Pane pane,Coord dy)
 {
  if( dy<=pane.dy )
    {
     Coord off=(pane.dy-dy)/2;

     return Pane(pane.x,pane.y+off,pane.dx,dy);
    }
  else
    {
     return pane;
    }
 }

Pane AlignBottom(Pane pane,Coord dy)
 {
  if( dy<=pane.dy )
    {
     Coord off=pane.dy-dy;

     return Pane(pane.x,pane.y+off,pane.dx,dy);
    }
  else
    {
     return pane;
    }
 }

Pane AlignCenter(Pane pane,Coord dx,Coord dy)
 {
  if( dx<=pane.dx )
    {
     if( dy<=pane.dy )
       {
        Coord off_x=(pane.dx-dx)/2;
        Coord off_y=(pane.dy-dy)/2;

        return Pane(pane.x+off_x,pane.y+off_y,dx,dy);
       }
     else
       {
        Coord off_x=(pane.dx-dx)/2;

        return Pane(pane.x+off_x,pane.y,dx,pane.dy);
       }
    }
  else
    {
     if( dy<=pane.dy )
       {
        Coord off_y=(pane.dy-dy)/2;

        return Pane(pane.x,pane.y+off_y,pane.dx,dy);
       }
     else
       {
        return pane;
       }
    }
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


