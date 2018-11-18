/* TempWindow.cpp */
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

#include <inc/TempWindow.h>

#include <CCore/inc/video/LayoutCombo.h>

namespace App {

/* class TempWindow */

TempWindow::TempWindow(SubWindowHost &host,const Config &cfg_)
 : ComboWindow(host),
   cfg(cfg_)
 {
 }

TempWindow::~TempWindow()
 {
 }

 // methods

Point TempWindow::getMinSize() const
 {
  return Point(100,100);
 }

bool TempWindow::copy(BookLab::Ref cursor)
 {
  Used(cursor);

  return false;
 }

bool TempWindow::copy(ulen slot,BookLab::Ref cursor)
 {
  Used(slot);
  Used(cursor);

  return false;
 }

bool TempWindow::past(ulen slot,BookLab::Ref cursor)
 {
  Used(slot);
  Used(cursor);

  return false;
 }

 // drawing

void TempWindow::layout()
 {
 }

void TempWindow::drawBack(DrawBuf buf,bool) const
 {
  buf.erase(+cfg.back);
 }

 // user input

void TempWindow::react(UserAction action)
 {
  wlist.react(action);
 }

/* class TempFrame */

TempFrame::TempFrame(Desktop *desktop,const Config &cfg_,Signal<> &update)
 : DragFrame(desktop,cfg_.frame_cfg,update),
   cfg(cfg_),

   client(*this,cfg.client_cfg),

   askCopy(client.askCopy),
   askPast(client.askPast)
 {
  bindClient(client);
 }

TempFrame::~TempFrame()
 {
 }

 // base

void TempFrame::dying()
 {
  DragFrame::dying();

  place=host->getPlace();
  has_place=true;
 }

 // create

Pane TempFrame::getPane(StrLen title) const
 {
  Point size=getMinSize(false,title,client.getMinSize());

  if( has_place ) return Pane(place.getBase(),Sup(place.getSize(),size));

  return GetWindowPlace(desktop,+cfg.pos_ry,size);
 }

} // namespace App

