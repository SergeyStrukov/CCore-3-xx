/* DrawBook.cpp */
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

#include <inc/DrawBook.h>
#include <inc/SpanLenEngine.h>

#include <CCore/inc/Path.h>

#include <CCore/inc/video/FigureLib.h>

#include <CCore/inc/Exception.h>

namespace App {
namespace DrawBook {

/* functions */

Point StackY(Point a,Point b)
 {
  Coord y=a.y+b.y;

  if( y<0 )
    {
     Printf(Exception,"App::StackY(...) : size overflow");
    }

  return Point( Max(a.x,b.x) , y );
 }

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

       Coord delta=(ts.dy-ts.by)/2;

       MPoint a=MPoint(base.addY(delta));
       MPoint b=a.addX(Fraction(ts.dx));

       art.path(width,fore,a,b);
      }
     break;

     case Book::Strikeout :
      {
       SmoothDrawArt art(buf.cutRebase(pane));

       Coord delta=ts.by-ts.dy/2;

       MPoint a=MPoint(base.subY(delta));
       MPoint b=a.addX(Fraction(ts.dx));

       art.path(width,fore,a,b);
      }
     break;
    }
 }

/* class FontMap */

auto FontMap::find(StrLen face,Coord size,int strength,bool bold,bool italic,Font fallback) -> Rec
 {
  const FontInfo *info=lookup.find(face,bold,italic);

  if( !info ) return {fallback,true,true};

  try
    {
     FreeTypeFont font(Range(info->file_name));

     font.setSize(size);

     FreeTypeFont::Config cfg;

     cfg.strength=strength;

     font.setConfig(cfg);

     return {font,true,false};
    }
  catch(...)
    {
     return {fallback,true,true};
    }
 }

auto FontMap::find(Book::TypeDef::Font *obj,Font fallback) -> Rec
 {
  return find(obj->face,scale*CastCoord(obj->size),obj->strength,obj->bold,obj->italic,fallback);
 }

void FontMap::SetSize(Font &font_,Coord size)
 {
  FreeTypeFont &font=static_cast<FreeTypeFont &>(font_);

  font.setSize(size);
 }

void FontMap::setScale(Ratio scale_)
 {
  scale=scale_;

  for(Rec &rec : map ) rec.ok=false;
 }

Font FontMap::operator () (Book::TypeDef::Font *obj,Font fallback)
 {
  if( !obj ) return fallback;

  if( ulen ext=obj->ext )
    {
     Rec &rec=map.at(ext-1);

     if( rec.ok ) return rec.font;

     if( rec.fallback )
       {
        rec.font=fallback;
       }
     else
       {
        SetSize(rec.font,scale*CastCoord(obj->size));
       }

     rec.ok=true;

     return rec.font;
    }
  else
    {
     Rec rec=find(obj,fallback);

     map.append_copy(rec);

     obj->ext=map.getLen();

     return rec.font;
    }
 }

/* class BitmapMap */

void BitmapMap::setRoot(StrLen file_name)
 {
  SplitPath split1(file_name);
  SplitName split2(split1.path);

  file_name.len-=split2.name.len;

  root=String(file_name);
 }

const Bitmap * BitmapMap::operator () (Book::TypeDef::Bitmap *obj)
 {
  if( !obj ) return 0;

  try
    {
     if( ulen ext=obj->ext )
       {
        return &map.at(ext-1);
       }
     else
       {
        Bitmap *ret=map.append_fill(Range(root),obj->file_name);

        obj->ext=map.getLen();

        return ret;
       }
    }
  catch(...) { return 0; }
 }

/* class FrameMap */

template <class T>
FrameExt * FrameMap::createType()
 {
  return new( pool.alloc(sizeof (T)) ) T();
 }

FrameExt * FrameMap::create(Book::TypeDef::OneLine *)
 {
  return createType<FrameExt_OneLine>();
 }

FrameExt * FrameMap::create(Book::TypeDef::MultiLine *)
 {
  return createType<FrameExt_MultiLine>();
 }

FrameExt * FrameMap::create(Book::TypeDef::Text *obj)
 {
  if( !obj ) return 0;

  FrameExt *ret=0;

  obj->placement.getPtr().apply( [&] (auto *placement) { ret=create(placement); } );

  return ret;
 }

