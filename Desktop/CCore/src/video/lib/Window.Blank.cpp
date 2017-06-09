/* Window.Blank.cpp */
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

#include <CCore/inc/video/lib/Window.Blank.h>

namespace CCore {
namespace Video {

/* class BlankWindow */

BlankWindow::BlankWindow(SubWindowHost &host,VColor back_)
 : SubWindow(host),
   back(back_)
 {
 }

BlankWindow::~BlankWindow()
 {
 }

 // drawing

bool BlankWindow::isGoodSize(Point size) const
 {
  return size>=getMinSize();
 }

void BlankWindow::draw(DrawBuf buf,bool) const
 {
  buf.erase(back);
 }

 // keyboard

FocusType BlankWindow::askFocus() const
 {
  return NoFocus;
 }

} // namespace Video
} // namespace CCore

