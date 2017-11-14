/* Shape.Slider.h */
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
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_video_lib_Shape_Slider_h
#define CCore_inc_video_lib_Shape_Slider_h

#include <CCore/inc/video/MinSizeType.h>
#include <CCore/inc/video/Color.h>
#include <CCore/inc/video/Font.h>
#include <CCore/inc/video/RefVal.h>

namespace CCore {
namespace Video {

/* classes */

struct SliderState;

class SliderShape;

class XSliderShape;

class YSliderShape;

/* struct SliderState */

struct SliderState
 {
  bool enable =  true ;
  bool focus  = false ;
  bool mover  = false ;

  unsigned pos   = 0 ;
  unsigned total = 0 ;

  bool drag = false ;
  Point drag_base;
  unsigned pos_base = 0 ;

  SliderState() {}
 };

/* class SliderShape */

class SliderShape : public SliderState
 {
  public:

   struct Config
    {
     RefVal<MCoord> width = Fraction(6,2) ;

     RefVal<VColor> border =      Blue ;
     RefVal<VColor> focus  = OrangeRed ;
     RefVal<VColor> gray   =      Gray ;
     RefVal<VColor> snow   =      Snow ;
     RefVal<VColor> snowUp = PaleGreen ;

     Config() noexcept {}

     template <class Bag>
     void bind(const Bag &bag)
      {
       width.bind(bag.width);
       border.bind(bag.border);
       focus.bind(bag.focus);
       gray.bind(bag.gray);
       snow.bind(bag.snow);
       snowUp.bind(bag.snowUp);
      }
    };

   // parameters

   const Config &cfg;
   Pane pane;

   // methods

   explicit SliderShape(const Config &cfg_) : cfg(cfg_) {}
 };

/* class XSliderShape */

class XSliderShape : public SliderShape
 {
  public:

   explicit XSliderShape(const Config &cfg) : SliderShape(cfg) {}

   Point getMinSize() const;

   bool isGoodSize(Point size) const { return size>=getMinSize(); }

   void draw(const DrawBuf &buf) const;
 };

/* class YSliderShape */

class YSliderShape : public SliderShape
 {
  public:

   explicit YSliderShape(const Config &cfg) : SliderShape(cfg) {}

   Point getMinSize() const;

   bool isGoodSize(Point size) const { return size>=getMinSize(); }

   void draw(const DrawBuf &buf) const;
 };

} // namespace Video
} // namespace CCore

#endif

