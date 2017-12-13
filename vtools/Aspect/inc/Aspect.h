/* Aspect.h */
//----------------------------------------------------------------------------------------
//
//  Project: Aspect 1.01
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef Aspect_h
#define Aspect_h

#include <inc/AspectData.h>

namespace App {

/* functions */

MPoint MCenter(Pane pane);

/* classes */

struct Filter;

class HideControl;

class CountControl;

class InnerDataWindow;

class DataWindow;

class AspectWindow;

/* struct Filter */

struct Filter
 {
  bool filter[ItemStatusLim] = {} ;

  bool operator () (ItemStatus status) const
   {
    if( status>=ItemStatusLim ) return true;

    return filter[status];
   }
 };

/* class HideControl */

class HideControl : public ComboWindow
 {
  public:

   struct Config
    {
     // user

     RefVal<Coord> space_dxy = 10 ;

     CtorRefVal<RefLabelWindow::ConfigType> label_cfg;
     CtorRefVal<CheckWindow::ConfigType> check_cfg;
     CtorRefVal<RefButtonWindow::ConfigType> btn_cfg;

     // app

     RefVal<Coord> status_dxy = 30 ;

     RefVal<DefString> text_Hide    = "Hide"_def ;
     RefVal<DefString> text_ShowAll = "Show all"_def ;

     RefVal<VColor> status_New    = SkyBlue ;
     RefVal<VColor> status_Ignore = Gray ;
     RefVal<VColor> status_Red    = Red ;
     RefVal<VColor> status_Yellow = Yellow ;
     RefVal<VColor> status_Green  = Green ;

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

       label_cfg.bind(proxy);
       check_cfg.bind(proxy);
       btn_cfg.bind(proxy);
      }

     template <class Bag>
     void bindApp(const Bag &bag)
      {
       status_dxy.bind(bag.status_dxy);

       text_Hide.bind(bag.text_Hide);
       text_ShowAll.bind(bag.text_ShowAll);

       status_New.bind(bag.status_New);
       status_Ignore.bind(bag.status_Ignore);
       status_Red.bind(bag.status_Red);
       status_Yellow.bind(bag.status_Yellow);
       status_Green.bind(bag.status_Green);
      }
    };

   using ConfigType = Config ;

  private:

   const Config &cfg;

   RefLabelWindow label_Hide;

   CheckWindow check_New;
   CheckWindow check_Ignore;
   CheckWindow check_Red;
   CheckWindow check_Yellow;
   CheckWindow check_Green;

   RefButtonWindow btn_ShowAll;

   Pane place_New;
   Pane place_Ignore;
   Pane place_Red;
   Pane place_Yellow;
   Pane place_Green;

  private:

   static Pane Inner(Pane pane,Coord dxy);

  private:

   void check_changed(bool);

   SignalConnector<HideControl,bool> connector_check_New_changed;
   SignalConnector<HideControl,bool> connector_check_Ignore_changed;
   SignalConnector<HideControl,bool> connector_check_Red_changed;
   SignalConnector<HideControl,bool> connector_check_Yellow_changed;
   SignalConnector<HideControl,bool> connector_check_Green_changed;

   void btn_pressed();

   SignalConnector<HideControl> connector_btn_pressed;

  public:

   HideControl(SubWindowHost &host,const Config &cfg);

   virtual ~HideControl();

   // methods

   Point getMinSize() const;

   bool operator [] (ItemStatus status) const;

   Filter getFilter() const;

   void reset();

   // drawing

   virtual void layout(unsigned flags);

   virtual void drawBack(DrawBuf buf,bool drag_active) const;

   // signals

   Signal<Filter> changed;
 };

/* class CountControl */

