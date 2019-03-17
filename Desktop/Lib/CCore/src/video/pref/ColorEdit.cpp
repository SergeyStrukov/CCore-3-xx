/* ColorEdit.cpp */
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

#include <CCore/inc/video/pref/ColorEdit.h>

#include <CCore/inc/video/LayoutCombo.h>

namespace CCore {
namespace Video {

/* class ColorEditWindow */

void ColorEditWindow::mix_changed(VColor vc)
 {
  named_color={Empty,vc};

  changed.assert(named_color);
 }

void ColorEditWindow::list_selected(ulen index)
 {
  NamedColor item=list_win.getInfo()->getLine(index);

  named_color=item;

  changed.assert(item);

  mix_win.setColor(item.vc);
 }

void ColorEditWindow::list_dclicked()
 {
  list_win.ping();
 }

ColorEditWindow::ColorEditWindow(SubWindowHost &host,const Config &cfg_)
 : ComboWindow(host),

   cfg(cfg_),

   mix_win(wlist,cfg.mix_cfg),
   list_win(wlist,cfg.list_cfg,ColorSet()),

   connector_mix_changed(this,&ColorEditWindow::mix_changed,mix_win.changed),
   connector_selected(this,&ColorEditWindow::list_selected,list_win.selected),
   connector_list_dclicked(this,&ColorEditWindow::list_dclicked,list_win.dclicked)
 {
  wlist.insTop(mix_win,list_win);
 }

ColorEditWindow::~ColorEditWindow()
 {
 }

 // methods

Point ColorEditWindow::getMinSize(Point cap) const
 {
  Coord space=+cfg.space_dxy;

  LayToRight lay{Lay(mix_win),LayCap(list_win)};

  return lay.getMinSize(space,cap);
 }

 // drawing

void ColorEditWindow::layout()
 {
  Coord space=+cfg.space_dxy;

  LayToRight lay{Lay(mix_win),LayCap(list_win)};

  lay.setPlace(getPane(),space);
 }

} // namespace Video
} // namespace CCore

