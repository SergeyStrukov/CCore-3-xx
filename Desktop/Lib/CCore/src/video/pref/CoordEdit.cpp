/* CoordEdit.cpp */
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
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/video/pref/CoordEdit.h>

#include <CCore/inc/video/SmoothDrawArt.h>

namespace CCore {
namespace Video {

/* class CoordEditWindow */

void CoordEditWindow::spin_changed(int value)
 {
  redraw();

  changed.assert(Coord(value));
 }

CoordEditWindow::CoordEditWindow(SubWindowHost &host,const ConfigType &cfg_)
 : ComboWindow(host),
   cfg(cfg_),

   spin(wlist,cfg.spin_cfg),

   connector_spin_changed(this,&CoordEditWindow::spin_changed,spin.changed)
 {
  wlist.insTop(spin);

  spin.setRange(MinCoord,MaxCoord);
 }

CoordEditWindow::~CoordEditWindow()
 {
 }

 // methods

Point CoordEditWindow::getMinSize() const
 {
  Point s=spin.getMinSize();

  return Point(s.x,2*Coordinate(s.y));
 }

 // drawing

void CoordEditWindow::layout(unsigned)
 {
  Point size=getSize();

  spin.setPlace(Pane(Null,size.x,size.y/2));

  pos.x=size.x/2;
  pos.y=Div(3,4)*size.y;
 }

void CoordEditWindow::drawBack(DrawBuf buf,bool) const
 {
  Coord mark_dy=+cfg.mark_dy;
  MCoord width=+cfg.width;
  VColor line=+cfg.line;

  SmoothDrawArt art(buf);

  Point end=pos.addX(getCoord());

  art.path(width,line,pos,end);

  art.path(width,line,pos.subY(mark_dy),pos.addY(mark_dy));

  art.path(width,line,end.subY(mark_dy),end.addY(mark_dy));
 }

} // namespace Video
} // namespace CCore


