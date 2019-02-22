/* Shape.Check.cpp */
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
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/video/lib/Shape.Check.h>

#include <CCore/inc/video/FigureLib.h>

namespace CCore {
namespace Video {

/* class CheckShape */

SizeBox CheckShape::getMinSize() const
 {
  return +cfg.dxy;
 }

void CheckShape::draw(const DrawBuf &buf,DrawParam) const
 {
  MPane p(pane);

  if( !p ) return;

  p.square();

  SmoothDrawArt art(buf.cut(pane));

  // border

  MCoord len=p.dx;
  MCoord width=len/10;

  FigureBox fig(p);

  VColor gray=+cfg.gray;

  // body

  {
   VColor bottom = ( mover && enable )? +cfg.grayUp : +cfg.snow ;

   fig.solid(art,TwoField(p.getTopLeft().addXY(width),gray,p.getBottomRight().subXY(width),bottom));
  }

  // mark

  if( check )
    {
     MCoord x0=p.x;
     MCoord x1=p.ex;

     MCoord y0=p.y;
     MCoord y1=p.ey;

     MCoord d=(3*width)/2;

     MPoint A(x0+d,y0+len/2);
     MPoint B(x0+(len+d)/3,y1-d);
     MPoint C(x1-d,y0+d);

     VColor mark = enable? +cfg.mark : gray ;

     art.path(width,mark,A,B,C);
    }

  // border

  {
   VColor border = focus? +cfg.focus : ( enable? +cfg.border : gray ) ;

   fig.loop(art,HalfPos,width,border);
  }
 }

} // namespace Video
} // namespace CCore

