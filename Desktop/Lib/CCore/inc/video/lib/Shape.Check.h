/* Shape.Check.h */
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

#ifndef CCore_inc_video_lib_Shape_Check_h
#define CCore_inc_video_lib_Shape_Check_h

#include <CCore/inc/video/MinSizeType.h>
#include <CCore/inc/video/Color.h>
#include <CCore/inc/video/Font.h>
#include <CCore/inc/video/RefVal.h>

#include <CCore/inc/video/lib/Shape.CheckState.h>

namespace CCore {
namespace Video {

/* classes */

class CheckShape;

/* class CheckShape */

class CheckShape : public CheckState
 {
  public:

   struct Config
    {
     RefVal<VColor> border =      Blue ;
     RefVal<VColor> focus  = OrangeRed ;
     RefVal<VColor> gray   =      Gray ;
     RefVal<VColor> grayUp =     Green ;
     RefVal<VColor> snow   =      Snow ;
     RefVal<VColor> mark   =     Black ;

     RefVal<Coord> dxy = 20 ;

     Config() noexcept {}

     template <class Bag>
     void bind(const Bag &bag)
      {
       border.bind(bag.border);
       focus.bind(bag.focus);
       gray.bind(bag.gray);
       grayUp.bind(bag.grayUp);
       snow.bind(bag.snow);
       mark.bind(bag.mark);

       dxy.bind(bag.check_dxy);
      }
    };

   const Config &cfg;
   Pane pane;

   // methods

   explicit CheckShape(const Config &cfg_,bool check_=false) : cfg(cfg_) { check=check_; }

   SizeBox getMinSize() const;

   bool isGoodSize(Point size) const { return size>=getMinSize(); }

   void draw(const DrawBuf &buf,DrawParam draw_param) const;
 };

} // namespace Video
} // namespace CCore

#endif

