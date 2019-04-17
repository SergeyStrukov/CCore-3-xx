/* Shape.ShiftSwitch.h */
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
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_video_lib_Shape_ShiftSwitch_h
#define CCore_inc_video_lib_Shape_ShiftSwitch_h

#include <CCore/inc/video/MinSizeType.h>
#include <CCore/inc/video/Color.h>
#include <CCore/inc/video/Font.h>
#include <CCore/inc/video/RefVal.h>

#include <CCore/inc/video/lib/Shape.CheckState.h>

namespace CCore {
namespace Video {

/* classes */

class ShiftSwitchShape;

class XShiftSwitchShape;

class YShiftSwitchShape;

/* class ShiftSwitchShape */

class ShiftSwitchShape : public CheckState
 {
  public:

   struct Config
    {
     RefVal<Fraction> width = Fraction(6,2) ;

     RefVal<VColor> back   =    Silver ;
     RefVal<VColor> focus  = OrangeRed ;
     RefVal<VColor> gray   =      Gray ;
     RefVal<VColor> border =      Blue ;
     RefVal<VColor> snow   =      Snow ;
     RefVal<VColor> snowUp = PaleGreen ;

     RefVal<VColor> shift  = Black    ;
     RefVal<VColor> on     = Green    ;
     RefVal<VColor> off    = DarkGray ;

     RefVal<Coord> len = 30 ;

     Config() noexcept {}

     template <class Bag>
     void bind(const Bag &bag)
      {
       width.bind(bag.width);

       back.bind(bag.back);
       focus.bind(bag.focus);
       gray.bind(bag.gray);
       border.bind(bag.border);
       snow.bind(bag.snow);
       snowUp.bind(bag.snowUp);

       shift.bind(bag.shift_shift);
       on.bind(bag.shift_on);
       off.bind(bag.shift_off);
       len.bind(bag.shift_len);
      }
    };

   const Config &cfg;
   Pane pane;

   // methods

   ShiftSwitchShape(const Config &cfg_,bool check_) : cfg(cfg_) { check=check_; }
 };

/* class XShiftSwitchShape */

class XShiftSwitchShape : public ShiftSwitchShape
 {
   static constexpr Point Aspect = Point(4,2) ;

  public:

   explicit XShiftSwitchShape(const Config &cfg,bool check=false) : ShiftSwitchShape(cfg,check) {}

   Point getMinSize() const;

   bool isGoodSize(Point size) const { return size>=getMinSize(); }

   void draw(const DrawBuf &buf,DrawParam draw_param) const;
 };

/* class YShiftSwitchShape */

class YShiftSwitchShape : public ShiftSwitchShape
 {
   static constexpr Point Aspect = Point(2,4) ;

  public:

   explicit YShiftSwitchShape(const Config &cfg,bool check=false) : ShiftSwitchShape(cfg,check) {}

   Point getMinSize() const;

   bool isGoodSize(Point size) const { return size>=getMinSize(); }

   void draw(const DrawBuf &buf,DrawParam draw_param) const;
 };

} // namespace Video
} // namespace CCore

#endif

