/* Shape.Spinor.cpp */
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

#include <CCore/inc/video/lib/Shape.Spinor.h>

#include <CCore/inc/video/FigureLib.h>

namespace CCore {
namespace Video {

/* class SpinorShape */

Point SpinorShape::getInnerSize(int val) const
 {
  char temp[TextBufLen];
  PrintBuf out(Range(temp));

  Putobj(out,BindOpt(opt,val));

  TextSize ts=cfg.font->text(out.close());

  return ts.getSize();
 }

Point SpinorShape::getMinSize() const
 {
  Point s=Sup(getInnerSize(12345),getInnerSize(min_val),getInnerSize(max_val));

  Coord len=cfg.width.get().roundUp();

  Coord dy=s.y+2*len;
  Coord dx=s.x+4*dy;

  return Point(Sup(dx,4*dy),dy);
 }

SpinType SpinorShape::getZone(Point point) const
 {
  if( pane.contains(point) )
    {
     int x=point.x-pane.x;

     if( x<pane.dy ) return SpinType_Plus;

     if( pane.dx-x<pane.dy ) return SpinType_Minus;
    }

  return SpinType_None;
 }

void SpinorShape::draw(const DrawBuf &buf,DrawParam) const
 {
  MPane p(pane);

  if( !p ) return;

  VColor gray=+cfg.gray;
  MCoord width=+cfg.width;

  SmoothDrawArt art(buf.cut(pane));

  if( pane.dx/4<pane.dy )
    {
     art.block(pane,gray);

     return;
    }

  // body

  MCoord radius=p.dy/2;
  FigureRoundBox fig(p,radius);

  {
   fig.curveSolid(art,+cfg.back);

   VColor border = focus? +cfg.focus : ( enable? +cfg.border : gray ) ;

   fig.curveLoop(art,HalfPos,width,border);
  }

  // text

  {
   Coord dx=pane.dy;
   Coord dy=RoundUpLen(width);

   Pane inner=pane.shrink(dx,dy);

   char temp[TextBufLen];
   PrintBuf out(Range(temp));

   Putobj(out,BindOpt(opt,val));

   VColor text = enable? +cfg.text : gray ;

   cfg.font->textOn(art,inner,TextPlace(AlignX_Center,AlignY_Center),out.close(),text);
  }

  // buttons

  {
   MPoint c1=fig.getTopLeft().addY(radius);
   MPoint c2=fig.getTopRight().addY(radius);

   MCoord radius2=Div(9,10)*radius;

   MPoint f1=c1.subY(radius2);
   MPoint f2=c1.addY(radius2);

   if( enable )
     {
      TwoField field(f1,+cfg.snow,f2,gray);
      TwoField fieldUp(f1,+cfg.snowUp,f2,gray);

      if( val<max_val )
        {
         if( down==SpinType_Plus )
           {
            art.ball(c1,radius2,gray);
           }
         else if( mover==SpinType_Plus )
           {
            art.ball(c1,radius2,fieldUp);
           }
         else
           {
            art.ball(c1,radius2,field);
           }
        }
      else
        {
         art.ball(c1,radius2,field);
        }

      if( val>min_val )
        {
         if( down==SpinType_Minus )
           {
            art.ball(c2,radius2,gray);
           }
         else if( mover==SpinType_Minus )
           {
            art.ball(c2,radius2,fieldUp);
           }
         else
           {
            art.ball(c2,radius2,field);
           }
        }
      else
        {
         art.ball(c2,radius2,field);
        }
     }
   else
     {
      TwoField field(f1,+cfg.snow,f2,gray);

      art.ball(c1,radius2,field);

      art.ball(c2,radius2,field);
     }

   VColor fc = enable? +cfg.face : gray ;

   MCoord a=radius2/2;
   MCoord w=radius2/3;

   if( val<max_val )
     {
      art.path(w,fc,c1.subX(a),c1.addX(a));
      art.path(w,fc,c1.subY(a),c1.addY(a));
     }
   else
     {
      art.path(w,gray,c1.subX(a),c1.addX(a));
      art.path(w,gray,c1.subY(a),c1.addY(a));
     }

   if( val>min_val )
     {
      art.path(w,fc,c2.subX(a),c2.addX(a));
     }
   else
     {
      art.path(w,gray,c2.subX(a),c2.addX(a));
     }

   VColor border = enable? +cfg.border : gray ;

   if( val<max_val )
     {
      art.circle(c1,radius2-width/2,width,border);
     }
   else
     {
      art.circle(c1,radius2-width/2,width,gray);
     }

   if( val>min_val )
     {
      art.circle(c2,radius2-width/2,width,border);
     }
   else
     {
      art.circle(c2,radius2-width/2,width,gray);
     }

   MCoord r=w/2;

   switch( delta )
     {
      case 10 :
       {
        MPoint p1(radius2+r,0);

        art.ball(c1+p1,r,fc);

        art.ball(c2-p1,r,fc);
       }
      break;

      case 100 :
       {
        MPoint p1(radius2+r,r);
        MPoint p2(radius2+r,-r);

        art.ball(c1+p1,r,fc);
        art.ball(c1+p2,r,fc);

        art.ball(c2-p1,r,fc);
        art.ball(c2-p2,r,fc);
       }
      break;

      case 1000 :
       {
        MPoint p1(radius2+r,2*r);
        MPoint p2(radius2+r,0);
        MPoint p3(radius2+r,-2*r);

        art.ball(c1+p1,r,fc);
        art.ball(c1+p2,r,fc);
        art.ball(c1+p3,r,fc);

        art.ball(c2-p1,r,fc);
        art.ball(c2-p2,r,fc);
        art.ball(c2-p3,r,fc);
       }
      break;

      case 10'000 :
       {
        MPoint p1(radius2+r,3*r);
        MPoint p2(radius2+r,r);
        MPoint p3(radius2+r,-r);
        MPoint p4(radius2+r,-3*r);

        art.ball(c1+p1,r,fc);
        art.ball(c1+p2,r,fc);
        art.ball(c1+p3,r,fc);
        art.ball(c1+p4,r,fc);

        art.ball(c2-p1,r,fc);
        art.ball(c2-p2,r,fc);
        art.ball(c2-p3,r,fc);
        art.ball(c2-p4,r,fc);
       }
      break;

      case 100'000 :
       {
        MPoint p1(radius2+r,4*r);
        MPoint p2(radius2+r,2*r);
        MPoint p3(radius2+r,0);
        MPoint p4(radius2+r,-2*r);
        MPoint p5(radius2+r,-4*r);

        art.ball(c1+p1,r,fc);
        art.ball(c1+p2,r,fc);
        art.ball(c1+p3,r,fc);
        art.ball(c1+p4,r,fc);
        art.ball(c1+p5,r,fc);

        art.ball(c2-p1,r,fc);
        art.ball(c2-p2,r,fc);
        art.ball(c2-p3,r,fc);
        art.ball(c2-p4,r,fc);
        art.ball(c2-p5,r,fc);
       }
      break;
     }
  }
 }

} // namespace Video
} // namespace CCore

