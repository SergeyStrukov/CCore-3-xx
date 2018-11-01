/* FieldEditor.cpp */
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

#include <inc/FieldEditor.h>

#include <CCore/inc/video/LayoutCombo.h>

namespace App {

/* class FieldWindow */

FieldWindow::FieldWindow(SubWindowHost &host,const Config &cfg_,BookLab::Book &book_)
 : ComboWindow(host),
   cfg(cfg_),

   book(book_)
 {
 }

FieldWindow::~FieldWindow()
 {
 }

 // methods

Point FieldWindow::getMinSize() const
 {
  return Point(100,100);
 }

void FieldWindow::setField(BookLab::PadType pad_)
 {
  pad=pad_;
 }

 // base

void FieldWindow::open()
 {
  ComboWindow::open();
 }

 // drawing

void FieldWindow::layout()
 {
 }

void FieldWindow::drawBack(DrawBuf buf,bool) const
 {
  buf.erase(+cfg.back);
 }

/* class FieldFrame */

FieldFrame::FieldFrame(Desktop *desktop,const Config &cfg_,BookLab::Book &book,Signal<> &update)
 : DragFrame(desktop,cfg_.frame_cfg,update),
   cfg(cfg_),

   client(*this,cfg.client_cfg,book),

   modified(client.modified)
 {
  bindClient(client);
 }

FieldFrame::~FieldFrame()
 {
 }

 // methods


 // base

void FieldFrame::dying()
 {
  DragFrame::dying();

  place=host->getPlace();
  has_place=true;
 }

 // create

Pane FieldFrame::getPane(StrLen title) const
 {
  Point size=getMinSize(false,title,client.getMinSize());

  if( has_place ) return Pane(place.getBase(),Sup(place.getSize(),size));

  return GetWindowPlace(desktop,+cfg.pos_ry,size);
 }

} // namespace App

