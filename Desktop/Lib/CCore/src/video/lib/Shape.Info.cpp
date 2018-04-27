/* Shape.Info.cpp */
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

#include <CCore/inc/video/lib/Shape.Info.h>

#include <CCore/inc/video/FigureLib.h>

#include <CCore/inc/video/InfoSize.h>

namespace CCore {
namespace Video {

/* class InfoShape */

void InfoShape::Cache::operator () (const Config &cfg,const Info &info)
 {
  if( !ok )
    {
     ulen count=info->getLineCount();

     const Font &font=cfg.font.get();

     FontSize fs=font->getSize();

     line_dy=fs.dy;
     med_dx=fs.medDX();

     Coord dx=0;

     for(ulen index=0; index<count ;index++)
       {
        TextSize ts=font->text(info->getLine(index));

        Replace_max(dx,ts.full_dx);
       }

     info_dx=dx;

     ok=true;
    }
 }

Point InfoShape::getMinSize(Point cap) const
 {
  const Font &font=cfg.font.get();

  Point space=+cfg.space;

  return 3*space+Inf(InfoSize(font,info),cap-2*space);
 }

void InfoShape::setMax()
 {
  cache(cfg,info);

  Pane inner=pane.shrink(+cfg.space);

  if( +inner )
    {
     xoffMax=PlusSub(cache.info_dx,inner.dx);

     ulen h=ulen(inner.dy/cache.line_dy);

     yoffMax=PlusSub(info->getLineCount(),h);

     dxoff=cache.med_dx;
    }
  else
    {
     xoffMax=0;
     yoffMax=0;
     dxoff=0;
    }
 }

void InfoShape::draw(const DrawBuf &buf) const
 {
  if( !pane ) return;

  SmoothDrawArt art(buf.cut(pane));

  VColor text = enable? +cfg.text : +cfg.inactive ;

  Point space=+cfg.space;

  // decor

  {
   MPane p(pane);

   MCoord width=+cfg.width;

   MPoint delta(space);

   if( focus )
     {
      FigureBox fig(p.shrink(delta/2));

      fig.loop(art,width,+cfg.focus);
     }

   MCoord dx=delta.x-width;
   MCoord dy=delta.y-width;

   if( xoff>0 )
     {
      FigureLeftMark fig(p,dx);

      fig.solid(art,text);
     }

   if( xoff<xoffMax )
     {
      FigureRightMark fig(p,dx);

      fig.solid(art,text);
     }

   if( yoff>0 )
     {
      FigureUpMark fig(p,dy);

      fig.solid(art,text);
     }

   if( yoff<yoffMax )
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
      font->text(tbuf,row,TextPlace(pos_x,AlignY_Top),info->getLine(index),text);
     }
  }
 }

} // namespace Video
} // namespace CCore

