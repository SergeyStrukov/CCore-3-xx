/* FieldEditor.h */
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

#ifndef FieldEditor_h
#define FieldEditor_h

#include <inc/BookLab.h>

namespace App {

/* classes */

struct FieldControl;

class FieldBool;

class FieldCoord;

class FieldString;

class FieldULen;

class FieldColor;

class FieldStrength;

class FieldAlign;

class FieldEffect;

class FieldPoint;

class FieldRatio;


class FieldWindow;

class FieldFrame;

/* struct FieldControl */

struct FieldControl
 {
  virtual void set(bool *def_pad,bool def) = 0 ;

  virtual void noField() = 0 ;
 };

/* class FieldBool */

class FieldBool : public ComboWindow , public FieldControl
 {
  public:

   struct Config
    {
     // user

     RefVal<Coord> space_dxy = 10 ;

     CtorRefVal<CheckWindow::ConfigType> check_cfg;
     CtorRefVal<LabelWindow::ConfigType> lab_cfg;

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
       space_dxy.bind(bag.space_dxy);

       check_cfg.bind(proxy);
       lab_cfg.bind(proxy);
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

   bool * pad = 0 ;

   // subs

   CheckWindow check_true;
   LabelWindow lab_true;

  public:

   FieldBool(SubWindowHost &host,const Config &cfg);

   virtual ~FieldBool();

   // methods

   Point getMinSize() const;

   void setField(bool *pad);

   virtual void set(bool *def_pad,bool def);

   virtual void noField();

   // drawing

   virtual void layout();
 };

/* class FieldWindow */

class FieldWindow : public ComboWindow
 {
  public:

   struct Config
    {
     // user

     RefVal<Coord> space_dxy = 10 ;

     RefVal<VColor> back = Silver ;

     CtorRefVal<ButtonWindow::ConfigType> btn_cfg;
     CtorRefVal<CheckWindow::ConfigType> check_cfg;
     CtorRefVal<LabelWindow::ConfigType> lab_cfg;

     // app

     CtorRefVal<FieldBool::ConfigType> field_bool_cfg;

     template <class AppPref>
     Config(const UserPreference &user_pref,const AppPref &app_pref) noexcept
      : field_bool_cfg(user_pref,app_pref)
      {
       bindUser(user_pref.get(),user_pref.getSmartConfig());
       bindApp(app_pref.get());
      }

     template <class Bag,class Proxy>
     void bindUser(const Bag &bag,Proxy proxy)
      {
       back.bind(bag.back);
       space_dxy.bind(bag.space_dxy);

       btn_cfg.bind(proxy);
       check_cfg.bind(proxy);
       lab_cfg.bind(proxy);
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

   BookLab::Book &book;

   bool * def_pad = 0 ;
   FieldControl * field_ctrl = 0 ;
   SubWindow * field = 0 ;

   // subs

   ButtonWindow btn_set;
   CheckWindow check_def;
   LabelWindow lab_def;

   // fields

   FieldBool field_bool;

  private:

   void noField();

   void setFieldCtrl(FieldControl *field_ctrl,SubWindow *field,bool withdef);

   template <class W,class T>
   void setFieldCtrl(W &sub,T *pad);

   template <class W,class T>
   void setFieldCtrl(W &sub,BookLab::OptDataBase<T> *pad);


   template <class T>
   void setField(T *) { noField(); }

   void setField(bool *pad);

   void setField(BookLab::OptDataBase<bool> *pad);

  private:

   void set_pressed();

   SignalConnector<FieldWindow> connector_set_pressed;

  public:

   FieldWindow(SubWindowHost &host,const Config &cfg,BookLab::Book &book);

   virtual ~FieldWindow();

   // methods

   Point getMinSize() const;

   void setField(BookLab::PadType pad);

   // drawing

   virtual void layout();

   virtual void drawBack(DrawBuf buf,bool drag_active) const;

   // signals

   Signal<> modified;
 };

/* class FieldFrame */

class FieldFrame : public DragFrame
 {
  public:

   struct Config
    {
     // user

     RefVal<Ratio> pos_ry = Div(5,12) ;

     CtorRefVal<DragFrame::ConfigType> frame_cfg;

     // app

     RefVal<DefString> title = "Edit field"_def ;

     FieldWindow::ConfigType client_cfg;

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
       title.bind(bag.field_title);
      }
    };

   using ConfigType = Config ;

  private:

   const Config &cfg;

   FieldWindow client;

   Pane place;
   bool has_place = false ;

  public:

   FieldFrame(Desktop *desktop,const Config &cfg,BookLab::Book &book,Signal<> &update);

   virtual ~FieldFrame();

   // methods

   void setField(BookLab::PadType pad) { client.setField(pad); }

   // base

   virtual void dying();

   // create

   Pane getPane(StrLen title) const;

   void create(FrameWindow *parent)
    {
     DefString title=+cfg.title;

     DragFrame::create(parent,getPane(title.str()),title);
    }

   // signals

   Signal<> &modified;
 };

} // namespace App

#endif

