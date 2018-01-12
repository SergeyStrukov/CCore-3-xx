/* WorkWindow.cpp */
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

#include <inc/WorkWindow.h>

#include <CCore/inc/Exception.h>

namespace App {

/* class WorkWindow */

WorkWindow::WorkWindow(SubWindowHost &host,const Config &cfg_,Signal<> &update)
 : ComboWindow(host),
   cfg(cfg_),

   book(wlist,cfg.book_cfg,update)
 {
  wlist.insTop(book);
 }

WorkWindow::~WorkWindow()
 {
 }

 // methods

Point WorkWindow::getMinSize(unsigned flags) const
 {
  return book.getMinSize(flags);
 }

bool WorkWindow::isModified() const
 {
  return false;
 }

void WorkWindow::blank()
 {
  book.blank();
 }

void WorkWindow::load(StrLen file_name)
 {
  book.load(file_name);
 }

bool WorkWindow::save()
 {
  return true;
 }

void WorkWindow::save(StrLen)
 {
  Printf(Exception,"App::WorkWindow::save(...) : not supported");
 }

 // drawing

void WorkWindow::layout(unsigned flags)
 {
  book.setPlace(Pane(Null,getSize()),flags);
 }

} // namespace App


