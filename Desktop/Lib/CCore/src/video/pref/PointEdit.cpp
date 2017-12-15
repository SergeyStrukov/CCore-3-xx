/* PointEdit.cpp */
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

#include <CCore/inc/video/pref/PointEdit.h>

#include <CCore/inc/video/FigureLib.h>

namespace CCore {
namespace Video {

/* class PointEditWindow */

void PointEditWindow::spin_changed(int)
 {
  redraw();

  changed.assert(getPoint());
 }

PointEditWindow::PointEditWindow(SubWindowHost &host,const ConfigType &cfg_)
 : ComboWindow(host),
   cfg(cfg_),

   spin_x(wlist,cfg.spin_cfg),
   spin_y(wlist,cfg.spin_cfg),

   connector_spin_x_changed(this,&PointEditWindow::spin_changed,spin_x.changed),
   connector_spin_y_changed(this,&PointEditWindow::spin_changed,spin_y.changed)
 {
  wlist.insTop(spin_x,spin_y);

  spin_x.setRange(MinCoord,MaxCoord);
  spin_y.setRange(MinCoord,MaxCoord);

  // bind hints

  spin_x.bindHint(cfg.hint_x);
  spin_y.bindHint(cfg.hint_y);
 }

PointEditWindow::~PointEditWindow()
 {
 }

 // methods

Point PointEditWindow::getMinSize() const
 {
  Point s=spin_x.getMinSize();

  Coord space_dxy=+cfg.space_dxy;

  Coordinate dx=2*Coordinate(s.x)+space_dxy;

  return Point(dx,s.y+dx);
 }

Point PointEditWindow::getPoint() const
 {
  return Point(Coord(spin_x.getValue()),Coord(spin_y.getValue()));
 }

void PointEditWindow::setPoint(Point value)
 {
  spin_x.setValue(value.x);
  spin_y.setValue(value.y);

  redraw();
 }

 // drawing

void PointEditWindow::layout(unsigned flags)
 {
  Point s=spin_x.getMinSize();

  Coord space_dxy=+cfg.space_dxy;

  spin_x.setPlace(Pane(Null,s),flags);

  spin_y.setPlace(Pane(Point(s.x+space_dxy,0),s),flags);

  Coord dx=s.x+space_dxy/2;

  pos=Point(dx,s.y+dx);
 }

void PointEditWindow::drawBack(DrawBuf buf,bool) const
 {
  SmoothDrawArt art(buf);

  Pane pane=Envelope(pos,pos+getPoint());

  MCoord width=+cfg.width;

  FigureBox fig(pane);

  fig.loop(art,HalfPos,width,+cfg.line);
 }

} // namespace Video
} // namespace CCore


