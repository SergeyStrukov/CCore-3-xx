/* Shape.Slider.cpp */
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

#include <CCore/inc/video/lib/Shape.Slider.h>

#include <CCore/inc/video/FigureLib.h>

namespace CCore {
namespace Video {

/* class XSliderShape */

SizeY XSliderShape::getMinSize() const
 {
  return +cfg.dxy;
 }

unsigned XSliderShape::getPos(Point point) const
 {
  MPane p(pane);

  if( !p ) return 0;

  if( pane.dx<8*pane.dy ) return 0;

  MCoord delta=p.dy/4;

  MCoord A=p.x+delta;
  MCoord B=p.ex-delta;

  MCoord X=Fraction(point.x);

  if( X<=A ) return 0;

  if( X>=B ) return cap;

  return UIntMulDiv<unsigned>(X-A,cap,B-A);
 }

void XSliderShape::draw(const DrawBuf &buf) const
 {
  MPane p(pane);

  if( !p ) return;

  MCoord width=+cfg.width;

  VColor snow=+cfg.snow;
  VColor snowUp=+cfg.snowUp;
  VColor gray=+cfg.gray;
  VColor mark=+cfg.mark;

  VColor top = enable? ( mover? snowUp : snow ) : gray ;

  SmoothDrawArt art(buf.cut(pane));

  if( pane.dx<8*pane.dy )
    {
     art.block(pane,gray);

     return;
    }

  // line

  MCoord delta=p.dy/4;
  MCoord wline=p.dy/5;

  MPoint A=p.getLeftMid().addX(delta);
  MPoint B=p.getRightMid().subX(delta);

  {
   MCoord y1=A.y-wline/2;
   MCoord y2=A.y+wline/2;

   MCoord y0=y1-wline;
   MCoord y3=y2+wline;

   FigureBox fig(A.x,B.x,y1,y2);

   fig.solid(art,YField(y1,gray,y2,top));

   for(unsigned i=0,m=10; i<=m ;i++)
     {
      MCoord x=Position(i,m,A.x,B.x);

      art.path(width,mark,MPoint(x,y0),MPoint(x,y1));
      art.path(width,mark,MPoint(x,y2),MPoint(x,y3));
     }
  }

  // slider

  {
   MCoord x=Position(pos,cap,A.x,B.x);
   MCoord d=delta/2;

   art.ball({x,A.y},wline/2,mark);

   FigurePoints<4> fig;

   fig[0]={x,p.y+d};
   fig[1]={x,p.ey-d};

   MCoord w=delta/4;

   fig[2]=fig[1].subXY(w);
   fig[3]=fig[0].subXaddY(w);

   fig.solid(art,top);

   fig[2]=fig[1].addXsubY(w);
   fig[3]=fig[0].addXY(w);

   fig.solid(art,gray);
  }

  // border

  {
   FigureBox fig(p);

   VColor border = focus? +cfg.focus : ( enable? +cfg.border : gray ) ;

   fig.loop(art,HalfPos,width,border);
  }
 }

/* class YSliderShape */

SizeX YSliderShape::getMinSize() const
 {
  return +cfg.dxy;
 }

unsigned YSliderShape::getPos(Point point) const // TODO
 {
 }

void YSliderShape::draw(const DrawBuf &buf) const // TODO
 {
 }

} // namespace Video
} // namespace CCore

