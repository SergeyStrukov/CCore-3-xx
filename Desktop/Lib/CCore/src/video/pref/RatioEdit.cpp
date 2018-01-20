/* RatioEdit.cpp */
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
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/video/pref/RatioEdit.h>

#include <CCore/inc/video/SmoothDrawArt.h>

#include <CCore/inc/Exception.h>

namespace CCore {
namespace Video {

/* class RatioEditWindow */

MCoord RatioEditWindow::Den(MCoord a,MCoord b,MCoord cap)
 {
  a%=b;

  if( a==0 ) return 1;

  MCoord A=1,B=0,C=0,D=1;

  while( a>0 && D<cap )
    {
     MCoord t=b/a;
     MCoord s=b%a;

     MCoord A1=B;
     MCoord B1=A+B*t;
     MCoord C1=D;
     MCoord D1=C+D*t;

     if( D1>cap ) break;

     A=A1;
     B=B1;
     C=C1;
     D=D1;

     b=a;
     a=s;
    }

  return D;
 }

void RatioEditWindow::spin_changed(int)
 {
  redraw();

  changed.assert(getRatio());
 }

RatioEditWindow::RatioEditWindow(SubWindowHost &host,const ConfigType &cfg_)
 : ComboWindow(host),
   cfg(cfg_),

   spin_a(wlist,cfg.spin_cfg),
   spin_b(wlist,cfg.spin_cfg),

   connector_spin_a_changed(this,&RatioEditWindow::spin_changed,spin_a.changed),
   connector_spin_b_changed(this,&RatioEditWindow::spin_changed,spin_b.changed)
 {
  wlist.insTop(spin_a,spin_b);

  spin_a.setRange(1,1000);
  spin_a.setValue(1);

  spin_b.setRange(1,1000);
  spin_b.setValue(1);

  // bind hints

  spin_a.bindHint(cfg.hint_a);
  spin_b.bindHint(cfg.hint_b);
 }

RatioEditWindow::~RatioEditWindow()
 {
 }

 // methods

Point RatioEditWindow::getMinSize(unsigned flags) const
 {
  Point s=spin_a.getMinSize(flags);

  Coord space_dxy=+cfg.space_dxy;

  Coordinate dx=2*Coordinate(s.x)+space_dxy;
  Coordinate dy=3*Coordinate(s.y);

  return Point(dx,dy);
 }

Ratio RatioEditWindow::getRatio() const
 {
  return Div((MCoord)spin_a.getValue(),(MCoord)spin_b.getValue());
 }

void RatioEditWindow::setRatio(Ratio value)
 {
  MCoord a=value.value;
  MCoord b=MCoord(1)<<Ratio::Precision;

  if( a<=0 )
    {
     Printf(Exception,"CCore::Video::RatioEditWindow::setRatio(...) : not a positive value");
    }

  MCoord d=Den(a,b,100);
  MCoord t=(d*a+b/2)/b;

  spin_a.setValue(t);
  spin_b.setValue(d);

  redraw();
 }

 // drawing

void RatioEditWindow::layout(unsigned flags)
 {
  Point s=spin_a.getMinSize(flags);

  Coord space_dxy=+cfg.space_dxy;

  spin_a.setPlace(Pane(Null,s),ClearUpdate(flags));

  spin_b.setPlace(Pane(Point(s.x+space_dxy,0),s),flags);

  Coord dx=s.x+space_dxy/2;

  pos=Point(dx,2*s.y);
 }

void RatioEditWindow::drawBack(DrawBuf buf,bool) const
 {
  Coord mark_dy=+cfg.mark_dy;
  MCoord width=+cfg.width;
  VColor line=+cfg.line;

  SmoothDrawArt art(buf);

  int scale=pos.x/20;

  {
   Point beg=pos;
   Point end=beg.addX(Coord(scale*spin_a.getValue()));

   art.path(width,line,beg,end);

   art.path(width,line,beg.subY(mark_dy),beg.addY(mark_dy));

   art.path(width,line,end.subY(mark_dy),end.addY(mark_dy));
  }

  {
   Point beg=pos.addY(5*mark_dy);
   Point end=beg.addX(Coord(scale*spin_b.getValue()));

   art.path(width,line,beg,end);

   art.path(width,line,beg.subY(mark_dy),beg.addY(mark_dy));

   art.path(width,line,end.subY(mark_dy),end.addY(mark_dy));
  }
 }

} // namespace Video
} // namespace CCore

