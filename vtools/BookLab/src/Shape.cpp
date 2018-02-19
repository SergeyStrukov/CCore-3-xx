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
#include <CCore/inc/Scope.h>

#include <CCore/inc/video/FigureLib.h>
#include <CCore/inc/video/LayoutCombo.h>

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
     return map.at(ext-1);
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
  return GetBY(cfg,font_map,obj->fmt);
 }

Coord Shape::GetBY(const Config &cfg,FontMap &font_map,const Book::TypeDef::FixedText *obj)
 {
  return GetBY(cfg,font_map,obj->fmt);
 }

Coord Shape::GetBY(const Config &,FontMap &,const Book::TypeDef::Bitmap *)
 {
  return 0;
 }

Coord Shape::GetBY(const Config &,FontMap &,const Book::TypeDef::TextList *)
 {
  return 0;
 }

Coord Shape::GetBY(const Config &cfg,FontMap &font_map,const Book::TypeDef::Frame &frame)
 {
  Coord ret=0;

  frame.body.getPtr().apply( [&] (auto *obj) { ret=GetBY(cfg,font_map,obj); } );

  return frame.inner.y+frame.outer.y+ret;
 }

/* struct Shape::SizeContext */

struct Shape::SizeContext
 {
  const Config &cfg;
  FontMap &font_map;
  BitmapMap &bmp_map;
  const Book::TypeDef::Frame &frame;
  Coordinate wdx;

  Coord &offx;
  DynArray<ulen> &split;
  DynArray<Shape> &subshapes;

  Font font;
  Coordinate space_dx;

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

    space_dx=sizeSpace(font);
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

    space_dx=sizeSpace(font);
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
    return space_dx;
   }

  Coordinate sizeSpan(Book::TypeDef::Span span)
   {
    return sizeSpan(useSpan(span.fmt),span.body);
   }

  struct DeltaSize
   {
    Coordinate dx;
    Coordinate edx;
   };

  DeltaSize sizeSpan(const Book::TypeDef::Format *fmt,Book::TypeDef::Span span)
   {
    Font font=useSpan(span.fmt);

    Coordinate sdx=0;

    if( !SkipSpace(span.body) )
      {
       if( fmt==span.fmt )
         {
          sdx=sizeSpace(font);
         }
       else
         {
          sdx=sizeSpace();
         }
      }

    Coordinate dx=sizeSpan(font,span.body);

    return {dx,dx+sdx};
   }

  Coordinate sizeLine(PtrLen<const Book::TypeDef::Span> line)
   {
    Coordinate dx=0;

    if( +line )
      {
       dx=sizeSpan(*line);

       const Book::TypeDef::Format *fmt=line->fmt;

       for(++line; +line ;++line)
         {
          dx+=sizeSpan(fmt,*line).edx;

          fmt=line->fmt;
         }
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

  Point size(PtrLen<const Book::TypeDef::Span> range,const Book::TypeDef::MultiLine *placement)
   {
    if( !placement ) return Null;

    FontSize fs=font->getSize();

    Coordinate tdx=fs.dy;
    Coordinate tdy=fs.dy;

    Coordinate dy=Cast(placement->line_space)*fs.dy;
    Coordinate first_dx=Cast(placement->first_line_space)*fs.dy;

    if( +range )
      {
       Coordinate dx=sizeSpan(*range)+first_dx;

       const Book::TypeDef::Format *fmt=range->fmt;

       while( +range )
         {
          ulen len=1;

          for(++range; +range ;++range,len++)
            {
             DeltaSize delta=sizeSpan(fmt,*range);

             fmt=range->fmt;

             if( delta.edx<=wdx-dx )
               {
                dx+=delta.edx;
               }
             else
               {
                Replace_max(tdx,dx);

                tdy+=dy;

                dx=delta.dx;

                break;
               }
            }

          split.append_copy(len);
         }

       Replace_max(tdx,dx);
      }

    return Point(tdx,tdy);
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

  Point size(Book::TypeDef::Bitmap *obj)
   {
    const Bitmap *bitmap=bmp_map(obj);

    if( !bitmap ) return Null;

    return {CountToCoordinate(bitmap->dX()),CountToCoordinate(bitmap->dY())};
   }

  Coord sizeBullet(Font font,StrLen text)
   {
    return +sizeSpan(font,text);
   }

  Point size(Font font,Book::TypeDef::ListItem item,Shape *shapes,Coord bullet_space)
   {
    FontSize fs=font->getSize();

    auto list=item.list.getRange();

    Coord by1=fs.by;
    Coord dy1=fs.dy;
    Coord dy2=0;

    if( +list )
      {
       Coord by2=GetBY(cfg,font_map,*list);

       if( by2>by1 )
         {
          dy1+=(by2-by1);
         }
       else
         {
          dy2=by1-by2;
         }
      }

    Coordinate dx=wdx-offx-bullet_space;

    Point s(0,dy2);

    for(ulen i=0; i<list.len ;i++)
      {
       s=StackYSize(s, shapes[i].set(cfg,font_map,bmp_map,list[i],dx) );
      }

    return StackXSize( Point(offx+bullet_space,dy1) , s );
   }

  Point size(Book::TypeDef::TextList *obj)
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

    Point ret=Null;

    Coord bullet_space=obj->bullet_space;

    for(ulen i=0; i<list.len ;i++)
      {
       ulen count=list[i].list.len;

       ret=StackYSize(ret,size(font,list[i],shapes,bullet_space));

       shapes+=count;
      }

    return ret.addY( +( (CountToCoordinate(list.len)-1)*obj->item_space ) );
   }

  Point size()
   {
    Point ret;

    frame.body.getPtr().apply( [&] (auto *ptr) { ret=size(ptr); } );

    return ret;
   }
 };

/* struct Shape::DrawContext */

struct Shape::DrawContext
 {
  const Config &cfg;
  FontMap &font_map;
  BitmapMap &bmp_map;
  VColor fore;
  DrawBuf buf;
  const Book::TypeDef::Frame &frame;
  Pane pane;
  Point base;

  Coord offx;
  PtrLen<const ulen> split;
  PtrLen<const Shape> subshapes;

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

    base.y+=fs.by;

    drawLine(range,base.addX(offx));
   }

  void draw(PtrLen<const Book::TypeDef::Span> range,const Book::TypeDef::MultiLine *placement)
   {
    if( !placement ) return;

    FontSize fs=font->getSize();

    base.y+=fs.by;

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

  void draw(Book::TypeDef::Bitmap *obj)
   {
    const Bitmap *bitmap=bmp_map(obj);

    if( !bitmap ) return;

    bitmap->draw(buf,pane.shrink(base));
   }

  Coord draw(Format fmt,Book::TypeDef::ListItem item,PtrLen<const Shape> shapes,Coord bullet_space)
   {
    FontSize fs=fmt.font->getSize();

    auto list=item.list.getRange();

    Coord by1=fs.by;
    Coord dy1=fs.dy;
    Coord dy2=0;

    if( +list )
      {
       Coord by2=GetBY(cfg,font_map,*list);

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

    Point b=base;

    b.y+=by1;

    drawBullet(fmt,item.bullet,b);

    Point p=base;

    p.x+=offx+bullet_space;
    p.y+=dy2;

    for(ulen i=0,len=Min(list.len,shapes.len); i<len ;i++)
      {
       Coord dy=shapes[i].drawSub(cfg,font_map,bmp_map,fore,buf,pane,p);

       p.y+=dy;
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

    Coord bullet_space=obj->bullet_space;

    for(ulen i=0; i<list.len ;i++)
      {
       ulen count=list[i].list.len;

       Coord dy=draw(fmt,list[i],subshapes.safe_part(off,count),bullet_space);

       off+=count;

       base.y += ( dy + obj->item_space ) ;
      }
   }

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

void Shape::draw(const Config &cfg,FontMap &font_map,BitmapMap &bmp_map,VColor fore,DrawBuf buf,Point base) const
 {
  Pane pane(base,size);

  Pane inner=pane.shrink(Cast(frame->outer));

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

  DrawContext ctx{cfg,font_map,bmp_map,fore,buf.cut(inner),*frame,inner,Cast(frame->inner),offx,Range(split),Range(subshapes)};

  ctx.draw();
 }

Point Shape::set(const Config &cfg,FontMap &font_map,BitmapMap &bmp_map,const Book::TypeDef::Frame &frame_,Coordinate dx)
 {
  frame=&frame_;

  Scope scope("App::Shape::set"_c);

  Point delta=2*( Cast(frame->inner)+Cast(frame->outer) );

  offx=0;
  split.erase();

  SizeContext ctx{cfg,font_map,bmp_map,*frame,dx-delta.x,offx,split,subshapes};

  size=ctx.size()+delta;

  return size;
 }

void Shape::draw(const Config &cfg,FontMap &font_map,BitmapMap &bmp_map,VColor fore,DrawBuf buf,ulen pos_x,ulen pos_y,bool posflag) const
 {
  Scope scope("App::Shape::draw"_c);

  if( posflag )
    draw(cfg,font_map,bmp_map,fore,buf,Point(-(Coord)pos_x,-(Coord)pos_y));
  else
    draw(cfg,font_map,bmp_map,fore,buf,Point(-(Coord)pos_x,(Coord)pos_y));
 }

Coord Shape::drawSub(const Config &cfg,FontMap &font_map,BitmapMap &bmp_map,VColor fore,DrawBuf buf,Pane parent,Point base) const
 {
  Pane pane(parent.getBase()+base,size);

  Pane inner=pane.shrink(Cast(frame->outer));

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

  DrawContext ctx{cfg,font_map,bmp_map,fore,buf.cut(Inf(inner,parent)),*frame,inner,Cast(frame->inner),offx,Range(split),Range(subshapes)};

  ctx.draw();

  return size.y;
 }

} // namespace App

