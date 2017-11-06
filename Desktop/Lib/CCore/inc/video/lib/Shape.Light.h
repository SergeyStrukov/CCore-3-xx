/* Shape.Light.h */
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
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_video_lib_Shape_Light_h
#define CCore_inc_video_lib_Shape_Light_h

#include <CCore/inc/video/MinSizeType.h>
#include <CCore/inc/video/Color.h>
#include <CCore/inc/video/Font.h>
#include <CCore/inc/video/RefVal.h>

namespace CCore {
namespace Video {

/* classes */

class LightShape;

/* class LightShape */

class LightShape
 {
  public:

   struct Config
    {
     RefVal<VColor> gray     = Gray ;
     RefVal<VColor> snow     = Snow ;
     RefVal<VColor> inactive = Gray ;

     RefVal<Coord> dxy = 20 ;

     Config() noexcept {}

     template <class Bag>
     void bind(const Bag &bag)
      {
       gray.bind(bag.gray);
       snow.bind(bag.snow);
       inactive.bind(bag.inactive);

       dxy.bind(bag.light_dxy);
      }
    };

   const Config &cfg;
   VColor face = Green ;
   Pane pane;

   // state

   bool on;

   // methods

   LightShape(const Config &cfg_,VColor face_,bool on_=false) : cfg(cfg_),face(face_),on(on_) {}

   SizeBox getMinSize() const;

   bool isGoodSize(Point size) const { return size>=getMinSize(); }

   void draw(const DrawBuf &buf) const;
 };

} // namespace Video
} // namespace CCore

#endif

