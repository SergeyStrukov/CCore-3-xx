/* Shape.Split.h */
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

#ifndef CCore_inc_video_lib_Shape_Split_h
#define CCore_inc_video_lib_Shape_Split_h

#include <CCore/inc/video/MinSizeType.h>
#include <CCore/inc/video/Color.h>
#include <CCore/inc/video/Font.h>
#include <CCore/inc/video/RefVal.h>

namespace CCore {
namespace Video {

/* classes */

struct SplitState;

class SplitShape;

class XSplitShape;

class YSplitShape;

/* struct SplitState */

struct SplitState
 {
  bool enable =  true ;
  bool mover  = false ;
  bool down   = false ;

  Point drag_base;

  SplitState() {}
 };

/* class SplitShape */

class SplitShape : public SplitState
 {
  public:

   struct Config
    {
     RefVal<Fraction> width = Fraction(6,2) ;

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

   // methods

   explicit SplitShape(const Config &cfg_) : cfg(cfg_) {}
 };

/* class XSplitShape */

class XSplitShape : public SplitShape
 {
  public:

   explicit XSplitShape(const Config &cfg) : SplitShape(cfg) {}

   SizeXSpace getMinSize() const;

   bool isGoodSize(Point size) const { return size>=getMinSize(); }

   void draw(const DrawBuf &buf,DrawParam draw_param) const;
 };

/* class YSplitShape */

class YSplitShape : public SplitShape
 {
  public:

   explicit YSplitShape(const Config &cfg) : SplitShape(cfg) {}

   SizeYSpace getMinSize() const;

   bool isGoodSize(Point size) const { return size>=getMinSize(); }

   void draw(const DrawBuf &buf,DrawParam draw_param) const;
 };

} // namespace Video
} // namespace CCore

#endif

