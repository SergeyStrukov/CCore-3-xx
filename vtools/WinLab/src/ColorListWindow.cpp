/* ColorListWindow.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.60
//
//  Tag: Desktop
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/ColorListWindow.h>

#include <CCore/inc/ForLoop.h>

#include <CCore/inc/video/FigureLib.h>

namespace CCore {
namespace Video {

namespace Private_ColorListWindow {

class DefList : public ColorInfoBase
 {
  public:

   DefList() {}

   virtual ~DefList() {}

   // AbstractColorInfo

   virtual ulen getLineCount() const { return 0; }

   virtual NamedColor getLine(ulen) const { return {}; }
 };

DefList Object CCORE_INITPRI_3 ;

} // namespace Private_ColorListWindow

using namespace Private_ColorListWindow;

/* GetNullColorInfoPtr() */

ColorInfoBase * GetNullColorInfoPtr() { return &Object; }

/* class ColorListShape */

StrLen ColorListShape::SampleLine()
 {
  return "Sample color"_c;
 }

Point ColorListShape::LineSize(Font font,Point space,const ColorInfo &info)
 {
  FontSize fs=font->getSize();

  Coord max_dx=0;

  for(ulen index : IndLim(info->getLineCount()) )
    {
     Coord dx=font->text(Range(info->getLine(index).name)).full_dx;

     Replace_max(max_dx,dx);
    }

  Coord dy=fs.dy+space.y;

  return Point(max_dx+space.x+2*dy,dy);
 }

Point ColorListShape::ExtSpace(const Config &cfg)
 {
  Point space=+cfg.space;
  MCoord width=+cfg.width;

  Coord ext=RoundUpLen(width);

  return space.addXY(2*ext);
 }

void ColorListShape::Cache::operator () (const Config &cfg,const ColorInfo &info)
 {
  if( !ok )
    {
     const Font &font=cfg.font.get();

     FontSize fs=font->getSize();

     Point space=+cfg.space;

     med_dx=fs.medDX();

     line=LineSize(font,space,info);

     ok=true;
    }
 }

Point ColorListShape::getMinSize(Point cap) const
 {
  const Font &font=cfg.font.get();

  Point space=ExtSpace(cfg);

  Point line=LineSize(font,+cfg.space,info);

  Coord dy=MulSize(info->getLineCount(),line.y);

  return 2*space+Inf(Point(line.x,dy),cap-2*space);
 }

Point ColorListShape::getMinSize(unsigned lines) const
 {
  const Font &font=cfg.font.get();

  Point space=+cfg.space;
  MCoord width=+cfg.width;

  Coord ext=RoundUpLen(width);

  Point ts=font->text(SampleLine()).getSize();

  Coord dy=ts.y+space.y;

  Point line(ts.x+space.x+2*dy,dy);

  return Point(line.x,MulSize(lines,line.y)).addXY(2*ext);
 }

void ColorListShape::layout()
 {
  cache(cfg,info);

  Pane inner=pane.shrink(ExtSpace(cfg));

  if( +inner )
    {
     xoff_max=PlusSub(cache.line.x,inner.dx);

     dxoff=cache.med_dx;

     page=ulen(inner.dy/cache.line.y);

     yoff_max=PlusSub(info->getLineCount(),page);
    }
  else
    {
     xoff_max=0;
     dxoff=0;
     page=0;
     yoff_max=0;
    }
 }

void ColorListShape::initSelect()
 {
  select=MaxULen;

  setSelectDown(0);
 }

bool ColorListShape::setSelectDown(ulen pos)
 {
  ulen count=info->getLineCount();

  if( !count ) return false;

  Replace_min(pos,count-1);

  return Change(select,pos);
 }

bool ColorListShape::setSelectUp(ulen pos)
 {
  ulen count=info->getLineCount();

  if( !count ) return false;

  Replace_min(pos,count-1);

  return Change(select,pos);
 }

