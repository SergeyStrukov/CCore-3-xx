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

     RefVal<VColor> back = Silver ;

     // app

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
       back.bind(bag.back);
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

   String number;
   unsigned max_span = 8 ;
   unsigned max_line = 8 ;

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
     CtorRefVal<XDoubleLineWindow::ConfigType> dline_cfg;

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
       dline_cfg.bind(proxy);
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

  private:

   ulen getNBits() const { return (ulen)spinor_nbits.getValue(); }

   ulen getMSBits() const { return (ulen)spinor_msbits.getValue(); }

   ulen getLSBits() const { return (ulen)spinor_lsbits.getValue(); }

   void updateShow();

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
