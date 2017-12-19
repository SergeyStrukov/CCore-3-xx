/* Shape.LineEdit.h */
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

#ifndef CCore_inc_video_lib_Shape_LineEdit_h
#define CCore_inc_video_lib_Shape_LineEdit_h

#include <CCore/inc/video/MinSizeType.h>
#include <CCore/inc/video/Color.h>
#include <CCore/inc/video/Font.h>
#include <CCore/inc/video/RefVal.h>

#include <CCore/inc/DeferCall.h>

namespace CCore {
namespace Video {

/* classes */

struct LineEditState;

class LineEditShape;

/* struct LineEditState */

struct LineEditState
 {
  bool enable      =  true ;
  bool focus       = false ;
  bool cursor      = false ;
  bool hide_cursor = false ;
  bool alert       = false ;
  ulen len         = 0 ;
  ulen pos         = 0 ;
  ulen select_off  = 0 ;
  ulen select_len  = 0 ;
  Coord xoff       = 0 ;

  Coord xoffMax = 0 ;
  Coord dxoff   = 0 ;

  bool drag = false ;
  Point drag_base;
  Coord xoff_base = 0 ;
  bool mouse_pos = false ;

  LineEditState() {}
 };

/* class LineEditShape */

class LineEditShape : public LineEditState
 {
   static MCoord FigEX(Coord fdy,MCoord width,Coord ex);

   Point getMinSize(TextSize ts) const;

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
     RefVal<VColor> select   =    Yellow ;
     RefVal<VColor> cursor   =      Blue ;

     RefVal<Coord> cursor_dx = 3 ;

     RefVal<VColor> text = Black ;

     RefVal<Coord> ex = 3 ;

     RefVal<Point> space = Point(6,4) ;

     RefVal<Font> font;

     RefVal<unsigned> period = 10_tick ;

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
       select.bind(bag.text_select);
       cursor.bind(bag.text_cursor);
       cursor_dx.bind(bag.text_cursor_dx);

       text.bind(bag.line_edit_text);
       ex.bind(bag.line_edit_ex);
       space.bind(bag.line_edit_space);
       font.bind(bag.line_edit_font.font);
       period.bind(bag.line_edit_period);
      }
    };

   const Config &cfg;
   PtrLen<Char> text_buf;
   Pane pane;

   // tick count

   unsigned tick_count = 0 ;

   // methods

   LineEditShape(PtrLen<Char> text_buf_,const Config &cfg_) : cfg(cfg_),text_buf(text_buf_) {}

   Point getMinSize(unsigned update_flag) const;

   Point getMinSize(unsigned update_flag,StrLen sample_text) const;

#ifdef CCORE_UTF8

   Point getMinSize(unsigned update_flag,PtrLen<const Char> sample_text) const;

#endif

   bool isGoodSize(Point size) const { return size>=getMinSize(0); }

   void setMax(unsigned update_flag);

   bool tick()
    {
     if( tick_count )
       {
        tick_count--;

        return false;
       }
     else
       {
        tick_count=PosSub(+cfg.period,1u);

        return true;
       }
    }

   void showCursor();

   ulen getPosition(Point point) const;

   virtual void drawText(Font font,const DrawBuf &buf,Pane pane,TextPlace place,PtrLen<const Char> text,ulen off,VColor vc) const;

   void draw(const DrawBuf &buf) const;
 };

} // namespace Video
} // namespace CCore

#endif

