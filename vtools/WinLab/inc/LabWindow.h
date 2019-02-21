/* LabWindow.h */
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

#ifndef LabWindow_h
#define LabWindow_h

#include <inc/App.h>

#include <inc/ColorListWindow.h>

namespace App {

/* classes */

class ColorSet;

class LabWindow;

/* class ColorSet */

class ColorSet : public ColorInfo
 {
   class Base;

  public:

   ColorSet();

   ~ColorSet();
 };

/* class LabWindow */

class LabWindow : public ColorListWindow
 {
  public:

   LabWindow(SubWindowHost &host,const Config &cfg);

   virtual ~LabWindow();
 };

} // namespace App

#endif
