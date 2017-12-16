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

struct TextLineState;

class TextLineShape;

/* struct TextLineState */

struct TextLineState
 {
  bool enable =  true ;
  bool focus  = false ;
  bool alert  = false ;
  Coord xoff  =     0 ;

  Coord xoffMax = 0 ;
  Coord dxoff   = 0 ;

  bool drag = false ;
  Point drag_base;
  Coord xoff_base = 0 ;

  TextLineState() {}
 };

/* class TextLineShape */

class TextLineShape : public TextLineState
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

   // methods

   TextLineShape(const Config &cfg_,const DefString &text_) : cfg(cfg_),text(text_) {}

   explicit TextLineShape(const Config &cfg_) : cfg(cfg_) {}

   Point getMinSize(unsigned update_flag) const;

   Point getMinSize(unsigned update_flag,StrLen text) const;

   bool isGoodSize(Point size) const { return size>=getMinSize(0); }

   void setMax(unsigned update_flag);

   void draw(const DrawBuf &buf) const;

  private:

   struct Cache
    {
     Coord btn_ex = 0 ;
     Coord inner_dx = 0 ;
     Coord inner_dy = 0 ;
     Coord text_dx = 0 ;
     Coord text_dy = 0 ;
     Coord med_dx  = 0 ;
     Coord font_dx0 = 0 ;
     bool ok = false ;

     void operator () (unsigned update_flag,const Config &cfg,StrLen text);
    };

   mutable Cache cache;
 };

} // namespace Video
} // namespace CCore

#endif

