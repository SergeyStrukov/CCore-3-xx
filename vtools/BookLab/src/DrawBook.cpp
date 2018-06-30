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

/* struct ExtMap */

FrameExt * ExtMap::operator () (const Book::TypeDef::Frame *frame)
 {
  Used(frame);

  static FrameExt stub;

  return &stub;
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

void Draw::drawLine(const Book::TypeDef::SingleLine *obj,Pane pane)
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

void Draw::drawLine(const Book::TypeDef::DoubleLine *obj,Pane pane)
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
void Draw::drawAnyLine(T line,Pane pane)
 {
  line.apply( [&] (auto *obj) { drawLine(obj,pane); } );
 }

 // draw()

void Draw::draw(const Book::TypeDef::Text *obj,Pane inner,Point pad)
 {
  Used(obj);
  Used(inner);
  Used(pad);
 }

void Draw::draw(const Book::TypeDef::FixedText *obj,Pane inner,Point pad)
 {
  Used(obj);
  Used(inner);
  Used(pad);
 }

void Draw::draw(const Book::TypeDef::Bitmap *obj,Pane inner,Point pad)
 {
  Used(obj);
  Used(inner);
  Used(pad);
 }

void Draw::draw(const Book::TypeDef::TextList *obj,Pane inner,Point pad)
 {
  Used(obj);
  Used(inner);
  Used(pad);
 }

void Draw::draw(const Book::TypeDef::Collapse *obj,Pane inner,Point pad)
 {
  Used(obj);
  Used(inner);
  Used(pad);
 }

void Draw::draw(const Book::TypeDef::Table *obj,Pane inner,Point pad)
 {
  Used(obj);
  Used(inner);
  Used(pad);
 }

template <class T>
void Draw::drawAny(T body,Pane inner,Point pad)
 {
  body.apply( [&] (auto *obj) { draw(obj,inner,pad); } );
 }

 // public

void Draw::operator () (const Book::TypeDef::Frame *frame)
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

  drawAnyLine(frame->line.getPtr(),inner);

  buf=buf.cut(inner);

  drawAny(frame->body.getPtr(),inner,scale*Cast(frame->inner));
 }

} // namespace DrawBook
} // namespace App

