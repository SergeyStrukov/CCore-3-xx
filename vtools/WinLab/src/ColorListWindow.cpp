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

  Point space=+cfg.space;

  Point line=LineSize(font,space,info);

  Coord dy=MulSize(info->getLineCount(),line.y);

  return 2*space+Inf(Point(line.x,dy),cap-2*space);
 }

Point ColorListShape::getMinSize(unsigned lines) const
 {
  const Font &font=cfg.font.get();

  Point space=+cfg.space;

  Point ts=font->text(SampleLine()).getSize();

  Coord dy=ts.y+space.y;

  Point line(ts.x+space.x+2*dy,dy);

  return Point(line.x,MulSize(lines,line.y));
 }

void ColorListShape::layout()
 {
  cache(cfg,info);

  Pane inner=pane.shrink(+cfg.space);

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
  Point space=+cfg.space;
  Pane inner=pane.shrink(space);

  if( !inner ) return 0;

  if( point.y<inner.y ) return yoff?yoff-1:0;

  if( point.y>=inner.y+inner.dy ) return yoff+page;

  FontSize fs=cfg.font->getSize();

  Coord dy=fs.dy+space.y;

  return yoff+ulen((point.y-inner.y)/dy);
 }

void ColorListShape::draw(const DrawBuf &buf) const // TODO
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

   FontSize fs=font->getSize();

   DrawBuf tbuf=buf.cut(inner);

   SmoothDrawArt tart(tbuf);

   if( fs.dy>inner.dy ) return;

   Point line=cache.line;


  }
 }

} // namespace Video
} // namespace CCore

