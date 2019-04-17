/* Shape.Switch.h */
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
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_video_lib_Shape_Switch_h
#define CCore_inc_video_lib_Shape_Switch_h

#include <CCore/inc/video/MinSizeType.h>
#include <CCore/inc/video/Color.h>
#include <CCore/inc/video/Font.h>
#include <CCore/inc/video/RefVal.h>

#include <CCore/inc/video/lib/Shape.CheckState.h>

namespace CCore {
namespace Video {

/* classes */

class SwitchShape;

/* class SwitchShape */

class SwitchShape : public CheckState
 {
   struct Face;

  public:

   struct Config
    {
     RefVal<VColor> border =      Blue ;
     RefVal<VColor> focus  = OrangeRed ;
     RefVal<VColor> gray   =      Gray ;
     RefVal<VColor> snow   =      Snow ;
     RefVal<VColor> face   =     Black ;
     RefVal<VColor> faceUp =      Blue ;

     RefVal<VColor> on     =     Green ;
     RefVal<VColor> off    =       Red ;

     RefVal<Coord> dxy = 30 ;

     Config() noexcept {}

     template <class Bag>
     void bind(const Bag &bag)
      {
       border.bind(bag.border);
       focus.bind(bag.focus);
       gray.bind(bag.gray);
       snow.bind(bag.snow);
       face.bind(bag.face);
       faceUp.bind(bag.faceUp);

       on.bind(bag.switch_on);
       off.bind(bag.switch_off);
       dxy.bind(bag.switch_dxy);
      }
    };

   const Config &cfg;
   Pane pane;

   // methods

   explicit SwitchShape(const Config &cfg_,bool check_=false) : cfg(cfg_) { check=check_; }

   SizeBox getMinSize() const;

   bool isGoodSize(Point size) const { return size>=getMinSize(); }

   void draw(const DrawBuf &buf,DrawParam draw_param) const;
 };

} // namespace Video
} // namespace CCore

#endif

