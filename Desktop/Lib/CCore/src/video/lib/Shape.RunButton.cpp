/* Shape.RunButton.cpp */
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

#include <CCore/inc/video/lib/Shape.RunButton.h>

#include <CCore/inc/video/FigureLib.h>

namespace CCore {
namespace Video {

/* class RunButtonShape */

MCoord RunButtonShape::FigEX(Coord fdy,MCoord width)
 {
  return Max_cast(width, (Fraction(fdy)+2*width)/4 );
 }

Point RunButtonShape::getMinSize() const
 {
  TextSize ts1=cfg.font->text(Range(face_off));
  TextSize ts2=cfg.font->text(Range(face_on));

  MCoord width=+cfg.width;

  MCoord ex=FigEX(ts1.dy,width);

  Coord dx=RoundUpLen(ex);
  Coord dy=RoundUpLen(width);

  return 2*Point(dx,dy)+Point(Max(ts1.full_dx,ts2.full_dx),ts1.dy)+(+cfg.space);
 }

void RunButtonShape::draw(const DrawBuf &buf,DrawParam) const
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

  if( on )
    {
     MCoord x=Position(pos+1,(+cfg.steps)+1,p.x,p.ex);

     fig.curveSolid(art,RadioField({x,p.y+p.dy/3},p.dy,+cfg.snow,+cfg.run));
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

   VColor text = enable? +cfg.text : gray ;

   if( on )
     font->textOn(art,pane.shrink(dx,dy),TextPlace(AlignX_Center,AlignY_Center),Range(face_on),text);
   else
     font->textOn(art,pane.shrink(dx,dy),TextPlace(AlignX_Center,AlignY_Center),Range(face_off),text);
  }

  // border

  {
   VColor border = focus? +cfg.focus : ( enable? +cfg.border : gray ) ;

   fig.curveLoop(art,HalfPos,width,border);
  }
 }

/* class RefRunButtonShape */

Point RefRunButtonShape::getMinSize() const
 {
  RunButtonShape temp(cfg,face_off.get(),face_on.get());

  temp.pane=pane;

  temp.enable=enable;
  temp.focus=focus;
  temp.mover=mover;
  temp.on=on;

  temp.pos=pos;

  return temp.getMinSize();
 }

void RefRunButtonShape::draw(const DrawBuf &buf,DrawParam draw_param) const
 {
  RunButtonShape temp(cfg,face_off.get(),face_on.get());

  temp.pane=pane;

  temp.enable=enable;
  temp.focus=focus;
  temp.mover=mover;
  temp.on=on;

  temp.pos=pos;

  temp.draw(buf,draw_param);
 }

} // namespace Video
} // namespace CCore

