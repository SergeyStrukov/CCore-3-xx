/* Shape.ShiftSwitch.cpp */
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
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/video/lib/Shape.ShiftSwitch.h>

#include <CCore/inc/video/FigureLib.h>

namespace CCore {
namespace Video {

/* class XShiftSwitchShape */

Point XShiftSwitchShape::getMinSize() const
 {
  Coord dx=+cfg.len;

  return Point(dx,YdivX(Aspect)*dx);
 }

void XShiftSwitchShape::draw(const DrawBuf &buf,DrawParam) const
 {
  Pane pane=AdjustAspect(Aspect,this->pane);

  MPane p(pane);

  if( !p ) return;

  SmoothDrawArt art(buf.cut(pane));

  MCoord radius=p.dy/2;
  MCoord radius2=radius/5;
  MCoord width=+cfg.width;

  MPoint A=p.getRightMid().subX(radius);
  MPoint B=p.getLeftMid().addX(radius);

  VColor gray=+cfg.gray;

  FigureBox fig(p);

  // back

  if( enable )
    {
     if( mover )
       {
        fig.solid(art,XField(p.x,gray,p.ex,+cfg.snowUp));
       }
     else
       {
        fig.solid(art,XField(p.x,gray,p.ex,+cfg.snow));
       }
    }
  else
    {
     fig.solid(art,+cfg.back);
    }

  // shift

  VColor shift=+cfg.shift;

  art.path(radius2,shift,A,B);
  art.ball(A,radius2,shift);
  art.ball(B,radius2,shift);

  // focus

  if( focus )
    {
     fig.loop(art,HalfPos,width,+cfg.focus);
    }
  else
    {
     fig.loop(art,HalfPos,width,gray);
    }

  // handle

  if( check )
    {
     if( enable )
       {
        art.ball(A,radius,RadioField(A.subXY(radius/3),radius,White,+cfg.on));
        art.circle(A,radius-width/2,width,+cfg.border);
       }
     else
       {
        art.ball(A,radius,+cfg.on);
        art.circle(A,radius-width/2,width,gray);
       }
    }
  else
    {
     if( enable )
       {
        art.ball(B,radius,RadioField(B.subXY(radius/3),radius,Black,+cfg.off));
        art.circle(B,radius-width/2,width,+cfg.border);
       }
     else
       {
        art.ball(B,radius,+cfg.off);
        art.circle(B,radius-width/2,width,gray);
       }
    }
 }

/* class YShiftSwitchShape */

Point YShiftSwitchShape::getMinSize() const
 {
  Coord dy=+cfg.len;

  return Point(XdivY(Aspect)*dy,dy);
 }

void YShiftSwitchShape::draw(const DrawBuf &buf,DrawParam) const
 {
  Pane pane=AdjustAspect(Aspect,this->pane);

  MPane p(pane);

  if( !p ) return;

  SmoothDrawArt art(buf.cut(pane));

  MCoord radius=p.dx/2;
  MCoord radius2=radius/5;
  MCoord width=+cfg.width;

  MPoint A=p.getTopMid().addY(radius);
  MPoint B=p.getBottomMid().subY(radius);

  VColor gray=+cfg.gray;

  FigureBox fig(p);

  // back

  if( enable )
    {
     if( mover )
       {
        fig.solid(art,YField(p.y,+cfg.snowUp,p.ey,gray));
       }
     else
       {
        fig.solid(art,YField(p.y,+cfg.snow,p.ey,gray));
       }
    }
  else
    {
     fig.solid(art,+cfg.back);
    }

  // shift

  VColor shift=+cfg.shift;

  art.path(radius2,shift,A,B);
  art.ball(A,radius2,shift);
  art.ball(B,radius2,shift);

  // focus

  if( focus )
    {
     fig.loop(art,HalfPos,width,+cfg.focus);
    }
  else
    {
     fig.loop(art,HalfPos,width,gray);
    }

  // handle

  if( check )
    {
     if( enable )
       {
        art.ball(A,radius,RadioField(A.subXY(radius/3),radius,White,+cfg.on));
        art.circle(A,radius-width/2,width,+cfg.border);
       }
     else
       {
        art.ball(A,radius,+cfg.on);
        art.circle(A,radius-width/2,width,gray);
       }
    }
  else
    {
     if( enable )
       {
        art.ball(B,radius,RadioField(B.subXY(radius/3),radius,Black,+cfg.off));
        art.circle(B,radius-width/2,width,+cfg.border);
       }
     else
       {
        art.ball(B,radius,+cfg.off);
        art.circle(B,radius-width/2,width,gray);
       }
    }
 }

} // namespace Video
} // namespace CCore

