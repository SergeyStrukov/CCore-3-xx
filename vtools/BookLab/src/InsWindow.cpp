/* InsWindow.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: BookLab 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/InsWindow.h>

namespace App {

/* class InsWindow */

InsWindow::InsWindow(SubWindowHost &host,const Config &cfg_)
 : ComboWindow(host),
   cfg(cfg_)
 {
 }

InsWindow::~InsWindow()
 {
 }

 // methods

Point InsWindow::getMinSize() const // TODO
 {
  return Point(300,300);
 }

 // drawing

void InsWindow::layout() // TODO
 {
 }

void InsWindow::drawBack(DrawBuf buf,bool) const
 {
  buf.erase(+cfg.back);
 }

/* class InsFrame */

InsFrame::InsFrame(Desktop *desktop,const Config &cfg_,Signal<> &update)
 : DragFrame(desktop,cfg_.frame_cfg,update),
   cfg(cfg_),

   client(*this,cfg.client_cfg)
 {
  bindClient(client);
 }

InsFrame::~InsFrame()
 {
 }

 // base

void InsFrame::dying()
 {
  DragFrame::dying();

  place=host->getPlace();
  has_place=true;
 }

 // create

Pane InsFrame::getPane(StrLen title) const
 {
  Point size=getMinSize(false,title,client.getMinSize());

  if( has_place ) return Pane(place.getBase(),Sup(place.getSize(),size));

  return GetWindowPlace(desktop,+cfg.pos_ry,size);
 }

} // namespace App


