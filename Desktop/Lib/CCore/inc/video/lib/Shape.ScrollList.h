/* Shape.ScrollList.h */
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

#ifndef CCore_inc_video_lib_Shape_ScrollList_h
#define CCore_inc_video_lib_Shape_ScrollList_h

#include <CCore/inc/video/MinSizeType.h>
#include <CCore/inc/video/Color.h>
#include <CCore/inc/video/Font.h>
#include <CCore/inc/video/RefVal.h>

#include <CCore/inc/video/Info.h>

namespace CCore {
namespace Video {

/* classes */

struct ScrollListState;

class ScrollListShape;

/* struct ScrollListState */

struct ScrollListState
 {
  bool enable =  true ;
  bool focus  = false ;
  ulen select = MaxULen ;

  ulen yoff     = 0 ;
  ulen page     = 0 ;
  ulen yoff_max  = 0 ;

  Coord xoff    = 0 ;
  Coord xoff_max = 0 ;
  Coord dxoff   = 0 ;

  ScrollListState() {}
 };

/* class ScrollListShape */

class ScrollListShape : public ScrollListState
 {
   static StrLen SampleLine();

   static Coord GetLineDX(const Font &font,ComboInfoItem item,Coord title_off);

   static Point InfoSize(Font font,ComboInfo info);

  public:

   struct Config
    {
     RefVal<Fraction> width = Fraction(6,2) ;

     RefVal<VColor> back         =    Silver ;
     RefVal<VColor> focus        = OrangeRed ;
     RefVal<VColor> gray         =      Gray ;
     RefVal<VColor> snow         =      Snow ;
     RefVal<VColor> inactive     =      Gray ;
     RefVal<VColor> select       =    Yellow ;
     RefVal<VColor> title        =      Navy ;
     RefVal<VColor> titleTop     =      Aqua ;
     RefVal<VColor> titleBottom  =      Gray ;
     RefVal<VColor> text         =     Black ;

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

       title.bind(bag.scroll_list_title);
       titleTop.bind(bag.scroll_list_titleTop);
       titleBottom.bind(bag.scroll_list_titleBottom);
      }
    };

   using InfoType = ComboInfo ;

   // parameters

   const Config &cfg;
   ComboInfo info;
   Pane pane;
   unsigned update_mask = LayoutUpdate ;

   // methods

   explicit ScrollListShape(const Config &cfg_) : cfg(cfg_) {}

   ScrollListShape(const Config &cfg_,const ComboInfo &info_) : cfg(cfg_),info(info_) { setSelectDown(0); }

   void update(unsigned flags) { if( flags&update_mask ) cache.ok=false; }

   Point getMinSize(Point cap=Point::Max()) const;

   Point getMinSize(unsigned lines) const;

   bool isGoodSize(Point size,Point cap=Point::Max()) const { return size>=getMinSize(cap); }

   void layout();

   void adjustScrollPos() {}

   void initSelect();

   ulen getLineCount() const { return info->getLineCount(); }

   bool isSelectable(ulen index) const { return info->getLine(index).type==ComboInfoText; }

   bool setSelectDown(ulen pos);

   bool setSelectUp(ulen pos);

   bool showSelect();

   ulen getPosition(Point point) const;

   void draw(const DrawBuf &buf,DrawParam draw_param) const;

  private:

   struct Cache
    {
     Coord info_dx = 0 ;
     Coord line_dy = 0 ;
     Coord med_dx = 0 ;
     bool ok = false ;

     void operator () (const Config &cfg,const ComboInfo &info);
    };

   mutable Cache cache;
 };

} // namespace Video
} // namespace CCore

#endif

