/* Shape.TextLine.h */
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

#ifndef CCore_inc_video_lib_Shape_TextLine_h
#define CCore_inc_video_lib_Shape_TextLine_h

#include <CCore/inc/video/MinSizeType.h>
#include <CCore/inc/video/Color.h>
#include <CCore/inc/video/Font.h>
#include <CCore/inc/video/RefVal.h>

namespace CCore {
namespace Video {

/* classes */

class TextLineShape;

/* class TextLineShape */

class TextLineShape
 {
   static MCoord FigEX(Coord fdy,MCoord width);

  public:

   struct Config
    {
     RefVal<MCoord> width = Fraction(6,2) ;

     RefVal<VColor> back     =    Silver ;
     RefVal<VColor> focus    = OrangeRed ;
     RefVal<VColor> gray     =      Gray ;
     RefVal<VColor> snow     =      Snow ;
     RefVal<VColor> inactive =      Gray ;
     RefVal<VColor> alert    =      Pink ;
     RefVal<VColor> text     =     Black ;

     RefVal<Point> space = Point(6,4) ;

     RefVal<Font> font;

     Config() noexcept {}

     template <class Bag>
     void bind(const Bag &bag)
      {
       width.bind(bag.width);
       back.bind(bag.back);
       focus.bind(bag.focus);
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
   DefString text;
   Pane pane;

   // state

   bool enable =  true ;
   bool focus  = false ;
   bool alert  = false ;
   Coord xoff  =     0 ;

   Coord xoffMax = 0 ;
   Coord dxoff   = 0 ;

   bool drag = false ;
   Point drag_base;
   Coord xoff_base = 0 ;

   // methods

   TextLineShape(const Config &cfg_,const DefString &text_) : cfg(cfg_),text(text_) {}

   explicit TextLineShape(const Config &cfg_) : cfg(cfg_) {}

   Point getMinSize() const;

   Point getMinSize(StrLen text) const;

   bool isGoodSize(Point size) const { return size>=getMinSize(); }

   void setMax();

   void draw(const DrawBuf &buf) const;
 };

} // namespace Video
} // namespace CCore

#endif

