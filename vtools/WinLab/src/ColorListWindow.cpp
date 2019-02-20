/* ColorListWindow.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.60
//
//  Tag: Desktop
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/ColorListWindow.h>

namespace CCore {
namespace Video {

namespace Private_ColorListWindow {

class DefList : public ColorInfoBase
 {
  public:

   DefList() {}

   virtual ~DefList() {}

   // AbstractColorInfo

   virtual ulen getLineCount() const { return 0; }

   virtual NamedColor getLine(ulen) const { return {}; }
 };

DefList Object CCORE_INITPRI_3 ;

} // namespace Private_ColorListWindow

using namespace Private_ColorListWindow;

/* GetNullColorInfoPtr() */

ColorInfoBase * GetNullColorInfoPtr() { return &Object; }

/* class ColorListShape */



} // namespace Video
} // namespace CCore

