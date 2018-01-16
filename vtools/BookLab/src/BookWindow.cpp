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

void FillBack(DrawBuf buf,Pane pane,Point base,TextSize ts,VColor back)
 {
  SmoothDrawArt art(buf.cutRebase(pane));

  MCoord skew=Fraction(ts.skew);

  Pane text(base.x,base.y-ts.by,ts.dx,ts.dy);

  MPane p(text);

  if( skew )
    {
     MCoord delta=Div(ts.dy-ts.by,ts.dy)*skew;

     p+=MPoint(-delta,0);
    }

  FigureSkew fig(p,skew);

  fig.solid(art,back);
 }

void MakeEffect(DrawBuf buf,Pane pane,Point base,TextSize ts,Effect effect,VColor fore,MCoord width)
 {
  switch( effect )
    {
     case Book::Underline :
      {
       SmoothDrawArt art(buf.cutRebase(pane));

       MPoint a=MPoint(base)-MPoint(MPoint::Half,MPoint::Half);
       MPoint b=a.addX(Fraction(ts.dx));

       art.path(HalfNeg,width,fore,a,b);
      }
     break;

     case Book::Strikeout :
      {
       SmoothDrawArt art(buf.cutRebase(pane));

       Coord delta=ts.by-ts.dy/2;

       MPoint a=MPoint(base.subY(delta));
       MPoint b=a.addX(Fraction(ts.dx));

       art.path(HalfPos,width,fore,a,b);
      }
     break;
    }
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

/* struct InnerBookWindow::SizeContext */

struct InnerBookWindow::SizeContext
 {
  const Config &cfg;
  FontMap &font_map;
  const Book::TypeDef::Frame &frame;
  Coordinate wdx;

  Coord &offx;

  Font font;

  void use(const Book::TypeDef::Format *fmt)
   {
    if( fmt )
      {
       font=font_map(fmt->font,+cfg.font);
      }
    else
      {
       font=+cfg.font;
      }
   }

  void useFixed(const Book::TypeDef::Format *fmt)
   {
    if( fmt )
      {
       font=font_map(fmt->font,+cfg.codefont);
      }
    else
      {
       font=+cfg.codefont;
      }
   }

  Font useSpan(const Book::TypeDef::Format *fmt)
   {
    if( fmt )
      {
       return font_map(fmt->font,font);
      }
    else
      {
       return font;
      }
   }

  Coordinate sizeSpan(Font font,StrLen text)
   {
    TextSize ts=font->text(text);

    return ts.dx;
   }

  Coordinate sizeSpace(Font font)
   {
    return sizeSpan(font," "_c);
   }

  Coordinate sizeSpace()
   {
    return sizeSpace(font);
   }

  Coordinate sizeSpan(Font font,StrLen text,bool space)
   {
    Coordinate dx=sizeSpan(font,text);

    if( space ) dx+=sizeSpace(font);

    return dx;
   }

  Coordinate sizeLine(Book::TypeDef::Span span,bool space)
   {
    Font font=useSpan(span.fmt);
    auto line=span.list.getRange();

    Coordinate dx=0;

    for(; +line ;++line)
      {
       dx+=sizeSpan(font,*line,line.len>1);
      }

    if( space ) dx+=sizeSpace();

    return dx;
   }

  Coordinate sizeLine(PtrLen<const Book::TypeDef::Span> line)
   {
    Coordinate dx=0;

    for(; +line ;++line)
      {
       dx+=sizeLine(*line,line.len>1);
      }

    return dx;
   }

  Point size(PtrLen<const Book::TypeDef::Span> range,const Book::TypeDef::OneLine *placement)
   {
    if( !placement ) return Null;

    Coordinate dx=sizeLine(range);

    switch( placement->align )
      {
       case Book::LineRight :
        {
         Coord extra=+PlusSub(wdx,dx);

         offx=extra;
        }
       break;

       case Book::LineCenter :
        {
         Coord extra=+PlusSub(wdx,dx);

         offx=extra/2;
        }
       break;

       default: // case Book::LineLeft :
        {
         offx=0;
        }
      }

    FontSize fs=font->getSize();

    return Point( Max(dx,wdx) , fs.dy );
   }

  Point size(PtrLen<const Book::TypeDef::Span> range,const Book::TypeDef::MultiLine *placement) // TODO
   {
    Used(range);

    if( !placement ) return Null;

    return Null;
   }

  Point size(const Book::TypeDef::Text *obj)
   {
    if( !obj ) return Null;

    use(obj->fmt);

    auto range=obj->list.getRange();

    Point ret;

    obj->placement.getPtr().apply( [&] (auto *placement) { ret=size(range,placement); } );

    return ret;
   }

  Coordinate sizeLine(Book::TypeDef::Line line)
   {
    Coordinate ret=0;

    for(const Book::TypeDef::FixedSpan &span : line.getRange() )
      {
       ret+=sizeSpan(useSpan(span.fmt),span.body);
      }

    return ret;
   }

  Point size(const Book::TypeDef::FixedText *obj)
   {
    if( !obj ) return Null;

    useFixed(obj->fmt);

    FontSize fs=font->getSize();

    Coord dy=fs.dy;

    auto range=obj->list.getRange();

    Coordinate dx=0;

    for(const Book::TypeDef::Line &line : range )
      {
       dx=Max(dx,sizeLine(line));
      }

    return Point(dx,CountToCoordinate(range.len)*dy);
   }

  Point size(const Book::TypeDef::Bitmap *obj)
   {
    if( !obj ) return Null;

    auto lines=obj->getRange();

    if( !lines ) return Null;

    auto line=lines[0].getRange();

    return {CountToCoordinate(line.len),CountToCoordinate(lines.len)};
   }

  Point size()
   {
    Point ret;

    frame.body.getPtr().apply( [&] (auto *ptr) { ret=size(ptr); } );

    return ret;
   }
 };

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
  Coord offx;

  Font font;
  Effect effect;

  void use(const Book::TypeDef::Format *fmt)
   {
    if( fmt )
      {
       font=font_map(fmt->font,+cfg.font);

       Combine(fore,fmt->fore);

       effect=fmt->effect;
      }
    else
      {
       font=+cfg.font;

       effect=Book::NoEffect;
      }
   }

  void useFixed(const Book::TypeDef::Format *fmt)
   {
    if( fmt )
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
   }

  struct Format
   {
    Font font;
    VColor back;
    VColor fore;
    Effect effect;
   };

  Format useSpan()
   {
    Format ret;

    ret.font=font;
    ret.back=Book::NoColor;
    ret.fore=fore;
    ret.effect=effect;

    return ret;
   }

  Format useSpan(const Book::TypeDef::Format *fmt)
   {
    if( fmt )
      {
       Format ret;

       ret.font=font_map(fmt->font,font);
       ret.back=Cast(fmt->back);
       ret.fore=Combine(fmt->fore,fore);
       ret.effect=fmt->effect;

       return ret;
      }
    else
      {
       return useSpan();
      }
   }

  Point drawSpan(Format fmt,StrLen text,Point base)
   {
    TextSize ts=fmt.font->text(text);

    if( fmt.back!=Book::NoColor ) FillBack(buf,pane,base,ts,fmt.back);

    if( fmt.effect ) MakeEffect(buf,pane,base,ts,fmt.effect,fmt.fore,+cfg.width);

    fmt.font->text(buf,pane,base,text,fmt.fore);

    base.x+=ts.dx;

    return base;
   }

  Point drawSpace(Format fmt,Point base)
   {
    return drawSpan(fmt," "_c,base);
   }

  Point drawSpace(Point base)
   {
    return drawSpace(useSpan(),base);
   }

  Point drawSpan(Format fmt,StrLen text,bool space,Point base)
   {
    base=drawSpan(fmt,text,base);

    if( space ) base=drawSpace(fmt,base);

    return base;
   }

  Point drawLine(Book::TypeDef::Span span,bool space,Point base)
   {
    Format fmt=useSpan(span.fmt);
    auto line=span.list.getRange();

    for(; +line ;++line)
      {
       base=drawSpan(fmt,*line,line.len>1,base);
      }

    if( space ) base=drawSpace(base);

    return base;
   }

  void drawLine(PtrLen<const Book::TypeDef::Span> line,Point base)
   {
    for(; +line ;++line)
      {
       base=drawLine(*line,line.len>1,base);
      }
   }

  void draw(PtrLen<const Book::TypeDef::Span> range,const Book::TypeDef::OneLine *placement)
   {
    if( !placement ) return;

    drawLine(range,base.addX(offx));
   }

  void draw(PtrLen<const Book::TypeDef::Span> range,const Book::TypeDef::MultiLine *placement) // TODO
   {
    Used(range);
    Used(placement);
   }

  void draw(const Book::TypeDef::Text *obj)
   {
    if( !obj ) return;

    use(obj->fmt);

    FontSize fs=font->getSize();

    base.y+=fs.by;

    auto range=obj->list.getRange();

    obj->placement.getPtr().apply( [&] (auto *placement) { draw(range,placement); } );
   }

  void drawLine(PtrLen<const Book::TypeDef::FixedSpan> line)
   {
    Point p=base;

    for(const Book::TypeDef::FixedSpan &span : line )
      {
       p=drawSpan(useSpan(span.fmt),span.body,p);
      }
   }

  void draw(const Book::TypeDef::FixedText *obj)
   {
    if( !obj ) return;

    useFixed(obj->fmt);

    FontSize fs=font->getSize();

    base.y+=fs.by;

    Coord dy=fs.dy;

    for(const Book::TypeDef::Line &line : obj->list.getRange() )
      {
       drawLine(line.getRange());

       base.y+=dy;
      }
   }

  class Fill
   {
     PtrLen<DDL::MapRange<Book::TypeDef::VColor> > map;

    private:

     static void Line(PtrLen<const Book::TypeDef::VColor> line,ulen x,ulen dx,DesktopColor::Raw *ptr)
      {
       for(auto part=SafePart(line,x,dx); +part ;++part,ptr+=DesktopColor::RawCount)
         {
          DesktopColor col(Cast(*part));

          col.copyTo(ptr);
         }
      }

    public:

     explicit Fill(const Book::TypeDef::Bitmap *obj) : map(obj->getRange()) {}

     void operator () (ulen x,ulen y,ulen dx,DesktopColor::Raw *ptr) const
      {
       if( y >= map.len ) return;

       Line(map[y].getRange(),x,dx,ptr);
      }
   };

  void draw(const Book::TypeDef::Bitmap *obj)
   {
    if( !obj ) return;

    pane=pane.shrink(base);

    buf.fill(pane,Fill(obj));
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

  SizeContext ctx{cfg,font_map,frame,dx-delta.x,offx};

  size=ctx.size()+delta;
 }

void InnerBookWindow::Shape::draw(const Config &cfg,FontMap &font_map,VColor fore,DrawBuf buf,const Book::TypeDef::Frame &frame,ulen pos_x,ulen pos_y,bool posflag) const
 {
  Scope scope("App::InnerBookWindow::Shape::draw"_c);

  if( posflag )
    draw(cfg,font_map,fore,buf,frame,Point(-(Coord)pos_x,-(Coord)pos_y));
  else
    draw(cfg,font_map,fore,buf,frame,Point(-(Coord)pos_x,(Coord)pos_y));
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

  DrawContext ctx{cfg,font_map,fore,buf,frame,inner,Cast(frame.inner),offx};

  ctx.draw();
 }

/* class InnerBookWindow */

void InnerBookWindow::cache(unsigned update_flag) const
 {
  Coord dx=getSize().x;

  if( update_flag || !ok || cache_dx!=dx )
    {
     ok=false;

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
     cache_dx=dx;
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
     return Point(500,300);
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

  VColor back=Combine(this->back,+cfg.back);
  VColor fore=Combine(this->fore,+cfg.fore);

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

     wlist.insTop(label_title,text_title,label_page,text_page,book);

     redraw();
    }
 }

BookWindow::BookWindow(SubWindowHost &host,const Config &cfg_,Signal<> &update)
 : ComboWindow(host),
   cfg(cfg_),

   label_title(wlist,cfg.label_cfg,cfg.text_Title),
   text_title(wlist,cfg.text_cfg),

   label_page(wlist,cfg.label_cfg,cfg.text_Page),
   text_page(wlist,cfg.text_cfg),

   book(wlist,cfg.book_cfg,font_map),
   progress(wlist,cfg.progress_cfg),

   msg(host.getFrameDesktop(),cfg.msg_cfg,update),

   progress_control(progress),
   font_inc(progress_control),

   connector_msg_destroyed(this,&BookWindow::enableFrame,msg.destroyed),
   connector_font_completed(this,&BookWindow::font_completed,font_inc.completed)
 {
  wlist.insTop(progress);
 }

BookWindow::~BookWindow()
 {
 }

 // methods

Point BookWindow::getMinSize(unsigned flags) const
 {
  Coord space=+cfg.space_dxy;

  LayToRight lay1{Lay(label_title),Lay(text_title),Lay(label_page),LayLeft(text_page)};

  LayToBottom lay2{ExtLayNoSpace(lay1),Lay(book)};

  LaySame lay(lay2,ExtLay{LayTop(progress)});

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
     error(DefString(result.etext));
    }
 }

 // drawing

void BookWindow::layout(unsigned flags)
 {
  Coord space=+cfg.space_dxy;

  LayToRight lay1{Lay(label_title),Lay(text_title),Lay(label_page),LayLeft(text_page)};

  LayToBottom lay2{ExtLayNoSpace(lay1),Lay(book)};

  LaySame lay(lay2,ExtLay{LayTop(progress)});

  lay.setPlace(Pane(Null,getSize()),flags,space);
 }

void BookWindow::drawBack(DrawBuf buf,bool) const
 {
  Pane pane(Null,getSize());

  VColor back=+cfg.back;

  if( book.isListed() )
    {
     PaneSub sub(pane,book.getPlace());

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

