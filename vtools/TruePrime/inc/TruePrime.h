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

class TruePrimeWindow;

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

     // app


     Config() noexcept {}

     template <class AppPref>
     Config(const UserPreference &user_pref,const AppPref &app_pref) noexcept
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

   BlankWindow blank;

   template <class ... WW> class LayMax;

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