FrameExt * FrameMap::create(Book::TypeDef::FixedText *)
 {
  return createType<FrameExt>();
 }

FrameExt * FrameMap::create(Book::TypeDef::Bitmap *)
 {
  return createType<FrameExt>();
 }

FrameExt * FrameMap::create(Book::TypeDef::TextList *)
 {
  return createType<FrameExt_TextList>();
 }

FrameExt * FrameMap::create(Book::TypeDef::Collapse *)
 {
  return createType<FrameExt_Collapse>();
 }

FrameExt * FrameMap::create(Book::TypeDef::Table *)
 {
  return createType<FrameExt_Table>();
 }

FrameExt * FrameMap::create(Book::TypeDef::Frame *obj)
 {
  FrameExt *ret=0;

  obj->body.getPtr().apply( [&] (auto *obj) { ret=create(obj); } );

  if( !ret ) return createType<FrameExt>();

  return ret;
 }

void FrameMap::erase()
 {
  for(FrameExt *ext : buf ) ext->~FrameExt();

  buf.erase();

  pool.erase();
 }

FrameExt * FrameMap::operator () (Book::TypeDef::Frame *obj)
 {
  if( !obj ) return 0;

  if( ulen ext=obj->ext )
    {
     return buf.at(ext-1);
    }
  else
    {
     buf.reserve(1);

     FrameExt *ret=create(obj);

     buf.append_copy(ret);

     obj->ext=buf.getLen();

     return ret;
    }
 }

/* struct Prepare */

 // private

void Prepare::addRef(RefType ref,Pane pane) // TODO
 {
  Used(ref);
  Used(pane);
 }

RefType Prepare::CastRef(AnyPtr<Book::TypeDef::Link,Book::TypeDef::Page> ref)
 {
  RefType ret;

  ref.apply( [ref,&ret] (auto *ptr) { ret=ptr; } );

  return ret;
 }

void Prepare::addRef(AnyPtr<Book::TypeDef::Link,Book::TypeDef::Page> ref,Pane pane)
 {
  if( +ref ) addRef(CastRef(ref),pane);
 }

 // common

Font Prepare::use(const Book::TypeDef::Format *fmt)
 {
  if( fmt )
    {
     return map(fmt->font,+cfg.font);
    }
  else
    {
     return +cfg.font;
    }
 }

Font Prepare::useFixed(const Book::TypeDef::Format *fmt)
 {
  if( fmt )
    {
     return map(fmt->font,+cfg.codefont);
    }
  else
    {
     return +cfg.codefont;
    }
 }

Font Prepare::over(Font font,const Book::TypeDef::Format *fmt)
 {
  if( fmt )
    {
     return map(fmt->font,font);
    }
  else
    {
     return font;
    }
 }

TextSize Prepare::SizeSpan(Font font,StrLen text)
 {
  return font->text(text);
 }

Coord Prepare::SizeSpace(Font font)
 {
  return SizeSpan(font," "_c).dx;
 }

 // size()

Point Prepare::size(Book::TypeDef::Text *obj,FrameExt *ext,Coord wdx,Point base) // TODO
 {
  Used(obj);
  Used(ext);
  Used(wdx);
  Used(base);

  return Null;
 }

Coord Prepare::sizeLine(Font font,const Book::TypeDef::Line &line,Point base)
 {
  Coord ret=0;

  for(const Book::TypeDef::FixedSpan &span : line.getRange() )
    {
     TextSize ts=SizeSpan(over(font,span.fmt),span.body);

     addRef(span.ref,Pane(base.subY(ts.by),ts.dx,ts.dy));

     ret+=ts.dx;
     base.x+=ts.dx;
    }

  return ret;
 }

Point Prepare::size(Book::TypeDef::FixedText *obj,FrameExt *,Coord,Point base)
 {
  if( !obj ) return Null;

  Font font=useFixed(obj->fmt);

  FontSize fs=font->getSize();

  Coord dy=fs.dy;

  auto range=obj->list.getRange();

  base.y+=fs.by;

  Coord dx=0;

  for(const Book::TypeDef::Line &line : range )
    {
     dx=Max(dx,sizeLine(font,line,base));

     base.y+=dy;
    }

  return Point(dx,CountToCoord(range.len)*dy);
 }

