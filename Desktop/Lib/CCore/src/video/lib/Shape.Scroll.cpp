/* Shape.Scroll.cpp */
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

#include <CCore/inc/video/lib/Shape.Scroll.h>

#include <CCore/inc/video/FigureLib.h>

namespace CCore {
namespace Video {

/* class ScrollShape */

unsigned ScrollShape::Accelerate(unsigned count,unsigned period)
 {
  if( count==0 ) return 1;

  if( count<period ) return 0;

  count-=period;

  count/=period;

  if( count<10 ) return count+1;

  return 10;
 }

ulen ScrollShape::Delta(ulen m,uCoord p,uCoord q)
 {
  if( p>=q ) return m;

  return UIntMulDiv<ulen>(m,p,q);
 }

ulen ScrollShape::delta(uCoord delta,uCoord len,uCoord dlen) const
 {
  if( page>=total ) return 0;

  if( dlen>len/5 ) dlen=len/5;

  uCoord ext=2*dlen;

  if( len<=ext ) return 0;

  len-=ext;

  if( len<=dlen ) return 0;

  if( Delta(total,dlen,len)<page ) return Delta(total,delta,len);

  return Delta(total-page,delta,len-dlen);
 }

void ScrollShape::dragPos(Coord from,Coord to,uCoord len,uCoord dlen)
 {
  if( from<to )
    {
     pos=AddToCap(drag_pos, delta(IntDist(from,to),len,dlen) ,getMaxPos());
    }
  else if( from>to )
    {
     pos=PosSub(drag_pos, delta(IntDist(to,from),len,dlen) );
    }
 }

/* class XScrollShape */

SizeY XScrollShape::getMinSize() const
 {
  return +cfg.dxy;
 }

ScrollType XScrollShape::getType(MPoint point) const
 {
  MPane p(pane);

  MCoord h=p.dy;

  if( !p || page>=total || !enable ) return ScrollType_None;

  if( p.dx/5 < h )
    {
     h=p.dx/5;
     p.ey=p.y+h;
    }

  MCoord y0=p.y;
  MCoord y1=p.ey;

  if( point.y<y0 || point.y>y1 ) return ScrollType_None;

  MCoord x0=p.x;
  MCoord x1=x0+h;
  MCoord x5=p.ex;
  MCoord x4=x5-h;

  if( point.x<x0 || point.x>x5 ) return ScrollType_None;

  if( point.x<x1 ) return ScrollType_Down;

  if( point.x>x4 ) return ScrollType_Up;

  MCoord len=Max(Position(page,total,0,x4-x1),h);

  ulen cap=total-page;

  MCoord x2=Position(pos,cap,x1,x4-len);
  MCoord x3=x2+len;

  if( point.x<x2 ) return ScrollType_DownPage;

  if( point.x>x3 ) return ScrollType_UpPage;

  return ScrollType_Drag;
 }

void XScrollShape::draw(const DrawBuf &buf,DrawParam draw_param) const
 {
  MPane p(pane);

  if( !p ) return;

  SmoothDrawArt art(buf.cut(pane));

  MCoord h=p.dy;

  if( p.dx/5 < h )
    {
     h=p.dx/5;
     p.ey=p.y+h;
    }

  draw_param.erase(buf,pane,+cfg.back);

  // layout

  MCoord y0=p.y;
  MCoord y1=p.ey;

  MCoord x0=p.x;
  MCoord x1=x0+h;
  MCoord x5=p.ex;
  MCoord x4=x5-h;

  bool enable_=enable;

  MCoord x2;
  MCoord x3;

  if( page>=total )
    {
     enable_=false;

     x2=x1;
     x3=x4;
    }
  else
    {
     MCoord len=Max(Position(page,total,0,x4-x1),h);

     ulen cap=total-page;

     x2=Position(pos,cap,x1,x4-len);
     x3=x2+len;
    }

  MCoord width=+cfg.width;
  MCoord d=Max_cast(width,h/6);

  VColor snow=+cfg.snow;
  VColor gray=+cfg.gray;
  VColor face=+cfg.face;
  VColor faceUp=+cfg.faceUp;

  VColor eface = enable_? face : gray ;

  // down

  if( down==ScrollType_Down )
    {
     FigureBox fig_box(x0,x1,y0,y1);

     fig_box.solid(art,gray);

     FigureLeftArrow fig(x0+d,x1-d,y0+d,y1-d);

     fig.shift(MPoint::Diag(width));

     fig.curveSolid(art,eface);
    }
  else
    {
     FigureTopBorder fig_top(x0,x1,y0,y1,width);

     fig_top.solid(art,snow);

     FigureBottomBorder fig_bottom(x0,x1,y0,y1,width);

     fig_bottom.solid(art,gray);

     FigureLeftArrow fig(x0+d,x1-d,y0+d,y1-d);

     VColor fc = enable_? ( (mover==ScrollType_Down)? faceUp : face ) : gray ;

     fig.curveSolid(art,fc);
    }

  // up

  if( down==ScrollType_Up )
    {
     FigureBox fig_box(x4,x5,y0,y1);

     fig_box.solid(art,gray);

     FigureRightArrow fig(x4+d,x5-d,y0+d,y1-d);

     fig.shift(MPoint::Diag(width));

     fig.curveSolid(art,eface);
    }
  else
    {
     FigureTopBorder fig_top(x4,x5,y0,y1,width);

     fig_top.solid(art,snow);

     FigureBottomBorder fig_bottom(x4,x5,y0,y1,width);

     fig_bottom.solid(art,gray);

     FigureRightArrow fig(x4+d,x5-d,y0+d,y1-d);

     VColor fc = enable_? ( (mover==ScrollType_Up)? faceUp : face ) : gray ;

     fig.curveSolid(art,fc);
    }

  // down page

  {
   FigureBox fig_top(x1,x2,y0,y0+width);

   fig_top.solid(art,snow);

   FigureBox fig_bottom(x1,x2,y1-width,y1);

   fig_bottom.solid(art,gray);
  }

  if( down==ScrollType_DownPage )
    {
     MCoord e=Ratio(427,10)*h;

     FigureBox fig(x1,x2,y0+e,y1-e);

     fig.solid(art,face);
    }
  else
    {
     MCoord e=Ratio(3,3)*h;

     FigureBox fig(x1,x2,y0+e,y1-e);

     VColor fc = enable_? ( (mover==ScrollType_DownPage)? faceUp : face ) : gray ;

     fig.solid(art,fc);
    }

  // up page

  {
   FigureBox fig_top(x3,x4,y0,y0+width);

   fig_top.solid(art,snow);

   FigureBox fig_bottom(x3,x4,y1-width,y1);

   fig_bottom.solid(art,gray);
  }

  if( down==ScrollType_UpPage )
    {
     MCoord e=Ratio(427,10)*h;

     FigureBox fig(x3,x4,y0+e,y1-e);

     fig.solid(art,face);
    }
  else
    {
     MCoord e=Ratio(3,3)*h;

     FigureBox fig(x3,x4,y0+e,y1-e);

     VColor fc = enable_? ( (mover==ScrollType_UpPage)? faceUp : face ) : gray ;

     fig.solid(art,fc);
    }

  // drag

  {
   FigureBox fig(x2,x3,y0,y1);

   VColor top = focus? +cfg.focus : snow ;

   fig.solid(art,YField(y0,top,y1,gray));
  }

  {
   MCoord f=(x3-x2)/4;

   MCoord a0=x2+f;
   MCoord a1=x2+(x3-x2)/2;
   MCoord a2=x3-f;

   MCoord e=h/3;

   MCoord b0=y0+e;
   MCoord b1=y0+h/2;
   MCoord b2=y1-e;

   VColor fc = enable_? ( (mover==ScrollType_Drag)? faceUp : face ) : gray ;

   if( a2-a0>2*(b2-b0) )
     {
      MCoord c=(a2-a0)/2-(b2-b0);

      FigurePoints<6> fig;

      fig[0]={a0,b1};
      fig[1]={a1-c,b0};
      fig[2]={a1+c,b0};
      fig[3]={a2,b1};
      fig[4]={a1+c,b2};
      fig[5]={a1-c,b2};

      fig.solid(art,fc);
     }
   else
     {
      FigurePoints<4> fig;

      fig[0]={a0,b1};
      fig[1]={a1,b0};
      fig[2]={a2,b1};
      fig[3]={a1,b2};

      fig.solid(art,fc);
     }
  }
 }

/* class YScrollShape */

SizeX YScrollShape::getMinSize() const
 {
  return +cfg.dxy;
 }

ScrollType YScrollShape::getType(MPoint point) const
 {
  MPane p(pane);

  MCoord h=p.dx;

  if( !p || page>=total || !enable ) return ScrollType_None;

  if( p.dy/5 < h )
    {
     h=p.dy/5;
     p.ex=p.x+h;
    }

  MCoord x0=p.x;
  MCoord x1=p.ex;

  if( point.x<x0 || point.x>x1 ) return ScrollType_None;

  MCoord y0=p.y;
  MCoord y1=y0+h;
  MCoord y5=p.ey;
  MCoord y4=y5-h;

  if( point.y<y0 || point.y>y5 ) return ScrollType_None;

  if( point.y<y1 ) return ScrollType_Down;

  if( point.y>y4 ) return ScrollType_Up;

  MCoord len=Max(Position(page,total,0,y4-y1),h);

  ulen cap=total-page;

  MCoord y2=Position(pos,cap,y1,y4-len);
  MCoord y3=y2+len;

  if( point.y<y2 ) return ScrollType_DownPage;

  if( point.y>y3 ) return ScrollType_UpPage;

  return ScrollType_Drag;
 }

void YScrollShape::draw(const DrawBuf &buf,DrawParam draw_param) const
 {
  MPane p(pane);

  if( !p ) return;

  SmoothDrawArt art(buf.cut(pane));

  MCoord h=p.dx;

  if( p.dy/5 < h )
    {
     h=p.dy/5;
     p.ex=p.x+h;
    }

  draw_param.erase(buf,pane,+cfg.back);

  MCoord x0=p.x;
  MCoord x1=p.ex;

  MCoord y0=p.y;
  MCoord y1=y0+h;
  MCoord y5=p.ey;
  MCoord y4=y5-h;

  bool enable_=enable;

  MCoord y2;
  MCoord y3;

  if( page>=total )
    {
     enable_=false;

     y2=y1;
     y3=y4;
    }
  else
    {
     MCoord len=Max(Position(page,total,0,y4-y1),h);

     ulen cap=total-page;

     y2=Position(pos,cap,y1,y4-len);
     y3=y2+len;
    }

  MCoord width=+cfg.width;
  MCoord d=Max_cast(width,h/6);

  VColor snow=+cfg.snow;
  VColor gray=+cfg.gray;
  VColor face=+cfg.face;
  VColor faceUp=+cfg.faceUp;

  VColor eface = enable_? face : gray ;

  // down

  if( down==ScrollType_Down )
    {
     FigureBox fig_box(x0,x1,y0,y1);

     fig_box.solid(art,gray);

     FigureUpArrow fig(x0+d,x1-d,y0+d,y1-d);

     fig.shift(MPoint::Diag(width));

     fig.curveSolid(art,eface);
    }
  else
    {
     FigureTopBorder fig_top(x0,x1,y0,y1,width);

     fig_top.solid(art,snow);

     FigureBottomBorder fig_bottom(x0,x1,y0,y1,width);

     fig_bottom.solid(art,gray);

     FigureUpArrow fig(x0+d,x1-d,y0+d,y1-d);

     VColor fc = enable_? ( (mover==ScrollType_Down)? faceUp : face ) : gray ;

     fig.curveSolid(art,fc);
    }

  // up

  if( down==ScrollType_Up )
    {
     FigureBox fig_box(x0,x1,y4,y5);

     fig_box.solid(art,gray);

     FigureDownArrow fig(x0+d,x1-d,y4+d,y5-d);

     fig.shift(MPoint::Diag(width));

     fig.curveSolid(art,eface);
    }
  else
    {
     FigureTopBorder fig_top(x0,x1,y4,y5,width);

     fig_top.solid(art,snow);

     FigureBottomBorder fig_bottom(x0,x1,y4,y5,width);

     fig_bottom.solid(art,gray);

     FigureDownArrow fig(x0+d,x1-d,y4+d,y5-d);

     VColor fc = enable_? ( (mover==ScrollType_Up)? faceUp : face ) : gray ;

     fig.curveSolid(art,fc);
    }

  // down page

  {
   FigureBox fig_top(x0,x0+width,y1,y2);

   fig_top.solid(art,snow);

   FigureBox fig_bottom(x1-width,x1,y1,y2);

   fig_bottom.solid(art,gray);
  }

  if( down==ScrollType_DownPage )
    {
     MCoord e=Ratio(427,10)*h;

     FigureBox fig(x0+e,x1-e,y1,y2);

     fig.solid(art,face);
    }
  else
    {
     MCoord e=Ratio(3,3)*h;

     FigureBox fig(x0+e,x1-e,y1,y2);

     VColor fc = enable_? ( (mover==ScrollType_DownPage)? faceUp : face ) : gray ;

     fig.solid(art,fc);
    }

  // up page

  {
   FigureBox fig_top(x0,x0+width,y3,y4);

   fig_top.solid(art,snow);

   FigureBox fig_bottom(x1-width,x1,y3,y4);

   fig_bottom.solid(art,gray);
  }

  if( down==ScrollType_UpPage )
    {
     MCoord e=Ratio(427,10)*h;

     FigureBox fig(x0+e,x1-e,y3,y4);

     fig.solid(art,face);
    }
  else
    {
     MCoord e=Ratio(3,3)*h;

     FigureBox fig(x0+e,x1-e,y3,y4);

     VColor fc = enable_? ( (mover==ScrollType_UpPage)? faceUp : face ) : gray ;

     fig.solid(art,fc);
    }

  // drag

  {
   FigureBox fig(x0,x1,y2,y3);

   VColor top = focus? +cfg.focus : snow ;

   fig.solid(art,XField(x0,top,x1,gray));
  }

  {
   MCoord e=h/3;

   MCoord a0=x0+e;
   MCoord a1=x0+h/2;
   MCoord a2=x1-e;

   MCoord f=(y3-y2)/4;

   MCoord b0=y2+f;
   MCoord b1=y2+(y3-y2)/2;
   MCoord b2=y3-f;

   VColor fc = enable_? ( (mover==ScrollType_Drag)? faceUp : face ) : gray ;

   if( b2-b0>2*(a2-a0) )
     {
      MCoord c=(b2-b0)/2-(a2-a0);

      FigurePoints<6> fig;

      fig[0]={a0,b1-c};
      fig[1]={a1,b0};
      fig[2]={a2,b1-c};
      fig[3]={a2,b1+c};
      fig[4]={a1,b2};
      fig[5]={a0,b1+c};

      fig.solid(art,fc);
     }
   else
     {
      FigurePoints<4> fig;

      fig[0]={a0,b1};
      fig[1]={a1,b0};
      fig[2]={a2,b1};
      fig[3]={a1,b2};

      fig.solid(art,fc);
     }
  }
 }

} // namespace Video
} // namespace CCore

