/* TextEditor.cpp */
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

#include <inc/TextEditor.h>

#include <CCore/inc/video/LayoutCombo.h>

namespace App {

/* class TextWindow */

TextWindow::TextWindow(SubWindowHost &host,const Config &cfg_)
 : SubWindow(host),
   cfg(cfg_)
 {
 }

TextWindow::~TextWindow()
 {
 }

// methods

Point TextWindow::getMinSize() const
 {
  return Point(100,100);
 }

void TextWindow::blank()
 {
 }

void TextWindow::load(PtrLen<BookLab::Span> text)
 {
  Used(text);
 }

void TextWindow::load(PtrLen<BookLab::TextLine> text)
 {
  Used(text);
 }

void TextWindow::save(DynArray<BookLab::Span> *pad)
 {
  Used(pad);
 }

void TextWindow::save(DynArray<BookLab::TextLine> *pad)
 {
  Used(pad);
 }

void TextWindow::setFormat(String name)
 {
  Used(name);
 }

void TextWindow::setLink(String name)
 {
  Used(name);
 }

/* class TextEditor */

void TextEditor::format_pressed()
 {
  edit_text.setFormat(edit_format.getString());
 }

void TextEditor::link_pressed()
 {
  edit_text.setLink(edit_link.getString());
 }

void TextEditor::show_format(String name)
 {
  edit_format.setText(Range(name));
 }

void TextEditor::show_link(String name)
 {
  edit_link.setText(Range(name));
 }

TextEditor::TextEditor(SubWindowHost &host,const Config &cfg_)
 : ComboWindow(host),
   cfg(cfg_),

   btn_format(wlist,cfg.btn_cfg,"Format"_def),
   btn_link(wlist,cfg.btn_cfg,"Link"_def),

   edit_format(wlist,cfg.edit_cfg),
   edit_link(wlist,cfg.edit_cfg),
   cont(wlist,cfg.cont_cfg),

   edit_text(wlist,cfg.text_cfg),

   connector_format_pressed(this,&TextEditor::format_pressed,btn_format.pressed),
   connector_link_pressed(this,&TextEditor::link_pressed,btn_link.pressed),

   connector_show_format(this,&TextEditor::show_format,edit_text.showFormat),
   connector_show_link(this,&TextEditor::show_link,edit_text.showLink)
 {
  wlist.insTop(btn_format,btn_link,edit_format,edit_link,cont,edit_text);

  edit_format.hideInactiveCursor();
  edit_link.hideInactiveCursor();
 }

TextEditor::~TextEditor()
 {
 }

 // methods

Point TextEditor::getMinSize() const
 {
  Coord space=+cfg.space_dxy;

  LayToRightCenter lay1{Lay(btn_format),Lay(edit_format)};

  LayToRightCenter lay2{Lay(btn_link),Lay(edit_link)};

  LayInner lay3{cont,Lay{edit_text}};

  LayToBottom lay{lay1,lay2,lay3};

  return lay.getMinSize(space);
 }

void TextEditor::blank()
 {
  edit_text.blank();
 }

void TextEditor::load(PtrLen<BookLab::Span> text)
 {
  edit_text.load(text);
 }

void TextEditor::load(PtrLen<BookLab::TextLine> text)
 {
  edit_text.load(text);
 }

void TextEditor::save(DynArray<BookLab::Span> *pad)
 {
  edit_text.save(pad);
 }

void TextEditor::save(DynArray<BookLab::TextLine> *pad)
 {
  edit_text.save(pad);
 }

 // drawing

void TextEditor::layout()
 {
  Coord space=+cfg.space_dxy;

  LayToRightCenter lay1{Lay(btn_format),Lay(edit_format)};

  LayToRightCenter lay2{Lay(btn_link),Lay(edit_link)};

  LayInner lay3{cont,Lay{edit_text}};

  LayToBottom lay{lay1,lay2,lay3};

  lay.setPlace(getPane(),space);
 }

void TextEditor::drawBack(DrawBuf buf,bool) const
 {
  buf.erase(+cfg.back);
 }

} // namespace App

