/* Sample.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: Sample 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/Sample.h>

namespace App {

/* class SampleWindow */

SampleWindow::SampleWindow(SubWindowHost &host,const Config &cfg_)
 : SubWindow(host),
   cfg(cfg_)
 {
 }

SampleWindow::~SampleWindow()
 {
 }

 // methods

Point SampleWindow::getMinSize(unsigned) const
 {
  return Point(100,100);
 }

 // drawing

void SampleWindow::layout(unsigned)
 {
 }

} // namespace App

