/* Shape.LineEdit.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
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

#include <CCore/inc/video/lib/Shape.LineEdit.h>

#include <CCore/inc/video/FigureLib.h>

namespace CCore {
namespace Video {

/* class LineEditShape */

MCoord LineEditShape::FigEX(Coord fdy,MCoord width,Coord ex)
 {
  return (Fraction(fdy)+2*width)/4+Fraction(ex);
 }

Point LineEditShape::getMinSize() const
 {
  return getMinSize("Sample 1234567890");
 }

Point LineEditShape::getMinSize(StrLen sample_text) const
 {
  Font font=cfg.font.get();

  MCoord width=+cfg.width;

  FontSize fs=font->getSize();

  MCoord ex=FigEX(fs.dy,width,+cfg.ex);

  Coordinate dx=RoundUpLen(ex+width);
  Coordinate dy=RoundUpLen(width);

  Coordinate cursor_dx=+cfg.cursor_dx;

  TextSize ts=font->text_guarded(sample_text);

  return Point(ts.full_dx,ts.dy)+Point(2*dx+2*cursor_dx+dy+IntAbs(fs.skew),2*dy+2*cursor_dx)+(+cfg.space);
 }

void LineEditShape::setMax()
 {
  Font font=cfg.font.get();

  MCoord width=+cfg.width;

  FontSize fs=font->getSize();

  MCoord ex=FigEX(fs.dy,width,+cfg.ex);

  Coord dx=RoundUpLen(ex+width);
  Coord dy=RoundUpLen(width);

  Pane inner=pane.shrink(dx,dy);

  if( +inner )
    {
     TextSize ts=font->text_guarded(text_buf.prefix(len));

     Coordinate cursor_dx=+cfg.cursor_dx;

     Coordinate extra=2*cursor_dx+dy+IntAbs(fs.skew);

     Coordinate tx=ts.full_dx+extra;

     if( tx>inner.dx )
       xoffMax=+tx-inner.dx;
     else
       xoffMax=0;

     dxoff=fs.medDX();
    }
  else
    {
     xoffMax=0;

     dxoff=fs.medDX();
    }
 }

void LineEditShape::showCursor()
 {
  Font font=cfg.font.get();

  MCoord width=+cfg.width;

  FontSize fs=font->getSize();

  MCoord ex=FigEX(fs.dy,width,+cfg.ex);

  Coord dx=RoundUpLen(ex+width);
  Coord dy=RoundUpLen(width);

  Pane inner=pane.shrink(dx,dy);

  if( +inner )
    {
     bool show_cursor = enable && ( !hide_cursor || focus ) ;

     ulen pos = show_cursor? this->pos : len ;

     TextSize ts=font->text_guarded(text_buf.prefix(pos));

     Coordinate cursor_dx=+cfg.cursor_dx;

     Coordinate x1=(fs.dx0+cursor_dx)-xoff;

     Coordinate x=x1+ts.dx;

     Coordinate a=cursor_dx;
     Coordinate b=inner.dx-2*cursor_dx;

     if( x<a )
       {
        xoff -= +Min_cast(a-x,xoff) ;
       }
     else if( x>b )
       {
        xoff += +Min_cast(x-b,xoffMax-xoff) ;
       }
    }
 }

ulen LineEditShape::getPosition(Point point) const
 {
  Font font=cfg.font.get();

  MCoord width=+cfg.width;

  FontSize fs=font->getSize();

  MCoord ex=FigEX(fs.dy,width,+cfg.ex);

  Coord dx=RoundUpLen(ex+width);
  Coord dy=RoundUpLen(width);

  Pane inner=pane.shrink(dx,dy);

  if( !inner ) return 0;

  bool show_cursor = enable && ( !hide_cursor || focus ) ;

  ulen pos = show_cursor? this->pos : len ;

  point-=inner.getBase();

  TextSize ts=font->text_guarded(text_buf.prefix(pos));

  Coordinate cursor_dx=+cfg.cursor_dx;

  Coordinate x1=(fs.dx0+cursor_dx)-xoff;
  Coordinate x2=x1+ts.dx;
  Coordinate x3=x2+cursor_dx;

  Coord ytop=(inner.dy-ts.dy)/2;
  Coord ybase=ytop+ts.by;

  ulen pos1=font->position(text_buf.prefix(pos),point-Point(x1,ybase));

  if( pos1==0 ) return 0;

  if( pos1<=pos ) return pos1-1;

  ulen pos2=font->position(text_buf.part(pos,len-pos),point-Point(x3,ybase));

  if( pos2==0 ) return pos;

  if( pos2<=len-pos ) return pos2-1+pos;

  return len;
 }

