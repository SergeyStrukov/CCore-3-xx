/* Shape.Radio.h */
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

#ifndef CCore_inc_video_lib_Shape_Radio_h
#define CCore_inc_video_lib_Shape_Radio_h

#include <CCore/inc/video/MinSizeType.h>
#include <CCore/inc/video/Color.h>
#include <CCore/inc/video/Font.h>
#include <CCore/inc/video/RefVal.h>

namespace CCore {
namespace Video {

/* classes */

struct RadioState;

class RadioShape;

/* struct RadioState */

struct RadioState
 {
  bool enable =  true ;
  bool focus  = false ;
  bool mover  = false ;
  bool check  = false ;

  RadioState() {}
 };

/* class RadioShape */

class RadioShape : public RadioState
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

       dxy.bind(bag.radio_dxy);
      }
    };

   const Config &cfg;
   Pane pane;

   // methods

   explicit RadioShape(const Config &cfg_,bool check_=false) : cfg(cfg_) { check=check_; }

   SizeBox getMinSize() const;

   bool isGoodSize(Point size) const { return size>=getMinSize(); }

   void draw(const DrawBuf &buf,DrawParam draw_param) const;
 };

} // namespace Video
} // namespace CCore

#endif

