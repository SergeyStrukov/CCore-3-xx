/* Shape.Scroll.h */
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

#ifndef CCore_inc_video_lib_Shape_Scroll_h
#define CCore_inc_video_lib_Shape_Scroll_h

#include <CCore/inc/video/MinSizeType.h>
#include <CCore/inc/video/Color.h>
#include <CCore/inc/video/Font.h>
#include <CCore/inc/video/RefVal.h>

#include <CCore/inc/DeferCall.h>

namespace CCore {
namespace Video {

/* enum ScrollType */

enum ScrollType
 {
  ScrollType_None = 0,

  ScrollType_Down,
  ScrollType_DownPage,
  ScrollType_Drag,
  ScrollType_UpPage,
  ScrollType_Up
 };

/* classes */

class ScrollShape;

class XScrollShape;

class YScrollShape;

/* class ScrollShape */

class ScrollShape
 {
  protected:

   static unsigned Accelerate(unsigned change_count,unsigned period);

   static ulen Delta(ulen m,uCoord p,uCoord q);

   ulen delta(uCoord delta,uCoord len,uCoord dlen) const;

   void dragPos(Coord from,Coord to,uCoord len,uCoord dlen);

  public:

   struct Config
    {
     RefVal<MCoord> width = Fraction(6,2) ;

     RefVal<VColor> back   =    Silver ;
     RefVal<VColor> focus  = OrangeRed ;
     RefVal<VColor> gray   =      Gray ;
     RefVal<VColor> snow   =      Snow ;
     RefVal<VColor> face   =     Black ;
     RefVal<VColor> faceUp =      Blue ;

     RefVal<Coord> dxy = 20 ;

     RefVal<unsigned> speedUpPeriod = 12_tick ;

     Config() noexcept {}

     template <class Bag>
     void bind(const Bag &bag)
      {
       width.bind(bag.width);
       back.bind(bag.back);
       focus.bind(bag.focus);
       gray.bind(bag.gray);
       snow.bind(bag.snow);
       face.bind(bag.face);
       faceUp.bind(bag.faceUp);

       dxy.bind(bag.scroll_dxy);
       speedUpPeriod.bind(bag.scroll_speedUpPeriod);
      }
    };

   const Config &cfg;
   Pane pane;

   // state

   ulen total = 0 ;
   ulen page  = 0 ; // page <= total
   ulen pos   = 0 ; // pos <= total-page

   bool enable=true;
   bool focus=false;
   ScrollType down = ScrollType_None ;
   ScrollType mover = ScrollType_None ;

   ScrollType press_type = ScrollType_None ;
   unsigned change_count = 0 ;
   bool mouse = false ;

   Point drag_base;
   ulen drag_pos = 0 ;

   // methods

   explicit ScrollShape(const Config &cfg_) : cfg(cfg_) {}

   ulen getMaxPos() const
    {
     if( page<total ) return total-page;

     return 0;
    }

   void adjustPos()
    {
     Replace_min(pos,getMaxPos());
    }

   void posMin()
    {
     pos=0;
    }

   void posMax()
    {
     pos=getMaxPos();
    }

   void posDown()
    {
     if( pos ) pos--;
    }

   void posDown(ulen delta)
    {
     pos=PosSub(pos,delta);
    }

   void posDownPage() { posDown(page); }

   void posUp()
    {
     if( pos<getMaxPos() ) pos++;
    }

   void posUp(ulen delta)
    {
     pos=AddToCap(pos,delta,getMaxPos());
    }

   void posUpPage() { posUp(page); }

   bool posChange()
    {
     ulen old_pos=pos;

     unsigned period=+cfg.speedUpPeriod;

     switch( press_type )
       {
        case ScrollType_Down :
         {
          posDown(Accelerate(change_count,period));
         }
        break;

        case ScrollType_Up :
         {
          posUp(Accelerate(change_count,period));
         }
        break;

        case ScrollType_DownPage :
         {
          if( (change_count%period)==0 ) posDownPage();
         }
        break;

        case ScrollType_UpPage :
         {
          if( (change_count%period)==0 ) posUpPage();
         }
        break;
       }

     change_count++;

     return old_pos!=pos;
    }
 };

/* class XScrollShape */

class XScrollShape : public ScrollShape
 {
  public:

   static const VKey DownKey = VKey_Left ;

   static const VKey UpKey = VKey_Right ;

   // methods

   explicit XScrollShape(const Config &cfg) : ScrollShape(cfg) {}

   SizeY getMinSize() const;

   bool isGoodSize(Point size) const { return size >= getMinSize() && size.x/5 >= size.y ; }

   ScrollType getType(MPoint point) const;

   void drag(Point point) { dragPos(drag_base.x,point.x,pane.dx,pane.dy); }

   void draw(const DrawBuf &buf) const;
 };

/* class YScrollShape */

class YScrollShape : public ScrollShape
 {
  public:

   static const VKey DownKey = VKey_Up ;

   static const VKey UpKey = VKey_Down ;

   // methods

   explicit YScrollShape(const Config &cfg) : ScrollShape(cfg) {}

   SizeX getMinSize() const;

   bool isGoodSize(Point size) const { return size >= getMinSize() && size.y/5 >= size.x ; }

   ScrollType getType(MPoint point) const;

   void drag(Point point) { dragPos(drag_base.y,point.y,pane.dy,pane.dx); }

   void draw(const DrawBuf &buf) const;
 };

} // namespace Video
} // namespace CCore

#endif

