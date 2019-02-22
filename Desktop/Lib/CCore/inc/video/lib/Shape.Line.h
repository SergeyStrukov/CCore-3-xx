/* Shape.Line.h */
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

#ifndef CCore_inc_video_lib_Shape_Line_h
#define CCore_inc_video_lib_Shape_Line_h

#include <CCore/inc/video/MinSizeType.h>
#include <CCore/inc/video/Color.h>
#include <CCore/inc/video/Font.h>
#include <CCore/inc/video/RefVal.h>

namespace CCore {
namespace Video {

/* classes */

class SingleLineShape;

class XSingleLineShape;

class YSingleLineShape;

class DoubleLineShape;

class XDoubleLineShape;

class YDoubleLineShape;

/* class SingleLineShape */

class SingleLineShape
 {
  public:

   struct Config
    {
     RefVal<Fraction> width = Fraction(6,2) ;

     RefVal<VColor> line = Gray ;

     Config() noexcept {}

     template <class Bag>
     void bind(const Bag &bag)
      {
       width.bind(bag.width);
       line.bind(bag.line);
      }
    };

   const Config &cfg;
   Pane pane;

   // methods

   explicit SingleLineShape(const Config &cfg_) : cfg(cfg_) {}
 };

/* class XSingleLineShape */

class XSingleLineShape : public SingleLineShape
 {
  public:

   // methods

   explicit XSingleLineShape(const Config &cfg) : SingleLineShape(cfg) {}

   SizeY getMinSize() const;

   bool isGoodSize(Point size) const { return size>=getMinSize(); }

   void draw(const DrawBuf &buf,DrawParam draw_param) const;
 };

/* class YSingleLineShape */

class YSingleLineShape : public SingleLineShape
 {
  public:

   // methods

   explicit YSingleLineShape(const Config &cfg) : SingleLineShape(cfg) {}

   SizeX getMinSize() const;

   bool isGoodSize(Point size) const { return size>=getMinSize(); }

   void draw(const DrawBuf &buf,DrawParam draw_param) const;
 };

/* class DoubleLineShape */

class DoubleLineShape
 {
  public:

   struct Config
    {
     RefVal<Fraction> width = Fraction(6,2) ;

     RefVal<VColor> gray = Gray ;
     RefVal<VColor> snow = Snow ;

     Config() noexcept {}

     template <class Bag>
     void bind(const Bag &bag)
      {
       width.bind(bag.width);
       gray.bind(bag.gray);
       snow.bind(bag.snow);
      }
    };

   const Config &cfg;
   Pane pane;

   // methods

   explicit DoubleLineShape(const Config &cfg_) : cfg(cfg_) {}
 };

/* class XDoubleLineShape */

class XDoubleLineShape : public DoubleLineShape
 {
  public:

   // methods

   explicit XDoubleLineShape(const Config &cfg) : DoubleLineShape(cfg) {}

   SizeY getMinSize() const;

   bool isGoodSize(Point size) const { return size>=getMinSize(); }

   void draw(const DrawBuf &buf,DrawParam draw_param) const;
 };

/* class YDoubleLineShape */

class YDoubleLineShape : public DoubleLineShape
 {
  public:

   // methods

   explicit YDoubleLineShape(const Config &cfg) : DoubleLineShape(cfg) {}

   SizeX getMinSize() const;

   bool isGoodSize(Point size) const { return size>=getMinSize(); }

   void draw(const DrawBuf &buf,DrawParam draw_param) const;
 };

} // namespace Video
} // namespace CCore

#endif

