/* Shape.SimpleTextList.h */
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

#ifndef CCore_inc_video_lib_Shape_SimpleTextList_h
#define CCore_inc_video_lib_Shape_SimpleTextList_h

#include <CCore/inc/video/MinSizeType.h>
#include <CCore/inc/video/Color.h>
#include <CCore/inc/video/Font.h>
#include <CCore/inc/video/RefVal.h>

#include <CCore/inc/video/Info.h>

namespace CCore {
namespace Video {

/* classes */

struct SimpleTextListState;

class SimpleTextListShape;

/* struct SimpleTextListState */

struct SimpleTextListState
 {
  bool enable =  true ;
  bool focus  = false ;
  ulen select = MaxULen ;

  ulen yoff     = 0 ;
  ulen page     = 0 ;
  ulen yoffMax  = 0 ;

  Coord xoff    = 0 ;
  Coord xoffMax = 0 ;
  Coord dxoff   = 0 ;

  SimpleTextListState() {}
 };

/* class SimpleTextListShape */

class SimpleTextListShape : public SimpleTextListState
 {
  public:

   struct Config
    {
     RefVal<MCoord> width = Fraction(6,2) ;

     RefVal<VColor> back     =    Silver ;
     RefVal<VColor> focus    = OrangeRed ;
     RefVal<VColor> gray     =      Gray ;
     RefVal<VColor> snow     =      Snow ;
     RefVal<VColor> inactive =      Gray ;
     RefVal<VColor> select   =    Yellow ;
     RefVal<VColor> text     =     Black ;

     RefVal<Point> space = Point(8,8) ;

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
       select.bind(bag.text_select);

       text.bind(bag.list_text);
       space.bind(bag.list_space);
       font.bind(bag.list_font.font);
      }
    };

   // parameters

   const Config &cfg;
   Info info;
   Pane pane;

   // methods

   explicit SimpleTextListShape(const Config &cfg_) : cfg(cfg_) {}

   SimpleTextListShape(const Config &cfg_,const Info &info_) : cfg(cfg_),info(info_) { initSelect(); }

   Point getMinSize(unsigned update_flag,Point cap=Point::Max()) const;

   bool isGoodSize(Point size,Point cap=Point::Max()) const { return size>=getMinSize(0,cap); }

   void setMax(unsigned update_flag);

   void initSelect()
    {
     if( info->getLineCount() ) select=0; else select=MaxULen;
    }

   void showSelect();

   ulen getPosition(Point point) const;

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