class CountControl : public ComboWindow
 {
  public:

   struct Config
    {
     // user

     CtorRefVal<TextLineWindow::ConfigType> text_cfg;

     // app

     RefVal<Coord> status_dxy = 15 ;

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
       Used(bag);

       text_cfg.bind(proxy);
      }

     template <class Bag>
     void bindApp(const Bag &bag)
      {
       status_dxy.bind(bag.count_status_dxy);
      }
    };

   using ConfigType = Config ;

  private:

   const Config &cfg;

   ulen count = 0 ;

   TextLineWindow text;

   Pane place_status;
   VColor color;

  public:

   CountControl(SubWindowHost &host,const Config &cfg,VColor color);

   virtual ~CountControl();

   // methods

   Point getMinSize() const;

   void setCount(ulen count);

   void incCount() { setCount(count+1); }

   void decCount() { if( count ) setCount(count-1); }

   // drawing

   virtual void layout(unsigned flags);

   virtual void drawBack(DrawBuf buf,bool drag_active) const;
 };

/* class InnerDataWindow */

class InnerDataWindow : public SubWindow
 {
  public:

   struct Config
    {
     // user

     RefVal<MCoord> width = Fraction(6,2) ;

     RefVal<VColor> focus = OrangeRed ;

     CtorRefVal<RadioShape::Config> radio_cfg;
     CtorRefVal<KnobShape::Config> knob_cfg;

     // app

     RefVal<Coord> dxy = 30 ;
     RefVal<Coord> rxy = 20 ;
     RefVal<Coord> rin =  2 ;
     RefVal<Coord> kxy = 20 ;

     RefVal<VColor> text = Black ;

     RefVal<VColor> status_New    = SkyBlue ;
     RefVal<VColor> status_Ignore =    Gray ;
     RefVal<VColor> status_Red    =     Red ;
     RefVal<VColor> status_Yellow =  Yellow ;
     RefVal<VColor> status_Green  =   Green ;

     RefVal<VColor> face1 = Black ;
     RefVal<VColor> face2 =  Gray ;
     RefVal<VColor> line  =  Navy ;

     RefVal<Font> font;

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
       width.bind(bag.width);
       focus.bind(bag.focus);

       radio_cfg.bind(proxy);
       knob_cfg.bind(proxy);
      }

     template <class Bag>
     void bindApp(const Bag &bag)
      {
       dxy.bind(bag.item_dxy);
       rxy.bind(bag.item_rxy);
       rin.bind(bag.item_rin);
       kxy.bind(bag.item_kxy);

       text.bind(bag.item_text);

       status_New.bind(bag.status_New);
       status_Ignore.bind(bag.status_Ignore);
       status_Red.bind(bag.status_Red);
       status_Yellow.bind(bag.status_Yellow);
       status_Green.bind(bag.status_Green);

       face1.bind(bag.item_face1);
       face2.bind(bag.item_face2);
       line.bind(bag.item_line);

       font.bind(bag.item_font.font);
      }
    };

   using ConfigType = Config ;

  private:

   const Config &cfg;

   AspectData &data;
   Filter data_filter;

   bool focus = false ;

   ulen off_x = 0 ;
   ulen off_y = 0 ;

   ulen total_x = 0 ;
   ulen total_y = 0 ;

   ulen page_x = 1 ;
   ulen page_y = 1 ;

   enum KnobType
    {
     KnobPlus,
     KnobMinus,
     KnobPlusPlus,
     KnobMinusMinus
    };

   enum PressType
    {
     PressNone = 0,

     PressPlus,
     PressPlusPlus,
     PressMinusMinus,

     PressNew,
     PressIgnore,
     PressRed,
     PressYellow,
     PressGreen
    };

   PressType hilight_type = PressNone ;
   ulen hilight_index = 0 ;

  private:

   void hilightOff();

   void updateList();

   void setMax();

   class DrawItem;

  private:

   void posX(ulen pos);

   void posY(ulen pos);

   SignalConnector<InnerDataWindow,ulen> connector_posX;
   SignalConnector<InnerDataWindow,ulen> connector_posY;

  private:

   static Point BaseX(Point point,ulen off,ulen depth,Coord dxy);

   static Point Base(ulen off,ulen depth,ulen line,Coord dxy);

   void setPosX(ulen pos);

   void addPosX(ulen delta);

   void subPosX(ulen delta);

   void setPosY(ulen pos);

   void addPosY(ulen delta);

   void subPosY(ulen delta);

   struct TestResult
    {
     ulen index;
     Point base;
    };

   TestResult test(const DrawItem &draw,Point point) const;

   void change(ulen index,const ItemData &item,ItemStatus status,bool recursive);

   void press(const DrawItem &draw,ulen index,Point point,bool recursive);

   void hilight(const DrawItem &draw,ulen index,Point point);

  public:

   InnerDataWindow(SubWindowHost &host,const Config &cfg,AspectData &data);

   virtual ~InnerDataWindow();

   // special methods

   bool shortDX() const { return page_x<total_x; }

   bool shortDY() const { return page_y<total_y; }

   template <class W>
   void setScrollXRange(W &window)
    {
     window.setRange(total_x,page_x,off_x);
    }

   template <class W>
   void setScrollYRange(W &window)
    {
     window.setRange(total_y,page_y,off_y);
    }

   void connect(Signal<ulen> &scroll_x,Signal<ulen> &scroll_y)
    {
     connector_posX.connect(scroll_x);
     connector_posY.connect(scroll_y);
    }

   // methods

   Point getMinSize(Point cap=Point::Max()) const;

   void update();

   void update(Filter filter);

   void filter(Filter filter);

   void collect();

   // drawing

   virtual bool isGoodSize(Point size) const;

   virtual void layout(unsigned flags);

   virtual void draw(DrawBuf buf,bool) const;

   // base

   virtual void open();

   // keyboard

   virtual FocusType askFocus() const;

   virtual void gainFocus();

   virtual void looseFocus();

   // mouse

   virtual void looseCapture();

   virtual MouseShape getMouseShape(Point,KeyMod) const;

   // user input

   virtual void react(UserAction action);

   void react_LeftClick(Point point,MouseKey mkey);

   void react_Move(Point point,MouseKey mkey);

   void react_Leave();

   void react_Wheel(Point point,MouseKey mkey,Coord delta);

   // signals

   Signal<ulen> scroll_x;
   Signal<ulen> scroll_y;
   Signal<> update_scroll;
   Signal<ItemStatus,ItemStatus> changed; // prev , status
   Signal<> manychanged;
 };

