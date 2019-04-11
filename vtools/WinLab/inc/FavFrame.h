/* FavFrame.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.60
//
//  Tag: Desktop
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_video_FavFrame_h
#define CCore_inc_video_FavFrame_h

//#include <CCore/inc/video/FavList.h>
#include <inc/FavList.h>

#include <CCore/inc/video/WindowLib.h>

namespace CCore {
namespace Video {

/* classes */

class FavListShape;

template <class Shape> class FavListWindowOf;

class FavWindow;

class FavFrame;

/* class FavListShape */

class FavListShape
 {
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
      }
    };

   // parameters

   const Config &cfg;
   FavList fav_list;
   Pane pane;

   // methods

   explicit FavListShape(const Config &cfg_) : cfg(cfg_) {}

   Point getMinSize() const;

   bool isGoodSize(Point size) const { return size>=getMinSize(); }

   void draw(const DrawBuf &buf,DrawParam draw_param) const;
 };

/* class FavListWindowOf<Shape> */

template <class Shape>
class FavListWindowOf : public SubWindow
 {
   Shape shape;

  public:

   using ShapeType = Shape ;
   using ConfigType = typename Shape::Config ;

   template <class ... TT>
   FavListWindowOf(SubWindowHost &host,TT && ... tt)
    : SubWindow(host),
      shape( std::forward<TT>(tt)... )
    {
    }

   virtual ~FavListWindowOf() {}

   // methods

   auto getMinSize() const { return shape.getMinSize(); }

   // drawing

   virtual bool isGoodSize(Point size) const
    {
     return shape.isGoodSize(size);
    }

   virtual void layout()
    {
     shape.pane=getPane();
    }

   virtual void draw(DrawBuf buf,DrawParam draw_param) const
    {
     shape.draw(buf,draw_param);
    }

   // keyboard

   virtual FocusType askFocus() const
    {
     return FocusOk;
    }
 };

/* type FavListWindow */

using FavListWindow = FavListWindowOf<FavListShape> ;

} // namespace Video
} // namespace CCore

#endif

