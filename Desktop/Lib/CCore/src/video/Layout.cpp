/* Layout.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
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

#include <CCore/inc/video/Layout.h>

namespace CCore {
namespace Video {

/* FitToScreen() */

Pane FitToScreen(Point base,Point size,Point screen_size)
 {
  if( base.x<0 || size.x>screen_size.x )
    {
     base.x=0;
    }
  else
    {
     Replace_min(base.x,screen_size.x-size.x);
    }

  if( base.y<0 ) base.y=0;

  if( base.y>=screen_size.y )
    {
     if( screen_size.y>size.y )
       {
        base.y=screen_size.y-size.y;
       }
     else
       {
        base.y=0;
        size.y=screen_size.y;
       }
    }
  else
    {
     Replace_min(size.y,screen_size.y-base.y);
    }

  return Pane(base,size);
 }

/* GetWindowPlace() */

Pane GetWindowPlace(Pane outer,Ratio ry,Point size)
 {
  Point s=outer.getSize();

  size=Inf(size,Div(5,6)*s);

  Point p=s-size;

  Point pos(p.x/2,ry*p.y);

  return Pane(outer.getBase()+pos,size);
 }

Pane GetWindowPlace(Desktop *desktop,Ratio ry,Point size)
 {
  return GetWindowPlace(desktop->getMaxPane(),ry,size);
 }

/* FreeCenter...() */

Pane FreeCenter(Pane outer,Point size)
 {
  Point p=outer.getSize()-size;

  Point pos=p/2;

  return Pane(outer.getBase()+pos,size);
 }

Pane FreeCenterX(Pane outer,Coord dx)
 {
  auto x=outer.x+(outer.dx-dx)/2;

  return Pane(x,outer.y,dx,outer.dy);
 }

Pane FreeCenterY(Pane outer,Coord dy)
 {
  auto y=outer.y+(outer.dy-dy)/2;

  return Pane(outer.x,y,outer.dx,dy);
 }

//----------------------------------------------------------------------------------------

/* PosSubMul() */

Coord PosSubMul(Coord a,ulen count,Coord b)
 {
  if( a<=0 ) return 0;

  if( b<=0 ) return a;

  Coord m=a/b;

  if( count>ulen(m) ) return 0;

  return a-Coord(count)*b;
 }

/* class PlaceRow */

PlaceRow::PlaceRow(Pane outer,Point size_,Coord space,ulen count)
 {
  size=Inf(size_,outer.getSize());

  Coord ext=PosSubMul(outer.dx,count,size.x);

  if( count>1 ) ext=PosSubMul(ext,count-1,space);

  ext/=2;

  base.x=outer.x+ext;
  base.y=outer.y+(outer.dy-size.y)/2;

  cap=outer.dx-ext;

  if( space<cap-size.x )
    delta=size.x+space;
  else
    delta=cap;
 }

/* class PlaceColumn */

PlaceColumn::PlaceColumn(Pane outer,Point size_,Coord space,ulen count)
 {
  size=Inf(size_,outer.getSize());

  Coord ext=PosSubMul(outer.dy,count,size.y);

  if( count>1 ) ext=PosSubMul(ext,count-1,space);

  ext/=2;

  base.x=outer.x+(outer.dx-size.x)/2;
  base.y=outer.y+ext;

  cap=outer.dy-ext;

  if( space<cap-size.y )
    delta=size.y+space;
  else
    delta=cap;
 }

/* class PaneCut */

 // methods

void PaneCut::shrink()
 {
  pane=pane.shrink(space);
 }

 // cut

PaneCut PaneCut::cutLeft(Coord dx,Coord space)
 {
  if( dx<=pane.dx )
    {
     PaneCut ret(SplitX(dx,pane),this->space);

     SplitX(space,pane);

     return ret;
    }
  else
    {
     PaneCut ret(*this);

     pane=Empty;

     return ret;
    }
 }

PaneCut PaneCut::cutRight(Coord dx,Coord space)
 {
  if( dx<=pane.dx )
    {
     PaneCut ret(SplitX(pane,dx),this->space);

     SplitX(pane,space);

     return ret;
    }
  else
    {
     PaneCut ret(*this);

     pane=Empty;

     return ret;
    }
 }

PaneCut PaneCut::cutTop(Coord dy,Coord space)
 {
  if( dy<=pane.dy )
    {
     PaneCut ret(SplitY(dy,pane),this->space);

     SplitY(space,pane);

     return ret;
    }
  else
    {
     PaneCut ret(*this);

     pane=Empty;

     return ret;
    }
 }

PaneCut PaneCut::cutBottom(Coord dy,Coord space)
 {
  if( dy<=pane.dy )
    {
     PaneCut ret(SplitY(pane,dy),this->space);

     SplitY(pane,space);

     return ret;
    }
  else
    {
     PaneCut ret(*this);

     pane=Empty;

     return ret;
    }
 }

} // namespace Video
} // namespace CCore