/* class DataWindow */

class DataWindow : public ScrollableWindow<InnerDataWindow>
 {
  public:

   using Base = ScrollableWindow<InnerDataWindow> ;

   struct Config : Base::Config
    {
     Config() noexcept {}

     template <class AppPref>
     Config(const UserPreference &user_pref,const AppPref &app_pref) noexcept
      : Base::Config(user_pref,app_pref)
      {
       bindUser(user_pref.get(),user_pref.getSmartConfig());
      }

     template <class Bag,class Proxy>
     void bindUser(const Bag &bag,Proxy proxy)
      {
       Used(bag);

       x_cfg.bind(proxy);
       y_cfg.bind(proxy);
      }
    };

   using ConfigType = Config ;

  private:

   void update_scroll();

   SignalConnector<DataWindow> connector_update_scroll;

  public:

   DataWindow(SubWindowHost &host,const Config &cfg,AspectData &data);

   virtual ~DataWindow();

   // methods

   void update();

   void update(Filter filter);

   void filter(Filter filter);

   void collect();

   // signals

   Signal<ItemStatus,ItemStatus> &changed; // prev , status
   Signal<> &manychanged;
 };

/* class AspectWindow */

class AspectWindow : public ComboWindow
 {
  public:

   struct Config
    {
     // user

     RefVal<VColor> back = Silver ;

     RefVal<Coord> space_dxy = 10 ;

     RefVal<DefString> text_Error = "Error"_def ;

     CtorRefVal<RefLabelWindow::ConfigType> label_cfg;
     CtorRefVal<TextLineWindow::ConfigType> text_cfg;
     CtorRefVal<MessageFrame::AlertConfigType> msg_cfg;
     CtorRefVal<XDoubleLineWindow::ConfigType> line_cfg;
     CtorRefVal<RefButtonWindow::ConfigType> btn_cfg;

     // app

     RefVal<DefString> text_Path   = "Path"_def ;
     RefVal<DefString> text_Aspect = "Aspect"_def ;

     RefVal<DefString> text_Nothing = "Nothing to save!"_def ;
     RefVal<DefString> text_Save    = "Save"_def ;

     HideControl::ConfigType hide_cfg;
     CountControl::ConfigType count_cfg;
     DataWindow::ConfigType data_cfg;

     Config() noexcept {}

     template <class AppPref>
     Config(const UserPreference &user_pref,const AppPref &app_pref) noexcept
      : hide_cfg(user_pref,app_pref),
        count_cfg(user_pref,app_pref),
        data_cfg(user_pref,app_pref)
      {
       bindUser(user_pref.get(),user_pref.getSmartConfig());
       bindApp(app_pref.get());
      }

     template <class Bag,class Proxy>
     void bindUser(const Bag &bag,Proxy proxy)
      {
       back.bind(bag.back);
       space_dxy.bind(bag.space_dxy);
       text_Error.bind(bag.text_Error);

       label_cfg.bind(proxy);
       text_cfg.bind(proxy);
       msg_cfg.bind(proxy);
       line_cfg.bind(proxy);
       btn_cfg.bind(proxy);
      }

     template <class Bag>
     void bindApp(const Bag &bag)
      {
       text_Path.bind(bag.text_Path);
       text_Aspect.bind(bag.text_Aspect);
       text_Nothing.bind(bag.text_Nothing);
       text_Save.bind(bag.text_Save);
      }
    };

   using ConfigType = Config ;

  private:

   const Config &cfg;

   AspectData data;

   String aspect_file_name;
   bool has_file = false ;

   const char *open_file_name;

   // subs

   RefLabelWindow label_path;
   RefLabelWindow label_aspect;

   TextLineWindow text_path;
   TextLineWindow text_aspect;

   XDoubleLineWindow line1;

   HideControl hide;

   CountControl count_red;
   CountControl count_yellow;
   CountControl count_green;

   RefButtonWindow btn_save;

   XDoubleLineWindow line2;

   DataWindow data_window;

   // frames

   MessageFrame msg_frame;

  private:

   void setModified() { text_aspect.alert(true); }

   void clearModified() { text_aspect.alert(false); }

   void setAspect(StrLen file_name);

   void clearAspect();

  private:

   void errorMsg(StrLen text);

   void errorMsg(const DefString &text) { errorMsg(text.str()); }

   void msg_destroyed();

   SignalConnector<AspectWindow> connector_msg_destroyed;

   void hide_changed(Filter filter);

   SignalConnector<AspectWindow,Filter> connector_hide_changed;

   void data_changed(ItemStatus prev,ItemStatus status);

   SignalConnector<AspectWindow,ItemStatus,ItemStatus> connector_data_changed;

   void data_manychanged();

   SignalConnector<AspectWindow> connector_data_manychanged;

   void btn_save_pressed();

   SignalConnector<AspectWindow> connector_btn_save_pressed;

  public:

   AspectWindow(SubWindowHost &host,const Config &cfg,const char *open_file_name);

   virtual ~AspectWindow();

   // methods

   Point getMinSize() const;

   bool isModified() const { return text_aspect.isAlerted(); }

   void blank(StrLen path);

   void load(StrLen file_name);

   bool save();

   void save(StrLen file_name);

   void updateCount();

   void update(bool new_data);

   void collect();

   // base

   virtual void open();

   // drawing

   virtual void layout(unsigned flags);

   virtual void drawBack(DrawBuf buf,bool drag_active) const;
 };

} // namespace App

#endif
