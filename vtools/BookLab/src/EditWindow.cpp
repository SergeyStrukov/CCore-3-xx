/* EditWindow.cpp */
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

#include <inc/EditWindow.h>

#include <CCore/inc/video/FigureLib.h>

#include <CCore/inc/Exception.h>

namespace App {

/* class InnerBookLabWindow */

void InnerBookLabWindow::cache() const // TODO
 {
  if( !ok )
    {
     size=Point(100,100);

     ok=true;
    }
 }

void InnerBookLabWindow::posX(ulen pos)
 {
  sx.setPos(pos);

  redraw();
 }

void InnerBookLabWindow::posY(ulen pos)
 {
  sy.setPos(pos);

  redraw();
 }

void InnerBookLabWindow::updated(unsigned flags)
 {
  if( flags&LayoutUpdate ) ok=false;
 }

InnerBookLabWindow::InnerBookLabWindow(SubWindowHost &host,const Config &cfg_)
 : SubWindow(host),
   cfg(cfg_),

   connector_posX(this,&InnerBookLabWindow::posX),
   connector_posY(this,&InnerBookLabWindow::posY),

   connector_updated(this,&InnerBookLabWindow::updated,host.getFrame()->updated)
 {
 }

InnerBookLabWindow::~InnerBookLabWindow()
 {
 }

 // methods

Point InnerBookLabWindow::getMinSize(Point cap) const
 {
  cache();

  Point delta=2*Point::Diag(+cfg.border_dxy);

  return Inf(size,cap-delta)+delta;
 }

void InnerBookLabWindow::blank()
 {
  ok=false;

  sx.beg();
  sy.beg();

  book.blank();

  changed.assert();
 }

ErrorText InnerBookLabWindow::load(StrLen file_name,PtrLen<char> ebuf)
 {
  ok=false;

  sx.beg();
  sy.beg();

  ErrorText ret=book.load(file_name,ebuf);

  changed.assert();

  return ret;
 }

ErrorText InnerBookLabWindow::save(StrLen file_name,PtrLen<char> ebuf) const
 {
  return book.save(file_name,ebuf);
 }

 // drawing

void InnerBookLabWindow::layout()
 {
  cache();

  Point s=getSize()-2*Point::Diag(+cfg.border_dxy);

  if( s>Null )
    {
     sx.total=(ulen)size.x;
     sx.page=(ulen)s.x;

     sy.total=(ulen)size.y;
     sy.page=(ulen)s.y;
    }
  else
    {
     sx.total=(ulen)size.x;
     sx.page=1;

     sy.total=(ulen)size.y;
     sy.page=1;
    }

  sx.adjustPos();
  sy.adjustPos();
 }

void InnerBookLabWindow::draw(DrawBuf buf,bool) const // TODO
 {
  cache();

  Pane pane=getPane();

  SmoothDrawArt art(buf);

  // back

  MCoord width=+cfg.width;

  art.erase(+cfg.back);

  // border

  MPane p(pane);

  if( !p ) return;

  FigureBox fig(p);

  if( focus ) fig.loop(art,width,+cfg.focus);

  // body

  // TODO
 }

 // base

void InnerBookLabWindow::open()
 {
  focus=false;
 }

 // keyboard

void InnerBookLabWindow::gainFocus()
 {
  if( Change(focus,true) ) redraw();
 }

void InnerBookLabWindow::looseFocus()
 {
  if( Change(focus,false) ) redraw();
 }

 // mouse

MouseShape InnerBookLabWindow::getMouseShape(Point point,KeyMod kmod) const // TODO
 {
  Used(point);
  Used(kmod);

  return Mouse_Arrow;
 }

 // user input

void InnerBookLabWindow::react(UserAction action)
 {
  action.dispatch(*this);
 }

void InnerBookLabWindow::react_Key(VKey vkey,KeyMod kmod,unsigned repeat) // TODO
 {
  Used(vkey);
  Used(kmod);
  Used(repeat);
 }

void InnerBookLabWindow::react_LeftClick(Point point,MouseKey mkey) // TODO
 {
  Used(point);
  Used(mkey);
 }

void InnerBookLabWindow::react_RightClick(Point point,MouseKey mkey) // TODO
 {
  Used(point);
  Used(mkey);
 }

void InnerBookLabWindow::react_Wheel(Point point,MouseKey mkey,Coord delta) // TODO
 {
  Used(point);
  Used(mkey);
  Used(delta);
 }

/* class BookLabWindow */

void BookLabWindow::changed()
 {
  layout();

  redraw();
 }

BookLabWindow::BookLabWindow(SubWindowHost &host,const ConfigType &cfg)
 : Base(host,cfg),

   connector_changed(this,&BookLabWindow::changed,window.changed),

   modified(window.modified)
 {
 }

BookLabWindow::~BookLabWindow()
 {
 }

/* class EditWindow */

EditWindow::EditWindow(SubWindowHost &host,const Config &cfg_,Signal<> &update)
 : ComboWindow(host),
   cfg(cfg_),

   book(wlist,cfg.book_cfg)
 {
  Used(update);
 }

EditWindow::~EditWindow()
 {
 }

 // methods

Point EditWindow::getMinSize() const
 {
  return Point(10,10);
 }

bool EditWindow::isModified() const
 {
  return false;
 }

void EditWindow::blank()
 {
 }

void EditWindow::load(StrLen file_name)
 {
  Used(file_name);
 }

bool EditWindow::save()
 {
  return true;
 }

void EditWindow::save(StrLen file_name)
 {
  Used(file_name);
 }

 // drawing

void EditWindow::layout()
 {
 }

void EditWindow::drawBack(DrawBuf buf,bool) const
 {
  buf.erase(Black);
 }

} // namespace App


