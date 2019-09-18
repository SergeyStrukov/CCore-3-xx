/* Shape.TextLine.h */
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

struct TextLineCodeState;

class TextLineShapeBase;

class TextLineShape;

class TextLineCodeShape;

/* struct TextLineState */

struct TextLineState
 {
  bool enable =  true ;
  bool focus  = false ;
  bool alert  = false ;
  Coord xoff  =     0 ;

  Coord xoff_max = 0 ;
  Coord dxoff    = 0 ;

  bool drag = false ;
  Point drag_base;
  Coord xoff_base = 0 ;

  TextLineState() {}
 };

/* struct TextLineCodeState */

enum AlertCode
 {
  AlertCodeGreen = 0,

  AlertCodeYellow,
  AlertCodeRed
 };

struct TextLineCodeState
 {
  bool enable    =           true ;
  bool focus     =          false ;
  AlertCode code = AlertCodeGreen ;
  Coord xoff     =              0 ;

  Coord xoff_max = 0 ;
  Coord dxoff    = 0 ;

  bool drag = false ;
  Point drag_base;
  Coord xoff_base = 0 ;

  TextLineCodeState() {}
 };

/* class TextLineShapeBase */

class TextLineShapeBase
 {
   static MCoord FigEX(Coord fdy,MCoord width);

  public:

   struct ConfigBase
    {
     RefVal<Fraction> width = Fraction(6,2) ;

     RefVal<VColor> back     =    Silver ;
     RefVal<VColor> focus    = OrangeRed ;
     RefVal<VColor> gray     =      Gray ;
     RefVal<VColor> snow     =      Snow ;
     RefVal<VColor> inactive =      Gray ;
     RefVal<VColor> text     =     Black ;

     RefVal<Point> space = Point(6,4) ;

     RefVal<Font> font;

     ConfigBase() noexcept {}

     template <class Bag>
     void bindBase(const Bag &bag)
      {
       width.bind(bag.width);
       back.bind(bag.back);
       focus.bind(bag.focus);
       gray.bind(bag.gray);
       snow.bind(bag.snow);
       inactive.bind(bag.inactive);

       text.bind(bag.message_text);
       space.bind(bag.message_space);
       font.bind(bag.message_font.font);
      }
    };

   String text;
   Pane pane;
   unsigned update_mask = LayoutUpdate ;

   void update(unsigned flags) { if( flags&update_mask ) cache.ok=false; }

  protected:

   Point getMinSize_cfg(const ConfigBase &cfg) const;

   Point getMinSize_cfg(const ConfigBase &cfg,StrLen text) const;

   void layout_cfg(const ConfigBase &cfg,Coord &xoff_max,Coord &dxoff);

   void draw_cfg(const ConfigBase &cfg,const DrawBuf &buf,Coord xoff,Coord xoff_max,bool enable,bool focus,VColor back) const;

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

     void operator () (const ConfigBase &cfg,StrLen text);
    };

   mutable Cache cache;
 };

/* class TextLineShape */

class TextLineShape : public TextLineState , public TextLineShapeBase
 {
   VColor getBack() const;

  public:

   struct Config : ConfigBase
    {
     RefVal<VColor> alert = Pink ;

     Config() noexcept {}

     template <class Bag>
     void bind(const Bag &bag)
      {
       bindBase(bag);

       alert.bind(bag.alert);
      }
    };

   const Config &cfg;

   // methods

   TextLineShape(const Config &cfg_,const String &text_) : cfg(cfg_) { text=text_; }

   explicit TextLineShape(const Config &cfg_) : cfg(cfg_) {}

   Point getMinSize() const;

   Point getMinSize(StrLen text) const;

   bool isGoodSize(Point size) const { return size>=getMinSize(); }

   void layout();

   void draw(const DrawBuf &buf,DrawParam draw_param) const;
 };

/* class TextLineCodeShape */

class TextLineCodeShape : public TextLineCodeState , public TextLineShapeBase
 {
   VColor getBack() const;

  public:

   struct Config : ConfigBase
    {
     RefVal<VColor> alert   =   Pink ;
     RefVal<VColor> warning = Yellow ;

     Config() noexcept {}

     template <class Bag>
     void bind(const Bag &bag)
      {
       bindBase(bag);

       alert.bind(bag.alert);
       warning.bind(bag.warning);
      }
    };

   const Config &cfg;

   // methods

   TextLineCodeShape(const Config &cfg_,const String &text_) : cfg(cfg_) { text=text_; }

   explicit TextLineCodeShape(const Config &cfg_) : cfg(cfg_) {}

   Point getMinSize() const;

   Point getMinSize(StrLen text) const;

   bool isGoodSize(Point size) const { return size>=getMinSize(); }

   void layout();

   void draw(const DrawBuf &buf,DrawParam draw_param) const;
 };

} // namespace Video
} // namespace CCore

#endif

