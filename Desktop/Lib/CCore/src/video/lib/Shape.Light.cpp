/* Shape.Light.cpp */
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

#include <CCore/inc/video/lib/Shape.Light.h>

#include <CCore/inc/video/FigureLib.h>

namespace CCore {
namespace Video {

/* class LightShape */

SizeBox LightShape::getMinSize() const
 {
  return +cfg.dxy;
 }

void LightShape::draw(const DrawBuf &buf,DrawParam) const
 {
  MPane p(pane);

  if( !p ) return;

  p.square();

  SmoothDrawArt art(buf.cut(pane));

  MCoord len=p.dy;
  MCoord radius=len/2;
  MCoord d=Ratio(600,10)*radius;
  MCoord radius2=Ratio(819,10)*radius;

  MPoint center=p.getCenter();

  art.ball(center,radius,TwoField(center.subXY(d),+cfg.gray,center.addXY(d),+cfg.snow));

  if( on )
    {
     art.ball(center,radius2,RadioField(center.subXY(radius/3),radius,White,face));
    }
  else
    {
     art.ball(center,radius2,+cfg.inactive);
    }
 }

} // namespace Video
} // namespace CCore

