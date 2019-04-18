/* Shape.Progress.h */
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

#ifndef CCore_inc_video_lib_Shape_Progress_h
#define CCore_inc_video_lib_Shape_Progress_h

#include <CCore/inc/video/MinSizeType.h>
#include <CCore/inc/video/Color.h>
#include <CCore/inc/video/Font.h>
#include <CCore/inc/video/RefVal.h>

#include <CCore/inc/DeferCall.h>

namespace CCore {
namespace Video {

/* classes */

struct ProgressState;

class ProgressShape;

class ArrowProgressShape;

/* struct ProgressState */

struct ProgressState
 {
  static constexpr unsigned MaxActivePos = 100 ;

  unsigned total      =   100 ;
  unsigned pos        =     0 ;
  unsigned active_pos =     0 ;
  bool has_active     = false ;

  unsigned time  = 0 ;
  unsigned count = 0 ;

  ProgressState() {}

  bool setPos(unsigned pos_)
   {
    return Change(pos,Min(total,pos_));
   }

  void resetTime(unsigned time_)
   {
    time=time_;
   }

  bool checkTime()
   {
    if( time )
      {
       time--;

       return true;
      }
    else
      {
       return false;
      }
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

  bool startActive()
   {
    if( !has_active )
      {
       has_active=true;
       active_pos=0;
       count=0;

       return true;
      }

    return false;
   }

  void nextActive()
   {
    if( (active_pos+=MaxActivePos/10)>MaxActivePos ) active_pos=0;
   }

  void stopActive()
   {
    has_active=false;
   }
 };

/* class ProgressShape */

class ProgressShape : public ProgressState
 {
  public:

   struct Config
    {
     RefVal<Fraction> width = Fraction(6,2) ;

     RefVal<VColor> border =     Black ;
     RefVal<VColor> gray   =      Gray ;
     RefVal<VColor> snow   =      Snow ;

     RefVal<VColor> grayUp = DarkGreen ;
     RefVal<VColor> snowUp =     Green ;

     RefVal<VColor> grayPing = Black ;
     RefVal<VColor> snowPing =  Snow ;

     RefVal<Coord> dy = 24 ;

     RefVal<unsigned> time   = 3_sectick ;
     RefVal<unsigned> period =    2_tick ;

     Config() noexcept {}

     template <class Bag>
     void bind(const Bag &bag)
      {
       width.bind(bag.width);
       gray.bind(bag.gray);
       snow.bind(bag.snow);

       border.bind(bag.progress_border);
       grayUp.bind(bag.progress_grayUp);
       snowUp.bind(bag.progress_snowUp);
       grayPing.bind(bag.progress_grayPing);
       snowPing.bind(bag.progress_snowPing);
       dy.bind(bag.progress_dy);
       time.bind(bag.progress_time);
       period.bind(bag.progress_period);
      }
    };

   const Config &cfg;
   Pane pane;

   // methods

   explicit ProgressShape(const Config &cfg_) : cfg(cfg_) {}

   SizeY getMinSize() const;

   bool isGoodSize(Point size) const
    {
     Coord dy=getMinSize().dy;

     return size.y >= dy && size.x/4 >= size.y ;
    }

   void resetTime() { ProgressState::resetTime(+cfg.time); }

   bool tick() { return ProgressState::tick(+cfg.period); }

   void draw(const DrawBuf &buf,DrawParam draw_param) const;
 };

/* class ArrowProgressShape */

class ArrowProgressShape : public ProgressState
 {
  public:

   struct Config
    {
     RefVal<Fraction> width = Fraction(6,2) ;

     RefVal<VColor> border =     Black ;
     RefVal<VColor> gray   =      Gray ;
     RefVal<VColor> snow   =      Snow ;

     RefVal<VColor> grayUp = DarkGreen ;
     RefVal<VColor> snowUp =     Green ;

     RefVal<VColor> grayArrow =    Blue ;
     RefVal<VColor> snowArrow = SkyBlue ;

     RefVal<Coord> dy = 24 ;

     RefVal<unsigned> time   = 3_sectick ;
     RefVal<unsigned> period =    2_tick ;

     Config() noexcept {}

     template <class Bag>
     void bind(const Bag &bag)
      {
       width.bind(bag.width);
       gray.bind(bag.gray);
       snow.bind(bag.snow);

       border.bind(bag.progress_border);
       grayUp.bind(bag.progress_grayUp);
       snowUp.bind(bag.progress_snowUp);
       grayArrow.bind(bag.progress_grayArrow);
       snowArrow.bind(bag.progress_snowArrow);
       dy.bind(bag.progress_dy);
       time.bind(bag.progress_time);
       period.bind(bag.progress_period);
      }
    };

   const Config &cfg;
   Pane pane;

   // methods

   explicit ArrowProgressShape(const Config &cfg_) : cfg(cfg_) {}

   SizeY getMinSize() const;

   bool isGoodSize(Point size) const
    {
     Coord dy=getMinSize().dy;

     return size.y >= dy && size.x/4 >= size.y ;
    }

   void resetTime() { ProgressState::resetTime(+cfg.time); }

   bool tick() { return ProgressState::tick(+cfg.period); }

   void draw(const DrawBuf &buf,DrawParam draw_param) const;
 };

} // namespace Video
} // namespace CCore

#endif

