/* Shape.Split.cpp */
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

#include <CCore/inc/video/lib/Shape.Split.h>

#include <CCore/inc/video/FigureLib.h>

namespace CCore {
namespace Video {

/* class XSplitShape */

SizeXSpace XSplitShape::getMinSize() const
 {
  Coord dxy=+cfg.dxy;

  return 2*dxy;
 }

void XSplitShape::draw(const DrawBuf &buf,DrawParam) const
 {
  MPane p(pane);

  if( !p ) return;

  SmoothDrawArt art(buf.cut(pane));

  MCoord width=+cfg.width;
  MCoord d=width/2;

  VColor bottom=+cfg.gray;

  VColor top = enable? ( down? +cfg.active : ( mover? +cfg.hilight : +cfg.snow ) ) : bottom ;

  MPoint A=p.getTopMid();
  MPoint B=p.getBottomMid();

  art.path(width,top,A.subX(d),B.subX(d));
  art.path(width,bottom,A.addX(d),B.addX(d));
 }

/* class YSplitShape */

SizeYSpace YSplitShape::getMinSize() const
 {
  Coord dxy=+cfg.dxy;

  return 2*dxy;
 }

void YSplitShape::draw(const DrawBuf &buf,DrawParam) const
 {
  MPane p(pane);

  if( !p ) return;

  SmoothDrawArt art(buf.cut(pane));

  MCoord width=+cfg.width;
  MCoord d=width/2;

  VColor bottom=+cfg.gray;

  VColor top = enable? ( down? +cfg.active : ( mover? +cfg.hilight : +cfg.snow ) ) : bottom ;

  MPoint A=p.getLeftMid();
  MPoint B=p.getRightMid();

  art.path(width,top,A.subY(d),B.subY(d));
  art.path(width,bottom,A.addY(d),B.addY(d));
 }

} // namespace Video
} // namespace CCore

