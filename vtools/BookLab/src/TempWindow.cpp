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

/* class SlotWindow */

SlotWindow::SlotWindow(SubWindowHost &host,const Config &cfg_)
 : SubWindow(host),
   cfg(cfg_)
 {
 }

SlotWindow::~SlotWindow()
 {
 }

 // methods

Point SlotWindow::getMinSize() const
 {
  return Point(100,100);
 }

 // drawing

void SlotWindow::layout()
 {
 }

void SlotWindow::draw(DrawBuf buf,bool) const
 {
  buf.erase(Black);
 }

/* class TempWindow */

void TempWindow::copy_pressed()
 {
 }

void TempWindow::past_pressed()
 {
 }

void TempWindow::del_pressed()
 {
 }

void TempWindow::name_pressed()
 {
 }

TempWindow::TempWindow(SubWindowHost &host,const Config &cfg_)
 : ComboWindow(host),
   cfg(cfg_),

   btn_copy(wlist,cfg.btn_cfg,cfg.text_Copy),
   btn_past(wlist,cfg.btn_cfg,cfg.text_Past),
   btn_del(wlist,cfg.btn_cfg,cfg.text_Del),
   btn_name(wlist,cfg.btn_cfg,cfg.text_Name),

   edit(wlist,cfg.edit_cfg),

   scroll(wlist,cfg.scroll_cfg),
   slots(wlist,cfg.slot_cfg),

   connector_copy_pressed(this,&TempWindow::copy_pressed,btn_copy.pressed),
   connector_past_pressed(this,&TempWindow::past_pressed,btn_past.pressed),
   connector_del_pressed(this,&TempWindow::del_pressed,btn_del.pressed),
   connector_name_pressed(this,&TempWindow::name_pressed,btn_name.pressed)
 {
  wlist.insTop(btn_copy,btn_past,btn_del,btn_name,edit,scroll,slots);
 }

TempWindow::~TempWindow()
 {
 }

 // methods

Point TempWindow::getMinSize() const
 {
  Coord space=+cfg.space_dxy;

  LayToRightCenter lay1{Lay(btn_copy),Lay(btn_past),Lay(btn_del),Lay(btn_name),Lay(edit)};

  LayToRight lay2{Lay(scroll),Lay(slots)};

  LayToBottom lay{lay1,lay2};

  return ExtLay(lay).getMinSize(space);
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
  Coord space=+cfg.space_dxy;

  LayToRightCenter lay1{Lay(btn_copy),Lay(btn_past),Lay(btn_del),Lay(btn_name),Lay(edit)};

  LayToRight lay2{Lay(scroll),Lay(slots)};

  LayToBottom lay{lay1,lay2};

  ExtLay(lay).setPlace(getPane(),space);
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

