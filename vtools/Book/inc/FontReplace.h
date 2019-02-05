/* FontReplace.h */
//----------------------------------------------------------------------------------------
//
//  Project: Book 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef FontReplace_h
#define FontReplace_h

#include <inc/Book.h>

#include <CCore/inc/CompactMap.h>
#include <CCore/inc/StrKey.h>

namespace App {

/* classes */

class FontReplace;

class FontMapWindow;

class FontReplaceWindow;

class FontReplaceFrame;

/* class FontReplace */

class FontReplace : NoCopy
 {
   CompactRBTreeMap<StringKey,String,StrKey> map;
   bool modified = false ;

  private:

   static StrLen ReplaceFile();

   static StrLen Pretext();

   void loadDDL(StrLen file_name);

   void saveDDL(StrLen file_name) const;

   void load(StrLen dir,StrLen file);

   void save(StrLen dir,StrLen file) const;

   void add(StrLen face,StrLen replace);

  public:

   FontReplace();

   ~FontReplace();

   StrLen operator () (StrLen face) const;

   void addNotFound(StrLen face);

   void load() noexcept;

   void save() const noexcept;

   bool testModified() { return Change(modified,false); }

   StrLen find(StrLen face) const;

   void del(StrLen face);

   void set(StrLen face,String replace);
 };

/* class FontMapWindow */

class FontMapWindow : public SubWindow
 {
  public:

   struct Config
    {
     // user

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
       Used(bag);
       Used(proxy);
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

   FontReplace &replace;

  public:

   FontMapWindow(SubWindowHost &host,const Config &cfg,FontReplace &replace);

   virtual ~FontMapWindow();

   // methods

   Point getMinSize() const;

   bool testModified() { return replace.testModified(); }

   void update();

   void save() { replace.save(); }

   StrLen find(StrLen face);

   void del(StrLen face);

   void set(StrLen face,String replace);

   // drawing

   virtual void layout();

   virtual void draw(DrawBuf buf,bool drag_active) const;

   // keyboard

   virtual void gainFocus();

   virtual void looseFocus();

   // user input

   virtual void react(UserAction action);

   void react_Key(VKey vkey,KeyMod kmod,unsigned repeat);

   void react_LeftClick(Point point,MouseKey mkey);

   void react_Wheel(Point point,MouseKey mkey,Coord delta);

   // signals

   Signal<StrLen,StrLen> selected;
 };

/* class FontReplaceWindow */

class FontReplaceWindow : public ComboWindow
 {
  public:

   struct Config
    {
     // user

     RefVal<Coord> space_dxy = 10 ;

     RefVal<VColor> back = Silver ;

     CtorRefVal<RefButtonWindow::ConfigType> btn_cfg;
     CtorRefVal<KnobWindow::ConfigType> knob_cfg;
     CtorRefVal<LineEditWindow::ConfigType> edit_cfg;

     // app

     RefVal<DefString> text_Find    = "Find"_def ;
     RefVal<DefString> text_Replace = "Replace"_def ;
     RefVal<DefString> text_Save    = "Save"_def ;
     RefVal<DefString> text_Apply   = "Apply"_def ;

     FontMapWindow::ConfigType map_cfg;

     template <class AppPref>
     Config(const UserPreference &user_pref,const AppPref &app_pref) noexcept
      : map_cfg(user_pref,app_pref)
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
       knob_cfg.bind(proxy);
       edit_cfg.bind(proxy);
      }

     template <class Bag>
     void bindApp(const Bag &bag)
      {
       text_Find.bind(bag.text_Find);
       text_Replace.bind(bag.text_Replace);
       text_Save.bind(bag.text_Save);
       text_Apply.bind(bag.text_Apply);
      }
    };

   using ConfigType = Config ;

  private:

   const Config &cfg;

   RefButtonWindow btn_find;
   LineEditWindow edit_face;
   KnobWindow knob_del;

   RefButtonWindow btn_replace;
   LineEditWindow edit_replace;

   FontMapWindow map;

   RefButtonWindow btn_save;
   RefButtonWindow btn_apply;

   CacheText<LineEditWindow> cache_face;

  private:

   void findFace();

   void delEntry();

   void replaceFace();

   void saveMap();

   void applyMap();

   SignalConnector<FontReplaceWindow> connector_find_pressed;
   SignalConnector<FontReplaceWindow> connector_del_pressed;
   SignalConnector<FontReplaceWindow> connector_replace_pressed;
   SignalConnector<FontReplaceWindow> connector_save_pressed;
   SignalConnector<FontReplaceWindow> connector_apply_pressed;

   void setEdit(StrLen face,StrLen replace);

   SignalConnector<FontReplaceWindow,StrLen,StrLen> connector_map_selected;

  public:

   FontReplaceWindow(SubWindowHost &host,const Config &cfg,FontReplace &replace);

   virtual ~FontReplaceWindow();

   // methods

   Point getMinSize() const;

   void update();

   // drawing

   virtual void layout();

   virtual void drawBack(DrawBuf buf,bool drag_active) const;

   // user input

   virtual void react(UserAction action);

   // signals

   Signal<> apply;
 };

/* class FontReplaceFrame */

class FontReplaceFrame : public DragFrame
 {
  public:

   struct Config
    {
     // user

     RefVal<Ratio> pos_ry = Div(5,12) ;

     CtorRefVal<DragFrame::ConfigType> frame_cfg;

     // app

     RefVal<DefString> title = "Font replace"_def ;

     FontReplaceWindow::ConfigType client_cfg;

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
       title.bind(bag.replace_title);
      }
    };

   using ConfigType = Config ;

  private:

   const Config &cfg;

   FontReplaceWindow client;

   struct FramePlace
    {
     Pane place;
     bool ok = false ;

     void set(Pane pane)
      {
       place=pane;
       ok=true;
      }
    };

   FramePlace place;

  public:

   FontReplaceFrame(Desktop *desktop,const Config &cfg,FontReplace &replace,Signal<> &update);

   virtual ~FontReplaceFrame();

   // methods

   void update() { client.update(); }

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

   Signal<> &apply;
 };

} // namespace App

#endif

