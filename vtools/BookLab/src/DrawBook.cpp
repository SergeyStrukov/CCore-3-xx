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

Point Draw::drawSpan(Format fmt,StrLen text,Pane inner,Point base,DrawBuf buf)
 {
  TextSize ts=fmt.font->text(text);

  if( fmt.back!=Book::NoColor ) FillBack(buf,inner,base,ts,fmt.back);

  if( fmt.effect ) MakeEffect(buf,inner,base,ts,fmt.effect,fmt.fore,+cfg.width);

  fmt.font->text(buf,inner,base,text,fmt.fore);

  return base.addX(ts.dx);
 }

 // draw(Book::TypeDef::Text *)

void Draw::draw(PtrLen<const Book::TypeDef::Span> range,const Book::TypeDef::OneLine *placement,Format format,Pane inner,Point pad,DrawBuf buf)
 {
 }

void Draw::draw(PtrLen<const Book::TypeDef::Span> range,const Book::TypeDef::MultiLine *placement,Format format,Pane inner,Point pad,DrawBuf buf)
 {
 }

void Draw::draw(Book::TypeDef::Text *obj,Pane inner,Point pad,DrawBuf buf)
 {
  if( !obj ) return;

  Format format=use(obj->fmt);

  auto range=obj->list.getRange();

  obj->placement.getPtr().apply( [&] (auto *placement) { draw(range,placement,format,inner,pad,buf); } );
 }

 // draw(Book::TypeDef::FixedText *)

void Draw::drawLine(PtrLen<const Book::TypeDef::FixedSpan> line,Format format,Pane inner,Point base,DrawBuf buf)
 {
  for(const Book::TypeDef::FixedSpan &span : line )
    {
     base=drawSpan(format.over(map,span.fmt),span.body,inner,base,buf);
    }
 }

void Draw::draw(Book::TypeDef::FixedText *obj,Pane inner,Point pad,DrawBuf buf)
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

void Draw::draw(Book::TypeDef::Bitmap *obj,Pane inner,Point pad,DrawBuf buf) // TODO
 {
  Used(obj);
  Used(inner);
  Used(pad);
  Used(buf);
 }

 // draw(Book::TypeDef::TextList *)

void Draw::draw(Book::TypeDef::TextList *obj,Pane inner,Point pad,DrawBuf buf) // TODO
 {
  Used(obj);
  Used(inner);
  Used(pad);
  Used(buf);
 }

 // draw(Book::TypeDef::Collapse *)

void Draw::draw(Book::TypeDef::Collapse *obj,Pane inner,Point pad,DrawBuf buf) // TODO
 {
  Used(obj);
  Used(inner);
  Used(pad);
  Used(buf);
 }

 // draw(Book::TypeDef::Table *)

void Draw::draw(Book::TypeDef::Table *obj,Pane inner,Point pad,DrawBuf buf) // TODO
 {
  Used(obj);
  Used(inner);
  Used(pad);
  Used(buf);
 }

 // drawAny()

template <class T>
void Draw::drawAny(T body,Pane inner,Point pad,DrawBuf buf)
 {
  body.apply( [&] (auto *obj) { draw(obj,inner,pad,buf); } );
 }

 // public

void Draw::operator () (Book::TypeDef::Frame *frame,DrawBuf buf,Point base)
 {
  FrameExt *ext=map(frame);

  Pane pane(base,ext->size);

  Pane inner=pane.shrink(scale*Cast(frame->outer));

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

  drawAny(frame->body.getPtr(),inner,scale*Cast(frame->inner),buf.cut(inner));
 }

} // namespace DrawBook
} // namespace App

