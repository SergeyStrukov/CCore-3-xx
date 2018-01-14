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

#include <CCore/inc/Scope.h>

namespace App {

/* functions */

void FillBack(DrawBuf buf,Pane pane,Point base,TextSize ts,VColor back) // TODO
 {
  Used(buf);
  Used(pane);
  Used(base);
  Used(ts);
  Used(back);
 }

void MakeEffect(DrawBuf buf,Pane pane,Point base,TextSize ts,Effect effect,VColor fore,MCoord width) // TODO
 {
  Used(buf);
  Used(pane);
  Used(base);
  Used(ts);
  Used(effect);
  Used(fore);
  Used(width);
 }

/* class FontMap */

Font FontMap::find(StrLen face,Coord size,int strength,bool bold,bool italic,Font fallback)
 {
  const FontInfo *info=lookup.find(face,bold,italic);

  if( !info ) return fallback;

  try
    {
     FontParam param;

     param.engine_type=FontParam::EngineFreeType;
     param.file_name=info->file_name;
     param.size_type=FontParam::SizeXY;
     param.set_size.size_xy=size;

     param.cfg.strength=strength;

     return param.create();
    }
  catch(...)
    {
     return fallback;
    }
 }

Font FontMap::find(Book::TypeDef::Font *font,Font fallback)
 {
  return find(font->face,font->size,font->strength,font->bold,font->italic,fallback);
 }

Font FontMap::operator () (Book::TypeDef::Font *font,Font fallback)
 {
  if( !font ) return fallback;

  if( ulen ext=font->ext )
    {
     return map[ext-1];
    }
  else
    {
     ulen ind=map.getLen();

     Font f=find(font,fallback);

     map.append_copy(f);

     font->ext=ind+1;

     return f;
    }
 }

/* struct InnerBookWindow::DrawContext */

struct InnerBookWindow::DrawContext
 {
  const Config &cfg;
  FontMap &font_map;
  VColor fore;
  DrawBuf buf;
  const Book::TypeDef::Frame &frame;
  Pane pane;
  Point base;

  Font font;
  Effect effect;

  void draw(const Book::TypeDef::Text *obj) const // TODO
   {
    if( !obj ) return;

   }

  Coord drawSpan(Font font,VColor back,VColor fore,Effect effect,StrLen text,Point base)
   {
    TextSize ts=font->text(text);

    if( back!=Book::NoColor ) FillBack(buf,pane,base,ts,back);

    if( effect ) MakeEffect(buf,pane,base,ts,effect,fore,+cfg.width);

    font->text(buf,pane,base,text,fore);

    return ts.dx;
   }

  void drawLine(Book::TypeDef::Line line)
   {
    Point p=base;

    for(const Book::TypeDef::FixedSpan &span : line.list.getRange() )
      {
       Font font;
       VColor back;
       VColor fore;
       Effect effect;

       if( const Book::TypeDef::Format *fmt=span.fmt )
         {
          font=font_map(fmt->font,this->font);
          back=Cast(fmt->back);
          fore=Combine(fmt->fore,this->fore);
          effect=fmt->effect;
         }
       else
         {
          font=this->font;
          back=Book::NoColor;
          fore=this->fore;
          effect=this->effect;
         }

       p.x+=drawSpan(font,back,fore,effect,span.body,p);
      }
   }

  void draw(const Book::TypeDef::FixedText *obj)
   {
    if( !obj ) return;

    if( const Book::TypeDef::Format *fmt=obj->fmt )
      {
       font=font_map(fmt->font,+cfg.codefont);

       Combine(fore,fmt->fore);

       effect=fmt->effect;
      }
    else
      {
       font=+cfg.codefont;

       effect=Book::NoEffect;
      }

    Coord dy=font->getSize().dy;

    for(const Book::TypeDef::Line &line : obj->list.getRange() )
      {
       drawLine(line);

       base.y+=dy;
      }
   }

  void draw(const Book::TypeDef::Bitmap *obj) // TODO
   {
    if( !obj ) return;

    pane=pane.shrink(base);

    // TODO draw obj on buf at pane
   }

