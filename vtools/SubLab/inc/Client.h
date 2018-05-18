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

class SpaceWindow;

class ClientWindow;

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

