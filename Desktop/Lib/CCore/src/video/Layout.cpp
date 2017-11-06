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

  size=Inf(size,s-s/4);

  Point p=s-size;

  Point pos( p.x/2 , ry*p.y );

  return Pane(outer.getBase()+pos,size);
 }

Pane GetWindowPlace(Desktop *desktop,Ratio ry,Point size)
 {
  return GetWindowPlace(desktop->getMaxPane(),ry,size);
 }

/* FreeCenter() */

Pane FreeCenter(Pane outer,Point size)
 {
  Point p=outer.getSize()-size;

  Point pos=p/2;

  return Pane(outer.getBase()+pos,size);
 }

Pane FreeCenterX(Pane outer,Coordinate dx)
 {
  auto x=outer.x+(outer.dx-dx)/2;

  return Pane(x,outer.y,dx,outer.dy);
 }

Pane FreeCenterY(Pane outer,Coordinate dy)
 {
  auto y=outer.y+(outer.dy-dy)/2;

  return Pane(outer.x,y,outer.dx,dy);
 }

//----------------------------------------------------------------------------------------

/* functions */

Pane AlignLeft(Pane pane,Coord dx)
 {
  if( dx<=pane.dx )
    {
     return Pane(pane.x,pane.y,dx,pane.dy);
    }
  else
    {
     return pane;
    }
 }

Pane AlignCenterX(Pane pane,Coord dx)
 {
  if( dx<=pane.dx )
    {
     Coord off=(pane.dx-dx)/2;

     return Pane(pane.x+off,pane.y,dx,pane.dy);
    }
  else
    {
     return pane;
    }
 }

Pane AlignRight(Pane pane,Coord dx)
 {
  if( dx<=pane.dx )
    {
     Coord off=pane.dx-dx;

     return Pane(pane.x+off,pane.y,dx,pane.dy);
    }
  else
    {
     return pane;
    }
 }

Pane AlignTop(Pane pane,Coord dy)
 {
  if( dy<=pane.dy )
    {
     return Pane(pane.x,pane.y,pane.dx,dy);
    }
  else
    {
     return pane;
    }
 }

Pane AlignCenterY(Pane pane,Coord dy)
 {
  if( dy<=pane.dy )
    {
     Coord off=(pane.dy-dy)/2;

     return Pane(pane.x,pane.y+off,pane.dx,dy);
    }
  else
    {
     return pane;
    }
 }

Pane AlignBottom(Pane pane,Coord dy)
 {
  if( dy<=pane.dy )
    {
     Coord off=pane.dy-dy;

     return Pane(pane.x,pane.y+off,pane.dx,dy);
    }
  else
    {
     return pane;
    }
 }

Pane AlignCenter(Pane pane,Coord dx,Coord dy)
 {
  if( dx<=pane.dx )
    {
     if( dy<=pane.dy )
       {
        Coord off_x=(pane.dx-dx)/2;
        Coord off_y=(pane.dy-dy)/2;

        return Pane(pane.x+off_x,pane.y+off_y,dx,dy);
       }
     else
       {
        Coord off_x=(pane.dx-dx)/2;

        return Pane(pane.x+off_x,pane.y,dx,pane.dy);
       }
    }
  else
    {
     if( dy<=pane.dy )
       {
        Coord off_y=(pane.dy-dy)/2;

        return Pane(pane.x,pane.y+off_y,pane.dx,dy);
       }
     else
       {
        return pane;
       }
    }
 }

/* class PlaceRow */

PlaceRow::PlaceRow(Pane outer,Point size_,Coord space,ulen count_)
 : size(size_),
   delta_x(IntAdd(size_.x,space))
 {
  auto count=CountToCoordinate(count_);

  auto total=count*size_.x+(count-1)*space;

  Point total_size(total,size_.y);

  Pane pane=AlignCenter(outer,total_size);

  if( pane.dx==total )
    base=pane.getBase();
  else
    size=Null;
 }

/* class PlaceColumn */

PlaceColumn::PlaceColumn(Pane outer,Point size_,Coord space,ulen count_)
 : size(size_),
   delta_y(IntAdd(size_.y,space))
 {
  auto count=CountToCoordinate(count_);

  auto total=count*size_.y+(count-1)*space;

  Point total_size(size_.x,total);

  Pane pane=AlignCenter(outer,total_size);

  if( pane.dy==total )
    base=pane.getBase();
  else
    size=Null;
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

