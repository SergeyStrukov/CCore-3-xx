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
  buf.erase();
 }

void TextBuf::load(PtrLen<BookLab::Span> text) // TODO
 {
  Used(text);
 }

void TextBuf::load(PtrLen<BookLab::TextLine> text) // TODO
 {
  Used(text);
 }

void TextBuf::save(DynArray<BookLab::Span> *pad) const // TODO
 {
  Used(pad);
 }

void TextBuf::save(DynArray<BookLab::TextLine> *pad) const // TODO
 {
  Used(pad);
 }

/* class TextWindow */

void TextWindow::clean()
 {
  block_cache=false;
  ok=false;

  sx.beg();
  sy.beg();

  cursor_x=0;
  cursor_y=0;
 }

[[nodiscard]] bool TextWindow::cache() const // TODO
 {
  if( block_cache )
    {
     return false;
    }

  try
    {
     if( !ok )
       {
        // TODO

        ok=true;
       }

     return true;
    }
  catch(...)
    {
     block_cache=true;

     return false;
    }
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

void TextWindow::updated(unsigned flags)
 {
  if( flags&LayoutUpdate ) ok=false;
 }

void TextWindow::tick()
 {
  if( tick_count )
    {
     tick_count--;
    }
  else
    {
     tick_count=PosSub(+cfg.period,1u);

     cursor_on=!cursor_on;

     redraw();
    }
 }

void TextWindow::tickStart()
 {
  cursor_on=true;

  defer_tick.start();
 }

void TextWindow::tickStop()
 {
  cursor_on=false;

  defer_tick.stop();
 }

TextWindow::TextWindow(SubWindowHost &host,const Config &cfg_)
 : SubWindow(host),
   cfg(cfg_),

   connector_posX(this,&TextWindow::posX),
   connector_posY(this,&TextWindow::posY),

   connector_updated(this,&TextWindow::updated,host.getFrame()->updated),

   input(this)
 {
  defer_tick=input.create(&TextWindow::tick);
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
  if( !cache() )
    {
     sx.pos=0;
     sx.total=1;
     sx.page=1;

     sy.pos=0;
     sy.total=1;
     sy.page=1;

     return;
    }

  // TODO

  sx.adjustPos();
  sy.adjustPos();
 }

void TextWindow::draw(DrawBuf buf,bool) const // TODO
 {
  if( !cache() )
    {
     buf.erase(Black);

     return;
    }

  // TODO
 }

 // base

void TextWindow::open()
 {
  focus=false;
  cursor_on=false;

  defer_tick.stop();
 }

void TextWindow::close()
 {
  defer_tick.stop();
 }

 // keyboard

void TextWindow::gainFocus()
 {
  if( Change(focus,true) )
    {
     tickStart();

     redraw();
    }
 }

void TextWindow::looseFocus()
 {
  if( Change(focus,false) )
    {
     tickStop();

     redraw();
    }
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

