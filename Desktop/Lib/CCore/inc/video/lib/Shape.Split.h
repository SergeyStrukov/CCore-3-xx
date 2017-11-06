/* Shape.Split.h */
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
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_video_lib_Shape_Split_h
#define CCore_inc_video_lib_Shape_Split_h

#include <CCore/inc/video/MinSizeType.h>
#include <CCore/inc/video/Color.h>
#include <CCore/inc/video/Font.h>
#include <CCore/inc/video/RefVal.h>

namespace CCore {
namespace Video {

/* classes */

class SplitShape;

class XSplitShape;

class YSplitShape;

/* class SplitShape */

class SplitShape
 {
  public:

   struct Config
    {
     RefVal<MCoord> width = Fraction(6,2) ;

     RefVal<VColor> gray    =  Gray ;
     RefVal<VColor> snow    =  Snow ;
     RefVal<VColor> hilight = Green ;
     RefVal<VColor> active  =   Red ;

     RefVal<Coord> dxy = 10 ;

     Config() noexcept {}

     template <class Bag>
     void bind(const Bag &bag)
      {
       width.bind(bag.width);
       gray.bind(bag.gray);
       snow.bind(bag.snow);
       hilight.bind(bag.dragHilight);
       active.bind(bag.dragActive);
       dxy.bind(bag.space_dxy);
      }
    };

   // parameters

   const Config &cfg;
   Pane pane;

   // state

   bool enable =  true ;
   bool mover  = false ;
   bool down   = false ;

   Point drag_base;

   // methods

   explicit SplitShape(const Config &cfg_) : cfg(cfg_) {}
 };

/* class XSplitShape */

class XSplitShape : public SplitShape
 {
  explicit XSplitShape(const Config &cfg) : SplitShape(cfg) {}

  SizeXSpace getMinSize() const;

  bool isGoodSize(Point size) const { return size>=getMinSize(); }

  void draw(const DrawBuf &buf) const;
 };

/* class YSplitShape */

class YSplitShape : public SplitShape
 {
  explicit YSplitShape(const Config &cfg) : SplitShape(cfg) {}

  SizeYSpace getMinSize() const;

  bool isGoodSize(Point size) const { return size>=getMinSize(); }

  void draw(const DrawBuf &buf) const;
 };

} // namespace Video
} // namespace CCore

#endif

