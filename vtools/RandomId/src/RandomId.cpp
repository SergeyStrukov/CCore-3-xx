/* RandomId.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: RandomId 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/RandomId.h>

namespace App {

/* class RandomIdWindow */

RandomIdWindow::RandomIdWindow(SubWindowHost &host,const Config &cfg_)
 : SubWindow(host),
   cfg(cfg_)
 {
 }

RandomIdWindow::~RandomIdWindow()
 {
 }

 // methods

Point RandomIdWindow::getMinSize() const
 {
  return Point(100,100);
 }

} // namespace App

