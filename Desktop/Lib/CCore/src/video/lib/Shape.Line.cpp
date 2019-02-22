/* Shape.Line.cpp */
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

#include <CCore/inc/video/lib/Shape.Line.h>

#include <CCore/inc/video/FigureLib.h>

namespace CCore {
namespace Video {

/* class XSingleLineShape */

SizeY XSingleLineShape::getMinSize() const
 {
  Coord dy=cfg.width.get().roundUp();

  return dy;
 }

void XSingleLineShape::draw(const DrawBuf &buf,DrawParam) const
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
  Coord dx=cfg.width.get().roundUp();

  return dx;
 }

void YSingleLineShape::draw(const DrawBuf &buf,DrawParam) const
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
  Coord dy=cfg.width.get().roundUp();

  return 2*dy;
 }

void XDoubleLineShape::draw(const DrawBuf &buf,DrawParam) const
 {
  MPane p(pane);

  if( !p ) return;

  SmoothDrawArt art(buf.cut(pane));

  MCoord width=+cfg.width;
  MCoord d=width/2;

  MPoint A=p.getLeftMid();
  MPoint B=p.getRightMid();

  art.path(width,+cfg.snow,A.subY(d),B.subY(d));
  art.path(width,+cfg.gray,A.addY(d),B.addY(d));
 }

/* class YDoubleLineShape */

SizeX YDoubleLineShape::getMinSize() const
 {
  Coord dx=cfg.width.get().roundUp();

  return 2*dx;
 }

void YDoubleLineShape::draw(const DrawBuf &buf,DrawParam) const
 {
  MPane p(pane);

  if( !p ) return;

  SmoothDrawArt art(buf.cut(pane));

  MCoord width=+cfg.width;
  MCoord d=width/2;

  MPoint A=p.getTopMid();
  MPoint B=p.getBottomMid();

  art.path(width,+cfg.snow,A.subX(d),B.subX(d));
  art.path(width,+cfg.gray,A.addX(d),B.addX(d));
 }

} // namespace Video
} // namespace CCore

