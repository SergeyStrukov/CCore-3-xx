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
#include <CCore/inc/video/LayoutCombo.h>

namespace App {

/* class InnerBookLabWindow */

bool InnerBookLabWindow::cache() const // TODO
 {
  if( block_cache ) return false;

  try
    {
     if( !ok )
       {
        size=book.prepare(cfg);

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
  if( !cache() ) return Inf(Point(100,100),cap);

  Point delta=2*Point::Diag(+cfg.border_dxy);

  return Inf(size,cap-delta)+delta;
 }

void InnerBookLabWindow::blank()
 {
  block_cache=false;
  ok=false;

  sx.beg();
  sy.beg();

  book.blank();

  changed.assert();
 }

ErrorText InnerBookLabWindow::load(StrLen file_name,PtrLen<char> ebuf)
 {
  block_cache=false;
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

ErrorText InnerBookLabWindow::link(PtrLen<char> ebuf)
 {
  if( book.isLinked() ) return Success;

  ok=false;

  ErrorText ret=book.link(ebuf);

  changed.assert();

  return ret;
 }

ErrorText InnerBookLabWindow::bookTo(StrLen file_name,PtrLen<char> ebuf) const
 {
  return book.book(file_name,ebuf);
 }

 // drawing

void InnerBookLabWindow::layout()
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

void InnerBookLabWindow::draw(DrawBuf buf,bool) const
 {
  if( !cache() )
    {
     buf.erase(Black);

     return;
    }

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

  pane=pane.shrink(+cfg.border_dxy);

  if( !pane ) return;

  book.draw(cfg,buf.cutRebase(pane),getBase());
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

void EditWindow::errorMsg(StrLen etext)
 {
  try
    {
     String text(etext);

     msg_frame.setInfo(text);

     msg_frame.create(getFrame(),+cfg.text_Error);

     disableFrameReact();
    }
  catch(CatchType)
    {
    }
 }

bool EditWindow::saveFile(StrLen file_name)
 {
  SimpleArray<char> temp(64_KByte);

  auto result=book.save(file_name,Range(temp));

  if( result.ok )
    {
     clearModified();

     return true;
    }
  else
    {
     errorMsg(result.etext);

     return false;
    }
 }

void EditWindow::book_modified()
 {
  text_file.alert();
 }

void EditWindow::msg_destroyed()
 {
  enableFrameReact();
 }

void EditWindow::file_destroyed()
 {
  enableFrameReact();

  StrLen file_name=file_frame.getFilePath();

  if( +file_name )
    {
     SimpleArray<char> temp(64_KByte);

     auto result=book.book(file_name,Range(temp));

     if( !result.ok )
       {
        errorMsg(result.etext);
       }
    }
 }

void EditWindow::tick()
 {
  if( !tick_count )
    {
     tick_count=60_sectick;

     book.collect();
    }

  tick_count--;
 }

EditWindow::EditWindow(SubWindowHost &host,const Config &cfg_,Signal<> &update)
 : ComboWindow(host),
   cfg(cfg_),

   label_file(wlist,cfg.label_cfg,cfg.text_File),
   text_file(wlist,cfg.text_cfg,+cfg.text_NoFile),
   btn_link(wlist,cfg.btn_cfg,cfg.text_Link),
   btn_book(wlist,cfg.btn_cfg,cfg.text_Book),

   book(wlist,cfg.book_cfg),

   msg_frame(host.getFrameDesktop(),cfg.msg_cfg,update),
   file_frame(host.getFrameDesktop(),cfg.file_cfg,{true,".book.ddl"_def},update),

   connector_book_modified(this,&EditWindow::book_modified,book.modified),
   connector_link_pressed(this,&EditWindow::link_pressed,btn_link.pressed),
   connector_book_pressed(this,&EditWindow::saveBook,btn_book.pressed),
   connector_msg_destroyed(this,&EditWindow::msg_destroyed,msg_frame.destroyed),
   connector_file_destroyed(this,&EditWindow::file_destroyed,file_frame.destroyed),
   input(this)
 {
  defer_tick=input.create(&EditWindow::tick);

  wlist.insTop(label_file,text_file,btn_link,btn_book,book);

  // file_frame

  file_frame.addFilter("*.book.ddl"_c);
  file_frame.addFilter("*"_c,false);
 }

EditWindow::~EditWindow()
 {
 }

 // methods

Point EditWindow::getMinSize() const
 {
  Coord space=+cfg.space_dxy;

  LayToRightCenter lay1{Lay(label_file),Lay(text_file),Lay(btn_link),LayLeft(btn_book)};

  LayToBottom lay{ExtLayNoSpace(lay1),Lay(book)};

  return lay.getMinSize(space);
 }

bool EditWindow::isModified() const
 {
  return text_file.isAlerted();
 }

void EditWindow::blank()
 {
  book.blank();

  text_file.setText(+cfg.text_NoFile);

  has_file=false;

  clearModified();

  book.setFocus();

  layout();

  redraw();
 }

void EditWindow::load(StrLen file_name)
 {
  blank();

  String text(file_name);

  SimpleArray<char> temp(64_KByte);

  auto result=book.load(file_name,Range(temp));

  if( result.ok )
    {
     text_file.setText(text);

     has_file=true;
    }
  else
    {
     text_file.setText(+cfg.text_NoFile);

     errorMsg(result.etext);
    }

  layout();

  redraw();
 }

bool EditWindow::save()
 {
  if( !has_file ) return false;

  return saveFile(text_file.getText().str());
 }

void EditWindow::save(StrLen file_name)
 {
  String text(file_name);

  if( saveFile(file_name) )
    {
     text_file.setText(text);

     has_file=true;

     layout();

     redraw();
    }
 }

bool EditWindow::link()
 {
  SimpleArray<char> temp(64_KByte);

  auto result=book.link(Range(temp));

  if( !result.ok )
    {
     errorMsg(result.etext);

     return false;
    }

  return true;
 }

void EditWindow::saveBook()
 {
  if( !link() ) return;

  file_frame.create(getFrame(),+cfg.text_SaveFile);

  disableFrameReact();
 }

 // drawing

void EditWindow::layout()
 {
  Coord space=+cfg.space_dxy;

  LayToRightCenter lay1{Lay(label_file),Lay(text_file),Lay(btn_link),LayLeft(btn_book)};

  LayToBottom lay{ExtLayNoSpace(lay1),Lay(book)};

  lay.setPlace(getPane(),space);
 }

void EditWindow::drawBack(DrawBuf buf,bool) const
 {
  VColor back=+cfg.back;

  PaneSub sub(getPane(),book.getPlace());

  buf.erase(sub.top,back);
  buf.erase(sub.bottom,back);
  buf.erase(sub.left,back);
  buf.erase(sub.right,back);
 }

 // base

void EditWindow::open()
 {
  tick_count=0;

  defer_tick.start();
 }

void EditWindow::close()
 {
  defer_tick.stop();
 }

} // namespace App


