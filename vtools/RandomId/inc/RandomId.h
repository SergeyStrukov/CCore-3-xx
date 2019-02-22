/* RandomId.h */
//----------------------------------------------------------------------------------------
//
//  Project: RandomId 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef RandomId_h
#define RandomId_h

#include <CCore/inc/PlatformRandom.h>

#include <inc/App.h>

namespace App {

/* classes */

class RandomIdWindow;

/* class RandomIdWindow */

class RandomIdWindow : public ComboWindow
 {
  public:

   struct Config
    {
     // user

     RefVal<Coord> space_dxy = 10 ;

     RefVal<VColor> back = Silver ;

     CtorRefVal<RefButtonWindow::ConfigType> btn_cfg;
     CtorRefVal<RadioWindow::ConfigType> radio_cfg;
     CtorRefVal<RefLabelWindow::ConfigType> label_cfg;
     CtorRefVal<ContourWindow::ConfigType> contour_cfg;

     TextLineWindow::ConfigType text_cfg;

     // app

     RefVal<String> text_Unid = "Unid"_str ;
     RefVal<String> text_Raw  = "Raw"_str ;
     RefVal<String> text_Roll = "Roll"_str ;
     RefVal<String> text_Copy = "Copy"_str ;

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
       radio_cfg.bind(proxy);
       label_cfg.bind(proxy);
       contour_cfg.bind(proxy);

       text_cfg=proxy;

       text_cfg.font.bind(bag.code_font.font);
      }

     template <class Bag>
     void bindApp(const Bag &bag)
      {
       text_Unid.bind(bag.text_Unid);
       text_Raw.bind(bag.text_Raw);
       text_Roll.bind(bag.text_Roll);
       text_Copy.bind(bag.text_Copy);
      }
    };

   using ConfigType = Config ;

  private:

   const Config &cfg;

   enum RadioId
    {
     Radio_Unid = 1,
     Radio_Raw  = 2
    };

   RadioGroup group_type;

   RadioWindow radio_Unid;
   RadioWindow radio_Raw;

   RefLabelWindow label_Unid;
   RefLabelWindow label_Raw;

   ContourWindow contour;

   RefButtonWindow btn_Roll;
   RefButtonWindow btn_Copy;

   TextLineWindow text;

   PlatformRandom random;

  private:

   void type_changed(int new_id,int prev_id);

   SignalConnector<RandomIdWindow,int,int> connector_type_changed;

   void rollUnid();

   void rollRaw();

   void roll();

   void copy();

   SignalConnector<RandomIdWindow> connector_btn_Roll_pressed;
   SignalConnector<RandomIdWindow> connector_btn_Copy_pressed;

  public:

   RandomIdWindow(SubWindowHost &host,const Config &cfg);

   virtual ~RandomIdWindow();

   // methods

   Point getMinSize() const;

   // drawing

   virtual void layout();

   virtual void drawBack(DrawBuf buf,DrawParam &draw_param) const;
 };

} // namespace App

#endif
