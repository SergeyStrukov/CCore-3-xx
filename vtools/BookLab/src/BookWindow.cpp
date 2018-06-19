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

#include <CCore/inc/Scope.h>

#include <CCore/inc/video/FigureLib.h>
#include <CCore/inc/video/LayoutCombo.h>
#include <CCore/inc/algon/BinarySearch.h>

namespace App {

/* class InnerBookWindow */

void InnerBookWindow::cache() const
 {
  Coord dx=getSize().x-2*cfg.width.get().roundUp();

  if( !ok || cache_dx!=dx )
    {
     if( shapes.getLen()!=frames.len )
       {
        shapes.erase();
        shapes.extend_default(frames.len);
       }

     Size s;

     ulen y=0;

     for(ulen i=0; i<frames.len ;i++)
       {
        Shape &shape=shapes[i];

        shape.set(cfg,font_map,bmp_map,scale,frames[i],dx);

        s=StackY(s,shape.size);

        shape.offy=y;

        y+=shape.getSize().y;
       }

     size=s;

     ok=true;
     cache_dx=dx;
    }
 }

void InnerBookWindow::addXPos(ulen delta,bool mul_flag)
 {
  sx.add(Delta(delta,mul_flag));

  scroll_x.assert(sx.pos);

  redraw();
 }

void InnerBookWindow::subXPos(ulen delta,bool mul_flag)
 {
  sx.sub(Delta(delta,mul_flag));

  scroll_x.assert(sx.pos);

  redraw();
 }

void InnerBookWindow::addYPos(ulen delta,bool mul_flag)
 {
  sy.add(Delta(delta,mul_flag));

  scroll_y.assert(sy.pos);

  redraw();
 }

void InnerBookWindow::subYPos(ulen delta,bool mul_flag)
 {
  sy.sub(Delta(delta,mul_flag));

  scroll_y.assert(sy.pos);

  redraw();
 }

PtrLen<const Shape> InnerBookWindow::getVisibleShapes(ulen off,ulen lim) const
 {
  PtrLen<const Shape> r=Range(shapes);

  r=Algon::BinarySearch_if(r, [lim] (const Shape &shape) { return shape.offy >= lim ; } );

  auto s=Algon::BinarySearch_if(r, [off] (const Shape &shape) { return shape.offy > off ; } );

  if( +s ) --r;

  return r;
 }

PtrLen<const Shape> InnerBookWindow::getVisibleShapes() const
 {
  ulen wdy=sy.page;
  ulen pos_y=sy.getPos();

  return getVisibleShapes(pos_y,pos_y+wdy);
 }

AnyPtr<Book::TypeDef::Link,Book::TypeDef::Page> InnerBookWindow::getRef(Point point) const
 {
  cache();

  Pane pane=getPane();

  MCoord width=+cfg.width;
  Pane inner=pane.shrink(RoundUpLen(width));

  point-=inner.getBase();

  ulen wdy=sy.page;

  ulen pos_x=sx.getPos();
  ulen pos_y=sy.getPos();

  for(auto &shape : getVisibleShapes(pos_y,pos_y+wdy) )
    {
     ulen y=shape.offy;

     Size size=shape.getSize();

     if( pos_x<size.dx )
       {
        if( y>=pos_y )
          {
           if( shape.hit(point,pos_x,y-pos_y,false) ) return shape.getRef(point,pos_x,y-pos_y,false);
          }
        else
          {
           if( shape.hit(point,pos_x,pos_y-y,true) ) return shape.getRef(point,pos_x,pos_y-y,true);
          }
       }
    }

  return Null;
 }

void InnerBookWindow::posFrame(ulen frame_index)
 {
  if( frame_index<shapes.getLen() )
    {
     sy.setPos( shapes[frame_index].offy );
    }
  else
    {
     sy.end();
    }
 }

void InnerBookWindow::begXPos()
 {
  sx.beg();

  scroll_x.assert(sx.pos);

  redraw();
 }

void InnerBookWindow::endXPos()
 {
  sx.end();

  scroll_x.assert(sx.pos);

  redraw();
 }

void InnerBookWindow::begYPos()
 {
  sy.beg();

  scroll_y.assert(sy.pos);

  redraw();
 }

void InnerBookWindow::endYPos()
 {
  sy.end();

  scroll_y.assert(sy.pos);

  redraw();
 }

void InnerBookWindow::addYPosPage()
 {
  sy.addPage();

  scroll_y.assert(sy.pos);

  redraw();
 }

void InnerBookWindow::subYPosPage()
 {
  sy.subPage();

  scroll_y.assert(sy.pos);

  redraw();
 }

void InnerBookWindow::posX(ulen pos)
 {
  sx.setPos(pos);

  redraw();
 }

void InnerBookWindow::posY(ulen pos)
 {
  sy.setPos(pos);

  redraw();
 }

void InnerBookWindow::updated(unsigned flags)
 {
  if( flags&LayoutUpdate ) ok=false;
 }

InnerBookWindow::InnerBookWindow(SubWindowHost &host,const Config &cfg_,FontMap &font_map_,BitmapMap &bmp_map_)
 : SubWindow(host),
   cfg(cfg_),

