/* InsWindow.h */
//----------------------------------------------------------------------------------------
//
//  Project: BookLab 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef InsWindow_h
#define InsWindow_h

#include <inc/BookLab.h>

namespace App {

/* classes */

class InsWindow;

class InsFrame;

/* class InsWindow */

class InsWindow : public ComboWindow
 {
  public:

   struct Config
    {
     // user

     RefVal<Coord> space_dxy = 10 ;

     RefVal<VColor> back = Silver ;

     RefVal<String> text_Ok     = "Ok"_str ;
     RefVal<String> text_Cancel = "Cancel"_str ;

     CtorRefVal<LineEditWindow::ConfigType> edit_cfg;
     CtorRefVal<LabelWindow::ConfigType> lab_cfg;
     CtorRefVal<RadioWindow::ConfigType> rad_cfg;
     CtorRefVal<RefButtonWindow::ConfigType> btn_cfg;
     CtorRefVal<XDoubleLineWindow::ConfigType> dline_cfg;

     // app

     template <class AppPref>
     Config(const UserPreference &user_pref,const AppPref &app_pref) noexcept
      {
       bindUser(user_pref.get(),user_pref.getSmartConfig());
       bindApp(app_pref.get());
      }

     template <class Bag,class Proxy>
     void bindUser(const Bag &bag,Proxy proxy)
      {
       back.bind(bag.back);

       space_dxy.bind(bag.space_dxy);

       text_Ok.bind(bag.text_Ok);
       text_Cancel.bind(bag.text_Cancel);

       edit_cfg.bind(proxy);
       lab_cfg.bind(proxy);
       rad_cfg.bind(proxy);
       btn_cfg.bind(proxy);
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

   BookLab::InsData data;

   // subs

   RadioGroup group_place;

   LabelWindow lab_before;
   RadioWindow rad_before;

   LabelWindow lab_after;
   RadioWindow rad_after;

   LabelWindow lab_inside;
   RadioWindow rad_inside;

   LabelWindow lab_text;
   LineEditWindow edit_text;

   RadioGroup group_type;

   LabelWindow lab1;
   RadioWindow rad1;

   LabelWindow lab2;
   RadioWindow rad2;

   LabelWindow lab3;
   RadioWindow rad3;

   LabelWindow lab4;
   RadioWindow rad4;

   LabelWindow lab5;
   RadioWindow rad5;

   LabelWindow lab6;
   RadioWindow rad6;

   LabelWindow lab7;
   RadioWindow rad7;

   LabelWindow lab8;
   RadioWindow rad8;

   LabelWindow lab9;
   RadioWindow rad9;

   LabelWindow lab10;
   RadioWindow rad10;

   LabelWindow lab11;
   RadioWindow rad11;

   LabelWindow lab12;
   RadioWindow rad12;

   LabelWindow lab13;
   RadioWindow rad13;

   LabelWindow lab14;
   RadioWindow rad14;

   LabelWindow lab15;
   RadioWindow rad15;

   LabelWindow lab16;
   RadioWindow rad16;

   LabelWindow lab17;
   RadioWindow rad17;

   LabelWindow lab18;
   RadioWindow rad18;

   LabelWindow lab19;
   RadioWindow rad19;

   XDoubleLineWindow line1;

   RefButtonWindow btn_Ok;
   RefButtonWindow btn_Cancel;

  private:

   void closeOk();

   SignalConnector<InsWindow> connector_Ok_pressed;

   void closeCancel();

   SignalConnector<InsWindow> connector_Cancel_pressed;

   void checkName();

   SignalConnector<InsWindow> connector_text_changed;

   void typeChanged(int new_id,int prev_id);

   SignalConnector<InsWindow,int,int> connector_type_changed;

  public:

   InsWindow(SubWindowHost &host,const Config &cfg);

   virtual ~InsWindow();

   // methods

   Point getMinSize() const;

   void enablePlace(bool all,bool inside,bool extern_flag);

   BookLab::InsData getData() const { return data; }

   // base

   virtual void open();

   // drawing

   virtual void layout();

   virtual void drawBack(DrawBuf buf,DrawParam &draw_param) const;
 };

/* class InsFrame */

class InsFrame : public DragFrame
 {
  public:

   struct Config
    {
     // user

     RefVal<Ratio> pos_ry = Div(5,12) ;

     CtorRefVal<DragFrame::ConfigType> frame_cfg;

     // app

     RefVal<String> title = "Select element"_str ;

     InsWindow::ConfigType client_cfg;

     template <class AppPref>
     Config(const UserPreference &user_pref,const AppPref &app_pref) noexcept
      : client_cfg(user_pref,app_pref)
      {
       bindUser(user_pref.get(),user_pref.getSmartConfig());
       bindApp(app_pref.get());
      }

     template <class Bag,class Proxy>
     void bindUser(const Bag &bag,Proxy proxy)
      {
       pos_ry.bind(bag.frame_pos_ry);

       frame_cfg.bind(proxy);
      }

     template <class Bag>
     void bindApp(const Bag &bag)
      {
       title.bind(bag.ins_title);
      }
    };

   using ConfigType = Config ;

  private:

   const Config &cfg;

   InsWindow client;

   Pane place;
   bool has_place = false ;

  public:

   InsFrame(Desktop *desktop,const Config &cfg,Signal<> &update);

   virtual ~InsFrame();

   // methods

   void enablePlace(bool all,bool inside,bool extern_flag) { client.enablePlace(all,inside,extern_flag); }

   BookLab::InsData getData() const { return client.getData(); }

   // base

   virtual void dying();

   // create

   Pane getPane(StrLen title) const;

   void create(FrameWindow *parent)
    {
     String title=+cfg.title;

     DragFrame::create(parent,getPane(Range(title)),title);
    }
 };

} // namespace App

#endif
