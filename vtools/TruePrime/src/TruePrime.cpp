/* TruePrime.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: TruePrime 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/TruePrime.h>

#include <CCore/inc/video/LayoutCombo.h>

namespace App {

/* class TruePrimeWindow */

TruePrimeWindow::TruePrimeWindow(SubWindowHost &host,const Config &cfg_)
 : ComboWindow(host),
   cfg(cfg_)

 {
 }

TruePrimeWindow::~TruePrimeWindow()
 {
 }

 // methods

Point TruePrimeWindow::getMinSize() const
 {
  return {100,100};

#if 0

  Coord space=+cfg.space_dxy;


  return ExtLay(lay).getMinSize(space);

#endif
 }

 // drawing

void TruePrimeWindow::layout()
 {
#if 0

  Coord space=+cfg.space_dxy;


  ExtLay(lay).setPlace(getPane(),space);

#endif
 }

void TruePrimeWindow::drawBack(DrawBuf buf,DrawParam &draw_param) const
 {
  draw_param.erase(buf,+cfg.back);
 }

} // namespace App

