/* Shape.ScrollList.cpp */
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

#include <CCore/inc/video/lib/Shape.ScrollList.h>

#include <CCore/inc/video/FigureLib.h>

namespace CCore {
namespace Video {

/* class ScrollListShape */

void ScrollListShape::Cache::operator () (const Config &cfg,const ComboInfo &info)
 {
  if( !ok )
    {
     ulen count=info->getLineCount();

     const Font &font=cfg.font.get();

     FontSize fs=font->getSize();

     med_dx=fs.medDX();

     line_dy=fs.dy;

     Coord off=fs.dy;

     Coord dx=0;

     for(ulen index=0; index<count ;index++)
       {
        Replace_max(dx,GetLineDX(font,info->getLine(index),off));
       }

     info_dx=dx;

     ok=true;
    }
 }

StrLen ScrollListShape::SampleLine()
 {
  return "Sample line 12345"_c;
 }

Coord ScrollListShape::GetLineDX(const Font &font,ComboInfoItem item,Coord off)
 {
  switch( item.type )
    {
     case ComboInfoText :
      {
       TextSize ts=font->text(item.text);

       return ts.full_dx;
      }
     break;

     case ComboInfoTitle :
      {
       TextSize ts=font->text(item.text);

       return ts.full_dx+off;
      }
     break;

     default: // case ComboInfoSeparator :
      {
       return 0;
      }
    }
 }

Point ScrollListShape::getMinSize(Point cap) const
 {
  const Font &font=cfg.font.get();

  Point space=+cfg.space;

  FontSize fs=font->getSize();

  Coord off=fs.dy;

  Coord dx=0;
  Coord dy=0;

  for(ulen index=0,count=info->getLineCount(); index<count ;index++)
    {
     Replace_max(dx,GetLineDX(font,info->getLine(index),off));

     dy+=fs.dy;
    }

  return 2*space+Inf(Point(dx,dy),cap-2*space);
 }

Point ScrollListShape::getMinSize(unsigned lines) const
 {
  const Font &font=cfg.font.get();

  Point space=+cfg.space;

  FontSize fs=font->getSize();

  Coord dx=font->text(SampleLine()).full_dx;

  return 2*space+Point(dx,CountToCoord(lines)*fs.dy);
 }

void ScrollListShape::setMax()
 {
  cache(cfg,info);

  Pane inner=pane.shrink(+cfg.space);

  if( +inner )
    {
     xoffMax=PlusSub(cache.info_dx,inner.dx);

     dxoff=cache.med_dx;

     page=ulen(inner.dy/cache.line_dy);

     yoffMax=PlusSub(info->getLineCount(),page);
    }
  else
    {
     xoffMax=0;
     dxoff=0;
     page=0;
     yoffMax=0;
    }
 }

void ScrollListShape::initSelect() // 0 -> down , MaxULen
 {
  select=MaxULen;

  setSelectDown(0);
 }

bool ScrollListShape::setSelectDown(ulen pos) // pos -> down , -> up , unchanged
 {
  ulen count=info->getLineCount();

  Replace_min(pos,count);

  for(ulen i=pos; i<count ;i++)
    {
     if( info->getLine(i).type==ComboInfoText )
       {
        return Change(select,i);
       }
    }

  for(ulen i=pos; i-- ;)
    {
     if( info->getLine(i).type==ComboInfoText )
       {
        return Change(select,i);
       }
    }

  return false;
 }

bool ScrollListShape::setSelectUp(ulen pos) // pos -> up , -> down , unchanged
 {
  ulen count=info->getLineCount();

  if( !count ) return false;

  Replace_min(pos,count-1);

  pos++;

  for(ulen i=pos; i-- ;)
    {
     if( info->getLine(i).type==ComboInfoText )
       {
        return Change(select,i);
       }
    }

  for(ulen i=pos; i<count ;i++)
    {
     if( info->getLine(i).type==ComboInfoText )
       {
        return Change(select,i);
       }
    }

  return false;
 }

bool ScrollListShape::showSelect()
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
        yoff=Min_cast(yoffMax,select-page+1);

        return true;
       }
    }

  return false;
 }

ulen ScrollListShape::getPosition(Point point) const
 {
  Pane inner=pane.shrink(+cfg.space);

  if( !inner ) return 0;

  if( point.y<inner.y ) return yoff?yoff-1:0;

  if( point.y>=inner.y+inner.dy ) return yoff+page;

  FontSize fs=cfg.font->getSize();

  return yoff+ulen((point.y-inner.y)/fs.dy);
 }

void ScrollListShape::draw(const DrawBuf &buf) const
 {
  if( !pane ) return;

  SmoothDrawArt art(buf.cut(pane));

  art.block(pane,+cfg.back);

  VColor text = enable? +cfg.text : +cfg.inactive ;
  VColor title = enable? +cfg.title : +cfg.inactive ;
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

   SmoothDrawArt tart(tbuf);

   if( fs.dy>inner.dy ) return;

   Pane row=inner;

   row.dy=fs.dy;

   Coord pos_x=fs.dx0-xoff;
   Coord lim=inner.y+(inner.dy-row.dy);

   VColor titleTop=+cfg.titleTop;
   VColor titleBottom=+cfg.titleBottom;
   Coord off=fs.dy;

   for(; index<count && row.y<=lim ;index++,row.y+=row.dy)
     {
      if( enable && index==select ) tbuf.erase(row,+cfg.select);

      ComboInfoItem item=info->getLine(index);

      switch( item.type )
        {
         case ComboInfoText :
          {
           font->text(tbuf,row,TextPlace(pos_x,AlignY_Top),item.text,text);
          }
         break;

         case ComboInfoTitle :
          {
           MPane p(row);

           TwoField field(p.getTopLeft(),titleTop,p.getBottomLeft(),titleBottom);

           FigureBox(p).solid(tart,field);

           font->text(tbuf,row,TextPlace(pos_x+off,AlignY_Top),item.text,title);
          }
         break;

         default: // case ComboInfoSeparator :
          {
           MPane p(row);
           MCoord delta=2*(p.dy/5);

           p=p.shrinkY(delta);

           TwoField field(p.getTopLeft(),snow,p.getBottomLeft(),gray);

           FigureBox(p).solid(tart,field);
          }
        }
     }
  }
 }

} // namespace Video
} // namespace CCore

