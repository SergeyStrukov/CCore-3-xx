/* Shape.Text.h */
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

#ifndef CCore_inc_video_lib_Shape_Text_h
#define CCore_inc_video_lib_Shape_Text_h

#include <CCore/inc/video/MinSizeType.h>
#include <CCore/inc/video/Color.h>
#include <CCore/inc/video/Font.h>
#include <CCore/inc/video/RefVal.h>

namespace CCore {
namespace Video {

/* classes */

class TextShape;

/* class TextShape */

class TextShape
 {
   static MCoord FigEX(Coord fdy,MCoord width);

  public:

   struct Config
    {
     RefVal<Fraction> width = Fraction(6,2) ;

     RefVal<VColor> back     = Silver ;
     RefVal<VColor> gray     =   Gray ;
     RefVal<VColor> snow     =   Snow ;
     RefVal<VColor> inactive =   Gray ;
     RefVal<VColor> alert    =   Pink ;
     RefVal<VColor> text     =  Black ;

     RefVal<Point> space = Point(6,4) ;

     RefVal<Font> font;

     Config() noexcept {}

     template <class Bag>
     void bind(const Bag &bag)
      {
       width.bind(bag.width);
       back.bind(bag.back);
       gray.bind(bag.gray);
       snow.bind(bag.snow);
       inactive.bind(bag.inactive);
       alert.bind(bag.alert);

       text.bind(bag.message_text);
       space.bind(bag.message_space);
       font.bind(bag.message_font.font);
      }
    };

   const Config &cfg;
   String text;
   AlignX align_x;
   AlignY align_y;
   Pane pane;

   // state

   bool enable = true ;
   bool alert  = false ;

   // methods

   TextShape(const Config &cfg_,const String &text_,AlignX align_x_=AlignX_Center,AlignY align_y_=AlignY_Center)
    : cfg(cfg_),text(text_),align_x(align_x_),align_y(align_y_) {}

   explicit TextShape(const Config &cfg_,AlignX align_x_=AlignX_Center,AlignY align_y_=AlignY_Center)
    : cfg(cfg_),align_x(align_x_),align_y(align_y_) {}

   Point getMinSize() const;

   Point getMinSize(StrLen text) const;

   bool isGoodSize(Point size) const { return size>=getMinSize(); }

   void draw(const DrawBuf &buf,DrawParam draw_param) const;
 };

} // namespace Video
} // namespace CCore

#endif

