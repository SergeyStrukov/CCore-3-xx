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

namespace App {

/* class ColorSet */

class ColorSet::Base : public ColorInfoBase
 {
   static NamedColor Table[10];

  public:

   Base() {}

   virtual ~Base() {}

   // AbstractColorInfo

   virtual ulen getLineCount() const
    {
     return DimOf(Table);
    }

   virtual NamedColor getLine(ulen index) const
    {
     GuardIndex(index,DimOf(Table));

     return Table[index];
    }
 };

NamedColor ColorSet::Base::Table[10]=
 {
  {"Black"_str,Black},
  {"Green"_str,Green},
  {"Red"_str,Red},
  {"Blue"_str,Blue},
  {"Maroon"_str,Maroon},

  {"Orange"_str,Orange},
  {"Crimson"_str,Crimson},
  {"Indigo"_str,Indigo},
  {"Ivory"_str,Ivory},
  {"Lavender"_str,Lavender}
 };

ColorSet::ColorSet()
 : ColorInfo(new Base())
 {
 }

ColorSet::~ColorSet()
 {
 }

/* class LabWindow */

LabWindow::LabWindow(SubWindowHost &host,const Config &cfg)
 : ColorListWindow(host,cfg,ColorSet())
 {
 }

LabWindow::~LabWindow()
 {
 }

} // namespace App

