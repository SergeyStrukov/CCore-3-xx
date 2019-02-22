/* EditRatioWindow.h */
//----------------------------------------------------------------------------------------
//
//  Project: ContourLab 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef EditRatioWindow_h
#define EditRatioWindow_h

#include <inc/Geometry.h>

namespace App {

/* classes */

class EditRatioWindow;

/* class EditRatioWindow */

class EditRatioWindow : public SubWindow
 {
  public:

   struct Config
    {
     // user

     RefVal<Fraction> width = Fraction(6,2) ;

     // app

     RefVal<Font> font;

     RefVal<Coord> shade_dxy = 8 ;

     RefVal<VColor> back    =     White ;
     RefVal<VColor> border  =     Black ;
     RefVal<VColor> face    =     Black ;
     RefVal<VColor> gray    =      Gray ;
     RefVal<VColor> text    =      Blue ;
     RefVal<VColor> hilight =     Green ;
     RefVal<VColor> focus   = OrangeRed ;

     RefVal<Coord> dx = 500 ;
     RefVal<Coord> dy = 100 ;

     Config() noexcept {}

     template <class AppPref>
     Config(const UserPreference &pref,const AppPref &app_pref) noexcept
      {
       bindUser(pref.get());
       bindApp(app_pref.get());
      }

     template <class Bag>
     void bindUser(const Bag &bag)
      {
       width.bind(bag.width);
      }

     template <class Bag>
     void bindApp(const Bag &bag)
      {
       font.bind(bag.font.font);
       shade_dxy.bind(bag.shade_dxy);
       back.bind(bag.back);
       border.bind(bag.border);
       face.bind(bag.face);
       gray.bind(bag.gray);
       text.bind(bag.text);
       hilight.bind(bag.hilight);
       focus.bind(bag.focus);

       dx.bind(bag.edit_ratio_dx);
       dy.bind(bag.edit_ratio_dy);
      }
    };

   using ConfigType = Config ;

  private:

   const Config &cfg;

   Geometry::Ratio value;
   Coord a;
   Coord b; // > 0

   bool hilight = false ;
   bool focus = false ;

   Pane pane;
   Pane shade1;
   Pane shade2;
   Point base;
   Pane text;

  private:

   static Coord ToCoord(Geometry::Real x);

   void newValue();

   void pin(Point point);

   void shiftA(Coord delta);

   void shiftB(Coord delta);

  public:

   EditRatioWindow(SubWindowHost &host,const Config &cfg);

   virtual ~EditRatioWindow();

   // methods

   Point getMinSize() const;

   Geometry::Ratio getValue() const { return value; }

   void setValue(Geometry::Ratio value_);

   // drawing

   virtual bool isGoodSize(Point size) const;

   virtual void layout();

   virtual void draw(DrawBuf buf,DrawParam draw_param) const;

   // base

   virtual void open();

   // keyboard

   virtual FocusType askFocus() const;

   virtual void gainFocus();

   virtual void looseFocus();

   // mouse

   virtual MouseShape getMouseShape(Point point,KeyMod kmod) const;

   // user input

   virtual void react(UserAction action);

   void react_Key(VKey vkey,KeyMod kmod,unsigned repeat);

   void react_LeftClick(Point point,MouseKey mkey);

   void react_Move(Point point,MouseKey mkey);

   void react_Leave();

   void react_Wheel(Point,MouseKey mkey,Coord delta);

   // signals

   Signal<Geometry::Ratio> changed;
 };

} // namespace App

#endif
