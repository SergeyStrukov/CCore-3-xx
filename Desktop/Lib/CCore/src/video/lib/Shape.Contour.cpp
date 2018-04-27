/* Shape.Contour.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Desktop
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/video/lib/Shape.Contour.h>

#include <CCore/inc/video/FigureLib.h>

namespace CCore {
namespace Video {

/* class ContourShape */

Point ContourShape::getMinSize() const
 {
  Coord dxy=cfg.width.get().roundUp();

  return Point::Diag(2*dxy+10);
 }

Point ContourShape::getMinSize(Point inner_size) const
 {
  Coord dxy=cfg.width.get().roundUp();

  return inner_size.addXY(+(2*dxy));
 }

Pane ContourShape::getInner() const
 {
  Coord dxy=cfg.width.get().roundUp();

  return pane.shrink(dxy);
 }

Point ContourShape::getDelta() const
 {
  Coord dxy=cfg.width.get().roundUp();

  return 2*Point::Diag(dxy);
 }

void ContourShape::draw(const DrawBuf &buf) const
 {
  MPane p(pane);

  if( !p ) return;

  SmoothDrawArt art(buf.cut(pane));

  MCoord width=+cfg.width;

  FigureTopBorder fig_top(p,width);

  fig_top.solid(art,+cfg.gray);

  FigureBottomBorder fig_bottom(p,width);

  fig_bottom.solid(art,+cfg.snow);
 }

/* class TextContourShape */

Point TextContourShape::getMinSize() const
 {
  TextSize ts=cfg.font->text(title.str());

  Coord dxy=cfg.width.get().roundUp();

  return 2*Point(ts.dy,dxy)+Point(ts.full_dx,ts.dy);
 }

Point TextContourShape::getMinSize(Point inner_size) const
 {
  TextSize ts=cfg.font->text(title.str());

  Coord dxy=cfg.width.get().roundUp();

  return Sup( Point(dxy,dxy)+Point(dxy,ts.dy)+inner_size , 2*Point(ts.dy,dxy)+Point(ts.full_dx,ts.dy) );
 }

Pane TextContourShape::getInner() const
 {
  FontSize fs=cfg.font->getSize();

  Coord dxy=cfg.width.get().roundUp();

  if( dxy>=pane.dx-dxy || fs.dy>=pane.dy-dxy ) return Empty;

  return Pane(pane.x+dxy,pane.y+fs.dy,pane.dx-2*dxy,pane.dy-fs.dy-dxy);
 }

Point TextContourShape::getDelta() const
 {
  FontSize fs=cfg.font->getSize();

  Coord dxy=cfg.width.get().roundUp();

  return Point::Diag(dxy)+Point(dxy,fs.dy);
 }

void TextContourShape::draw(const DrawBuf &buf) const
 {
  MPane p(pane);

  if( !p ) return;

  SmoothDrawArt art(buf.cut(pane));

  const Font &font=cfg.font.get();

  TextSize ts=font->text(title.str());

  Coord ty=Min(ts.dy,pane.dy);
  Coord tx=Min_cast(ty,pane.dx/2);

  Coord len=pane.dx-2*tx;
  Coord free;

  if( len<=ts.full_dx )
    free=0;
  else
    free=len-ts.full_dx;

  MCoord width=+cfg.width;

  MCoord x0=p.x;
  MCoord x1=p.ex;

  MCoord y0=p.y+Fraction(ty)/2;
  MCoord y1=p.ey;

  MCoord t0;
  MCoord t1;

  switch( align_x )
    {
     case AlignX_Left :
      {
       MCoord d=Fraction(tx)/2;

       t0=d;
       t1=p.dx-d-Fraction(free);
      }
     break;

     case AlignX_Right :
      {
       MCoord d=Fraction(tx)/2;

       t0=d+Fraction(free);
       t1=p.dx-d;
      }
     break;

     default:
      {
       MCoord d=Fraction(tx+free)/2;

       t0=d;
       t1=p.dx-d;
      }
    }

  t0+=p.x;
  t1+=p.x;

  // border

  VColor gray=+cfg.gray;

  FigureTopBorder fig_top(x0,x1,y0,y1,width);

  fig_top.getLeftCut(t0).solid(art,gray);

  fig_top.getRightCut(t1).solid(art,gray);

  FigureBottomBorder fig_bottom(x0,x1,y0,y1,width);

  fig_bottom.solid(art,+cfg.snow);

  // title

  font->text(buf,Pane(pane.x+tx,pane.y,len,ty),TextPlace(align_x,AlignY_Center),title.str(),+cfg.text);
 }

/* class RefTextContourShape */

Point RefTextContourShape::getMinSize() const
 {
  TextContourShape temp(cfg,+title,align_x);

  temp.pane=pane;

  return temp.getMinSize();
 }

Point RefTextContourShape::getMinSize(Point inner_size) const
 {
  TextContourShape temp(cfg,+title,align_x);

  temp.pane=pane;

  return temp.getMinSize(inner_size);
 }

Pane RefTextContourShape::getInner() const
 {
  TextContourShape temp(cfg,+title,align_x);

  temp.pane=pane;

  return temp.getInner();
 }

Point RefTextContourShape::getDelta() const
 {
  TextContourShape temp(cfg,+title,align_x);

  temp.pane=pane;

  return temp.getDelta();
 }

void RefTextContourShape::draw(const DrawBuf &buf) const
 {
  TextContourShape temp(cfg,+title,align_x);

  temp.pane=pane;

  temp.draw(buf);
 }

} // namespace Video
} // namespace CCore

