/* Shape.Slider.cpp */
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

#include <CCore/inc/video/lib/Shape.Slider.h>

namespace CCore {
namespace Video {

/* class XSliderShape */

SizeY XSliderShape::getMinSize() const
 {
  return +cfg.dxy;
 }

unsigned XSliderShape::getPos(Point point) const // TODO
 {
 }

void XSliderShape::draw(const DrawBuf &buf) const // TODO
 {
 }

/* class YSliderShape */

SizeX YSliderShape::getMinSize() const
 {
  return +cfg.dxy;
 }

unsigned YSliderShape::getPos(Point point) const // TODO
 {
 }

void YSliderShape::draw(const DrawBuf &buf) const // TODO
 {
 }

} // namespace Video
} // namespace CCore

