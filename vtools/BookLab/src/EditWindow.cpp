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

#include <CCore/inc/Exception.h>

namespace App {

/* class EditWindow */

EditWindow::EditWindow(SubWindowHost &host,const Config &cfg_,Signal<> &update)
 : ComboWindow(host),
   cfg(cfg_)
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


