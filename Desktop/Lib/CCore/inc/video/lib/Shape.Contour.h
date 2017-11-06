/* Shape.Contour.h */
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

#ifndef CCore_inc_video_lib_Shape_Contour_h
#define CCore_inc_video_lib_Shape_Contour_h

#include <CCore/inc/video/MinSizeType.h>
#include <CCore/inc/video/Color.h>
#include <CCore/inc/video/Font.h>
#include <CCore/inc/video/RefVal.h>

namespace CCore {
namespace Video {

/* classes */

class ContourShape;

class TextContourShape;

class RefTextContourShape;

/* class ContourShape */

class ContourShape
 {
  public:

   struct Config
    {
     RefVal<MCoord> width = Fraction(6,2) ;

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

   explicit ContourShape(const Config &cfg_) : cfg(cfg_) {}

   Point getMinSize() const;

   Point getMinSize(Point inner_size) const;

   bool isGoodSize(Point size) const { return size>=getMinSize(); }

   Pane getInner() const;

   void draw(const DrawBuf &buf) const;
 };

/* class TextContourShape */

class TextContourShape
 {
  public:

   struct Config
    {
     RefVal<MCoord> width = Fraction(6,2) ;

     RefVal<VColor> gray =  Gray ;
     RefVal<VColor> snow =  Snow ;
     RefVal<VColor> text = Black ;

     RefVal<Font> font;

     Config() noexcept {}

     template <class Bag>
     void bind(const Bag &bag)
      {
       width.bind(bag.width);
       gray.bind(bag.gray);
       snow.bind(bag.snow);

       text.bind(bag.contour_text);
       font.bind(bag.contour_font.font);
      }
    };

   const Config &cfg;
   DefString title;
   AlignX align_x;
   Pane pane;

   // methods

   TextContourShape(const Config &cfg_,const DefString &title_,AlignX align_x_=AlignX_Left) : cfg(cfg_),title(title_),align_x(align_x_) {}

   Point getMinSize() const;

   Point getMinSize(Point inner_size) const;

   bool isGoodSize(Point size) const { return size>=getMinSize(); }

   Pane getInner() const;

   void draw(const DrawBuf &buf) const;
 };

/* class RefTextContourShape */

class RefTextContourShape
 {
  public:

   using Config = TextContourShape::Config ;

   const Config &cfg;
   const RefVal<DefString> &title;
   AlignX align_x;
   Pane pane;

   // methods

   RefTextContourShape(const Config &cfg_,const RefVal<DefString> &title_,AlignX align_x_=AlignX_Left) : cfg(cfg_),title(title_),align_x(align_x_) {}

   Point getMinSize() const;

   Point getMinSize(Point inner_size) const;

   bool isGoodSize(Point size) const { return size>=getMinSize(); }

   Pane getInner() const;

   void draw(const DrawBuf &buf) const;
 };

} // namespace Video
} // namespace CCore

#endif