   font_map(font_map_),
   bmp_map(bmp_map_),

   connector_posX(this,&InnerBookWindow::posX),
   connector_posY(this,&InnerBookWindow::posY),

   connector_updated(this,&InnerBookWindow::updated,host.getFrame()->updated)
 {
 }

InnerBookWindow::~InnerBookWindow()
 {
 }

 // methods

Point InnerBookWindow::getMinSize(Point cap) const
 {
  cache();

  if( frames.len )
    {
     Coord dx=CapSize(size.dx,cap.x);
     Coord dy=CapSize(size.dy,cap.y);

     return Point(dx,dy)+2*Point::Diag(cfg.width.get().roundUp());
    }
  else
    {
     return Point(500,300);
    }
 }

void InnerBookWindow::setPage(Book::TypeDef::Page *page,VColor back_,VColor fore_)
 {
  frames=Null;

  book_back=back_;
  book_fore=fore_;

  scale=Ratio(1,0);

  if( page )
    {
     frames=page->list;

     back=Combine(page->back,back_);
     fore=Combine(page->fore,fore_);
    }
  else
    {
     back=back_;
     fore=fore_;
    }

  sx.beg();
  sy.beg();

  ok=false;
 }

void InnerBookWindow::setPage(Book::TypeDef::Page *page,ulen frame_index)
 {
  frames=Null;

  if( page )
    {
     frames=page->list;

     back=Combine(page->back,book_back);
     fore=Combine(page->fore,book_fore);
    }
  else
    {
     back=book_back;
     fore=book_fore;
    }

  sx.beg();
  sy.beg();

  ok=false;

  cache();

  posFrame(frame_index);
 }

void InnerBookWindow::setScale(Ratio scale_)
 {
  scale=scale_;

  font_map.setScale(scale_);

  ok=false;
 }

