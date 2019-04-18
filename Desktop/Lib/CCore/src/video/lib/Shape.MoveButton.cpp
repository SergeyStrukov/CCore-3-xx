/* Shape.MoveButton.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.60
//
//  Tag: Desktop
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/video/lib/Shape.MoveButton.h>

#include <CCore/inc/video/FigureLib.h>

namespace CCore {
namespace Video {

/* class MoveButtonShape */

Point MoveButtonShape::getMinSize() const
 {
  Coord dy=+cfg.dy;

  return Point(XdivY(Aspect)*dy,dy);
 }

void MoveButtonShape::draw(const DrawBuf &buf,DrawParam) const
 {
  Pane pane=AdjustAspect(Aspect,this->pane);

  MPane p(pane);

  if( !p ) return;

  SmoothDrawArt art(buf.cut(pane));

  // figure

  MCoord width=+cfg.width;

  VColor gray=+cfg.gray;

  MCoord H=p.dy;

  FigureButton fig(p,H/5);

  // body

  if( down )
    {
     fig.curveSolid(art,gray);
    }
  else
    {
     VColor top = ( mover && enable )? +cfg.snowUp : +cfg.snow ;

     fig.curveSolid(art,YField(p.y,top,p.ey,gray));
    }

  // face

  {
   VColor face = enable? +cfg.face : gray ;

   Coord dy=RoundUpLen(width);

   MCoord shift=0;

   if( down ) shift=Fraction( (dy+1)/2 );

   MCoord s=H/10;
   MCoord radius=H/2-2*s;

   MCoord y0=p.y+s+shift;
   MCoord y1=p.y+H/2+shift;
   MCoord y2=p.ey-s+shift;

   if( this->face==BackDir )
     {
      MCoord x0=p.x+H/4+shift;
      MCoord x1=x0+(H-2*s);
      MCoord x2=x1+(radius-s/2);

      FigureLeftArrow fig1(x0,x1,y0,y2);

      fig1.curveSolid(art,face);

      art.ball(MPoint(x2,y1),radius,face);
     }
   else
     {
      MCoord x0=p.ex-H/4+shift;
      MCoord x1=x0-(H-2*s);
      MCoord x2=x1-(radius-s/2);

      FigureRightArrow fig1(x1,x0,y0,y2);

      fig1.curveSolid(art,face);

      art.ball(MPoint(x2,y1),radius,face);
     }
  }

  // border

  {
   VColor border = focus? +cfg.focus : ( enable? +cfg.border : gray ) ;

   fig.curveLoop(art,HalfPos,width,border);
  }
 }

} // namespace Video
} // namespace CCore