Point Prepare::size(Book::TypeDef::Bitmap *obj,FrameExt *,Coord,Point)
 {
  const Bitmap *bitmap=map(obj);

  if( !bitmap ) return Null;

  return {CountToCoord(bitmap->dX()),CountToCoord(bitmap->dY())};
 }

Point Prepare::size(Book::TypeDef::TextList *obj,FrameExt_TextList *ext,Coord wdx,Point base) // TODO
 {
  Used(obj);
  Used(ext);
  Used(wdx);
  Used(base);

  return Null;
 }

Point Prepare::size(Book::TypeDef::Collapse *obj,FrameExt_Collapse *ext,Coord wdx,Point base) // TODO
 {
  Used(obj);
  Used(ext);
  Used(wdx);
  Used(base);

  return Null;
 }

Point Prepare::size(Book::TypeDef::Table *obj,FrameExt_Table *ext,Coord wdx,Point base) // TODO
 {
  Used(obj);
  Used(ext);
  Used(wdx);
  Used(base);

  return Null;
 }

template <class T>
Point Prepare::sizeAny(T body,FrameExt *ext,Coord wdx,Point base)
 {
  Point ret=Null;

  body.apply( [&] (auto *obj) { ret=size(obj,AutoCast(ext),wdx,base); } );

  return ret;
 }

 // public

Point Prepare::operator () (Book::TypeDef::Frame *frame,Coord wdx,Point base)
 {
  FrameExt *ext=map(frame);

  Point outer=scale*Cast(frame->outer);
  Point inner=scale*Cast(frame->inner);

  ext->outer=outer;
  ext->inner=inner;

  Point off=outer+inner;
  Point delta=2*off;

  Point size=sizeAny(frame->body.getPtr(),ext,wdx-delta.x,base+off)+delta;

  ext->size=size;

  return size;
 }

/* struct Draw */

 // GetAnyBack()

VColor Draw::GetBack(const Book::TypeDef::Format *fmt)
 {
  if( fmt ) return CastColor(fmt->back);

  return Book::NoColor;
 }

VColor Draw::GetBack(const Book::TypeDef::Text *obj)
 {
  if( obj ) return GetBack(obj->fmt.getPtr());

  return Book::NoColor;
 }

VColor Draw::GetBack(const Book::TypeDef::FixedText *obj)
 {
  if( obj ) return GetBack(obj->fmt.getPtr());

  return Book::NoColor;
 }

VColor Draw::GetBack(const Book::TypeDef::Bitmap *)
 {
  return Book::NoColor;
 }

VColor Draw::GetBack(const Book::TypeDef::TextList *)
 {
  return Book::NoColor;
 }

VColor Draw::GetBack(const Book::TypeDef::Collapse *)
 {
  return Book::NoColor;
 }

VColor Draw::GetBack(const Book::TypeDef::Table *)
 {
  return Book::NoColor;
 }

template <class T>
VColor Draw::GetAnyBack(T body)
 {
  VColor ret=Book::NoColor;

  body.apply( [&] (auto *obj) { ret=GetBack(obj); } );

  return ret;
 }

 // drawAnyLine()

void Draw::drawLine(const Book::TypeDef::SingleLine *obj,Pane pane,DrawBuf buf)
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

void Draw::drawLine(const Book::TypeDef::DoubleLine *obj,Pane pane,DrawBuf buf)
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
void Draw::drawAnyLine(T line,Pane pane,DrawBuf buf)
 {
  line.apply( [&] (auto *obj) { drawLine(obj,pane,buf); } );
 }

 // common

bool Draw::InsSpace(StrLen text)
 {
  if( text.len!=1 ) return true;

  switch( *text )
    {
     case '.' : case ',' : case ';' : case ':' : return false;

     default: return true;
    }
 }

auto Draw::Format::over(ExtMap &map,const Book::TypeDef::Format *fmt) const -> Format
 {
  if( fmt )
    {
     Format ret;

     ret.font=map(fmt->font,font);

     ret.back=Combine(fmt->back,back);
     ret.fore=Combine(fmt->fore,fore);

     ret.effect=fmt->effect;

     return ret;
    }

  return *this;
 }

