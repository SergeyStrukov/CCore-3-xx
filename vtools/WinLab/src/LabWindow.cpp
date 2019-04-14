/* LabWindow.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: WinLab 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/LabWindow.h>

#include <CCore/inc/video/DesktopKey.h>

namespace App {

/* class LabWindow */

LabWindow::LabWindow(SubWindowHost &host,const Config &cfg)
 : FavWindow(host,cfg,HomeKey(),"/test.ddl"_c)
 {
  setInsData("new title"_str,"new path"_str);
 }

LabWindow::~LabWindow()
 {
 }

} // namespace App

