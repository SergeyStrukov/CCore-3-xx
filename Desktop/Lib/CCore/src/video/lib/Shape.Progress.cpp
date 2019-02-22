/* Shape.Progress.cpp */
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

#include <CCore/inc/video/lib/Shape.Progress.h>

#include <CCore/inc/video/FigureLib.h>

namespace CCore {
namespace Video {

/* class ProgressShape */

SizeY ProgressShape::getMinSize() const
 {
  return +cfg.dy;
 }

void ProgressShape::draw(const DrawBuf &buf,DrawParam) const
 {
  MPane p(pane);

  if( !p ) return;

  SmoothDrawArt art(buf.cut(pane));

  MCoord t=Position(pos,total,p.x,p.ex);

  MCoord width=+cfg.width;

  VColor border=+cfg.border;

  // body

  {
   FigureBox fig(p.cutLeft(t));

   fig.solid(art,YField(p.y,+cfg.snowUp,p.ey,+cfg.grayUp));
  }
  {
   FigureBox fig(p.cutRight(t));

   fig.solid(art,YField(p.y,+cfg.snow,p.ey,+cfg.gray));
  }
  {
   FigureBox fig(p);

   fig.loop(art,HalfPos,width,border);
  }

  // active

  if( has_active )
    {
     MCoord y=p.y+Div(1,10)*p.dy;
     MCoord dy=Div(8,10)*p.dy;
     MCoord ey=y+dy;

     MCoord x=p.x+width;
     MCoord dx=dy+Div(active_pos,MaxActivePos)*dy;

     MCoord len=dx/3;
     MCoord shift=len-width;

     MCoord radius=Div(40,100)*Min(len,dy);

     YField field(y,+cfg.snowPing,ey,+cfg.grayPing);

     for(unsigned count=5; count ;count--,x+=shift)
       {
        FigureRoundBox fig(x,x+len,y,ey,radius);

        fig.curveSolid(art,field);

        fig.curveLoop(art,HalfPos,width,border);
       }
    }
 }

/* class ArrowProgressShape */

SizeY ArrowProgressShape::getMinSize() const
 {
  return +cfg.dy;
 }

void ArrowProgressShape::draw(const DrawBuf &buf,DrawParam) const
 {
  MPane p(pane);

  if( !p ) return;

  SmoothDrawArt art(buf.cut(pane));

  MCoord t=Position(pos,total,p.x,p.ex);

  MCoord width=+cfg.width;

  VColor border=+cfg.border;

  // body

  {
   FigureBox fig(p.cutLeft(t));

   fig.solid(art,YField(p.y,+cfg.snowUp,p.ey,+cfg.grayUp));
  }
  {
   FigureBox fig(p.cutRight(t));

   fig.solid(art,YField(p.y,+cfg.snow,p.ey,+cfg.gray));
  }
  {
   FigureBox fig(p);

   fig.loop(art,HalfPos,width,border);
  }

  // active

  if( has_active )
    {
     MCoord y=p.y+Div(1,10)*p.dy;
     MCoord dy=Div(8,10)*p.dy;
     MCoord ey=y+dy;

     YField field(y,+cfg.snowArrow,ey,+cfg.grayArrow);

     MCoord x=p.x+width;
     MCoord dx=ey-y;

     MCoord shift=Div(active_pos,MaxActivePos)*dx;

     x+=shift/4;

     for(unsigned count=5; count ;count--,x+=shift)
       {
        MPane outer(x,x+dx,y,ey);

        FigureRightArrow fig1(outer);

        fig1.curveSolid(art,field);

        auto fig2=fig1.border(width);

        fig2.curveSolid(art,border);
       }
    }
 }

} // namespace Video
} // namespace CCore

