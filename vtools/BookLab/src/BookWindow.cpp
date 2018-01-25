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
#include <CCore/inc/Path.h>

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

/* struct InnerBookWindow::SizeContext */

bool InnerBookWindow::SkipSpace(StrLen text)
 {
  if( text.len!=1 ) return false;

  switch( *text )
    {
     case '.' : case ',' : case ';' : case ':' : return true;

     default: return false;
    }
 }

struct InnerBookWindow::SizeContext
 {
  const Config &cfg;
  FontMap &font_map;
  BitmapMap &bmp_map;
  const Book::TypeDef::Frame &frame;
  Coordinate wdx;

  Coord &offx;
  DynArray<ulen> &split;

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

  Point size(Book::TypeDef::TextList *obj) // TODO
   {
    return Null;
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
  BitmapMap &bmp_map;
  VColor fore;
  DrawBuf buf;
  const Book::TypeDef::Frame &frame;
  Pane pane;
  Point base;
  Coord offx;
  PtrLen<const ulen> split;

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

  void draw(Book::TypeDef::TextList *obj) // TODO
   {
    if( !obj ) return;


   }

  void draw()
   {
    frame.body.getPtr().apply( [&] (auto *obj) { draw(obj); } );
   }
 };

/* struct InnerBookWindow::Shape */

void InnerBookWindow::Shape::set(const Config &cfg,FontMap &font_map,BitmapMap &bmp_map,const Book::TypeDef::Frame &frame,Coordinate dx)
 {
  Scope scope("App::InnerBookWindow::Shape::set"_c);

  Point delta=2*( Cast(frame.inner)+Cast(frame.outer) );

  offx=0;
  split.erase();

  SizeContext ctx{cfg,font_map,bmp_map,frame,dx-delta.x,offx,split};

  size=ctx.size()+delta;
 }

void InnerBookWindow::Shape::draw(const Config &cfg,FontMap &font_map,BitmapMap &bmp_map,VColor fore,DrawBuf buf,const Book::TypeDef::Frame &frame,ulen pos_x,ulen pos_y,bool posflag) const
 {
  Scope scope("App::InnerBookWindow::Shape::draw"_c);

  if( posflag )
    draw(cfg,font_map,bmp_map,fore,buf,frame,Point(-(Coord)pos_x,-(Coord)pos_y));
  else
    draw(cfg,font_map,bmp_map,fore,buf,frame,Point(-(Coord)pos_x,(Coord)pos_y));
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

VColor InnerBookWindow::Shape::GetBack(const Book::TypeDef::TextList *)
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

void InnerBookWindow::Shape::draw(const Config &cfg,FontMap &font_map,BitmapMap &bmp_map,VColor fore,DrawBuf buf,const Book::TypeDef::Frame &frame,Point base) const
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

  DrawContext ctx{cfg,font_map,bmp_map,fore,buf,frame,inner,Cast(frame.inner),offx,Range(split)};

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

        shape.set(cfg,font_map,bmp_map,frames[i],dx);

        s=StackY(s,shape.size);
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

     return Point(dx,dy)+2*Point::Diag(RoundUpLen(+cfg.width));
    }
  else
    {
     return Point(500,300);
    }
 }

void InnerBookWindow::setPage(StrLen file_name,Book::TypeDef::Page *page,VColor back_,VColor fore_)
 {
  frames=Null;

  bmp_map.erase();

  bmp_map.setRoot(file_name);

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

  Point s=getSize()-2*Point::Diag(RoundUpLen(+cfg.width));

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
  cache(0);

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

  Point s=inner.getSize();

  ulen wdy=(ulen)s.y;

  ulen pos_x=sx.getPos();
  ulen pos_y=sy.getPos();
  ulen y=0;

  for(ulen i=0,len=Min(frames.len,shapes.getLen()); i<len ;i++)
    {
     auto &frame=frames[i];
     auto &shape=shapes[i];

     Size size=shape.getSize();

     if( y>=pos_y )
       {
        ulen delta=y-pos_y;

        if( delta<wdy )
          {
           if( pos_x<size.dx ) shape.draw(cfg,font_map,bmp_map,fore,buf,frame,pos_x,delta,false);
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
           shape.draw(cfg,font_map,bmp_map,fore,buf,frame,pos_x,delta,true);
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

void InnerBookWindow::react_LeftClick(Point point,MouseKey) // TODO
 {
  Used(point);
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

void DisplayBookWindow::setPage(StrLen file_name,Book::TypeDef::Page *page,VColor back,VColor fore)
 {
  window.setPage(file_name,page,back,fore);

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
  book.setPage(Null,0,Book::NoColor,Book::NoColor);

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

        book.setPage(file_name,page,Cast(ptr->back),Cast(ptr->fore));
       }
     else
       {
        text_page.setText(""_def);

        layout(LayoutUpdate);

        book.setPage(Null,0,Cast(ptr->back),Cast(ptr->fore));
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

  lay.setPlace(getPane(),flags,space);
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

