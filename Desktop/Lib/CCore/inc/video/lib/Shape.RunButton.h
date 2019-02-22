/* Shape.RunButton.h */
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

#ifndef CCore_inc_video_lib_Shape_RunButton_h
#define CCore_inc_video_lib_Shape_RunButton_h

#include <CCore/inc/video/MinSizeType.h>
#include <CCore/inc/video/Color.h>
#include <CCore/inc/video/Font.h>
#include <CCore/inc/video/RefVal.h>

#include <CCore/inc/DeferCall.h>

namespace CCore {
namespace Video {

/* classes */

struct RunButtonState;

class RunButtonShape;

class RefRunButtonShape;

/* struct RunButtonState */

struct RunButtonState
 {
  bool enable =  true ;
  bool focus  = false ;
  bool mover  = false ;
  bool on     = false ;

  unsigned count = 0 ;
  unsigned pos = 0 ;

  RunButtonState() {}

  void startRun()
   {
    count=0;
    pos=0;
   }

  void nextRun(unsigned steps)
   {
    if( ++pos >= steps ) pos=0;
   }

  void stopRun()
   {
   }

  bool tick(unsigned period)
   {
    if( count )
      {
       count--;

       return false;
      }
    else
      {
       count=PosSub(period,1u);

       return true;
      }
   }
 };

/* class RunButtonShape */

class RunButtonShape : public RunButtonState
 {
   static MCoord FigEX(Coord fdy,MCoord width);

  public:

   struct Config
    {
     RefVal<Fraction> width = Fraction(6,2) ;

     RefVal<VColor> border =      Blue ;
     RefVal<VColor> focus  = OrangeRed ;
     RefVal<VColor> gray   =      Gray ;
     RefVal<VColor> snow   =      Snow ;
     RefVal<VColor> snowUp = PaleGreen ;
     RefVal<VColor> text   =     Black ;

     RefVal<Point> space = Point(6,4) ;

     RefVal<Font> font;

     RefVal<VColor> run = Red ;

     RefVal<unsigned> period = 2_tick ;
     RefVal<unsigned> steps  =     10 ;

     Config() noexcept {}

     template <class Bag>
     void bind(const Bag &bag)
      {
       width.bind(bag.width);
       border.bind(bag.border);
       focus.bind(bag.focus);
       gray.bind(bag.gray);
       snow.bind(bag.snow);
       snowUp.bind(bag.snowUp);

       text.bind(bag.button_text);
       space.bind(bag.button_space);
       font.bind(bag.button_font.font);

       run.bind(bag.run);
       period.bind(bag.run_period);
       steps.bind(bag.run_steps);
      }
    };

   // parameters

   using FaceType = String ;

   const Config &cfg;
   FaceType face_off;
   FaceType face_on;
   Pane pane;

   // methods

   RunButtonShape(const Config &cfg_,const FaceType &face_off_,const FaceType &face_on_)
    : cfg(cfg_),face_off(face_off_),face_on(face_on_)
    {
    }

   Point getMinSize() const;

   bool isGoodSize(Point size) const { return size>=getMinSize(); }

   void nextRun() { RunButtonState::nextRun(+cfg.steps); }

   bool tick() { return RunButtonState::tick(+cfg.period); }

   void draw(const DrawBuf &buf,DrawParam draw_param) const;
 };

/* class RefRunButtonShape */

class RefRunButtonShape : public RunButtonState
 {
  public:

   using Config = RunButtonShape::Config ;

   // parameters

   using FaceType = const RefVal<String> & ;

   const Config &cfg;
   FaceType face_off;
   FaceType face_on;
   Pane pane;

   // methods

   RefRunButtonShape(const Config &cfg_,FaceType face_off_,FaceType face_on_)
    : cfg(cfg_),face_off(face_off_),face_on(face_on_)
    {
    }

   Point getMinSize() const;

   bool isGoodSize(Point size) const { return size>=getMinSize(); }

   void nextRun() { RunButtonState::nextRun(+cfg.steps); }

   bool tick() { return RunButtonState::tick(+cfg.period); }

   void draw(const DrawBuf &buf,DrawParam draw_param) const;
 };

} // namespace Video
} // namespace CCore

#endif

