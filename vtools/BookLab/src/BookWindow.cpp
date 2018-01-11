/* BookWindow.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: BookLab 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/BookWindow.h>

namespace App {

/* class InnerBookWindow */

void InnerBookWindow::posX(ulen pos)
 {
  sx.pos=pos;

  redraw();
 }

void InnerBookWindow::posY(ulen pos)
 {
  sy.pos=pos;

  redraw();
 }

InnerBookWindow::InnerBookWindow(SubWindowHost &host,const Config &cfg_)
 : SubWindow(host),
   cfg(cfg_),

   connector_posX(this,&InnerBookWindow::posX),
   connector_posY(this,&InnerBookWindow::posY)
 {
 }

InnerBookWindow::~InnerBookWindow()
 {
 }

 // methods

Point InnerBookWindow::getMinSize(unsigned flags,Point cap) const // TODO
 {
  Used(flags);
  Used(cap);

  return Point(100,100);
 }

void InnerBookWindow::setPage(Book::TypeDef::Page *page,VColor back_,VColor fore_)
 {
  frames=Null;

  if( page )
    {
     frames=page->list;

     back=VColor(page->back);
     fore=VColor(page->fore);

     if( back==Book::NoColor ) back=back_;

     if( fore==Book::NoColor ) fore=fore_;
    }

  sx.pos=0;
  sy.pos=0;

  layouts.erase();

  ok=false;
 }

 // drawing

void InnerBookWindow::layout(unsigned flags) // TODO
 {
  Used(flags);
 }

void InnerBookWindow::draw(DrawBuf buf,bool) const // TODO
 {
  buf.erase(Gray);
 }

 // base

void InnerBookWindow::open()
 {
  focus=false;
 }

 // keyboard

void InnerBookWindow::gainFocus()
 {
  if( Change(focus,true) ) redraw();
 }

void InnerBookWindow::looseFocus()
 {
  if( Change(focus,false) ) redraw();
 }

 // mouse

MouseShape InnerBookWindow::getMouseShape(Point point,KeyMod kmod) const // TODO
 {
  Used(point);
  Used(kmod);

  return Mouse_Arrow;
 }

/* class BookWindow */

BookWindow::BookWindow(SubWindowHost &host,const Config &cfg_)
 : SubWindow(host),
   cfg(cfg_)
 {
 }

BookWindow::~BookWindow()
 {
 }

 // methods

Point BookWindow::getMinSize(unsigned) const
 {
  return Point(100,100);
 }

void BookWindow::blank()
 {
 }

void BookWindow::load(StrLen file_name)
 {
  Used(file_name);
 }

 // drawing

void BookWindow::layout(unsigned flags)
 {
  Used(flags);
 }

} // namespace App

