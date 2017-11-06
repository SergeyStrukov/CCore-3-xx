/* Shape.ScrollList.h */
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

class ScrollListShape;

/* class ScrollListShape */

class ScrollListShape
 {
   static Coord AddSat(Coord a,Coord b);

   static Coord GetLineDX(Font font,ComboInfoItem item,Coord off);

  public:

   struct Config
    {
     RefVal<MCoord> width = Fraction(6,2) ;

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

   // parameters

   const Config &cfg;
   ComboInfo info;
   Pane pane;

   // state

   bool enable =  true ;
   bool focus  = false ;
   ulen select = MaxULen ;

   ulen yoff  = 0 ;
   Coord xoff = 0 ;

   ulen page     = 0 ;
   ulen yoffMax  = 0 ;
   Coord xoffMax = 0 ;
   Coord dxoff   = 0 ;

   // methods

   explicit ScrollListShape(const Config &cfg_) : cfg(cfg_) {}

   ScrollListShape(const Config &cfg_,const ComboInfo &info_) : cfg(cfg_),info(info_) { setSelectDown(0); }

   Point getMinSize(Point cap=Point::Max()) const;

   bool isGoodSize(Point size,Point cap=Point::Max()) const { return size>=getMinSize(cap); }

   void setMax();

   void initSelect();

   bool setSelectDown(ulen pos);

   bool setSelectUp(ulen pos);

   bool showSelect();

   ulen getPosition(Point point) const;

   void draw(const DrawBuf &buf) const;
 };

} // namespace Video
} // namespace CCore

#endif

