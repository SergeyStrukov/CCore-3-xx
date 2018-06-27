/* Shape.cpp */
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

#include <inc/Shape.h>

#include <CCore/inc/Path.h>

#include <CCore/inc/video/FigureLib.h>
#include <CCore/inc/video/LayoutCombo.h>

#include <CCore/inc/Exception.h>

namespace App {

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

auto FontMap::find(Book::TypeDef::Font *font,Font fallback) -> Rec
 {
  return find(font->face,scale*Coord(font->size),font->strength,font->bold,font->italic,fallback);
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

Font FontMap::operator () (Book::TypeDef::Font *font,Font fallback)
 {
  if( !font ) return fallback;

  if( ulen ext=font->ext )
    {
     Rec &rec=map.at(ext-1);

     if( rec.ok ) return rec.font;

     if( rec.fallback )
       {
        rec.font=fallback;
       }
     else
       {
        SetSize(rec.font,scale*Coord(font->size));
       }

     rec.ok=true;

     return rec.font;
    }
  else
    {
     ulen ind=map.getLen();

     Rec rec=find(font,fallback);

     map.append_copy(rec);

     font->ext=ind+1;

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

const Bitmap * BitmapMap::operator () (Book::TypeDef::Bitmap *bmp)
 {
  if( !bmp ) return 0;

  try
    {
     if( ulen ext=bmp->ext )
       {
        return &map.at(ext-1);
       }
     else
       {
        ulen ind=map.getLen();

        Bitmap *ret=map.append_fill(Range(root),bmp->file_name);

        bmp->ext=ind+1;

        return ret;
       }
    }
  catch(...) { return 0; }
 }

/* class Shape */

bool Shape::SkipSpace(StrLen text)
 {
  if( text.len!=1 ) return false;

  switch( *text )
    {
     case '.' : case ',' : case ';' : case ':' : return true;

     default: return false;
    }
 }

Coord Shape::GetBY(const Config &cfg,FontMap &font_map,const Book::TypeDef::Format *fmt)
 {
  Font font;

  if( fmt )
    {
     font=font_map(fmt->font,+cfg.font);
    }
  else
    {
     font=+cfg.font;
    }

  return font->getSize().by;
 }

Coord Shape::GetBY(const Config &cfg,FontMap &font_map,const Book::TypeDef::Text *obj)
 {
  if( obj ) return GetBY(cfg,font_map,obj->fmt);

  return 0;
 }

Coord Shape::GetBY(const Config &cfg,FontMap &font_map,const Book::TypeDef::FixedText *obj)
 {
  if( obj ) return GetBY(cfg,font_map,obj->fmt);

  return 0;
 }

Coord Shape::GetBY(const Config &,FontMap &,const Book::TypeDef::Bitmap *)
 {
  return 0;
 }

Coord Shape::GetBY(const Config &,FontMap &,const Book::TypeDef::TextList *)
 {
  return 0;
 }

Coord Shape::GetBY(const Config &cfg,FontMap &font_map,const Book::TypeDef::Collapse *obj)
 {
  if( obj ) return GetBY(cfg,font_map,obj->collapse_fmt);

  return 0;
 }

Coord Shape::GetBY(const Config &,FontMap &,const Book::TypeDef::Table *)
 {
  return 0;
 }

Coord Shape::GetBY(const Config &cfg,FontMap &font_map,const Book::TypeDef::Frame &frame,Ratio scale)
 {
  Coord ret=0;

  frame.body.getPtr().apply( [&] (auto *obj) { ret=GetBY(cfg,font_map,obj); } );

  return scale*Coord(frame.inner.y)+scale*Coord(frame.outer.y)+ret;
 }

/* struct Shape::SizeContext */

struct Shape::SizeContext
 {
  const Config &cfg;
  FontMap &font_map;
  BitmapMap &bmp_map;
  Ratio scale;
  const Book::TypeDef::Frame &frame;
  Coord wdx;

  Coord &offx;
  DynArray<ulen> &split;
  DynArray<Shape> &subshapes;
  DynArray<RefPane> &refs;

  Font font;
  Coord space_dx;

  // methods

  static Coord SizeSpan(Font font,StrLen text)
   {
    TextSize ts=font->text(text);

    return ts.dx;
   }

  static Coord SizeSpace(Font font)
   {
    return SizeSpan(font," "_c);
   }

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

    space_dx=SizeSpace(font);
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

    space_dx=SizeSpace(font);
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

  void addRef(RefType ref,Pane pane)
   {
    if( +ref ) refs.append_copy(RefPane{pane,ref});
   }

  static RefType CastRef(AnyPtr<Book::TypeDef::Link,Book::TypeDef::Page> ref)
   {
    RefType ret;

    ref.apply( [ref,&ret] (auto *ptr) { ret=ptr; } );

    return ret;
   }

  void addRef(AnyPtr<Book::TypeDef::Link,Book::TypeDef::Page> ref,Pane pane)
   {
    if( +ref ) refs.append_copy(RefPane{pane,CastRef(ref)});
   }

  // size Text

  Coord sizeSpan(Book::TypeDef::Span span,Point base,Coord dy)
   {
    Coord dx=SizeSpan(useSpan(span.fmt),span.body);

    addRef(span.ref,Pane(base,dx,dy));

    return dx;
   }

  struct DeltaSize
   {
    Coord dx;
    Coord edx;
   };

  DeltaSize sizeSpan(const Book::TypeDef::Format *fmt,Book::TypeDef::Span span,Point base,Coord dy)
   {
    Font font=useSpan(span.fmt);

    Coord sdx=0;

    if( !SkipSpace(span.body) )
      {
       if( fmt==span.fmt )
         {
          sdx=SizeSpace(font);
         }
       else
         {
          sdx=space_dx;
         }
      }

    Coord dx=SizeSpan(font,span.body);

    addRef(span.ref,Pane(base.addX(sdx),dx,dy));

    return {dx,dx+sdx};
   }

  Coord sizeLine(PtrLen<const Book::TypeDef::Span> line,Point base,Coord dy)
   {
    Coord tdx=0;

    if( +line )
      {
       tdx=sizeSpan(*line,base,dy);

       const Book::TypeDef::Format *fmt=line->fmt;

       base.x+=tdx;

       for(++line; +line ;++line)
         {
          Coord dx=sizeSpan(fmt,*line,base,dy).edx;

          tdx+=dx;

          base.x+=dx;

          fmt=line->fmt;
         }
      }

    return tdx;
   }

  void correctRefs(ulen refs_len)
   {
    Coord delta=offx;

    for(RefPane &ref : Range(refs).part(refs_len) )
      {
       ref.pane.x+=delta;
      }
   }

  Point size(PtrLen<const Book::TypeDef::Span> range,const Book::TypeDef::OneLine *placement,Point base)
   {
    if( !placement ) return Null;

    FontSize fs=font->getSize();

    ulen refs_len=refs.getLen();

    Coord dx=sizeLine(range,base,fs.dy);

    switch( placement->align )
      {
       case Book::LineRight :
        {
         Coord extra=PlusSub(wdx,dx);

         offx=extra;

         correctRefs(refs_len);
        }
       break;

       case Book::LineCenter :
        {
         Coord extra=PlusSub(wdx,dx);

         offx=extra/2;

         correctRefs(refs_len);
        }
       break;

       default: // case Book::LineLeft :
        {
         offx=0;
        }
      }

    return Point(Max(dx,wdx),fs.dy);
   }

  Point size(PtrLen<const Book::TypeDef::Span> range,const Book::TypeDef::MultiLine *placement,Point base)
   {
    if( !placement ) return Null;

    FontSize fs=font->getSize();

    Coord tdx=fs.dy;
    Coord tdy=fs.dy;

    Coord dy=Cast(placement->line_space)*fs.dy;
    Coord first_dx=Cast(placement->first_line_space)*fs.dy;

    if( +range )
      {
       Coord dx=sizeSpan(*range,base.addX(first_dx),tdy)+first_dx;

       const Book::TypeDef::Format *fmt=range->fmt;

       Point p=base;

       p.x+=dx;

       while( +range )
         {
          ulen len=1;

          for(++range; +range ;++range,len++)
            {
             DeltaSize delta=sizeSpan(fmt,*range,p,tdy);

             fmt=range->fmt;

             if( delta.edx<=wdx-dx )
               {
                dx+=delta.edx;

                p.x+=delta.edx;
               }
             else
               {
                Replace_max(tdx,dx);

                tdy+=dy;

                dx=delta.dx;

                base.y+=tdy;

                p=base;

                p.x+=dx;

                break;
               }
            }

          split.append_copy(len);
         }

       Replace_max(tdx,dx);
      }

    return Point(tdx,tdy);
   }

  Point size(const Book::TypeDef::Text *obj,Point base)
   {
    if( !obj ) return Null;

    use(obj->fmt);

    auto range=obj->list.getRange();

    Point ret;

    obj->placement.getPtr().apply( [&] (auto *placement) { ret=size(range,placement,base); } );

    return ret;
   }

  // size FixedText

  Coord sizeLine(Book::TypeDef::Line line,Point base,Coord dy)
   {
    Coord ret=0;

    for(const Book::TypeDef::FixedSpan &span : line.getRange() )
      {
       Coord dx=SizeSpan(useSpan(span.fmt),span.body);

       addRef(span.ref,Pane(base,dx,dy));

       ret+=dx;
       base.x+=dx;
      }

    return ret;
   }

  Point size(const Book::TypeDef::FixedText *obj,Point base)
   {
    if( !obj ) return Null;

    useFixed(obj->fmt);

    FontSize fs=font->getSize();

    Coord dy=fs.dy;

    auto range=obj->list.getRange();

    Coord dx=0;

    for(const Book::TypeDef::Line &line : range )
      {
       dx=Max(dx,sizeLine(line,base,dy));

       base.y+=dy;
      }

    return Point(dx,CountToCoord(range.len)*dy);
   }

  // size Bitmap

  Point size(Book::TypeDef::Bitmap *obj,Point base)
   {
    Used(base);

    const Bitmap *bitmap=bmp_map(obj);

    if( !bitmap ) return Null;

    return {CountToCoord(bitmap->dX()),CountToCoord(bitmap->dY())};
   }

  // size TextList

  Coord sizeBullet(Font font,StrLen text)
   {
    return SizeSpan(font,text);
   }

  Point size(Font font,Book::TypeDef::ListItem item,Shape *shapes,Coord bullet_space,Point base)
   {
    FontSize fs=font->getSize();

    auto list=item.list.getRange();

    Coord by1=fs.by;
    Coord dy1=fs.dy;
    Coord dy2=0;

    if( +list )
      {
       Coord by2=GetBY(cfg,font_map,*list,scale);

       if( by2>by1 )
         {
          dy1+=(by2-by1);
         }
       else
         {
          dy2=by1-by2;
         }
      }

    Coord dx=wdx-offx-bullet_space;

    Point s(0,dy2);

    Point p=base;

    p.x+=offx+bullet_space;
    p.y+=dy2;

    for(ulen i=0; i<list.len ;i++)
      {
       Point t=shapes[i].set(cfg,font_map,bmp_map,scale,list[i],dx,p);

       s=StackY(s,t);

       p.y+=t.y;
      }

    return StackXSize(Point(offx+bullet_space,dy1),s);
   }

  Point size(Book::TypeDef::TextList *obj,Point base)
   {
    if( !obj ) return Null;

    auto list=obj->list.getRange();

    if( !list.len ) return Null;

    Font font=useSpan(obj->bullet_fmt);

    ulen total=0;

    for(ulen i=0; i<list.len ;i++) total=LenAdd(total,list[i].list.len);

    if( subshapes.getLen()!=total )
      {
       subshapes.erase();
       subshapes.extend_default(total);
      }

    for(ulen i=0; i<list.len ;i++) Replace_max(offx,sizeBullet(font,list[i].bullet));

    Shape *shapes=subshapes.getPtr();

    Coord bullet_space=scale*Coord(obj->bullet_space);

    Coord item_space=scale*Coord(obj->item_space);

    Point ret(0, (CountToCoord(list.len)-1)*item_space );

    for(ulen i=0; i<list.len ;i++)
      {
       ulen count=list[i].list.len;

       Point s=size(font,list[i],shapes,bullet_space,base);

       ret=StackY(ret,s);

       shapes+=count;

       base.y+=(s.y+item_space);
      }

    return ret;
   }

  // size Collapse

  Point size(Book::TypeDef::Collapse *obj,Point base)
   {
    if( !obj ) return Null;

    Font font=useSpan(obj->collapse_fmt);

    offx=font->getSize().dy;

    addRef(RefType(obj),Pane(base,offx));

    if( obj->open )
      {
       Point ret;

       if( obj->hide )
         {
          ret=Point(offx,BoxExt(offx));
         }
       else
         {
          Coord tx=SizeSpan(font,obj->title);

          ret=Point::Diag(BoxExt(offx)).addX(tx);
         }

       auto list=obj->list.getRange();

       if( subshapes.getLen()!=list.len )
         {
          subshapes.erase();
          subshapes.extend_default(list.len);
         }

       base.y+=ret.y;

       for(ulen i=0; i<list.len ;i++)
         {
          Point s=subshapes[i].set(cfg,font_map,bmp_map,scale,list[i],wdx,base);

          ret=StackY(ret,s);

          base.y+=s.y;
         }

       return ret;
      }
    else
      {
       Point ret;

       Coord tx=SizeSpan(font,obj->title);

       ret=Point::Diag(BoxExt(offx)).addX(tx);

       return ret;
      }
   }

  // size Table

  Point size(Book::TypeDef::Table *obj,Point base) // TODO
   {
    return Null;
   }

  // size

  Point size(Point base)
   {
    Point ret;

    frame.body.getPtr().apply( [&] (auto *ptr) { ret=size(ptr,base); } );

    return ret;
   }
 };

/* class Shape */

Point Shape::set(const Config &cfg,FontMap &font_map,BitmapMap &bmp_map,Ratio scale,const Book::TypeDef::Frame &frame_,Coord dx,Point base)
 {
  frame=&frame_;

  Point off=scale*Cast(frame->inner)+scale*Cast(frame->outer);
  Point delta=2*off;

  offx=0;
  split.erase();
  refs.shrink_all();

  SizeContext ctx{cfg,font_map,bmp_map,scale,*frame,dx-delta.x,offx,split,subshapes,refs};

  size=ctx.size(base+off)+delta;

  return size;
 }

/* struct Shape::DrawContext */

struct Shape::DrawContext
 {
  const Config &cfg;
  FontMap &font_map;
  BitmapMap &bmp_map;
  Ratio scale;
  VColor fore;
  DrawBuf buf;
  const Book::TypeDef::Frame &frame;
  Pane pane;
  Point inner; // base

  Coord offx;
  PtrLen<const ulen> split;
  PtrLen<const Shape> subshapes;

  Font font;
  Effect effect;

  // methods

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

  void drawBullet(Format fmt,StrLen text,Point base)
   {
    TextSize ts=fmt.font->text(text);

    base.x+=offx-ts.dx;

    if( fmt.back!=Book::NoColor ) FillBack(buf,pane,base,ts,fmt.back);

    if( fmt.effect ) MakeEffect(buf,pane,base,ts,fmt.effect,fmt.fore,+cfg.width);

    fmt.font->text(buf,pane,base,text,fmt.fore);
   }

  Point drawSpace(Format fmt,Point base)
   {
    return drawSpan(fmt," "_c,base);
   }

  Point drawSpace(Point base)
   {
    return drawSpace(useSpan(),base);
   }

  // draw Text

  Point drawSpan(Book::TypeDef::Span span,Point base)
   {
    return drawSpan(useSpan(span.fmt),span.body,base);
   }

  Point drawSpan(const Book::TypeDef::Format *fmt,Book::TypeDef::Span span,Point base)
   {
    Format format=useSpan(span.fmt);

    if( !SkipSpace(span.body) )
      {
       if( fmt==span.fmt )
         {
          base=drawSpace(format,base);
         }
       else
         {
          base=drawSpace(base);
         }
      }

    return drawSpan(format,span.body,base);
   }

  void drawLine(PtrLen<const Book::TypeDef::Span> line,Point base)
   {
    if( +line )
      {
       base=drawSpan(*line,base);

       const Book::TypeDef::Format *fmt=line->fmt;

       for(++line; +line ;++line)
         {
          base=drawSpan(fmt,*line,base);

          fmt=line->fmt;
         }
      }
   }

  void draw(PtrLen<const Book::TypeDef::Span> range,const Book::TypeDef::OneLine *placement)
   {
    if( !placement ) return;

    FontSize fs=font->getSize();

    drawLine(range,inner+Point(offx,fs.by));
   }

  void draw(PtrLen<const Book::TypeDef::Span> range,const Book::TypeDef::MultiLine *placement)
   {
    if( !placement ) return;

    FontSize fs=font->getSize();

    Point base=inner.addY(fs.by);

    Coord dy=Cast(placement->line_space)*fs.dy;
    Coord first_dx=Cast(placement->first_line_space)*fs.dy;

    ulen off=0;

    if( +split )
      {
       {
        ulen len=*split;

        auto part=range.safe_part(off,len);

        off+=len;

        drawLine(part,base.addX(first_dx));

        base.y+=dy;
       }

       for(ulen len : split.part(1) )
         {
          auto part=range.safe_part(off,len);

          off+=len;

          drawLine(part,base);

          base.y+=dy;
         }
      }
   }

  void draw(const Book::TypeDef::Text *obj)
   {
    if( !obj ) return;

    use(obj->fmt);

    auto range=obj->list.getRange();

    obj->placement.getPtr().apply( [&] (auto *placement) { draw(range,placement); } );
   }

  // draw FixedSpan

  void drawLine(PtrLen<const Book::TypeDef::FixedSpan> line,Point base)
   {
    for(const Book::TypeDef::FixedSpan &span : line )
      {
       base=drawSpan(useSpan(span.fmt),span.body,base);
      }
   }

  void draw(const Book::TypeDef::FixedText *obj)
   {
    if( !obj ) return;

    useFixed(obj->fmt);

    FontSize fs=font->getSize();

    Point base=inner.addY(fs.by);

    Coord dy=fs.dy;

    for(const Book::TypeDef::Line &line : obj->list.getRange() )
      {
       drawLine(line.getRange(),base);

       base.y+=dy;
      }
   }

  // draw Bitmap

  void draw(Book::TypeDef::Bitmap *obj)
   {
    const Bitmap *bitmap=bmp_map(obj);

    if( !bitmap ) return;

    bitmap->draw(buf,pane.shrink(inner));
   }

  // draw TextList

  Coord draw(Format fmt,Book::TypeDef::ListItem item,PtrLen<const Shape> shapes,Coord bullet_space,Point base)
   {
    FontSize fs=fmt.font->getSize();

    auto list=item.list.getRange();

    Coord by1=fs.by;
    Coord dy1=fs.dy;
    Coord dy2=0;

    if( +list )
      {
       Coord by2=GetBY(cfg,font_map,*list,scale);

       if( by2>by1 )
         {
          dy1+=(by2-by1);
          by1=by2;
         }
       else
         {
          dy2=by1-by2;
         }
      }

    drawBullet(fmt,item.bullet,base.addY(by1));

    base.x+=offx+bullet_space;
    base.y+=dy2;

    for(ulen i=0,len=Min(list.len,shapes.len); i<len ;i++)
      {
       Coord dy=shapes[i].drawSub(cfg,font_map,bmp_map,scale,fore,buf,pane,base);

       base.y+=dy;
       dy2+=dy;
      }

    return Max(dy1,dy2);
   }

  void draw(Book::TypeDef::TextList *obj)
   {
    if( !obj ) return;

    Format fmt=useSpan(obj->bullet_fmt);

    auto list=obj->list.getRange();

    ulen off=0;

    Coord bullet_space=scale*Coord(obj->bullet_space);

    Coord item_space=scale*Coord(obj->item_space);

    Point base=inner;

    for(ulen i=0; i<list.len ;i++)
      {
       ulen count=list[i].list.len;

       Coord dy=draw(fmt,list[i],subshapes.safe_part(off,count),bullet_space,base);

       off+=count;

       base.y+=(dy+item_space);
      }
   }

  // draw Collapse

  void drawPlus(Point base,Coord len_)
   {
    MPane p(Pane(pane.getBase()+base,len_));

    if( !p ) return;

    SmoothDrawArt art(buf.cut(pane));

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

  void drawMinus(Point base,Coord len_)
   {
    MPane p(Pane(pane.getBase()+base,len_));

    if( !p ) return;

    SmoothDrawArt art(buf.cut(pane));

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

  void draw(Book::TypeDef::Collapse *obj)
   {
    if( !obj ) return;

    Format fmt=useSpan(obj->collapse_fmt);

    if( obj->open )
      {
       Point base=inner;

       drawMinus(base,offx);

       if( !obj->hide )
         {
          Coord by=fmt.font->getSize().by;

          drawSpan(fmt,obj->title,base+Point(BoxExt(offx),by));
         }

       auto list=obj->list.getRange();

       base.y+=BoxExt(offx);

       for(ulen i=0; i<list.len ;i++)
         {
          Coord dy=subshapes[i].drawSub(cfg,font_map,bmp_map,scale,fore,buf,pane,base);

          base.y+=dy;
         }
      }
    else
      {
       Point base=inner;
       Coord by=fmt.font->getSize().by;

       drawPlus(base,offx);

       drawSpan(fmt,obj->title,base+Point(BoxExt(offx),by));
      }
   }

  // draw Table

  void draw(Book::TypeDef::Table *obj) // TODO
   {
   }

  // draw

  void draw()
   {
    frame.body.getPtr().apply( [&] (auto *obj) { draw(obj); } );
   }
 };

/* class Shape */

VColor Shape::GetBack(const Book::TypeDef::Format *fmt)
 {
  if( fmt ) return Cast(fmt->back);

  return Book::NoColor;
 }

VColor Shape::GetBack(const Book::TypeDef::Text *obj)
 {
  if( obj ) return GetBack(obj->fmt.getPtr());

  return Book::NoColor;
 }

VColor Shape::GetBack(const Book::TypeDef::FixedText *obj)
 {
  if( obj ) return GetBack(obj->fmt.getPtr());

  return Book::NoColor;
 }

VColor Shape::GetBack(const Book::TypeDef::Bitmap *)
 {
  return Book::NoColor;
 }

VColor Shape::GetBack(const Book::TypeDef::TextList *)
 {
  return Book::NoColor;
 }

VColor Shape::GetBack(const Book::TypeDef::Collapse *)
 {
  return Book::NoColor;
 }

VColor Shape::GetBack(const Book::TypeDef::Table *)
 {
  return Book::NoColor;
 }

template <class T>
VColor Shape::GetAnyBack(T body)
 {
  VColor ret=Book::NoColor;

  body.apply( [&] (auto *ptr) { ret=GetBack(ptr); } );

  return ret;
 }

void Shape::DrawLine(const Config &cfg,DrawBuf buf,const Book::TypeDef::SingleLine *obj,Pane pane)
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

void Shape::DrawLine(const Config &cfg,DrawBuf buf,const Book::TypeDef::DoubleLine *obj,Pane pane)
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
void Shape::DrawAnyLine(const Config &cfg,DrawBuf buf,T line,Pane pane)
 {
  line.apply( [&] (auto *obj) { DrawLine(cfg,buf,obj,pane); } );
 }

void Shape::draw(const Config &cfg,FontMap &font_map,BitmapMap &bmp_map,Ratio scale,VColor fore,DrawBuf buf,Point base) const
 {
  Pane pane(base,size);

  Pane inner=pane.shrink(scale*Cast(frame->outer));

  if( VColor col=Cast(frame->col) ; col!=Book::NoColor )
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

  DrawAnyLine(cfg,buf,frame->line.getPtr(),inner);

  DrawContext ctx{cfg,font_map,bmp_map,scale,fore,buf.cut(inner),*frame,inner,scale*Cast(frame->inner),offx,Range(split),Range(subshapes)};

  ctx.draw();
 }

Coord Shape::drawSub(const Config &cfg,FontMap &font_map,BitmapMap &bmp_map,Ratio scale,VColor fore,DrawBuf buf,Pane parent,Point base) const
 {
  Pane pane(parent.getBase()+base,size);

  Pane inner=pane.shrink(scale*Cast(frame->outer));

  if( VColor col=Cast(frame->col) ; col!=Book::NoColor )
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

  DrawAnyLine(cfg,buf,frame->line.getPtr(),inner);

  DrawContext ctx{cfg,font_map,bmp_map,scale,fore,buf.cut(Inf(inner,parent)),*frame,inner,scale*Cast(frame->inner),offx,Range(split),Range(subshapes)};

  ctx.draw();

  return size.y;
 }

bool Shape::hit(Point point) const
 {
  return point>=Null && point<size ;
 }

RefType Shape::getRef(Point point) const
 {
  for(auto &obj : refs ) if( obj.pane.contains(point) ) return obj.ref;

  for(auto &shape : subshapes )
    {
     auto ref=shape.getRef(point);

     if( +ref ) return ref;
    }

  return Null;
 }

Point Shape::set(const Config &cfg,FontMap &font_map,BitmapMap &bmp_map,Ratio scale,const Book::TypeDef::Frame &frame,Coord dx)
 {
  return set(cfg,font_map,bmp_map,scale,frame,dx,Null);
 }

void Shape::draw(const Config &cfg,FontMap &font_map,BitmapMap &bmp_map,Ratio scale,VColor fore,DrawBuf buf,Coord pos_x,Coord pos_y) const
 {
  draw(cfg,font_map,bmp_map,scale,fore,buf,Point(pos_x,pos_y));
 }

bool Shape::hit(Point point,Coord pos_x,Coord pos_y) const
 {
  return hit(point-Point(pos_x,pos_y));
 }

RefType Shape::getRef(Point point,Coord pos_x,Coord pos_y) const
 {
  return getRef(point-Point(pos_x,pos_y));
 }

} // namespace App

