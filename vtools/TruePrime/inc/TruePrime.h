/* TruePrime.h */
//----------------------------------------------------------------------------------------
//
//  Project: TruePrime 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef TruePrime_h
#define TruePrime_h

#include <inc/App.h>
#include <inc/PrimeBuilder.h>

namespace App {

/* classes */

class NumberWindow;

class TruePrimeWindow;

/* class NumberWindow */

class NumberWindow : public SubWindow
 {
  public:

   struct Config
    {
     // user

     RefVal<Fraction> width = Fraction(6,2) ;

     RefVal<VColor> back = Silver ;
     RefVal<VColor> gray =   Gray ;
     RefVal<VColor> snow =   Snow ;

     // app

     RefVal<VColor> text = Black ;

     RefVal<Point> space = Point(8,8) ;

     RefVal<Font> font;

     Config() noexcept {}

     template <class AppPref>
     Config(const UserPreference &user_pref,const AppPref &app_pref) noexcept
      {
       bindUser(user_pref.get(),user_pref.getSmartConfig());
       bindApp(app_pref.get());
      }

     template <class Bag,class Proxy>
     void bindUser(const Bag &bag,Proxy)
      {
       width.bind(bag.width);
       back.bind(bag.back);
       gray.bind(bag.gray);
       snow.bind(bag.snow);
      }

     template <class Bag>
     void bindApp(const Bag &bag)
      {
       text.bind(bag.number_text);
       space.bind(bag.number_space);
       font.bind(bag.number_font.font);
      }
    };

   using ConfigType = Config ;

  private:

   const Config &cfg;

   String number;
   unsigned max_span = 8 ;
   unsigned max_line = 8 ;

   // draw

   class Cursor;

   unsigned line = 8 ;
   Point base;
   Point delta;

  public:

   NumberWindow(SubWindowHost &host,const Config &cfg);

   virtual ~NumberWindow();

   // methods

   Point getMinSize() const;

   void setBin(const String &number);

   void setDec(const String &number);

   void setHex(const String &number);

   // drawing

   virtual bool isGoodSize(Point size) const;

   virtual void layout();

   virtual void draw(DrawBuf buf,DrawParam draw_param) const;

   // keyboard

   virtual FocusType askFocus() const;
 };

/* class TruePrimeWindow */

class TruePrimeWindow : public ComboWindow
 {
  public:

   struct Config
    {
     // user

     RefVal<Coord> space_dxy = 10 ;

     RefVal<VColor> back = Silver ;

     CtorRefVal<ButtonWindow::ConfigType> btn_cfg;
     CtorRefVal<RunButtonWindow::ConfigType> run_cfg;
     CtorRefVal<LabelWindow::ConfigType> lab_cfg;
     CtorRefVal<SpinorWindow::ConfigType> spinor_cfg;
     CtorRefVal<RadioWindow::ConfigType> rad_cfg;
     CtorRefVal<LightWindow::ConfigType> light_cfg;
     CtorRefVal<XDoubleLineWindow::ConfigType> dline_cfg;
     CtorRefVal<InfoWindow::ConfigType> info_cfg;
     CtorRefVal<CheckWindow::ConfigType> check_cfg;

     // app

     NumberWindow::ConfigType num_cfg;

     Config() noexcept {}

     template <class AppPref>
     Config(const UserPreference &user_pref,const AppPref &app_pref) noexcept
      : num_cfg(user_pref,app_pref)
      {
       bindUser(user_pref.get(),user_pref.getSmartConfig());
       bindApp(app_pref.get());
      }

     template <class Bag,class Proxy>
     void bindUser(const Bag &bag,Proxy proxy)
      {
       space_dxy.bind(bag.space_dxy);
       back.bind(bag.back);

       btn_cfg.bind(proxy);
       run_cfg.bind(proxy);
       lab_cfg.bind(proxy);
       spinor_cfg.bind(proxy);
       rad_cfg.bind(proxy);
       light_cfg.bind(proxy);
       dline_cfg.bind(proxy);
       info_cfg.bind(proxy);
       check_cfg.bind(proxy);
      }

     template <class Bag>
     void bindApp(const Bag &bag)
      {
       Used(bag);
      }
    };

   using ConfigType = Config ;

  private:

   const Config &cfg;

   PrimeBuilder builder;

   // subs

   LabelWindow lab_nbits;
   SpinorWindow spinor_nbits;

   LabelWindow lab_msbits;
   SpinorWindow spinor_msbits;

   LabelWindow lab_lsbits;
   SpinorWindow spinor_lsbits;

   ButtonWindow btn_gen;
   RunButtonWindow run_test;

   LightWindow light;

   CheckWindow check_para;
   LabelWindow lab_para;

   ButtonWindow btn_copy;

   XDoubleLineWindow line1;

   LabelWindow lab_bin;
   LabelWindow lab_dec;
   LabelWindow lab_hex;

   enum ShowBase
    {
     ShowBin,
     ShowDec,
     ShowHex
    };

   RadioGroup group_base;

   RadioWindow rad_bin;
   RadioWindow rad_dec;
   RadioWindow rad_hex;

   NumberWindow num_win;

   InfoWindow info;

   bool restart = false ;

  private:

   ulen getNBits() const { return (ulen)spinor_nbits.getValue(); }

   ulen getMSBits() const { return (ulen)spinor_msbits.getValue(); }

   ulen getLSBits() const { return (ulen)spinor_lsbits.getValue(); }

   void updateShow();

   void runTest();

   void showStatus(BuilderState state,String text);

   void nbits_changed(int value);

   void msbits_changed(int value);

   void lsbits_changed(int value);

   SignalConnector<TruePrimeWindow,int> connector_nbits_changed;
   SignalConnector<TruePrimeWindow,int> connector_msbits_changed;
   SignalConnector<TruePrimeWindow,int> connector_lsbits_changed;

   void gen_pressed();

   SignalConnector<TruePrimeWindow> connector_gen_pressed;

   void base_changed(int new_id,int prev_id);

   SignalConnector<TruePrimeWindow,int,int> connector_base_changed;

   void test_changed(bool on);

   SignalConnector<TruePrimeWindow,bool> connector_test_changed;

   void copy_pressed();

   SignalConnector<TruePrimeWindow> connector_copy_pressed;

   void wakeup();

   SignalConnector<TruePrimeWindow> connector_wakeup;

  public:

   TruePrimeWindow(SubWindowHost &host,const Config &cfg);

   virtual ~TruePrimeWindow();

   // methods

   Point getMinSize() const;

   // base

   virtual void open();

   // drawing

   virtual void layout();

   virtual void drawBack(DrawBuf buf,DrawParam &draw_param) const;
 };

} // namespace App

#endif
