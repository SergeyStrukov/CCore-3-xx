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

/* class TextBuf */

TextBuf::TextBuf()
 {
 }

TextBuf::~TextBuf()
 {
 }

void TextBuf::blank()
 {
 }

void TextBuf::load(PtrLen<BookLab::Span> text)
 {
  Used(text);
 }

void TextBuf::load(PtrLen<BookLab::TextLine> text)
 {
  Used(text);
 }

void TextBuf::save(DynArray<BookLab::Span> *pad) const
 {
  Used(pad);
 }

void TextBuf::save(DynArray<BookLab::TextLine> *pad) const
 {
  Used(pad);
 }

/* class TextWindow */

void TextWindow::clean() // TODO
 {
  sx.beg();
  sy.beg();
 }

void TextWindow::posX(ulen pos)
 {
  sx.setPos(pos);

  redraw();
 }

void TextWindow::posY(ulen pos)
 {
  sy.setPos(pos);

  redraw();
 }

TextWindow::TextWindow(SubWindowHost &host,const Config &cfg_)
 : SubWindow(host),
   cfg(cfg_),

   connector_posX(this,&TextWindow::posX),
   connector_posY(this,&TextWindow::posY)
 {
 }

TextWindow::~TextWindow()
 {
 }

// methods

Point TextWindow::getMinSize(Point) const
 {
  FontSize fs=cfg.font->getSize();

  Coord dy=10*fs.dy;

  return Point(2*dy,dy);
 }

void TextWindow::blank()
 {
  clean();

  text.blank();

  changed.assert();
 }

void TextWindow::load(PtrLen<BookLab::Span> text_)
 {
  clean();

  text.load(text_);

  changed.assert();
 }

void TextWindow::load(PtrLen<BookLab::TextLine> text_)
 {
  clean();

  text.load(text_);

  changed.assert();
 }

void TextWindow::setFormat(String name) // TODO
 {
  Used(name);
 }

void TextWindow::setLink(String name) // TODO
 {
  Used(name);
 }

 // drawing

void TextWindow::layout() // TODO
 {
 }

void TextWindow::draw(DrawBuf buf,bool) const // TODO
 {
  Used(buf);
 }

 // base

void TextWindow::open() // TODO
 {
 }

void TextWindow::close() // TODO
 {
 }

 // keyboard

void TextWindow::gainFocus() // TODO
 {
 }

void TextWindow::looseFocus() // TODO
 {
 }

 // mouse

void TextWindow::looseCapture() // TODO
 {
 }

MouseShape TextWindow::getMouseShape(Point point,KeyMod kmod) const // TODO
 {
  Used(point);
  Used(kmod);

  return Mouse_IBeem;
 }

 // user input

void TextWindow::react(UserAction action)
 {
  action.dispatch(*this);
 }

void TextWindow::react_Key(VKey vkey,KeyMod kmod,unsigned repeat) // TODO
 {
  Used(vkey);
  Used(kmod);
  Used(repeat);
 }

void TextWindow::react_Char(Char ch) // TODO
 {
  Used(ch);
 }

void TextWindow::react_LeftClick(Point point,MouseKey mkey) // TODO
 {
  Used(point);
  Used(mkey);
 }

void TextWindow::react_LeftUp(Point point,MouseKey mkey) // TODO
 {
  Used(point);
  Used(mkey);
 }

void TextWindow::react_Move(Point point,MouseKey mkey) // TODO
 {
  Used(point);
  Used(mkey);
 }

void TextWindow::react_Leave() // TODO
 {
 }

void TextWindow::react_Wheel(Point point,MouseKey mkey,Coord delta) // TODO
 {
  Used(point);
  Used(mkey);
  Used(delta);
 }

/* class ScrollTextWindow */

void ScrollTextWindow::changed()
 {
  layout();

  redraw();
 }

ScrollTextWindow::ScrollTextWindow(SubWindowHost &host,const ConfigType &cfg)
 : ScrollableWindow<TextWindow>(host,cfg),

   connector_changed(this,&ScrollTextWindow::changed,window.changed),

   showFormat(window.showFormat),
   showLink(window.showLink)
 {
 }

ScrollTextWindow::~ScrollTextWindow()
 {
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

