/* Shape.Spinor.h */
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

#ifndef CCore_inc_video_lib_Shape_Spinor_h
#define CCore_inc_video_lib_Shape_Spinor_h

#include <CCore/inc/video/MinSizeType.h>
#include <CCore/inc/video/Color.h>
#include <CCore/inc/video/Font.h>
#include <CCore/inc/video/RefVal.h>

#include <CCore/inc/DeferCall.h>

namespace CCore {
namespace Video {

/* enum SpinType */

enum SpinType
 {
  SpinType_None = 0,

  SpinType_Plus,
  SpinType_Minus
 };

/* classes */

struct SpinorState;

class SpinorShape;

/* struct SpinorState */

struct SpinorState
 {
  bool enable =  true ;
  bool focus  = false ;
  SpinType mover = SpinType_None ;
  SpinType down  = SpinType_None ;
  unsigned time   = 0 ;
  unsigned period = 0 ;

  bool mouse = false ;

  SpinorState() {}

  void tickStart(unsigned period_)
   {
    time=0;
    period=period_;
   }

  bool tick()
   {
    if( (++time)>=period )
      {
       time=0;

       if( period>1 ) period--;

       return true;
      }

    return false;
   }
 };

/* class SpinorShape */

class SpinorShape : public SpinorState
 {
   Point getInnerSize(int val) const;

  public:

   struct Config
    {
     RefVal<Fraction> width = Fraction(6,2) ;

     RefVal<VColor> back   =    Silver ;
     RefVal<VColor> border =      Blue ;
     RefVal<VColor> focus  = OrangeRed ;
     RefVal<VColor> gray   =      Gray ;
     RefVal<VColor> snow   =      Snow ;
     RefVal<VColor> snowUp = PaleGreen ;
     RefVal<VColor> face   =     Black ;
     RefVal<VColor> text   =     Black ;

     RefVal<Font> font;

     RefVal<unsigned> period = 1_sectick/2 ;

     Config() noexcept {}

     template <class Bag>
     void bind(const Bag &bag)
      {
       width.bind(bag.width);
       back.bind(bag.back);
       border.bind(bag.border);
       focus.bind(bag.focus);
       gray.bind(bag.gray);
       snow.bind(bag.snow);
       snowUp.bind(bag.snowUp);
       face.bind(bag.face);

       text.bind(bag.spinor_text);
       font.bind(bag.spinor_font.font);
       period.bind(bag.spinor_period);
      }
    };

   // parameters

   static constexpr int DeltaCap = 100'000 ;

   const Config &cfg;
   int min_val = 0 ;
   int max_val = 0 ;
   int val = 0 ;
   int delta = 1 ;
   IntPrintOpt opt;
   Pane pane;

   // methods

   explicit SpinorShape(const Config &cfg_) : cfg(cfg_) {}

   Point getMinSize() const;

   bool isGoodSize(Point size) const { return size>=getMinSize() && size.x/4>=size.y ; }

   SpinType getZone(Point point) const;

   void tickStart() { SpinorState::tickStart(+cfg.period); }

   void draw(const DrawBuf &buf,DrawParam draw_param) const;
 };

} // namespace Video
} // namespace CCore

#endif

