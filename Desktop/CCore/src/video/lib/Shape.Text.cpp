/* Shape.Text.cpp */
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

#include <CCore/inc/video/lib/Shape.Text.h>

#include <CCore/inc/video/FigureLib.h>

namespace CCore {
namespace Video {

/* class TextShape */

MCoord TextShape::FigEX(Coord fdy,MCoord width)
 {
  return (Fraction(fdy)+2*width)/4;
 }

Point TextShape::getMinSize() const
 {
  return getMinSize(text.str());
 }

Point TextShape::getMinSize(StrLen text) const
 {
  TextSize ts=cfg.font->text_guarded(text);

  MCoord width=+cfg.width;

  MCoord ex=FigEX(ts.dy,width);

  Coord dx=RoundUpLen(ex);
  Coord dy=RoundUpLen(width);

  return 2*Point(dx,dy)+Point(ts.full_dx,ts.dy)+(+cfg.space);
 }

void TextShape::draw(const DrawBuf &buf) const
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

  // body

  fig.curveSolid(art,enable? ( alert? +cfg.alert : +cfg.back ) : +cfg.back );

  // text

  Coord dx=RoundUpLen(ex);
  Coord dy=RoundUpLen(width);

  font->text(buf,pane.shrink(dx,dy),TextPlace(align_x,align_y),text.str(), enable? +cfg.text : +cfg.inactive );

  // border

  auto fig_top=fig.getTop();

  fig_top.curvePath(art,HalfPos,width,+cfg.gray);

  auto fig_bottom=fig.getBottom();

  fig_bottom.curvePath(art,HalfPos,width,+cfg.snow);
 }

} // namespace Video
} // namespace CCore

