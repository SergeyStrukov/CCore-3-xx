/* EditAngleWindow.h */
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

#ifndef EditAngleWindow_h
#define EditAngleWindow_h

#include <inc/Geometry.h>

namespace App {

/* classes */

class EditAngleWindow;

/* class EditAngleWindow */

class EditAngleWindow : public SubWindow
 {
  public:

   struct Config
    {
     RefVal<MCoord> width = Fraction(6,2) ;

     // app

     RefVal<Font> font;

     RefVal<Coord> shade_dxy = 8 ;

     RefVal<MCoord> arrow_size = Fraction(5) ;

     RefVal<VColor> back    =     White ;
     RefVal<VColor> border  =     Black ;
     RefVal<VColor> face    =     Black ;
     RefVal<VColor> gray    =      Gray ;
     RefVal<VColor> text    =      Blue ;
     RefVal<VColor> hilight =     Green ;
     RefVal<VColor> focus   = OrangeRed ;

     RefVal<Coord> dxy = 100 ;

     Config() noexcept {}

     template <class AppPref>
     Config(const UserPreference &pref,const AppPref &app_pref) noexcept
      {
       bind(pref.get());
       bindApp(app_pref.get());
      }

     template <class Bag>
     void bind(const Bag &bag)
      {
       width.bind(bag.width);
      }

     template <class Bag>
     void bindApp(const Bag &bag)
      {
       font.bind(bag.font.font);
       shade_dxy.bind(bag.shade_dxy);
       arrow_size.bind(bag.arrow_size);
       back.bind(bag.back);
       border.bind(bag.border);
       face.bind(bag.face);
       gray.bind(bag.gray);
       text.bind(bag.text);
       hilight.bind(bag.hilight);
       focus.bind(bag.focus);

       dxy.bind(bag.edit_angle_dxy);
      }
    };

   using ConfigType = Config ;

  private:

   const Config &cfg;

   Geometry::Angle value;

   bool hilight = false ;
   bool focus = false ;

   Coord len = 0 ;
   Pane pane;
   Pane shade1;
   Pane shade2;
   Point base;
   Pane text_plus;
   Pane text_minus;

  private:

   void newValue(Geometry::Angle value);

   void pin(Point point);

   void rotate(Coord delta);

  public:

   EditAngleWindow(SubWindowHost &host,const Config &cfg);

   virtual ~EditAngleWindow();

   // methods

   SizeBox getMinSize() const;

   Geometry::Angle getValue() const { return value; }

   void setValue(Geometry::Angle value_)
    {
     if( value_.rex )
       value=Geometry::Angle(0);
     else
       value=value_;

     redraw();
    }

   // drawing

   virtual bool isGoodSize(Point size) const;

   virtual void layout(unsigned flags);

   virtual void draw(DrawBuf buf,bool drag_active) const;

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

   Signal<Geometry::Angle> changed;
 };

} // namespace App

#endif