auto Draw::use(const Book::TypeDef::Format *fmt) -> Format
 {
  Format ret;

  if( fmt )
    {
     ret.font=map(fmt->font,+cfg.font);

     ret.fore=Combine(fmt->fore,fore);

     ret.effect=fmt->effect;
    }
  else
    {
     ret.font=+cfg.font;

     ret.fore=fore;

     ret.effect=Book::NoEffect;
    }

  ret.back=Book::NoColor;

  return ret;
 }

auto Draw::useFixed(const Book::TypeDef::Format *fmt) -> Format
 {
  Format ret;

  if( fmt )
    {
     ret.font=map(fmt->font,+cfg.codefont);

     ret.fore=Combine(fmt->fore,fore);

     ret.effect=fmt->effect;
    }
  else
    {
     ret.font=+cfg.codefont;

     ret.fore=fore;

     ret.effect=Book::NoEffect;
    }

  ret.back=Book::NoColor;

  return ret;
 }

auto Draw::useBack(const Book::TypeDef::Format *fmt) -> Format
 {
  Format ret;

  if( fmt )
    {
     ret.font=map(fmt->font,+cfg.font);

     ret.back=CastColor(fmt->back);
     ret.fore=Combine(fmt->fore,fore);

     ret.effect=fmt->effect;
    }
  else
    {
     ret.font=+cfg.font;

     ret.back=Book::NoColor;
     ret.fore=fore;

     ret.effect=Book::NoEffect;
    }

  return ret;
 }

Point Draw::drawSpan(Format format,StrLen text,Pane inner,Point base,DrawBuf buf)
 {
  TextSize ts=format.font->text(text);

  if( format.back!=Book::NoColor ) FillBack(buf,inner,base,ts,format.back);

  if( format.effect ) MakeEffect(buf,inner,base,ts,format.effect,format.fore,+cfg.width);

  format.font->text(buf,inner,base,text,format.fore);

  return base.addX(ts.dx);
 }

Point Draw::drawSpace(Format format,Pane inner,Point base,DrawBuf buf)
 {
  return drawSpan(format," "_c,inner,base,buf);
 }

 // draw(Book::TypeDef::Text *)

Point Draw::drawSpan(Book::TypeDef::Span span,Format format,Pane inner,Point base,DrawBuf buf)
 {
  return drawSpan(format.over(map,span.fmt),span.body,inner,base,buf);
 }

Point Draw::drawSpan(const Book::TypeDef::Format *prev_fmt,Book::TypeDef::Span span,Format format,Pane inner,Point base,DrawBuf buf)
 {
  Format span_format=format.over(map,span.fmt);

  if( InsSpace(span.body) )
    {
     if( prev_fmt==span.fmt )
       {
        base=drawSpace(span_format,inner,base,buf);
       }
     else
       {
        base=drawSpace(format,inner,base,buf);
       }
    }

  return drawSpan(span_format,span.body,inner,base,buf);
 }

void Draw::drawLine(PtrLen<const Book::TypeDef::Span> line,Format format,Pane inner,Point base,DrawBuf buf)
 {
  if( +line )
    {
     base=drawSpan(*line,format,inner,base,buf);

     const Book::TypeDef::Format *fmt=line->fmt;

     for(++line; +line ;++line)
       {
        base=drawSpan(fmt,*line,format,inner,base,buf);

        fmt=line->fmt;
       }
    }
 }

void Draw::draw(PtrLen<const Book::TypeDef::Span> range,const Book::TypeDef::OneLine *placement,FrameExt_OneLine *ext,Format format,Pane inner,Point pad,DrawBuf buf)
 {
  if( !placement ) return;

  FontSize fs=format.font->getSize();

  drawLine(range,format,inner,pad+Point(ext->offx,fs.by),buf);
 }

