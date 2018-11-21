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
#include <CCore/inc/video/FigureLib.h>

#include <CCore/inc/algon/SimpleRotate.h>

#include <CCore/inc/RangeDel.h>

namespace App {

/* class SlotWindow */

TempSlot * SlotWindow::ref(ulen slot)
 {
  return list.at(slot).getPtr();
 }

void SlotWindow::append()
 {
  list.append_fill(OwnPtr<TempSlot>(new TempSlot()));
 }

SlotWindow::SlotWindow(SubWindowHost &host,const Config &cfg_)
 : SubWindow(host),
   cfg(cfg_),

   list(DoReserve,100)
 {
  append();
 }

SlotWindow::~SlotWindow()
 {
 }

 // methods

Point SlotWindow::getMinSize() const // TODO
 {
  return Point(100,100);
 }

void SlotWindow::setPos(ulen pos)
 {
  if( Change(off,Min(pos,getMaxPos())) ) redraw();
 }

BookLab::TempData & SlotWindow::refSlot(ulen slot)
 {
  return ref(slot)->data;
 }

BookLab::TempData & SlotWindow::freeSlot()
 {
  if( ref(0)->notEmpty() )
    {
     append();

     Algon::RangeRotateRight(Range(list));

     off=0;
     cur=0;

     layout();

     redraw();
    }

  return refSlot(0);
 }

void SlotWindow::setCurName(String name)
 {
  ref(cur)->name=name;

  if( cur==0 )
    {
     append();

     Algon::RangeRotateRight(Range(list));

     off=0;
     cur=1;

     layout();
    }

  redraw();
 }

void SlotWindow::delCurSlot()
 {
  ulen count=list.getLen();

  if( count>1 && RangeSwapDel(Range(list),cur) )
    {
     list.shrink_one();

     Replace_min(cur,count-2);

     layout();

     redraw();
    }
 }

 // drawing

void SlotWindow::layout() // TODO
 {
  len=5; // TODO

  ulen count=list.getLen();

  Replace_min(len,count);
  Replace_min(off,count-len);

  reposed.assert({count,len,off});
 }

void SlotWindow::draw(DrawBuf buf,bool) const // TODO
 {


 }

 // user input

void SlotWindow::react(UserAction action) // TODO
 {
  action.dispatch(*this);
 }

/* class TempWindow */

void TempWindow::copy_pressed()
 {
  askCopy.assert(slots.getCurSlot());
 }

void TempWindow::past_pressed()
 {
  askPast.assert(slots.getCurSlot());
 }

void TempWindow::del_pressed()
 {
  slots.delCurSlot();
 }

void TempWindow::name_pressed()
 {
  slots.setCurName(edit.getString());
 }

void TempWindow::slots_reposed(ScrollPos pos)
 {
  scroll.setRange(pos);
 }

void TempWindow::scroll_changed(ulen pos)
 {
  slots.setPos(pos);
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
   connector_name_pressed(this,&TempWindow::name_pressed,btn_name.pressed),
   connector_slots_reposed(this,&TempWindow::slots_reposed,slots.reposed),
   connector_scroll_changed(this,&TempWindow::scroll_changed,scroll.changed)
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
  if( slots.freeSlot().copy(cursor) )
    {
     slots.redraw();

     return true;
    }

  return false;
 }

bool TempWindow::copy(ulen slot,BookLab::Ref cursor)
 {
  if( slots.refSlot(slot).copy(cursor) )
    {
     slots.redraw();

     return true;
    }

  return false;
 }

bool TempWindow::past(ulen slot,BookLab::Ref cursor)
 {
  return slots.refSlot(slot).past(cursor);
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

