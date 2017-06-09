/* Shape.Split.cpp */
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
  return 2*(+cfg.dxy);
 }

void XSplitShape::draw(const DrawBuf &buf) const
 {
  MPane p(pane);

  if( !p ) return;

  SmoothDrawArt art(buf.cut(pane));

  MCoord width=+cfg.width;
  MCoord d=width/2;

  VColor bottom=+cfg.gray;

  VColor top = enable? ( down? +cfg.active : ( mover? +cfg.hilight : +cfg.snow ) ) : bottom ;

  art.path(width,top,p.getTopMid().subX(d),p.getBottomMid().subX(d));
  art.path(width,bottom,p.getTopMid().addX(d),p.getBottomMid().addX(d));
 }

/* class YSplitShape */

SizeYSpace YSplitShape::getMinSize() const
 {
  return 2*(+cfg.dxy);
 }

void YSplitShape::draw(const DrawBuf &buf) const
 {
  MPane p(pane);

  if( !p ) return;

  SmoothDrawArt art(buf.cut(pane));

  MCoord width=+cfg.width;
  MCoord d=width/2;

  VColor bottom=+cfg.gray;

  VColor top = enable? ( down? +cfg.active : ( mover? +cfg.hilight : +cfg.snow ) ) : bottom ;

  art.path(width,top,p.getLeftMid().subY(d),p.getRightMid().subY(d));
  art.path(width,bottom,p.getLeftMid().addY(d),p.getRightMid().addY(d));
 }

} // namespace Video
} // namespace CCore

