/* MCoordEdit.cpp */
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

#include <CCore/inc/video/pref/MCoordEdit.h>

namespace CCore {
namespace Video {

/* class MCoordEditWindow */

void MCoordEditWindow::spinor_changed(int)
 {
  changed.assert(getMCoord());
 }

MCoordEditWindow::MCoordEditWindow(SubWindowHost &host,const ConfigType &cfg_)
 : ComboWindow(host),
   cfg(cfg_),

   spinor(wlist,cfg.spinor_cfg),

   connector_spinor_changed(this,&MCoordEditWindow::spinor_changed,spinor.changed)
 {
  wlist.insTop(spinor);

  spinor.setRange(1,10'000);
  spinor.setOptions(".f2"_c);
 }

MCoordEditWindow::~MCoordEditWindow()
 {
 }

 // methods

Point MCoordEditWindow::getMinSize() const
 {
  return spinor.getMinSize();
 }

 // drawing

void MCoordEditWindow::layout(unsigned)
 {
  spinor.setPlace(Pane(Null,getSize()));
 }

} // namespace Video
} // namespace CCore

