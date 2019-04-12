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

     RefVal<VColor> text        =  Black ;
     RefVal<VColor> text_select = Yellow ;

     RefVal<VColor> section_text = White ;
     RefVal<VColor> section_back = Black ;

     RefVal<Point> space = Point(8,8) ;

     RefVal<Font> font;

     Config() noexcept {}

     template <class Bag>
     void bind(const Bag &bag) // TODO
      {
       width.bind(bag.width);
       border.bind(bag.border);
       focus.bind(bag.focus);
       gray.bind(bag.gray);

       // text
       // text_select
       // section_text
       // section_back
       // font

       font.bind(bag.list_font.font);
      }
    };

   // parameters

   const Config &cfg;
   FavList fav_list;
   Pane pane;

   // state

   bool focus = false ;

   // methods

   explicit FavListShape(const Config &cfg_) : cfg(cfg_) {}

   Point getMinSize() const;

   bool isGoodSize(Point size) const { return size>=getMinSize(); }

   void layout();

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

   bool load(StrLen file_name)
    {
     bool ret;

     try
       {
        ret=shape.fav_list.load(file_name);
       }
     catch(...)
       {
        ret=false;
       }

     layout();

     redraw();

     return ret;
    }

   void save(StrLen file_name) const
    {
     shape.fav_list.save(file_name);
    }

   bool load(StrLen key,StrLen file) noexcept
    {
     bool ret=shape.fav_list.load(key,file);

     layout();

     redraw();

     return ret;
    }

   void save(StrLen key,StrLen file) const noexcept
    {
     shape.fav_list.save(key,file);
    }

   // drawing

   virtual bool isGoodSize(Point size) const
    {
     return shape.isGoodSize(size);
    }

   virtual void layout()
    {
     shape.pane=getPane();

     shape.layout();
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

   virtual void gainFocus()
    {
     if( Change(shape.focus,true) ) redraw();
    }

   virtual void looseFocus()
    {
     if( Change(shape.focus,false) ) redraw();
    }

   // user input

   virtual void react(UserAction action)
    {
     action.dispatch(*this);
    }

   void react_Key(VKey vkey,KeyMod kmod)
    {
     switch( vkey )
       {
        case VKey_Up :
         {
          if( kmod&KeyMod_Shift )
            {
             if( shape.fav_list.offUp() ) redraw();
            }
          else
            {
             if( shape.fav_list.curUp() ) redraw();
            }
         }
        break;

        case VKey_Down :
         {
          if( kmod&KeyMod_Shift )
            {
             if( shape.fav_list.offDown() ) redraw();
            }
          else
            {
             if( shape.fav_list.curDown() ) redraw();
            }
         }
        break;
       }
    }
 };

/* type FavListWindow */

using FavListWindow = FavListWindowOf<FavListShape> ;

} // namespace Video
} // namespace CCore

#endif