void Draw::draw(PtrLen<const Book::TypeDef::Span> range,const Book::TypeDef::MultiLine *placement,FrameExt_MultiLine *ext,Format format,Pane inner,Point pad,DrawBuf buf)
 {
  if( !placement ) return;

  FontSize fs=format.font->getSize();

  Point base=pad.addY(fs.by);

  Coord first_dx=ext->first_dx; // Cast(placement->first_line_space)*fs.dy;
  Coord dy=ext->dy;             // Cast(placement->line_space)*fs.dy;

  PtrLen<ulen> split=Range(ext->split);

  ulen off=0;

  if( +split )
    {
     {
      ulen len=*split;

      auto part=range.safe_part(off,len);

      off+=len;

      drawLine(part,format,inner,base.addX(first_dx),buf);

      base.y+=dy;
     }

     for(ulen len : split.part(1) )
       {
        auto part=range.safe_part(off,len);

        off+=len;

        drawLine(part,format,inner,base,buf);

        base.y+=dy;
       }
    }
 }

void Draw::draw(Book::TypeDef::Text *obj,FrameExt *ext,Pane inner,Point pad,DrawBuf buf)
 {
  if( !obj ) return;

  Format format=use(obj->fmt);

  auto range=obj->list.getRange();

  obj->placement.getPtr().apply( [&] (auto *placement) { draw(range,placement,AutoCast(ext),format,inner,pad,buf); } );
 }

 // draw(Book::TypeDef::FixedText *)

void Draw::drawLine(PtrLen<const Book::TypeDef::FixedSpan> line,Format format,Pane inner,Point base,DrawBuf buf)
 {
  for(const Book::TypeDef::FixedSpan &span : line )
    {
     base=drawSpan(format.over(map,span.fmt),span.body,inner,base,buf);
    }
 }

void Draw::draw(Book::TypeDef::FixedText *obj,FrameExt *,Pane inner,Point pad,DrawBuf buf)
 {
  if( !obj ) return;

  Format format=useFixed(obj->fmt);

  FontSize fs=format.font->getSize();

  Point base=pad.addY(fs.by);

  Coord dy=fs.dy;

  for(const Book::TypeDef::Line &line : obj->list.getRange() )
    {
     drawLine(line.getRange(),format,inner,base,buf);

     base.y+=dy;
    }
 }

 // draw(Book::TypeDef::Bitmap *)

void Draw::draw(Book::TypeDef::Bitmap *obj,FrameExt *,Pane inner,Point pad,DrawBuf buf)
 {
  const Bitmap *bitmap=map(obj);

  if( !bitmap ) return;

  bitmap->draw(buf,inner.shrink(pad));
 }

 // draw(Book::TypeDef::TextList *)

void Draw::drawBullet(Format format,StrLen text,Coord bullet_len,Pane inner,Point base,DrawBuf buf)
 {
  TextSize ts=format.font->text(text);

  base.x+=bullet_len-ts.dx;

  if( format.back!=Book::NoColor ) FillBack(buf,inner,base,ts,format.back);

  if( format.effect ) MakeEffect(buf,inner,base,ts,format.effect,format.fore,+cfg.width);

  format.font->text(buf,inner,base,text,format.fore);
 }

Coord Draw::drawItem(Format format,Book::TypeDef::ListItem item,FrameExt_TextList::Delta delta,Coord bullet_len,Coord bullet_space,Pane inner,Point base,DrawBuf buf)
 {
  drawBullet(format,item.bullet,bullet_len,inner,base.addY(delta.by1),buf);

  Point ebase=(*this)(item.list,buf,inner,base+Point(bullet_len+bullet_space,delta.by2));

  return Max_cast(delta.dy1,ebase.y-base.y);
 }

void Draw::draw(Book::TypeDef::TextList *obj,FrameExt_TextList *ext,Pane inner,Point pad,DrawBuf buf)
 {
  if( !obj ) return;

  Coord bullet_len=ext->bullet_len;
  Coord bullet_space=ext->bullet_space;
  Coord item_space=ext->item_space;

  FrameExt_TextList::Delta *delta=ext->delta.getPtr();

  Format format=useBack(obj->bullet_fmt);

  Point base=pad;

  auto list=obj->list.getRange();

  for(ulen i=0; i<list.len ;i++)
    {
     Coord dy=drawItem(format,list[i],delta[i],bullet_len,bullet_space,inner,base,buf);

     base.y+=(dy+item_space);
    }
 }

 // draw(Book::TypeDef::Collapse *)

