/* Shape.Info.h */
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

#ifndef CCore_inc_video_lib_Shape_Info_h
#define CCore_inc_video_lib_Shape_Info_h

#include <CCore/inc/video/MinSizeType.h>
#include <CCore/inc/video/Color.h>
#include <CCore/inc/video/Font.h>
#include <CCore/inc/video/RefVal.h>

#include <CCore/inc/video/Info.h>

namespace CCore {
namespace Video {

/* classes */

struct InfoState;

class InfoShape;

/* struct InfoState */

struct InfoState
 {
  bool enable =  true ;
  bool focus  = false ;

  ulen yoff    = 0 ;
  ulen yoffMax = 0 ;

  Coord xoff    = 0 ;
  Coord xoffMax = 0 ;
  Coord dxoff   = 0 ;

  bool drag = false ;
  Point drag_base;
  Coord xoff_base = 0 ;

  InfoState() {}
 };

/* class InfoShape */

class InfoShape : public InfoState
 {
  public:

   struct Config
    {
     RefVal<MCoord> width = Fraction(6,2) ;

     RefVal<VColor> focus    = OrangeRed ;
     RefVal<VColor> inactive =      Gray ;
     RefVal<VColor> text     =     Black ;

     RefVal<Point> space = Point(8,8) ;

     RefVal<Font> font;

     Config() noexcept {}

     template <class Bag>
     void bind(const Bag &bag)
      {
       width.bind(bag.width);
       focus.bind(bag.focus);
       inactive.bind(bag.inactive);

       text.bind(bag.info_text);
       space.bind(bag.info_space);
       font.bind(bag.info_font.font);
      }
    };

   // parameters

   const Config &cfg;
   Info info;
   Pane pane;

   // methods

   explicit InfoShape(const Config &cfg_) : cfg(cfg_) {}

   InfoShape(const Config &cfg_,const Info &info_) : cfg(cfg_),info(info_) {}

   Point getMinSize(unsigned update_flag,Point cap=Point::Max()) const;

   bool isGoodSize(Point size,Point cap=Point::Max()) const { return size>=getMinSize(0,cap); }

   void setMax(unsigned update_flag);

   void draw(const DrawBuf &buf) const;

  private:

   struct Cache
    {
     Coord info_dx = 0 ;
     Coord line_dy = 0 ;
     Coord med_dx = 0 ;
     bool ok = false ;

     void operator () (unsigned update_flag,const Config &cfg,const Info &info);
    };

   mutable Cache cache;
 };

} // namespace Video
} // namespace CCore

#endif

