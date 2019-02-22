/* Shape.Label.cpp */
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

#include <CCore/inc/video/lib/Shape.Label.h>

namespace CCore {
namespace Video {

/* class LabelShape */

Point LabelShape::getMinSize() const
 {
  return getMinSize(Range(text));
 }

Point LabelShape::getMinSize(StrLen text) const
 {
  TextSize ts=cfg.font->text(text);

  return ts.getSize().addXY(2);
 }

void LabelShape::draw(const DrawBuf &buf,DrawParam) const
 {
  cfg.font->text(buf,pane,TextPlace(align_x,align_y),Range(text), enable? +cfg.text : +cfg.inactive );
 }

/* class RefLabelShape */

Point RefLabelShape::getMinSize() const
 {
  LabelShape temp(cfg,text.get(),align_x,align_y);

  temp.pane=pane;

  temp.enable=enable;

  return temp.getMinSize();
 }

Point RefLabelShape::getMinSize(StrLen text_) const
 {
  LabelShape temp(cfg,text.get(),align_x,align_y);

  temp.pane=pane;

  temp.enable=enable;

  return temp.getMinSize(text_);
 }

void RefLabelShape::draw(const DrawBuf &buf,DrawParam draw_param) const
 {
  LabelShape temp(cfg,text.get(),align_x,align_y);

  temp.pane=pane;

  temp.enable=enable;

  temp.draw(buf,draw_param);
 }

} // namespace Video
} // namespace CCore