 // drawing

void InnerBookWindow::layout()
 {
  cache();

  Point s=getSize()-2*Point::Diag(cfg.width.get().roundUp());

  if( s>Null )
    {
     sx.total=size.dx;
     sx.page=(ulen)s.x;

     sy.total=size.dy;
     sy.page=(ulen)s.y;
    }
  else
    {
     sx.total=size.dx;
     sx.page=1;

     sy.total=size.dy;
     sy.page=1;
    }
 }

void InnerBookWindow::draw(DrawBuf buf,bool) const
 {
  cache();

  Pane pane=getPane();

  buf=buf.cut(pane);

  SmoothDrawArt art(buf);

  // back , fore

  MCoord width=+cfg.width;

  VColor back=Combine(this->back,+cfg.back);
  VColor fore=Combine(this->fore,+cfg.fore);

  art.erase(back);

  // border

  {
   MPane p(pane);

   FigureBox fig(p);

   VColor vc = focus? +cfg.focus : +cfg.border ;

   fig.loop(art,width,vc);
  }

  // frames

  Pane inner=pane.shrink(RoundUpLen(width));

  buf=buf.cutRebase(inner);

  ulen wdy=sy.page;

  ulen pos_x=sx.getPos();
  ulen pos_y=sy.getPos();

  for(auto &shape : getVisibleShapes(pos_y,pos_y+wdy) )
    {
     ulen y=shape.offy;

     Size size=shape.getSize();

     if( pos_x<size.dx )
       {
        if( y>=pos_y )
          {
           shape.draw(cfg,font_map,bmp_map,scale,fore,buf,pos_x,y-pos_y,false);
          }
        else
          {
           shape.draw(cfg,font_map,bmp_map,scale,fore,buf,pos_x,pos_y-y,true);
          }
       }
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

MouseShape InnerBookWindow::getMouseShape(Point point,KeyMod) const
 {
  AnyPtr<Book::TypeDef::Link,Book::TypeDef::Page> ref=getRef(point);

  return +ref?Mouse_Hand:Mouse_Arrow;
 }

 // user input

void InnerBookWindow::react(UserAction action)
 {
  action.dispatch(*this);
 }

void InnerBookWindow::react_Key(VKey vkey,KeyMod kmod,unsigned repeat)
 {
  switch( vkey )
    {
     case VKey_Left :
      {
       subXPos(repeat,!(kmod&KeyMod_Shift));
      }
     break;

     case VKey_Right :
      {
       addXPos(repeat,!(kmod&KeyMod_Shift));
      }
     break;

     case VKey_Up :
      {
       subYPos(repeat,!(kmod&KeyMod_Shift));
      }
     break;

     case VKey_Down :
      {
       addYPos(repeat,!(kmod&KeyMod_Shift));
      }
     break;

     case VKey_Home :
      {
       begXPos();
      }
     break;

     case VKey_End :
      {
       endXPos();
      }
     break;

     case VKey_PageUp :
      {
       if( kmod&KeyMod_Ctrl )
         begYPos();
       else
         subYPosPage();
      }
     break;

     case VKey_PageDown :
      {
       if( kmod&KeyMod_Ctrl )
         endYPos();
       else
         addYPosPage();
      }
     break;
    }
 }

void InnerBookWindow::react_LeftClick(Point point,MouseKey)
 {
  AnyPtr<Book::TypeDef::Link,Book::TypeDef::Page> ref=getRef(point);

  if( !ref ) return;

  struct Func
   {
    InnerBookWindow *obj;

    void operator () (Book::TypeDef::Link *ref)
     {
      obj->link.assert(*ref);
     }

    void operator () (Book::TypeDef::Page *ref)
     {
      obj->hint.assert(ref);
     }
   };

  Func func{this};

  ElaborateAnyPtr(func,ref);
 }

void InnerBookWindow::react_Wheel(Point,MouseKey mkey,Coord delta)
 {
  if( delta<0 )
    {
     if( mkey&MouseKey_Shift )
       addXPos(IntAbs(delta),true);
     else
       addYPos(IntAbs(delta),true);
    }
  else
    {
     if( mkey&MouseKey_Shift )
       subXPos(IntAbs(delta),true);
     else
       subYPos(IntAbs(delta),true);
    }
 }

/* class DisplayBookWindow */

DisplayBookWindow::DisplayBookWindow(SubWindowHost &host,const ConfigType &cfg,FontMap &font_map,BitmapMap &bmp_map)
 : Base(host,cfg,font_map,bmp_map),

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

  layout();
 }

void DisplayBookWindow::setPage(Book::TypeDef::Page *page,ulen frame_index)
 {
  window.setPage(page,frame_index);

  layout();
 }

void DisplayBookWindow::setScale(Ratio scale)
 {
  window.setScale(scale);

  layout();

  redraw();
 }

/* class DisplayBookFrame */

DisplayBookFrame::DisplayBookFrame(Desktop *desktop,const Config &cfg_,FontMap &font_map,BitmapMap &bmp_map,Signal<> &update)
 : DragFrame(desktop,cfg_.frame_cfg,update),
   cfg(cfg_),
   client(*this,cfg.book_cfg,font_map,bmp_map)
 {
  bindClient(client);
 }

DisplayBookFrame::~DisplayBookFrame()
 {
 }

 // methods

void DisplayBookFrame::setPage(VColor back,VColor fore)
 {
  client.setPage(0,back,fore);

  client.redraw();
 }

void DisplayBookFrame::setPage(Book::TypeDef::Page *page)
 {
  client.setPage(page,0);

  client.redraw();
 }

void DisplayBookFrame::setScale(Ratio scale)
 {
  client.setScale(scale);
 }

 // base

void DisplayBookFrame::dying()
 {
  place=getFrameHost()->getPlace();

  has_place=true;
 }

/* class BookWindow::ProgressControl */

BookWindow::ProgressControl::ProgressControl(ArrowProgressWindow &window_)
 : window(window_)
 {
 }

BookWindow::ProgressControl::~ProgressControl()
 {
 }

 // IncrementalProgress

void BookWindow::ProgressControl::start()
 {
 }

void BookWindow::ProgressControl::setTotal(unsigned total)
 {
  window.setTotal(total);
 }

bool BookWindow::ProgressControl::setPos(unsigned pos)
 {
  window.setPosPing(pos);

  return true;
 }

void BookWindow::ProgressControl::stop() noexcept
 {
 }

/* class BookWindow */

void BookWindow::error(DefString etext)
 {
  if( msg.isDead() )
    {
     msg.setInfo(etext);

     msg.create(getFrame(),+cfg.text_Error);

     disableFrameReact();
    }
 }

void BookWindow::setNav(Book::TypeDef::Page *page)
 {
  if( page )
    {
     prev=page->prev;
     up=page->up;
     next=page->next;
    }
  else
    {
     prev=0;
     up=0;
     next=0;
    }

  knob_prev.enable(prev);
  knob_up.enable(up);
  knob_next.enable(next);
 }

void BookWindow::enableFrame()
 {
  enableFrameReact();
 }

void BookWindow::font_completed(bool ok)
 {
  font_flag=false;

  if( ok )
    {
     wlist.del(progress);

     wlist.insTop(label_title,text_title,label_page,text_page,knob_prev,knob_up,knob_next,spinor,book);

     redraw();
    }
 }

void BookWindow::link(Book::TypeDef::Link dst)
 {
  if( auto *page=dst.page.getPtr() )
    {
     text_page.setText(DefString(page->name.getStr()));

     setNav(page);

     layout();

     book.setPage(page,dst.frame_index);
    }

  redraw();
 }

void BookWindow::hint(Book::TypeDef::Page *page)
 {
  popup.setPage(page);

  if( page )
    {
     String title(page->name.getStr());

     if( popup.isDead() )
       {
        Pane place;

        if( !popup.getPlace(place) )
          {
           Pane pane=toScreen(getPane());

           place=SplitX(pane,Div(1,3)*pane.dx);
          }

        popup.create(getFrame(),place,title);
       }
     else
       {
        popup.setTitle(title);
       }
    }
 }

void BookWindow::gotoPrev()
 {
  if( prev ) link({prev,0});
 }

void BookWindow::gotoUp()
 {
  if( up ) link({up,0});
 }

void BookWindow::gotoNext()
 {
  if( next ) link({next,0});
 }

void BookWindow::setScale(int scale_)
 {
  Ratio scale=Div(scale_,100);

  book.setScale(scale);
  popup.setScale(scale);
 }

BookWindow::BookWindow(SubWindowHost &host,const Config &cfg_,Signal<> &update)
 : ComboWindow(host),
   cfg(cfg_),

   label_title(wlist,cfg.label_cfg,cfg.text_Title),
   text_title(wlist,cfg.text_cfg),

   label_page(wlist,cfg.label_cfg,cfg.text_Page),
   text_page(wlist,cfg.text_cfg),

   knob_prev(wlist,cfg.knob_cfg,KnobShape::FaceLeft),
   knob_up(wlist,cfg.knob_cfg,KnobShape::FaceUp),
   knob_next(wlist,cfg.knob_cfg,KnobShape::FaceRight),

   spinor(wlist,cfg.spinor_cfg),

   book(wlist,cfg.book_cfg,font_map,bmp_map),
   progress(wlist,cfg.progress_cfg),

   msg(host.getFrameDesktop(),cfg.msg_cfg,update),

   popup(host.getFrameDesktop(),cfg.popup_cfg,font_map,bmp_map,update),

   progress_control(progress),
   font_inc(progress_control),

   connector_msg_destroyed(this,&BookWindow::enableFrame,msg.destroyed),
   connector_font_completed(this,&BookWindow::font_completed,font_inc.completed),

   connector_link(this,&BookWindow::link,book.link),
   connector_hint(this,&BookWindow::hint,book.hint),

   connector_prev_pressed(this,&BookWindow::gotoPrev,knob_prev.pressed),
   connector_up_pressed(this,&BookWindow::gotoUp,knob_up.pressed),
   connector_next_pressed(this,&BookWindow::gotoNext,knob_next.pressed),

   connector_scale_changed(this,&BookWindow::setScale,spinor.changed)
 {
  wlist.insTop(progress);

  knob_prev.disable();
  knob_up.disable();
  knob_next.disable();

  spinor.setRange(25,400);
  spinor.setValue(100);
  spinor.setOptions(".f2"_c);
 }

BookWindow::~BookWindow()
 {
 }

 // methods

Point BookWindow::getMinSize() const
 {
  Coord space=+cfg.space_dxy;

  LayToRightCenter lay1{Lay(label_title),Lay(text_title),Lay(label_page),Lay(text_page),Lay(knob_prev),Lay(knob_up),Lay(knob_next),LayLeft(spinor)};

  LayToBottom lay2{ExtLayNoSpace(lay1),Lay(book)};

  LaySame lay(lay2,ExtLay{LayTop(progress)});

  return lay.getMinSize(space);
 }

void BookWindow::blank()
 {
  if( popup.isAlive() ) popup.destroy();

  bmp_map.erase();

  bmp_map.setRoot(""_c);

  book.setPage(0,Book::NoColor,Book::NoColor);

  font_map.erase();

  text_title.setText(""_def);
  text_page.setText(""_def);
  spinor.setValue(100);

  setNav(0);

  layout();

  redraw();
 }

void BookWindow::load(StrLen file_name)
 {
  if( font_flag )
    {
     error(+cfg.text_NotReady);

     return;
    }

  blank();

  SimpleArray<char> temp(64_KByte);

  auto result=book_map.load(file_name,Range(temp));

  if( result.ok )
    {
     auto *ptr=book_map.get();

     text_title.setText(DefString(ptr->title.getStr()));

     if( auto *page=ptr->start.getPtr() )
       {
        text_page.setText(DefString(page->name.getStr()));

        setNav(page);

        layout();

        bmp_map.setRoot(file_name);

        VColor back=Cast(ptr->back);
        VColor fore=Cast(ptr->fore);

        popup.setPage(back,fore);

        book.setPage(page,back,fore);
       }
     else
       {
        text_page.setText(""_def);

        setNav(0);

        layout();

        book.setPage(0,Cast(ptr->back),Cast(ptr->fore));
       }

     redraw();
    }
  else
    {
     error(DefString(result.etext));
    }
 }

 // drawing

void BookWindow::layout()
 {
  Coord space=+cfg.space_dxy;

  LayToRightCenter lay1{Lay(label_title),Lay(text_title),Lay(label_page),Lay(text_page),Lay(knob_prev),Lay(knob_up),Lay(knob_next),LayLeft(spinor)};

  LayToBottom lay2{ExtLayNoSpace(lay1),Lay(book)};

  LaySame lay(lay2,ExtLay{LayTop(progress)});

  lay.setPlace(getPane(),space);
 }

void BookWindow::drawBack(DrawBuf buf,bool) const
 {
  VColor back=+cfg.back;

  if( book.isListed() )
    {
     PaneSub sub(getPane(),book.getPlace());

     buf.erase(sub.top,back);
     buf.erase(sub.bottom,back);
     buf.erase(sub.left,back);
     buf.erase(sub.right,back);
    }
  else
    {
     buf.erase(back);
    }
 }

 // base

void BookWindow::open()
 {
  ComboWindow::open();

  if( font_flag )
    {
     font_map.cache(font_inc);
    }
 }

} // namespace App