  void draw()
   {
    frame.body.getPtr().apply( [&] (auto *obj) { draw(obj); } );
   }
 };

/* struct InnerBookWindow::Shape */

void InnerBookWindow::Shape::set(const Config &cfg,FontMap &font_map,const Book::TypeDef::Frame &frame,Coordinate dx)
 {
  Scope scope("App::InnerBookWindow::Shape::set"_c);

  Point delta=2*( Cast(frame.inner)+Cast(frame.outer) );

  size = body(cfg,frame,dx-delta.x) + delta ;
 }

void InnerBookWindow::Shape::draw(const Config &cfg,FontMap &font_map,VColor fore,DrawBuf buf,const Book::TypeDef::Frame &frame,ulen pos_x,ulen pos_y,bool posflag) const
 {
  Scope scope("App::InnerBookWindow::Shape::draw"_c);

  if( posflag )
    draw(cfg,font_map,fore,buf,frame,Point(-(Coord)pos_x,-(Coord)pos_y));
  else
    draw(cfg,font_map,fore,buf,frame,Point(-(Coord)pos_x,(Coord)pos_y));
 }

Point InnerBookWindow::Shape::body(const Config &cfg,const Book::TypeDef::Text *obj,Coordinate dx) // TODO
 {
  Used(cfg);
  Used(obj);
  Used(dx);

  if( !obj ) return Null;

  return Point(500,300);
 }

Point InnerBookWindow::Shape::body(const Config &cfg,const Book::TypeDef::FixedText *obj,Coordinate) // TODO
 {
  Used(cfg);
  Used(obj);

  if( !obj ) return Null;

  return Point(500,300);
 }

Point InnerBookWindow::Shape::body(const Config &,const Book::TypeDef::Bitmap *obj,Coordinate)
 {
  if( !obj ) return Null;

  auto lines=obj->map.getRange();

  if( !lines ) return Null;

  auto line=lines[0].getRange();

  return {CountToCoordinate(line.len),CountToCoordinate(lines.len)};
 }

Point InnerBookWindow::Shape::body(const Config &cfg,const Book::TypeDef::Frame &frame,Coordinate dx)
 {
  Point ret;

  frame.body.getPtr().apply( [&] (auto *ptr) { ret=body(cfg,ptr,dx); } );

  return ret;
 }

VColor InnerBookWindow::Shape::GetBack(const Book::TypeDef::Format *fmt)
 {
  if( fmt ) return Cast(fmt->back);

  return Book::NoColor;
 }

VColor InnerBookWindow::Shape::GetBack(const Book::TypeDef::Text *obj)
 {
  if( obj ) return GetBack(obj->fmt.getPtr());

  return Book::NoColor;
 }

VColor InnerBookWindow::Shape::GetBack(const Book::TypeDef::FixedText *obj)
 {
  if( obj ) return GetBack(obj->fmt.getPtr());

  return Book::NoColor;
 }

VColor InnerBookWindow::Shape::GetBack(const Book::TypeDef::Bitmap *)
 {
  return Book::NoColor;
 }

template <class T>
VColor InnerBookWindow::Shape::GetAnyBack(T body)
 {
  VColor ret=Book::NoColor;

  body.apply( [&] (auto *ptr) { ret=GetBack(ptr); } );

  return ret;
 }

void InnerBookWindow::Shape::DrawLine(const Config &cfg,DrawBuf buf,const Book::TypeDef::SingleLine *obj,Pane pane)
 {
  if( !obj ) return;

  MPane p(pane);

  if( !p ) return;

  VColor line=Combine(obj->line,+cfg.line);

  MCoord width=Cast(obj->width)*(+cfg.width);

  SmoothDrawArt art(buf);

  FigureBox fig(p);

  fig.loop(art,width,line);
 }

void InnerBookWindow::Shape::DrawLine(const Config &cfg,DrawBuf buf,const Book::TypeDef::DoubleLine *obj,Pane pane)
 {
  if( !obj ) return;

  MPane p(pane);

  if( !p ) return;

  VColor gray=Combine(obj->gray,+cfg.gray);
  VColor snow=Combine(obj->snow,+cfg.snow);

  MCoord width=Cast(obj->width)*(+cfg.width);

  SmoothDrawArt art(buf);

  FigureBox fig(p);

  fig.loop(art,HalfPos,width,gray);
  fig.loop(art,HalfNeg,width,snow);
 }

template <class T>
void InnerBookWindow::Shape::DrawAnyLine(const Config &cfg,DrawBuf buf,T line,Pane pane)
 {
  line.apply( [&] (auto *obj) { DrawLine(cfg,buf,obj,pane); } );
 }

void InnerBookWindow::Shape::draw(const Config &cfg,FontMap &font_map,VColor fore,DrawBuf buf,const Book::TypeDef::Frame &frame,Point base) const
 {
  Pane pane(base,size);

  Pane inner=pane.shrink(Cast(frame.outer));

  if( VColor col=Cast(frame.col) ; col!=Book::NoColor )
    {
     PaneSub sub(pane,inner);

     buf.erase(sub.top,col);
     buf.erase(sub.bottom,col);
     buf.erase(sub.left,col);
     buf.erase(sub.right,col);
    }

  if( VColor back=GetAnyBack(frame.body.getPtr()) ; back!=Book::NoColor )
    {
     buf.erase(inner,back);
    }

  DrawAnyLine(cfg,buf,frame.line.getPtr(),inner);

  DrawContext ctx{cfg,font_map,fore,buf,frame,inner,Cast(frame.inner)};

  ctx.draw();
 }

/* class InnerBookWindow */

void InnerBookWindow::cache(unsigned update_flag) const
 {
  if( update_flag || !ok )
    {
     Coord dx=getSize().x;

     if( shapes.getLen()!=frames.len )
       {
        shapes.erase();
        shapes.extend_default(frames.len);
       }

     Size s;

     for(ulen i=0; i<frames.len ;i++)
       {
        Shape &shape=shapes[i];

        shape.set(cfg,font_map,frames[i],dx);

        s=StackY(s,shape.size);
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

InnerBookWindow::InnerBookWindow(SubWindowHost &host,const Config &cfg_,FontMap &font_map_)
 : SubWindow(host),
   cfg(cfg_),

   font_map(font_map_),

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

  if( frames.len )
    {
     Coord dx=CapSize(size.dx,cap.x);
     Coord dy=CapSize(size.dy,cap.y);

     return Point(dx,dy);
    }
  else
    {
     return Point(100,100);
    }
 }

void InnerBookWindow::setPage(Book::TypeDef::Page *page,VColor back_,VColor fore_)
 {
  frames=Null;

  if( page )
    {
     frames=page->list;

     back=Combine(page->back,back_);
     fore=Combine(page->fore,fore_);
    }

  sx.pos=0;
  sy.pos=0;

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

void InnerBookWindow::draw(DrawBuf buf,bool) const
 {
  cache(0);

  Pane pane(Null,getSize());

  buf=buf.cut(pane);

  SmoothDrawArt art(buf);

  // back , fore

  VColor back=this->back;
  VColor fore=this->fore;

  if( back==Book::NoColor ) back=+cfg.back;

  if( fore==Book::NoColor ) fore=+cfg.fore;

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

  Point s=getSize();

  ulen wdy=(ulen)s.y;

  ulen pos_x=sx.getPos();
  ulen pos_y=sy.getPos();
  ulen y=0;

  for(ulen i=0; i<frames.len ;i++)
    {
     auto &frame=frames[i];
     auto &shape=shapes[i];

     Size size=shape.getSize();

     if( y>=pos_y )
       {
        ulen delta=y-pos_y;

        if( delta<wdy )
          {
           if( pos_x<size.dx ) shape.draw(cfg,font_map,fore,buf,frame,pos_x,delta,false);
          }
        else
          {
           break;
          }
       }
     else
       {
        ulen delta=pos_y-y;

        if( delta<size.dy && pos_x<size.dx )
          {
           shape.draw(cfg,font_map,fore,buf,frame,pos_x,delta,true);
          }
       }

     y+=size.dy;
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

DisplayBookWindow::DisplayBookWindow(SubWindowHost &host,const ConfigType &cfg,FontMap &font_map)
 : Base(host,cfg,font_map),

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

void BookWindow::error(StrLen etext)
 {
  if( msg.isDead() )
    {
     msg.setInfo(DefString(etext));

     msg.create(getFrame(),+cfg.text_Error);

     disableFrameReact();
    }
 }

void BookWindow::enableFrame()
 {
  enableFrameReact();
 }

BookWindow::BookWindow(SubWindowHost &host,const Config &cfg_,Signal<> &update)
 : ComboWindow(host),
   cfg(cfg_),

   label_title(wlist,cfg.label_cfg,cfg.text_Title),
   text_title(wlist,cfg.text_cfg),

   label_page(wlist,cfg.label_cfg,cfg.text_Page),
   text_page(wlist,cfg.text_cfg),

   book(wlist,cfg.book_cfg,font_map),

   msg(host.getFrameDesktop(),cfg.msg_cfg,update),

   connector_msg_destroyed(this,&BookWindow::enableFrame,msg.destroyed)
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

  font_map.erase();

  text_title.setText(""_def);
  text_page.setText(""_def);

  layout(LayoutUpdate);

  redraw();
 }

void BookWindow::load(StrLen file_name)
 {
  blank();

  SimpleArray<char> temp(64_KByte);

  auto result=book_map.load(file_name,Range(temp));

  if( result.ok )
    {
     auto *ptr=book_map.get();

     text_title.setText(DefString(ptr->title.getStr()));

     auto list=ptr->list.getRange();

     if( list.len )
       {
        auto *page=list[0].getPtr();

        text_page.setText(DefString(page->name.getStr()));

        layout(LayoutUpdate);

        book.setPage(page,Cast(ptr->back),Cast(ptr->fore));
       }
     else
       {
        text_page.setText(""_def);

        layout(LayoutUpdate);

        book.setPage(0,Cast(ptr->back),Cast(ptr->fore));
       }

     redraw();
    }
  else
    {
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

