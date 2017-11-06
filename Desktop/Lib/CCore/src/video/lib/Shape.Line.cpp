/* Shape.Line.cpp */
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

#include <CCore/inc/video/lib/Shape.Line.h>

#include <CCore/inc/video/FigureLib.h>

namespace CCore {
namespace Video {

/* class XSingleLineShape */

SizeY XSingleLineShape::getMinSize() const
 {
  Coord dy=RoundUpLen(+cfg.width);

  return dy;
 }

void XSingleLineShape::draw(const DrawBuf &buf) const
 {
  MPane p(pane);

  if( !p ) return;

  SmoothDrawArt art(buf.cut(pane));

  MCoord width=+cfg.width;

  art.path(width,+cfg.line,p.getLeftMid(),p.getRightMid());
 }

/* class YSingleLineShape */

SizeX YSingleLineShape::getMinSize() const
 {
  Coord dx=RoundUpLen(+cfg.width);

  return dx;
 }

void YSingleLineShape::draw(const DrawBuf &buf) const
 {
  MPane p(pane);

  if( !p ) return;

  SmoothDrawArt art(buf.cut(pane));

  MCoord width=+cfg.width;

  art.path(width,+cfg.line,p.getTopMid(),p.getBottomMid());
 }

/* class XDoubleLineShape */

SizeY XDoubleLineShape::getMinSize() const
 {
  Coordinate dy=RoundUpLen(+cfg.width);

  return 2*dy;
 }

void XDoubleLineShape::draw(const DrawBuf &buf) const
 {
  MPane p(pane);

  if( !p ) return;

  SmoothDrawArt art(buf.cut(pane));

  MCoord width=+cfg.width;
  MCoord d=width/2;

  art.path(width,+cfg.snow,p.getLeftMid().subY(d),p.getRightMid().subY(d));
  art.path(width,+cfg.gray,p.getLeftMid().addY(d),p.getRightMid().addY(d));
 }

/* class YDoubleLineShape */

SizeX YDoubleLineShape::getMinSize() const
 {
  Coordinate dx=RoundUpLen(+cfg.width);

  return 2*dx;
 }

void YDoubleLineShape::draw(const DrawBuf &buf) const
 {
  MPane p(pane);

  if( !p ) return;

  SmoothDrawArt art(buf.cut(pane));

  MCoord width=+cfg.width;
  MCoord d=width/2;

  art.path(width,+cfg.snow,p.getTopMid().subX(d),p.getBottomMid().subX(d));
  art.path(width,+cfg.gray,p.getTopMid().addX(d),p.getBottomMid().addX(d));
 }

} // namespace Video
} // namespace CCore

