/* Shape.Radio.cpp */
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

#include <CCore/inc/video/lib/Shape.Radio.h>

#include <CCore/inc/video/FigureLib.h>

namespace CCore {
namespace Video {

/* class RadioShape */

SizeBox RadioShape::getMinSize() const
 {
  return +cfg.dxy;
 }

void RadioShape::draw(const DrawBuf &buf,DrawParam) const
 {
  MPane p(pane);

  if( !p ) return;

  p.square();

  SmoothDrawArt art(buf.cut(pane));

  MCoord len=p.dy;
  MCoord width=len/10;
  MCoord radius=len/2;

  MPoint center=p.getCenter();

  VColor gray=+cfg.gray;

  // body

  {
   VColor bottom = ( mover && enable )? +cfg.grayUp : +cfg.snow ;

   MCoord d=Ratio(600,10)*radius;

   art.ball(center,radius,TwoField(center.subXY(d),gray,center.addXY(d),bottom));
  }

  // mark

  if( check )
    {
     VColor mark = enable? +cfg.mark : gray ;

     art.ball(center,radius/3,mark);
    }

  // border

  {
   VColor border = focus? +cfg.focus : ( enable? +cfg.border : gray ) ;

   art.circle(center,radius-width/2,width,border);
  }
 }

} // namespace Video
} // namespace CCore

