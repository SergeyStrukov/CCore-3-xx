/* Picture.cpp */
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

#include <CCore/inc/video/Picture.h>

#include <CCore/inc/video/FigureLib.h>

namespace CCore {
namespace Video {

namespace Private_Picture {

class EmptyPicture : public PictureBase
 {
  public:

   EmptyPicture() {}

   virtual ~EmptyPicture() {}

   // AbstractPicture

   virtual ulen getCount() const { return 1; }

   virtual Point getSize() const { return {8,8}; }

   virtual VColor defaultGround() const { return Black; }

   virtual void draw(ulen,DrawBuf,Coord,Coord) const {}
 };

EmptyPicture Object CCORE_INITPRI_3 ;

} // namespace Private_Picture

using namespace Private_Picture;

/* class Picture */

Picture::Picture() noexcept
 : ptr(&Object)
 {
  ptr->incRef();
 }

/* class DefaultAppIcon */

class DefaultAppIcon::Base : public PictureBase
 {
  public:

   Base()
    {
    }

   virtual ~Base()
    {
    }

   // AbstractPicture

   virtual ulen getCount() const
    {
     return 1;
    }

   virtual Point getSize() const
    {
     return {256,256};
    }

   virtual VColor defaultGround() const
    {
     return White;
    }

   virtual void draw(ulen index,DrawBuf buf,Coord dx,Coord dy) const
    {
     if( index ) return;

     Pane pane(0,0,dx,dy);

     MPane p(pane);

     if( !p ) return;

     SmoothDrawArt art(buf.cut(pane));

     p=p.shrinkX(p.dx/10);
     p=p.shrinkY(p.dy/6);

     MCoord r=Min(p.dx,p.dy)/6;
     MCoord width=r/5;

     FigureRoundBox fig(p,r);

     fig.curveSolid(art,RoyalBlue);
     fig.curveLoop(art,width,Black);

     MPoint a=fig.getLeftTop();
     MPoint b=fig.getRightTop();
     MPoint c=fig.getLeftBottom();

     art.path(width,Black,a,b);

     MPane q(a.x+r,b.x-r,a.y+r,c.y);

     FigureBox box(q);

     box.solid(art,Silver);

     MCoord r1=r/3;

     MPoint d=b.subY(r/2).subX(r);

     art.ball(d,r1,Red);

     d=d.subX(r);

     art.ball(d,r1,Snow);

     d=d.subX(r);

     art.ball(d,r1,Snow);
    }
 };

DefaultAppIcon::DefaultAppIcon() : Picture(new Base()) {}

} // namespace Video
} // namespace CCore

