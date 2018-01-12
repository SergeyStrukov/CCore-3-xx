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

#include <CCore/inc/video/FigureLib.h>
#include <CCore/inc/video/LayoutCombo.h>

namespace App {

/* struct InnerBookWindow::FrameLayout */

void InnerBookWindow::FrameLayout::set(const Book::TypeDef::Frame &frame,Coord dx) // TODO
 {
  Used(frame);
  Used(dx);

  size.dx=1;
  size.dy=1;
 }

/* class InnerBookWindow */

void InnerBookWindow::cache(unsigned update_flag) const
 {
  if( update_flag || !ok )
    {
     Coord dx=getSize().x;

     if( layouts.getLen()!=frames.len )
       {
        layouts.erase();
        layouts.extend_default(frames.len);
       }

     Size s;

     for(ulen i=0; i<frames.len ;i++)
       {
        FrameLayout &fl=layouts[i];

        fl.set(frames[i],dx);

        s=StackY(s,fl.size);
       }

     size=s;

     ok=true;
    }
 }

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

Point InnerBookWindow::getMinSize(unsigned flags,Point cap) const
 {
  cache(flags&LayoutUpdate);

  Coord dx=(Coord)Min(size.dx,(ulen)cap.x);
  Coord dy=(Coord)Min(size.dy,(ulen)cap.y);

  return Point(dx,dy);
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

void InnerBookWindow::layout(unsigned flags)
 {
  cache(flags&LayoutUpdate);

  Point s=getSize();

  sx.total=size.dx;
  sx.page=(ulen)s.x;

  sy.total=size.dy;
  sy.page=(ulen)s.y;
 }

void InnerBookWindow::draw(DrawBuf buf,bool) const // TODO
 {
  cache(0);

  Pane pane(Null,getSize());

  SmoothDrawArt art(buf.cut(pane));

  // back

  VColor back=this->back;

  if( back==Book::NoColor ) back=+cfg.back;

  art.erase(back);

  // focus

  if( focus )
    {
     MPane p(pane);

     MCoord width=+cfg.width;

     FigureBox fig(p);

     fig.loop(art,width,+cfg.focus);
    }

  // frames

  for(ulen i=0; i<frames.len ;i++)
    {
     // TODO
    }
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

/* class DisplayBookWindow */

DisplayBookWindow::DisplayBookWindow(SubWindowHost &host,const ConfigType &cfg)
 : Base(host,cfg),

   link(window.link),
   hint(window.hint)
 {
 }

DisplayBookWindow::~DisplayBookWindow()
 {
 }

 // methods

void DisplayBookWindow::setPage(Book::TypeDef::Page *page,VColor back,VColor fore)
 {
  window.setPage(page,back,fore);

  layout(LayoutUpdate);

  redraw();
 }

/* class BookWindow */

void BookWindow::error(StrLen etext) // TODO
 {
 }

BookWindow::BookWindow(SubWindowHost &host,const Config &cfg_)
 : ComboWindow(host),
   cfg(cfg_),

   label_title(wlist,cfg.label_cfg,cfg.text_Title),
   text_title(wlist,cfg.text_cfg),

   label_page(wlist,cfg.label_cfg,cfg.text_Page),
   text_page(wlist,cfg.text_cfg),

   book(wlist,cfg.book_cfg)
 {
  wlist.insTop(label_title,text_title,label_page,text_page,book);
 }

BookWindow::~BookWindow()
 {
 }

 // methods

Point BookWindow::getMinSize(unsigned flags) const
 {
  Coord space=+cfg.space_dxy;

  LayToRight lay1{Lay(label_title),Lay(text_title),Lay(label_page),LayLeft(text_page)};

  LayToBottom lay{ExtLayNoSpace(lay1),Lay(book)};

  return lay.getMinSize(flags,space);
 }

void BookWindow::blank()
 {
  book.setPage(0,Book::NoColor,Book::NoColor);

  text_title.setText(""_def);
  text_page.setText(""_def);

  layout(LayoutUpdate);

  redraw();
 }

void BookWindow::load(StrLen file_name)
 {
  SimpleArray<char> temp(64_KByte);

  auto result=book_map.load(file_name,Range(temp));

  if( result.ok )
    {
     book.setPage(0,Book::NoColor,Book::NoColor);

     auto *ptr=book_map.get();

     text_title.setText(DefString(ptr->title.getStr()));

     auto list=ptr->list.getRange();

     if( list.len )
       {
        auto *page=list[0].getPtr();

        text_page.setText(DefString(page->name.getStr()));

        layout(LayoutUpdate);

        book.setPage(page,(VColor)ptr->back,(VColor)ptr->fore);
       }
     else
       {
        text_page.setText(""_def);

        layout(LayoutUpdate);

        book.setPage(0,(VColor)ptr->back,(VColor)ptr->fore);
       }

     redraw();
    }
  else
    {
     blank();

     error(result.etext);
    }
 }

 // drawing

void BookWindow::layout(unsigned flags)
 {
  Coord space=+cfg.space_dxy;

  LayToRight lay1{Lay(label_title),Lay(text_title),Lay(label_page),LayLeft(text_page)};

  LayToBottom lay{ExtLayNoSpace(lay1),Lay(book)};

  lay.setPlace(Pane(Null,getSize()),flags,space);
 }

void BookWindow::drawBack(DrawBuf buf,bool) const
 {
  Pane pane(Null,getSize());

  PaneSub sub(pane,book.getPlace());

  buf.erase(sub.top,+cfg.back);
  buf.erase(sub.bottom,+cfg.back);
  buf.erase(sub.left,+cfg.back);
  buf.erase(sub.right,+cfg.back);
 }

} // namespace App

