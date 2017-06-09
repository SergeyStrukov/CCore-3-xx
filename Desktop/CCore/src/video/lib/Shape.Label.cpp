/* Shape.Label.cpp */
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

#include <CCore/inc/video/lib/Shape.Label.h>

namespace CCore {
namespace Video {

/* class LabelShape */

Point LabelShape::getMinSize() const
 {
  TextSize ts=cfg.font->text_guarded(text.str());

  return Point(ts.full_dx,ts.dy).addXY(2);
 }

void LabelShape::draw(const DrawBuf &buf) const
 {
  cfg.font->text(buf,pane,TextPlace(align_x,align_y),text.str(), enable? +cfg.text : +cfg.inactive );
 }

/* class RefLabelShape */

Point RefLabelShape::getMinSize() const
 {
  LabelShape temp(cfg,text.get(),align_x,align_y);

  temp.pane=pane;

  temp.enable=enable;

  return temp.getMinSize();
 }

void RefLabelShape::draw(const DrawBuf &buf) const
 {
  LabelShape temp(cfg,text.get(),align_x,align_y);

  temp.pane=pane;

  temp.enable=enable;

  temp.draw(buf);
 }

} // namespace Video
} // namespace CCore

