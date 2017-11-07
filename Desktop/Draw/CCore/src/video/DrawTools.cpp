/* DrawTools.cpp */
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

#include <CCore/inc/video/DrawTools.h>

namespace CCore {
namespace Video {

/* struct CircleSpline */

CircleSpline::CircleSpline(Point center,Coord radius)
 {
  IntGuard( radius>0 );

  Coord x=Coord( radius/2 );
  Coord y=Coord( UIntFunc<uMCoord>::SqRoot(Sq<uMCoord>(radius)-Sq<uMCoord>(x),radius) );

  buf[0]=center+Point(0,radius);
  buf[1]=center+Point(x,y);
  buf[2]=center+Point(y,x);

  buf[3]=center+Point(radius,0);
  buf[4]=center+Point(y,-x);
  buf[5]=center+Point(x,-y);

  buf[6]=center-Point(0,radius);
  buf[7]=center-Point(x,y);
  buf[8]=center-Point(y,x);

  buf[9]=center-Point(radius,0);
  buf[10]=center-Point(y,-x);
  buf[11]=center-Point(x,-y);
 }

/* struct PaneBorder */

PaneBorder::PaneBorder(Pane pane)
 {
  Coord x=pane.x+pane.dx-1;
  Coord y=pane.y+pane.dy-1;

  buf[0]=Point(pane.x,pane.y);
  buf[1]=Point(pane.x,y);
  buf[2]=Point(x,y);
  buf[3]=Point(x,pane.y);
 }

} // namespace Video
} // namespace CCore

