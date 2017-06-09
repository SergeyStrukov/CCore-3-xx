/* Client.h */
//----------------------------------------------------------------------------------------
//
//  Project: SubLab 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef Client_h
#define Client_h

#include <inc/Application.h>

#include <CCore/inc/video/WindowLib.h>

namespace App {

/* classes */

class AltShape;

class SpaceWindow;

class ClientWindow;

/* class AltShape */

class AltShape
 {
  public:

   struct Config
    {
     RefVal<VColor> border =      Blue ;
     RefVal<VColor> focus  = OrangeRed ;
     RefVal<VColor> gray   =      Gray ;
     RefVal<VColor> snow   =      Snow ;
     RefVal<VColor> snowUp = PaleGreen ;

     // app

     RefVal<Coord> dy = 32 ;

     RefVal<VColor> mark_false    = RGBColor(64,0,0) ;
     RefVal<VColor> mark_true     = RGBColor(0,64,0) ;
     RefVal<VColor> mark_false_on = RGBColor(255,100,100) ;
     RefVal<VColor> mark_true_on  = RGBColor(100,255,100) ;

     Config() noexcept {}

     explicit Config(const UserPreference &pref) noexcept
      {
       bind(pref.get());
      }

     template <class Bag>
     void bind(const Bag &bag)
      {
       border.bind(bag.border);
       focus.bind(bag.focus);
       gray.bind(bag.gray);
       snow.bind(bag.snow);
       snowUp.bind(bag.snowUp);
      }
    };

   const Config &cfg;
   Pane pane;

   // state

   using CheckType = bool ;

   static CheckType Next(CheckType check) { return !check; }

   bool enable     =  true ;
   bool focus      = false ;
   bool mover      = false ;
   CheckType zone  = false ;
   CheckType check = false ;

   // methods

   explicit AltShape(const Config &cfg_,CheckType check_=false) : cfg(cfg_),check(check_) {}

   Point getMinSize() const;

   bool isGoodSize(Point size) const { return size>=getMinSize(); }

   CheckType getZone(Point point) const;

   void draw(const DrawBuf &buf) const;
 };

/* class SpaceWindow */

class SpaceWindow : public SubWindow
 {
  public:

   struct Config
    {
     // app

     RefVal<Coord> space_dxy = 100 ;
     RefVal<Coord> border_dxy = 10 ;

     RefVal<VColor> border = SkyBlue ;

     Config() noexcept {}
    };

   using ConfigType = Config ;

  private:

   const Config &cfg;

   Point space;

   bool drag = false ;
   Point drag_base;
   Point space_base;

  private:

   void startDrag(Point point);

   void dragTo(Point point);

   void endDrag();

   void endDrag(Point point);

  public:

   SpaceWindow(SubWindowHost &host,const ConfigType &cfg);

   virtual ~SpaceWindow();

   // methods

   Point getMinSize() const { return Null; }

   Pane getInner() const { return getPlace().shrink(space); }

   // drawing

   virtual bool isGoodSize(Point size) const;

   virtual void layout();

   virtual void draw(DrawBuf buf,bool drag_active) const;

   // base

   virtual void open();

   // keyboard

   virtual FocusType askFocus() const;

   // mouse

   virtual void looseCapture();

   virtual MouseShape getMouseShape(Point point,KeyMod kmod) const;

   // user input

   virtual void react(UserAction action);

   void react_LeftClick(Point point,MouseKey);

   void react_LeftUp(Point point,MouseKey);

   void react_Move(Point point,MouseKey mkey);

   // signals

   Signal<> changed;
 };

/* class ClientWindow */

class ClientWindow : public ComboWindow
 {
  public:

   struct Config
    {
     RefVal<VColor> back = Silver ;

     RefVal<Coord> space_dxy = 10 ;

     CtorRefVal<CheckWindow::ConfigType> check_cfg;
     CtorRefVal<LabelWindow::ConfigType> label_cfg;
     CtorRefVal<ScrollListWindow::ConfigType> list_cfg;

     // app

     RefVal<VColor> backAlt = Wheat ;

     RefVal<DefString> hint_Text  = "Show SubWindow variety"_def ;

     RefVal<DefString> hint_Wheat = "Check to Wheat the background"_def ;

     RefVal<DefString> hint_List  = "Select some SubWindow type"_def ;

     RefVal<DefString> hint_Space = "Drag here to change the space"_def ;

     CtorRefVal<SpaceWindow::ConfigType> space_cfg;

     Config() noexcept {}

     Config(const UserPreference &pref) noexcept
      {
       bind(pref.get(),pref.getSmartConfig());
      }

     template <class Bag,class Proxy>
     void bind(const Bag &bag,Proxy proxy)
      {
       back.bind(bag.back);
       space_dxy.bind(bag.space_dxy);

       check_cfg.bind(proxy);
       label_cfg.bind(proxy);
       list_cfg.bind(proxy);
      }
    };

   using ConfigType = Config ;

  private:

   const Config &cfg;
   const UserPreference &pref;

   using SubFactory = SubWindow * (*)(SubWindowHost &host,const UserPreference &pref) ;

   class TypeInfo : public ComboInfo
    {
      class Base;

     public:

      TypeInfo();

      ~TypeInfo();

      // methods

      SubFactory getFactory(ulen index) const;
    };

   TypeInfo info;

   CheckWindow check_wheat;
   LabelWindow label_wheat;
   ScrollListWindow list_type;
   SpaceWindow space;

   ulen cur_index = MaxULen ;
   OwnPtr<SubWindow> cur;

  private:

   VColor getBack() const { return check_wheat.isChecked()? +cfg.backAlt : +cfg.back ; }

   void wheat_changed(bool check);

   SignalConnector<ClientWindow,bool> connector_wheat_changed;

   void type_selected(ulen index);

   SignalConnector<ClientWindow,ulen> connector_type_selected;

   void space_changed();

   SignalConnector<ClientWindow> connector_space_changed;

  public:

   ClientWindow(SubWindowHost &host,const Config &cfg,const UserPreference &pref);

   virtual ~ClientWindow();

   // drawing

   virtual void layout();

   virtual void drawBack(DrawBuf buf,bool drag_active) const;

   // base

   virtual void open();
 };

} // namespace App

#endif