void LineEditShape::drawText(Font font,const DrawBuf &buf,Pane pane,TextPlace place,StrLen text,ulen,VColor vc) const
 {
  font->text(buf,pane,place,text,vc);
 }

void LineEditShape::draw(const DrawBuf &buf) const
 {
  MPane p(pane);

  if( !p ) return;

  SmoothDrawArt art(buf.cut(pane));

  Font font=cfg.font.get();

  // figure

  MCoord width=+cfg.width;

  FontSize fs=font->getSize();

  MCoord ex=FigEX(fs.dy,width,+cfg.ex);

  if( ex>p.dx/3 )
    {
     art.block(pane,+cfg.inactive);

     return;
    }

  VColor text = enable? +cfg.text : +cfg.inactive ;

  FigureButton fig(p,ex);

  // body

  fig.curveSolid(art,enable? ( alert? +cfg.alert : +cfg.back ) : ( len? +cfg.back : +cfg.inactive ) ) ;

  // border

  if( focus )
    {
     fig.curveLoop(art,HalfPos,width,+cfg.focus);
    }
  else
    {
     auto fig_top=fig.getTop();

     fig_top.curvePath(art,HalfPos,width,+cfg.gray);

     auto fig_bottom=fig.getBottom();

     fig_bottom.curvePath(art,HalfPos,width,+cfg.snow);
    }

  // arrows

  {
   MCoord len=ex-width;
   MCoord y=p.y+p.dy/2;

   if( xoff>0 ) // Left
     {
      MCoord x=p.x+width;

      FigureLeftMark fig(x,y,len);

      fig.solid(art,text);
     }

   if( xoff<xoffMax ) // Right
     {
      MCoord x=p.ex-width;

      FigureRightMark fig(x,y,len);

      fig.solid(art,text);
     }
  }

  // text

  {
   Coord dx=RoundUpLen(ex+width);
   Coord dy=RoundUpLen(width);

   Pane inner=pane.shrink(dx,dy);

   if( !inner ) return;

   bool show_cursor = enable && ( !hide_cursor || focus ) ;

   DrawBuf tbuf=buf.cut(inner);

   SmoothDrawArt tart(tbuf);

   ulen pos = show_cursor? this->pos : len ;

   TextSize ts=font->text_guarded(text_buf.prefix(pos));

   Coordinate cursor_dx=+cfg.cursor_dx;

   Coordinate x1=(fs.dx0+cursor_dx)-xoff;
   Coordinate x2=x1+ts.dx;
   Coordinate x3=x2+cursor_dx;

   MCoord DX=Fraction(dx);
   MCoord X1=Fraction(x1)+DX;
   MCoord X2=Fraction(x2)+DX;
   MCoord X3=Fraction(x3)+DX;

   Coord ytop=(inner.dy-ts.dy)/2;
   Coord ybase=ytop+ts.by;

   MCoord w=Fraction(cursor_dx);
   MCoord h=Fraction(ts.dy);
   MCoord skew=Fraction(ts.skew);

   MCoord Y0=Fraction(ytop)+Fraction(dy);
   MCoord Y1=Y0+h;

   MCoord skew1=Div(h-Fraction(ts.by),h)*skew;

   // selection

   if( enable && select_len )
     {
      MCoord xs0;

      if( select_off<pos )
        {
         xs0=X1+Fraction( font->text_guarded(text_buf.prefix(pos),select_off).dx );
        }
      else
        {
         xs0=X3+Fraction( font->text_guarded(text_buf.part(pos,len-pos),select_off-pos).dx );
        }

      ulen lim=select_off+select_len;

      MCoord xs1;

      if( lim<=pos )
        {
         xs1=X1+Fraction( font->text_guarded(text_buf.prefix(pos),lim).dx );
        }
      else
        {
         xs1=X3+Fraction( font->text_guarded(text_buf.part(pos,len-pos),lim-pos).dx );
        }

      FigureSkew fig(xs0-skew1,xs1-skew1,Y0,Y1,skew);

      fig.shift(pane.getBase());

      fig.solid(tart,+cfg.select);
     }

   drawText(font,tbuf,inner,TextPlace(x1,ybase),text_buf.prefix(pos),0,text);

   drawText(font,tbuf,inner,TextPlace(x3,ybase),text_buf.part(pos,len-pos),pos,text);

   // cursor

   if( show_cursor )
     {
      FigureCursor fig(X2-skew1,Y0,Y1,w,skew);

      fig.shift(pane.getBase());

      if( focus && cursor )
        {
         fig.solid(tart,+cfg.cursor);
        }
      else
        {
         fig.loop(tart,HalfPos,w/3,+cfg.cursor);
        }
     }
  }
 }

} // namespace Video
} // namespace CCore

