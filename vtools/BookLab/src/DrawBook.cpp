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

/* size functions */

void GuardSizeOverflow(const char *name)
 {
  Printf(Exception,"#;(...) : size overflow",name);
 }

Coord AddSize(Coord a,Coord b)
 {
  Coord ret=a+b;

  if( ret<0 ) GuardSizeOverflow("App::DrawBook::AddSize");

  return ret;
 }

Point StackY(Point a,Point b)
 {
  return Point( Max(a.x,b.x) , AddSize(a.y,b.y) );
 }

/* functions */

bool InsSpace(StrLen text)
 {
  if( text.len!=1 ) return true;

  switch( *text )
    {
     case '.' : case ',' : case ';' : case ':' : return false;

     default: return true;
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

void Prepare::addRef(RefType ref,Pane pane)
 {
  if( +ref ) refs.append_copy({pane,ref});
 }

void Prepare::addRef(AnyPtr<Book::TypeDef::Link,Book::TypeDef::Page> ref,Pane pane)
 {
  if( +ref ) addRef(CastAnyPtr<RefType>(ref),pane);
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

 // size(Book::TypeDef::Text *)

void Prepare::correctRefs(ulen refs_len,Coord delta_x)
 {
  for(RefPane &ref : Range(refs).part(refs_len) )
    {
     ref.pane.x+=delta_x;
    }
 }

Coord Prepare::sizeSpan(Font font,Book::TypeDef::Span span,Point base)
 {
  TextSize ts=SizeSpan(over(font,span.fmt),span.body);

  addRef(span.ref,TextPane(base,ts));

  return ts.dx;
 }

auto Prepare::sizeSpan(const Book::TypeDef::Format *prev_fmt,Font font,Coord space_dx,Book::TypeDef::Span span,Point base) -> LineSize
 {
  Font span_font=over(font,span.fmt);

  Coord sdx=0;

  if( InsSpace(span.body) )
    {
     if( span.fmt && prev_fmt==span.fmt )
       {
        sdx=SizeSpace(span_font);
       }
     else
       {
        sdx=space_dx;
       }
    }

  TextSize ts=SizeSpan(span_font,span.body);

  addRef(span.ref,TextPane(base.addX(sdx),ts));

  return {ts.dx,ts.dx+sdx};
 }

Coord Prepare::sizeLine(Font font,Coord space_dx,PtrLen<const Book::TypeDef::Span> line,Point base)
 {
  Coord tdx=0;

  if( +line )
    {
     tdx=sizeSpan(font,*line,base);

     const Book::TypeDef::Format *fmt=line->fmt;

     base.x+=tdx;

     for(++line; +line ;++line)
       {
        Coord dx=sizeSpan(fmt,font,space_dx,*line,base).edx;

        tdx=AddSize(tdx,dx);

        base.x+=dx;

        fmt=line->fmt;
       }
    }

  return tdx;
 }

Point Prepare::size(Font font,Coord space_dx,PtrLen<const Book::TypeDef::Span> range,Book::TypeDef::OneLine *placement,FrameExt_OneLine *ext,Coord wdx,Point base)
 {
  if( !placement ) return Null;

  FontSize fs=font->getSize();

  ulen refs_len=refs.getLen();

  Coord dx=sizeLine(font,space_dx,range,base.addY(fs.by));

  switch( placement->align )
    {
     case Book::LineRight :
      {
       Coord extra=PlusSub(wdx,dx);

       Coord offx=extra;

       ext->offx=offx;

       correctRefs(refs_len,offx);
      }
     break;

     case Book::LineCenter :
      {
       Coord extra=PlusSub(wdx,dx);

       Coord offx=extra/2;

       ext->offx=offx;

       correctRefs(refs_len,offx);
      }
     break;

     default: // case Book::LineLeft :
      {
       ext->offx=0;
      }
    }

  return Point(Max(dx,wdx),fs.dy);
 }

Point Prepare::size(Font font,Coord space_dx,PtrLen<const Book::TypeDef::Span> range,Book::TypeDef::MultiLine *placement,FrameExt_MultiLine *ext,Coord wdx,Point base)
 {
  if( !placement ) return Null;

  FontSize fs=font->getSize();

  Coord tdx=fs.dy;
  Coord tdy=fs.dy;

  Coord first_dx=Cast(placement->first_line_space)*fs.dy;
  Coord dy=Cast(placement->line_space)*fs.dy;

  ext->first_dx=first_dx;
  ext->dy=dy;

  ext->split.erase();

  if( +range )
    {
     base.y+=fs.by;

     Coord dx=AddSize( sizeSpan(font,*range,base.addX(first_dx)) ,first_dx);

     const Book::TypeDef::Format *fmt=range->fmt;

     Point p=base;

     p.x+=dx;

     while( +range )
       {
        ulen len=1;

        for(++range; +range ;++range,len++)
          {
           LineSize delta=sizeSpan(fmt,font,space_dx,*range,p);

           fmt=range->fmt;

           if( delta.edx<=wdx-dx )
             {
              dx=AddSize(dx,delta.edx);

              p.x+=delta.edx;
             }
           else
             {
              Replace_max(tdx,dx);

              tdy=AddSize(tdy,dy);

              dx=delta.dx;

              base.y+=dy;

              p=base;

              p.x+=dx;

              break;
             }
          }

        ext->split.append_copy(len);
       }

     Replace_max(tdx,dx);
    }

  return Point(tdx,tdy);
 }

Point Prepare::size(Book::TypeDef::Text *obj,FrameExt *ext,Coord wdx,Point base)
 {
  if( !obj ) return Null;

  Font font=use(obj->fmt);

  Coord space_dx=SizeSpace(font);

  auto range=obj->list.getRange();

  Point ret;

  obj->placement.getPtr().apply( [&] (auto *placement) { ret=size(font,space_dx,range,placement,AutoCast(ext),wdx,base); } );

  return ret;
 }

 // size(Book::TypeDef::FixedText *)

Coord Prepare::sizeLine(Font font,const Book::TypeDef::Line &line,Point base)
 {
  Coord tdx=0;

  for(const Book::TypeDef::FixedSpan &span : line.getRange() )
    {
     TextSize ts=SizeSpan(over(font,span.fmt),span.body);

     addRef(span.ref,TextPane(base,ts));

     tdx=AddSize(tdx,ts.dx);

     base.x+=ts.dx;
    }

  return tdx;
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

  return Point(dx,MulSize(range.len,dy));
 }

 // size(Book::TypeDef::Bitmap *)

Point Prepare::size(Book::TypeDef::Bitmap *obj,FrameExt *,Coord,Point)
 {
  const Bitmap *bitmap=map(obj);

  if( !bitmap ) return Null;

  return {CountToCoord(bitmap->dX()),CountToCoord(bitmap->dY())};
 }

 // size(Book::TypeDef::TextList *)

Point Prepare::size(Book::TypeDef::TextList *obj,FrameExt_TextList *ext,Coord wdx,Point base) // TODO
 {
  Used(obj);
  Used(ext);
  Used(wdx);
  Used(base);

  return Null;
 }

 // size(Book::TypeDef::Collapse *)

Point Prepare::size(Book::TypeDef::Collapse *obj,FrameExt_Collapse *ext,Coord wdx,Point base) // TODO
 {
  Used(obj);
  Used(ext);
  Used(wdx);
  Used(base);

  return Null;
 }

 // size(Book::TypeDef::Table *)

Point Prepare::size(Book::TypeDef::Table *obj,FrameExt_Table *ext,Coord wdx,Point base) // TODO
 {
  Used(obj);
  Used(ext);
  Used(wdx);
  Used(base);

  return Null;
 }

 // sizeAny()

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

/* struct DrawOut */

void DrawOut::back(TextSize ts,VColor back)
 {
  SmoothDrawArt art(buf.cutRebase(pane));

  MCoord skew=Fraction(ts.skew);

  MPane p(TextPane(base,ts));

  if( skew )
    {
     MCoord delta=Div(ts.dy-ts.by,ts.dy)*skew;

     p+=MPoint(-delta,0);
    }

  FigureSkew fig(p,skew);

  fig.solid(art,back);
 }

void DrawOut::effect(TextSize ts,Effect effect,VColor fore,MCoord width)
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

void DrawOut::text(Font font,StrLen text,VColor fore)
 {
  font->text(buf,pane,base,text,fore);
 }

void DrawOut::bitmap(const Bitmap *bitmap)
 {
  if( !bitmap ) return;

  bitmap->draw(buf,pane.shrink(base));
 }

void DrawOut::drawPlus(const Config &cfg,Coord len_)
 {
  MPane p(Pane(base,len_));

  if( !p ) return;

  SmoothDrawArt art(buf.cutRebase(pane));

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

void DrawOut::drawMinus(const Config &cfg,Coord len_)
 {
  MPane p(Pane(base,len_));

  if( !p ) return;

  SmoothDrawArt art(buf.cutRebase(pane));

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

Point Draw::drawSpan(Format format,StrLen text,DrawOut out)
 {
  TextSize ts=format.font->text(text);

  if( format.back!=Book::NoColor ) out.back(ts,format.back);

  if( format.effect ) out.effect(ts,format.effect,format.fore,+cfg.width);

  out.text(format.font,text,format.fore);

  return out.base.addX(ts.dx);
 }

Point Draw::drawSpace(Format format,DrawOut out)
 {
  return drawSpan(format," "_c,out);
 }

 // draw(Book::TypeDef::Text *)

Point Draw::drawSpan(Format format,Book::TypeDef::Span span,DrawOut out)
 {
  return drawSpan(format.over(map,span.fmt),span.body,out);
 }

Point Draw::drawSpan(const Book::TypeDef::Format *prev_fmt,Format format,Book::TypeDef::Span span,DrawOut out)
 {
  Format span_format=format.over(map,span.fmt);

  if( InsSpace(span.body) )
    {
     if( prev_fmt==span.fmt )
       {
        out.base=drawSpace(span_format,out);
       }
     else
       {
        out.base=drawSpace(format,out);
       }
    }

  return drawSpan(span_format,span.body,out);
 }

void Draw::drawLine(Format format,PtrLen<const Book::TypeDef::Span> line,DrawOut out)
 {
  if( +line )
    {
     out.base=drawSpan(format,*line,out);

     const Book::TypeDef::Format *fmt=line->fmt;

     for(++line; +line ;++line)
       {
        out.base=drawSpan(fmt,format,*line,out);

        fmt=line->fmt;
       }
    }
 }

void Draw::draw(Format format,PtrLen<const Book::TypeDef::Span> range,const Book::TypeDef::OneLine *placement,FrameExt_OneLine *ext,DrawOut out)
 {
  if( !placement ) return;

  FontSize fs=format.font->getSize();

  drawLine(format,range,out.add(ext->offx,fs.by));
 }

void Draw::draw(Format format,PtrLen<const Book::TypeDef::Span> range,const Book::TypeDef::MultiLine *placement,FrameExt_MultiLine *ext,DrawOut out)
 {
  if( !placement ) return;

  FontSize fs=format.font->getSize();

  out.base.y+=fs.by;

  Coord first_dx=ext->first_dx;
  Coord dy=ext->dy;

  PtrLen<ulen> split=Range(ext->split);

  ulen off=0;

  if( +split )
    {
     {
      ulen len=*split;

      auto part=range.safe_part(off,len);

      off+=len;

      drawLine(format,part,out.addX(first_dx));

      out.base.y+=dy;
     }

     for(ulen len : split.part(1) )
       {
        auto part=range.safe_part(off,len);

        off+=len;

        drawLine(format,part,out);

        out.base.y+=dy;
       }
    }
 }

void Draw::draw(Book::TypeDef::Text *obj,FrameExt *ext,DrawOut out)
 {
  if( !obj ) return;

  Format format=use(obj->fmt);

  auto range=obj->list.getRange();

  obj->placement.getPtr().apply( [&] (auto *placement) { draw(format,range,placement,AutoCast(ext),out); } );
 }

 // draw(Book::TypeDef::FixedText *)

void Draw::drawLine(Format format,PtrLen<const Book::TypeDef::FixedSpan> line,DrawOut out)
 {
  for(const Book::TypeDef::FixedSpan &span : line )
    {
     out.base=drawSpan(format.over(map,span.fmt),span.body,out);
    }
 }

void Draw::draw(Book::TypeDef::FixedText *obj,FrameExt *,DrawOut out)
 {
  if( !obj ) return;

  Format format=useFixed(obj->fmt);

  FontSize fs=format.font->getSize();

  out.base.y+=fs.by;

  Coord dy=fs.dy;

  for(const Book::TypeDef::Line &line : obj->list.getRange() )
    {
     drawLine(format,line.getRange(),out);

     out.base.y+=dy;
    }
 }

 // draw(Book::TypeDef::Bitmap *)

void Draw::draw(Book::TypeDef::Bitmap *obj,FrameExt *,DrawOut out)
 {
  out.bitmap(map(obj));
 }

 // draw(Book::TypeDef::TextList *)

void Draw::drawBullet(Format format,StrLen text,Coord bullet_len,DrawOut out)
 {
  TextSize ts=format.font->text(text);

  out.base.x+=bullet_len-ts.dx;

  if( format.back!=Book::NoColor ) out.back(ts,format.back);

  if( format.effect ) out.effect(ts,format.effect,format.fore,+cfg.width);

  out.text(format.font,text,format.fore);
 }

Coord Draw::drawItem(Format format,Book::TypeDef::ListItem item,FrameExt_TextList::Delta delta,Coord bullet_len,Coord bullet_space,DrawOut out)
 {
  drawBullet(format,item.bullet,bullet_len,out.addY(delta.by1));

  Point ebase=(*this)(item.list,out.add(bullet_len+bullet_space,delta.by2));

  return Max_cast(delta.dy1,ebase.y-out.base.y);
 }

void Draw::draw(Book::TypeDef::TextList *obj,FrameExt_TextList *ext,DrawOut out)
 {
  if( !obj ) return;

  Coord bullet_len=ext->bullet_len;
  Coord bullet_space=ext->bullet_space;
  Coord item_space=ext->item_space;

  FrameExt_TextList::Delta *delta=ext->delta.getPtr();

  Format format=useBack(obj->bullet_fmt);

  auto list=obj->list.getRange();

  for(ulen i=0; i<list.len ;i++)
    {
     Coord dy=drawItem(format,list[i],delta[i],bullet_len,bullet_space,out);

     out.base.y+=(dy+item_space);
    }
 }

 // draw(Book::TypeDef::Collapse *)

void Draw::draw(Book::TypeDef::Collapse *obj,FrameExt_Collapse *ext,DrawOut out)
 {
  if( !obj ) return;

  Coord len=ext->len;
  Coord elen=BoxExt(len);

  Format format=useBack(obj->collapse_fmt);

  if( obj->open )
    {
     out.drawMinus(cfg,len);

     if( !obj->hide )
       {
        Coord by=format.font->getSize().by;

        drawSpan(format,obj->title,out.add(elen,by));
       }

     (*this)(obj->list,out.addY(elen));
    }
  else
    {
     Coord by=format.font->getSize().by;

     out.drawPlus(cfg,len);

     drawSpan(format,obj->title,out.add(elen,by));
    }
 }

 // draw(Book::TypeDef::Table *)

void Draw::draw(Book::TypeDef::Table *obj,FrameExt_Table *ext,DrawOut out) // TODO
 {
  Used(obj);
  Used(ext);
  Used(out);
 }

 // drawAny()

template <class T>
void Draw::drawAny(T body,FrameExt *ext,DrawOut out)
 {
  body.apply( [&] (auto *obj) { draw(obj,AutoCast(ext),out); } );
 }

 // frame

Point Draw::operator () (Book::TypeDef::Frame *frame,DrawOut out)
 {
  Coord dy=(*this)(frame,out.buf,out.fullBase());

  return out.base.addY(dy);
 }

Point Draw::operator () (PtrLen<Book::TypeDef::Frame> list,DrawOut out)
 {
  for(Book::TypeDef::Frame &frame : list )
    {
     out.base=(*this)(&frame,out);
    }

  return out.base;
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

  drawAny(frame->body.getPtr(),ext,{buf.cut(inner),inner,ext->inner});

  return ext->size.y;
 }

/* class Shape */

void Shape::prepare(const Config &cfg,ExtMap &map,Ratio scale,Coord wdx)
 {
  Prepare ctx{cfg,map,scale,refs};

  size=ctx(frame,wdx,Null);
 }

void Shape::draw(const Config &cfg,ExtMap &map,VColor fore,DrawBuf buf,Point base) const
 {
  Draw ctx{cfg,map,fore};

  ctx(frame,buf,base);
 }

bool Shape::hit(Point point) const
 {
  return point>=Null && point<size ;
 }

RefType Shape::getRef(Point point) const
 {
  for(auto &obj : refs ) if( obj.pane.contains(point) ) return obj.ref;

  return Null;
 }

Point Shape::set(const Config &cfg,ExtMap &map,Ratio scale,Book::TypeDef::Frame &frame_,Coord wdx,Coord down_)
 {
  frame=&frame_;
  down=down_;

  refs.erase();

  prepare(cfg,map,scale,wdx);

  return size;
 }

void Shape::draw(const Config &cfg,ExtMap &map,VColor fore,DrawBuf buf,Coord pos_x,Coord pos_y) const
 {
  draw(cfg,map,fore,buf,Point(pos_x,pos_y));
 }

bool Shape::hit(Point point,Coord pos_x,Coord pos_y) const
 {
  return hit(point-Point(pos_x,pos_y));
 }

RefType Shape::getRef(Point point,Coord pos_x,Coord pos_y) const
 {
  return getRef(point-Point(pos_x,pos_y));
 }

} // namespace DrawBook
} // namespace App

