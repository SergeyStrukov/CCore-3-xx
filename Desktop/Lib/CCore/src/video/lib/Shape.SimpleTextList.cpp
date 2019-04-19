/* Shape.SimpleTextList.cpp */
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
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/video/lib/Shape.SimpleTextList.h>

#include <CCore/inc/video/FigureLib.h>

#include <CCore/inc/video/InfoSize.h>

namespace CCore {
namespace Video {

/* class SimpleTextListShape */

void SimpleTextListShape::Cache::operator () (const Config &cfg,const Info &info)
 {
  if( !ok )
    {
     const Font &font=cfg.font.get();

     FontSize fs=font->getSize();

     line_dy=fs.dy;
     med_dx=fs.medDX();

     info_dx=InfoSize(font,info).x;

     ok=true;
    }
 }

Point SimpleTextListShape::getMinSize(Point cap) const
 {
  const Font &font=cfg.font.get();

  Point space=+cfg.space;

  return 2*space+Inf(InfoSize(font,info),cap-2*space);
 }

void SimpleTextListShape::layout()
 {
  cache(cfg,info);

  Pane inner=pane.shrink(+cfg.space);

  if( +inner )
    {
     dxoff=cache.med_dx;

     xoff_max=PlusSub(cache.info_dx,inner.dx);

     page=ulen( inner.dy/cache.line_dy );

     yoff_max=PlusSub(info->getLineCount(),page);
    }
  else
    {
     dxoff=0;
     xoff_max=0;
     page=0;
     yoff_max=0;
    }
 }

void SimpleTextListShape::showSelect()
 {
  if( select==MaxULen ) return;

  if( select<yoff )
    {
     yoff=select;
    }
  else
    {
     if( select-yoff>=page && page>0 )
       {
        yoff=Min<ulen>(select-page+1,yoff_max);
       }
    }
 }

ulen SimpleTextListShape::getPosition(Point point) const
 {
  Pane inner=pane.shrink(+cfg.space);

  if( !inner ) return 0;

  if( point.y<inner.y ) return yoff?yoff-1:0;

  if( point.y>=inner.y+inner.dy ) return yoff+page;

  FontSize fs=cfg.font->getSize();

  return yoff+ulen( (point.y-inner.y)/fs.dy );
 }

void SimpleTextListShape::draw(const DrawBuf &buf,DrawParam draw_param) const
 {
  if( !pane ) return;

  draw_param.erase(buf,pane,+cfg.back);

  SmoothDrawArt art(buf.cut(pane));

  VColor text = enable? +cfg.text : +cfg.inactive ;

  Point space=+cfg.space;

  // decor

  {
   MPane p(pane);

   MCoord width=+cfg.width;

   MPoint s(space);

   FigureTopBorder fig_top(p,width);

   fig_top.solid(art,+cfg.gray);

   FigureBottomBorder fig_bottom(p,width);

   fig_bottom.solid(art,+cfg.snow);

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

  // text

  {
   Pane inner=pane.shrink(space);

   if( !inner ) return;

   ulen count=info->getLineCount();
   ulen index=yoff;

   const Font &font=cfg.font.get();

   FontSize fs=font->getSize();

   DrawBuf tbuf=buf.cut(inner);

   if( fs.dy>inner.dy ) return;

   Pane row=inner;

   row.dy=fs.dy;

   Coord pos_x=fs.dx0-xoff;
   Coord lim=inner.y+(inner.dy-row.dy);

   for(; index<count && row.y<=lim ;index++,row.y+=row.dy)
     {
      if( enable && index==select ) tbuf.erase(row,+cfg.select);

      font->text(tbuf,row,TextPlace(pos_x,AlignY_Top),info->getLine(index),text);
     }
  }
 }

} // namespace Video
} // namespace CCore