bool ColorListShape::showSelect()
 {
  if( select==MaxULen ) return false;

  if( select<yoff )
    {
     yoff=select;

     return true;
    }
  else
    {
     ulen i=select-yoff;

     if( i>=page && page>0 )
       {
        yoff=Min_cast(yoff_max,select-page+1);

        return true;
       }
    }

  return false;
 }

ulen ColorListShape::getPosition(Point point) const
 {
  Pane inner=pane.shrink(ExtSpace(cfg));

  if( !inner ) return 0;

  if( point.y<inner.y ) return yoff?yoff-1:0;

  if( point.y>=inner.y+inner.dy ) return yoff+page;

  FontSize fs=cfg.font->getSize();

  Point space=+cfg.space;

  Coord dy=fs.dy+space.y;

  return yoff+ulen((point.y-inner.y)/dy);
 }

void ColorListShape::draw(const DrawBuf &buf) const
 {
  if( !pane ) return;

  cache(cfg,info);

  SmoothDrawArt art(buf.cut(pane));

  art.block(pane,+cfg.back);

  VColor text = enable? +cfg.text : +cfg.inactive ;
  VColor gray=+cfg.gray;
  VColor snow=+cfg.snow;

  Point space=+cfg.space;

  // decor

  {
   MPane p(pane);

   MCoord width=+cfg.width;

   MPoint s(space);

   FigureTopBorder fig_top(p,width);

   fig_top.solid(art,gray);

   FigureBottomBorder fig_bottom(p,width);

   fig_bottom.solid(art,snow);

   if( focus )
     {
      FigureBox fig(p.shrink(s/2));

      fig.loop(art,width,+cfg.focus);
     }

   MCoord dx=s.x-width;
   MCoord dy=s.y-width;

   if( xoff>0 )
     {
      FigureLeftMark fig(p,dx);

      fig.solid(art,text);
     }

   if( xoff<xoff_max )
     {
      FigureRightMark fig(p,dx);

      fig.solid(art,text);
     }

   if( yoff>0 )
     {
      FigureUpMark fig(p,dy);

      fig.solid(art,text);
     }

   if( yoff<yoff_max )
     {
      FigureDownMark fig(p,dy);

      fig.solid(art,text);
     }
  }

  // table

  {
   Pane inner=pane.shrink(space);

   if( !inner ) return;

   ulen count=info->getLineCount();
   ulen index=yoff;

   if( !count ) return;

   const Font &font=cfg.font.get();

   Point line=cache.line;

   if( line.y>inner.dy ) return;

   DrawBuf tbuf=buf.cut(inner);

   SmoothDrawArt tart(tbuf);

   MCoord width=+cfg.width;
   VColor net=+cfg.net;

   Coord ext=RoundUpLen(width);

   Pane cell(inner.x-xoff+ext,inner.y+ext,line.x,line.y);

   Coord lim=cell.y+(inner.dy-line.y);
   Coord tx=line.x-2*line.y;

   auto hline = [&] (Point p)
                    {
                     MPoint a=p;

                     a=a.subXY(MPoint::Half);

                     MPoint b=a.addX(Fraction(cell.dx));

                     tart.path(width,net,a,b);

                     return a;

                    } ;

   MPoint A=hline(cell.getBase());
   MPoint B=A;

   for(; index<count && cell.y<=lim ;index++,cell.y+=line.y)
     {
      if( enable && index==select )
        {
         Pane pane=cell;

         pane.dx=tx;

         tart.block(pane.shrink(ext),+cfg.select);
        }

      NamedColor item=info->getLine(index);

      font->text(tbuf,cell.pushLeft(space.x/2),TextPlace(AlignX_Left,AlignY_Center),Range(item.name),text);

      {
       Pane pane=cell.pushLeft(tx);

       tart.block(pane.shrink(ext),item.vc);
      }

      B=hline(cell.addDY());
     }

   tart.path(width,net,A,B);

   auto vline = [&] (Coord dx)
                    {
                     MCoord mx=Fraction(dx);

                     tart.path(width,net,A.addX(mx),B.addX(mx));

                    } ;

   vline(tx);

   vline(cell.dx);
  }
 }

} // namespace Video
} // namespace CCore

