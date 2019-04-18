/* Shape.AllButton.cpp */
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

#include <CCore/inc/video/lib/Shape.AllButton.h>

#include <CCore/inc/video/FigureLib.h>

namespace CCore {
namespace Video {

/* class AllButtonShape */

Point AllButtonShape::getMinSize() const
 {
  Coord dy=+cfg.dy;

  return Point(XdivY(Aspect)*dy,dy);
 }

void AllButtonShape::draw(const DrawBuf &buf,DrawParam) const
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

   MCoord y0=p.y+H/2+shift;

   MCoord x0=p.x+Div(6,10)*H+shift;
   MCoord x1=x0+Div(2,3)*H;

   FigureAsterisk fig1({x0,y0},radius);

   fig1.curveSolid(art,face);

   MPoint center(x1,y0);

   MCoord a=Div(4,5)*radius;
   MCoord w=Div(2,5)*radius;

   if( this->face==AllPlus )
     {
      art.path(w,face,center.subX(a),center.addX(a));
      art.path(w,face,center.subY(a),center.addY(a));
     }
   else
     {
      art.path(w,face,center.subX(a),center.addX(a));
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


