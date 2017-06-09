/* Shape.TextLine.cpp */
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

#include <CCore/inc/video/lib/Shape.TextLine.h>

#include <CCore/inc/video/FigureLib.h>

namespace CCore {
namespace Video {

/* class TextLineShape */

MCoord TextLineShape::FigEX(Coord fdy,MCoord width)
 {
  return Max_cast(width, (Fraction(fdy)+2*width)/4 );
 }

Point TextLineShape::getMinSize() const
 {
  return getMinSize(text.str());
 }

Point TextLineShape::getMinSize(StrLen text) const
 {
  TextSize ts=cfg.font->text_guarded(text);

  MCoord width=+cfg.width;

  MCoord ex=FigEX(ts.dy,width);

  Coord dx=RoundUpLen(ex+width);
  Coord dy=RoundUpLen(width);

  return 2*Point(dx,dy)+Point(ts.full_dx,ts.dy)+(+cfg.space);
 }

void TextLineShape::setMax()
 {
  Font font=cfg.font.get();

  MCoord width=+cfg.width;

  FontSize fs=font->getSize();

  MCoord ex=FigEX(fs.dy,width);

  Coord dx=RoundUpLen(ex+width);
  Coord dy=RoundUpLen(width);

  Pane inner=pane.shrink(dx,dy);

  if( +inner )
    {
     TextSize ts=font->text_guarded(text.str());

     Coord tx=ts.full_dx;

     if( tx>inner.dx )
       xoffMax=tx-inner.dx;
     else
       xoffMax=0;

     dxoff=fs.medDX();
    }
  else
    {
     xoffMax=0;
     dxoff=0;
    }
 }

void TextLineShape::draw(const DrawBuf &buf) const
 {
  MPane p(pane);

  if( !p ) return;

  SmoothDrawArt art(buf.cut(pane));

  Font font=cfg.font.get();

  // figure

  MCoord width=+cfg.width;

  FontSize fs=font->getSize();

  MCoord ex=FigEX(fs.dy,width);

  if( ex>p.dx/3 )
    {
     art.block(pane,+cfg.inactive);

     return;
    }

  FigureButton fig(p,ex);

  VColor text=+cfg.text;

  // body

  fig.curveSolid(art, alert? +cfg.alert : +cfg.back );

  // text

  {
   Coord dx=RoundUpLen(ex+width);
   Coord dy=RoundUpLen(width);

   Pane inner=pane.shrink(dx,dy);

   Coord pos_x=fs.dx0-xoff;

   font->text(buf,inner,TextPlace(pos_x,AlignY_Center),this->text.str(), enable? text : +cfg.inactive );
  }

  // border

  if( focus )
    {
     fig.curveLoop(art,HalfPos,width,+cfg.focus);
    }
  else
    {
     auto fig_top=fig.getTop();

     fig_top.curvePath(art,HalfPos,width,+cfg.gray);

     auto fig_bottom=fig.getBottom();

     fig_bottom.curvePath(art,HalfPos,width,+cfg.snow);
    }

  // arrows

  {
   MCoord len=ex-width;
   MCoord y=p.y+p.dy/2;

   if( xoff>0 ) // Left
     {
      MCoord x=p.x+width;

      FigureLeftMark fig(x,y,len);

      fig.solid(art,text);
     }

   if( xoff<xoffMax ) // Right
     {
      MCoord x=p.ex-width;

      FigureRightMark fig(x,y,len);

      fig.solid(art,text);
     }
  }
 }

} // namespace Video
} // namespace CCore

