/* Shape.Button.cpp */
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

#include <CCore/inc/video/lib/Shape.Button.h>

#include <CCore/inc/video/FigureLib.h>

namespace CCore {
namespace Video {

/* class ButtonShape */

MCoord ButtonShape::FigEX(Coord fdy,MCoord width)
 {
  return Max_cast(width, (Fraction(fdy)+2*width)/4 );
 }

Point ButtonShape::getMinSize() const
 {
  TextSize ts=cfg.font->text(Range(face));

  MCoord width=+cfg.width;

  MCoord ex=FigEX(ts.dy,width);

  Coord dx=RoundUpLen(ex);
  Coord dy=RoundUpLen(width);

  return 2*Point(dx,dy)+ts.getSize()+(+cfg.space);
 }

void ButtonShape::draw(const DrawBuf &buf,DrawParam) const
 {
  MPane p(pane);

  if( !p ) return;

  SmoothDrawArt art(buf.cut(pane));

  const Font &font=cfg.font.get();

  // figure

  MCoord width=+cfg.width;

  FontSize fs=font->getSize();

  MCoord ex=FigEX(fs.dy,width);

  VColor gray=+cfg.gray;

  if( ex>p.dx/3 )
    {
     art.block(pane,gray);

     return;
    }

  FigureButton fig(p,ex);

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

  // text

  {
   Coord dx=RoundUpLen(ex);
   Coord dy=RoundUpLen(width);

   Point shift=Null;

   if( down ) shift=Point::Diag( (dy+1)/2 );

   VColor text = enable? +cfg.text : gray ;

   font->textOn(art,pane.shrink(dx,dy)+shift,TextPlace(AlignX_Center,AlignY_Center),Range(face),text);
  }

  // border

  {
   VColor border = focus? +cfg.focus : ( enable? +cfg.border : gray ) ;

   fig.curveLoop(art,HalfPos,width,border);
  }
 }

/* class RefButtonShape */

Point RefButtonShape::getMinSize() const
 {
  ButtonShape temp(cfg,face.get());

  temp.pane=pane;

  temp.enable=enable;
  temp.focus=focus;
  temp.mover=mover;
  temp.down=down;

  temp.mouse=mouse;

  return temp.getMinSize();
 }

void RefButtonShape::draw(const DrawBuf &buf,DrawParam draw_param) const
 {
  ButtonShape temp(cfg,face.get());

  temp.pane=pane;

  temp.enable=enable;
  temp.focus=focus;
  temp.mover=mover;
  temp.down=down;

  temp.mouse=mouse;

  temp.draw(buf,draw_param);
 }

/* class KnobShape */

SizeBox KnobShape::getMinSize() const
 {
  return +cfg.dxy;
 }

void KnobShape::draw(const DrawBuf &buf,DrawParam) const
 {
  MPane p(pane);

  if( !p ) return;

  p.square();

  SmoothDrawArt art(buf.cut(pane));

  // center and radius

  MCoord len=p.dx;
  MCoord radius=len/2;

  MPoint center=p.getCenter();

  VColor gray=+cfg.gray;

  // body

  if( down )
    {
     art.ball(center,radius,gray);
    }
  else
    {
     VColor top = ( mover && enable )? +cfg.snowUp : +cfg.snow ;

     art.ball(center,radius,YField(p.y,top,p.ey,gray));
    }

  // face

  VColor fc = enable? +cfg.face : gray ;

  switch( face )
    {
     case FaceOk :
      {
       MCoord a=radius/2;
       MCoord w=radius/3;

       MPoint A=center+MPoint(-a,0);
       MPoint B=center+MPoint(-a/3,a);
       MPoint C=center+MPoint(a,-a);

       art.path(w,fc,A,B,C);
      }
     break;

     case FacePlus :
      {
       MCoord a=radius/2;
       MCoord w=radius/3;

       art.path(w,fc,center.subX(a),center.addX(a));
       art.path(w,fc,center.subY(a),center.addY(a));
      }
     break;

     case FaceMinus :
      {
       MCoord a=radius/2;
       MCoord w=radius/3;

       art.path(w,fc,center.subX(a),center.addX(a));
      }
     break;

     case FaceList :
      {
       MCoord a=radius/2;
       MCoord w=radius/3;

       MPoint p=center.subY(a);
       MPoint q=center.addY(a);

       art.path(w,fc,p.subX(a),p.addX(a));
       art.path(w,fc,center.subX(a),center.addX(a));
       art.path(w,fc,q.subX(a),q.addX(a));
      }
     break;

     case FaceCross :
      {
       MCoord a=radius/2;
       MCoord w=radius/3;

       art.path(w,fc,center.subXY(a),center.addXY(a));
       art.path(w,fc,center.addXsubY(a),center.subXaddY(a));
      }
     break;

     case FaceAsterisk :
      {
       FigureAsterisk fig(center,Ratio(652,10)*radius);

       fig.curveSolid(art,fc);
      }
     break;

     case FaceExclamation :
      {
       PolyFigureExclamation fig(center.x,center.y-Div(2,3)*radius,Div(4,3)*radius);

       fig.solid(art,fc);
      }
     break;

     case FaceQuestion :
      {
       PolyFigureQuestion fig(center.x,center.y-Div(2,3)*radius,Div(4,3)*radius);

       fig.solid(art,fc);
      }
     break;

     case FaceLeft :
      {
       MCoord a=radius/2;
       MCoord d=radius/12;

       FigureLeftArrow fig(-d-a,a-d,-a,a);

       fig.shift(center);

       fig.curveSolid(art,fc);
      }
     break;

     case FaceRight :
      {
       MCoord a=radius/2;
       MCoord d=radius/12;

       FigureRightArrow fig(d-a,a+d,-a,a);

       fig.shift(center);

       fig.curveSolid(art,fc);
      }
     break;

     case FaceUp :
      {
       MCoord a=radius/2;
       MCoord d=radius/12;

       FigureUpArrow fig(-a,a,-d-a,a-d);

       fig.shift(center);

       fig.curveSolid(art,fc);
      }
     break;

     case FaceDown :
      {
       MCoord a=radius/2;
       MCoord d=radius/12;

       FigureDownArrow fig(-a,a,d-a,a+d);

       fig.shift(center);

       fig.curveSolid(art,fc);
      }
     break;

     case FaceStop :
      {
       MCoord a=radius/2;

       FigureBox fig(-a,a,-a,a);

       fig.shift(center);

       fig.solid(art,fc);
      }
     break;

     case FaceRightRight :
      {
       MCoord a=radius/2;
       MCoord d2=radius/3;
       MCoord d1=d2/2;

       FigureRightArrow fig1(-a,a,-a,a);
       FigureRightArrow fig2(fig1);

       fig1.shift(center.subX(d1));

       fig1.curveSolid(art,fc);

       fig2.shift(center.addX(d2));

       fig2.curveSolid(art,fc);
      }
     break;

     case FaceLeftLeft :
      {
       MCoord a=radius/2;
       MCoord d2=radius/3;
       MCoord d1=d2/2;

       FigureLeftArrow fig1(-a,a,-a,a);
       FigureLeftArrow fig2(fig1);

       fig1.shift(center.addX(d1));

       fig1.curveSolid(art,fc);

       fig2.shift(center.subX(d2));

       fig2.curveSolid(art,fc);
      }
     break;

     case FaceReload :
      {
       FigureReload fig(center.x,center.y,Div(5,6)*radius);

       fig.curveSolid(art,fc);
      }
     break;

     case FaceLove :
      {
       FigureLove fig(center.x,center.y,Div(3,4)*radius);

       fig.curveSolid(art,fc);
      }
     break;

     case FaceCog :
      {
       FigureCog fig(center.x,center.y,Div(3,4)*radius);

       fig.curveSolid(art,fc);
      }
     break;
    }

  // border

  {
   MCoord width=+cfg.width;

   VColor border = focus? +cfg.focus : ( enable? +cfg.border : gray ) ;

   art.circle(center,radius-width/2,width,border);
  }
 }

} // namespace Video
} // namespace CCore

