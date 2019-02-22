/* Shape.Label.h */
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

#ifndef CCore_inc_video_lib_Shape_Label_h
#define CCore_inc_video_lib_Shape_Label_h

#include <CCore/inc/video/MinSizeType.h>
#include <CCore/inc/video/Color.h>
#include <CCore/inc/video/Font.h>
#include <CCore/inc/video/RefVal.h>

namespace CCore {
namespace Video {

/* classes */

class LabelShape;

class RefLabelShape;

/* class LabelShape */

class LabelShape
 {
  public:

   struct Config
    {
     RefVal<VColor> inactive =  Gray ;
     RefVal<VColor> text     = Black ;

     RefVal<Font> font;

     Config() noexcept {}

     template <class Bag>
     void bind(const Bag &bag)
      {
       inactive.bind(bag.inactive);

       text.bind(bag.label_text);
       font.bind(bag.label_font.font);
      }
    };

   const Config &cfg;
   String text;
   AlignX align_x;
   AlignY align_y;
   Pane pane;

   // state

   bool enable = true ;

   // methods

   LabelShape(const Config &cfg_,const String &text_,AlignX align_x_=AlignX_Center,AlignY align_y_=AlignY_Center)
    : cfg(cfg_),text(text_),align_x(align_x_),align_y(align_y_) {}

   Point getMinSize() const;

   Point getMinSize(StrLen text) const;

   bool isGoodSize(Point size) const { return size>=getMinSize(); }

   void draw(const DrawBuf &buf,DrawParam draw_param) const;
 };

/* class RefLabelShape */

class RefLabelShape
 {
  public:

   using Config = LabelShape::Config ;

   const Config &cfg;
   const RefVal<String> &text;
   AlignX align_x;
   AlignY align_y;
   Pane pane;

   // state

   bool enable = true ;

   // methods

   RefLabelShape(const Config &cfg_,const RefVal<String> &text_,AlignX align_x_=AlignX_Center,AlignY align_y_=AlignY_Center)
    : cfg(cfg_),text(text_),align_x(align_x_),align_y(align_y_) {}

   Point getMinSize() const;

   Point getMinSize(StrLen text) const;

   bool isGoodSize(Point size) const { return size>=getMinSize(); }

   void draw(const DrawBuf &buf,DrawParam draw_param) const;
 };

} // namespace Video
} // namespace CCore

#endif