void Draw::drawPlus(Point base,Coord len_,Pane inner,DrawBuf buf)
 {
  MPane p(Pane(base,len_));

  if( !p ) return;

  SmoothDrawArt art(buf.cutRebase(inner));

  // center and radius

  MCoord len=p.dx;
  MCoord radius=len/2;

  MPoint center=p.getCenter();

  VColor gray=+cfg.gray;

  // body

  VColor top=+cfg.snow;

  art.ball(center,radius,YField(p.y,top,p.ey,gray));

  // face

  VColor fc=+cfg.face;

  MCoord a=radius/2;
  MCoord w=radius/3;

  art.path(w,fc,center.subX(a),center.addX(a));
  art.path(w,fc,center.subY(a),center.addY(a));
 }

void Draw::drawMinus(Point base,Coord len_,Pane inner,DrawBuf buf)
 {
  MPane p(Pane(base,len_));

  if( !p ) return;

  SmoothDrawArt art(buf.cutRebase(inner));

  // center and radius

  MCoord len=p.dx;
  MCoord radius=len/2;

  MPoint center=p.getCenter();

  VColor gray=+cfg.gray;

  // body

  VColor top=+cfg.snow;

  art.ball(center,radius,YField(p.y,top,p.ey,gray));

  // face

  VColor fc=+cfg.face;

  MCoord a=radius/2;
  MCoord w=radius/3;

  art.path(w,fc,center.subX(a),center.addX(a));
 }

void Draw::draw(Book::TypeDef::Collapse *obj,FrameExt_Collapse *ext,Pane inner,Point pad,DrawBuf buf)
 {
  if( !obj ) return;

  Coord len=ext->len;
  Coord elen=BoxExt(len);

  Format format=useBack(obj->collapse_fmt);

  if( obj->open )
    {
     drawMinus(pad,len,inner,buf);

     if( !obj->hide )
       {
        Coord by=format.font->getSize().by;

        drawSpan(format,obj->title,inner,pad+Point(elen,by),buf);
       }

     (*this)(obj->list,buf,inner,pad.addY(elen));
    }
  else
    {
     Coord by=format.font->getSize().by;

     drawPlus(pad,len,inner,buf);

     drawSpan(format,obj->title,inner,pad+Point(elen,by),buf);
    }
 }

 // draw(Book::TypeDef::Table *)

void Draw::draw(Book::TypeDef::Table *obj,FrameExt_Table *ext,Pane inner,Point pad,DrawBuf buf) // TODO
 {
  Used(obj);
  Used(ext);
  Used(inner);
  Used(pad);
  Used(buf);
 }

 // drawAny()

template <class T>
void Draw::drawAny(T body,FrameExt *ext,Pane inner,Point pad,DrawBuf buf)
 {
  body.apply( [&] (auto *obj) { draw(obj,AutoCast(ext),inner,pad,buf); } );
 }

 // public

Coord Draw::operator () (Book::TypeDef::Frame *frame,DrawBuf buf,Point base)
 {
  FrameExt *ext=map(frame);

  Pane pane(base,ext->size);

  Pane inner=pane.shrink(ext->outer);

  if( VColor col=CastColor(frame->col) ; col!=Book::NoColor )
    {
     PaneSub sub(pane,inner);

     buf.erase(sub.top,col);
     buf.erase(sub.bottom,col);
     buf.erase(sub.left,col);
     buf.erase(sub.right,col);
    }

  if( VColor back=GetAnyBack(frame->body.getPtr()) ; back!=Book::NoColor )
    {
     buf.erase(inner,back);
    }

  drawAnyLine(frame->line.getPtr(),inner,buf);

  drawAny(frame->body.getPtr(),ext,inner,ext->inner,buf.cut(inner));

  return ext->size.y;
 }

Point Draw::operator () (Book::TypeDef::Frame *frame,DrawBuf buf,Pane inner,Point base)
 {
  Coord dy=(*this)(frame,buf,inner.getBase()+base);

  return base.addY(dy);
 }

Point Draw::operator () (PtrLen<Book::TypeDef::Frame> list,DrawBuf buf,Pane inner,Point base)
 {
  for(Book::TypeDef::Frame &frame : list )
    {
     base=(*this)(&frame,buf,inner,base);
    }

  return base;
 }

} // namespace DrawBook
} // namespace App

