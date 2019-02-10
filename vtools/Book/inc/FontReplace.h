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

#include <CCore/inc/video/FrameOf.h>

#include <CCore/inc/CompactMap.h>
#include <CCore/inc/StrKey.h>

namespace App {

/* classes */

class FontReplace;

class FontMapWindow;

class FontSelectWindow;

class FontSelectFrame;

class FontReplaceWindow;

class FontReplaceFrame;

/* class FontReplace */

class FontReplace : NoCopy
 {
   struct Rec
    {
     String str;
     ulen index = 0 ;

     Rec() noexcept {}

     Rec(String str_) : str(str_) {}
    };

   CompactRBTreeMap<StringKey,Rec,StrKey> map;
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

   ulen getCount() const { return map.getCount(); }

   StrLen operator () (StrLen face) const;

   void addNotFound(StrLen face);

   void load() noexcept;

   void save() const noexcept;

   bool testModified() { return Change(modified,false); }

   struct FindResult
    {
     StrLen str;
     ulen index = MaxULen ;
    };

   FindResult find(StrLen face) const;

   void del(StrLen face);

   ulen set(StrLen face,String replace); // MaxULen if new

   template <FuncArgType<StrLen,StrLen,ulen &> Func>
   void apply(Func func)
    {
     map.applyIncr( [&] (const StringKey &key,Rec &rec) { func(Range(key.str),Range(rec.str),rec.index); } );
    }
 };

/* class FontMapWindow */

class FontMapWindow : public ScrollListWindow
 {
   FontReplace &replace;

  private:

   struct Rec
    {
     String text;
     ulen face;
     ulen replace;

     Rec(const String &text_,ulen face_,ulen replace_) : text(text_),face(face_),replace(replace_) {}

     ComboInfoItem item() const { return {ComboInfoText,Range(text)}; }

     StrLen getFace() const { return Range(text).prefix(face); }

     StrLen getReplace() const { return Range(text).suffix(replace); }

     void update(StrLen replace);
    };

   class InfoBase : public ComboInfoBase
    {
      DynArray<Rec> list;

     private:

      void add(StrLen face,StrLen replace);

     public:

      InfoBase() noexcept;

      explicit InfoBase(FontReplace &replace);

      virtual ~InfoBase();

      // AbstractComboInfo

      virtual ulen getLineCount() const;

      virtual ComboInfoItem getLine(ulen index) const;

      // methods

      Rec get(ulen index) const;

      void update(ulen index,StrLen replace);
    };

   class Info : public ComboInfo
    {
     public:

      Info();

      explicit Info(FontReplace &replace);

      ~Info();

      // methods

      Rec get(ulen index) const;

      void update(ulen index,StrLen replace);
    };

   Info info;

  private:

   void updatePreserve();

   void set(ulen index);

   SignalConnector<FontMapWindow,ulen> connector_selected;

  public:

   FontMapWindow(SubWindowHost &host,const Config &cfg,FontReplace &replace);

   virtual ~FontMapWindow();

   // methods

   bool testModified() { return replace.testModified(); }

   void update();

   void save() { replace.save(); }

   StrLen find(StrLen face);

   void del(StrLen face);

   void set(StrLen face,String replace);

   // signals

   Signal<StrLen,StrLen> selected; // face , replace
 };

/* class FontSelectWindow */

class FontSelectWindow : public ComboWindow
 {
  public:

   struct FrameConfigApp
    {
     RefVal<String> title = "Font selection"_str ;

     template <class Bag>
     void bindApp(const Bag &bag)
      {
       title.bind(bag.font_selection_title);
      }
    };

   struct Config
    {
     // user

     RefVal<Coord> space_dxy = 10 ;

     RefVal<VColor> back = Silver ;

     CtorRefVal<RefButtonWindow::ConfigType> btn_cfg;
     CtorRefVal<FontEditWindow::ConfigType> fontedit_cfg;

     // app

     RefVal<String> text_Select = "Select"_str ;

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
       fontedit_cfg.bind(proxy);
      }

     template <class Bag>
     void bindApp(const Bag &bag)
      {
       text_Select.bind(bag.text_Select);
      }
    };

   using ConfigType = Config ;

  private:

   const Config &cfg;

   RefButtonWindow btn_select;
   FontEditWindow fontedit;

  private:

   void selectFont();

   SignalConnector<FontSelectWindow> btn_pressed;

  public:

   FontSelectWindow(SubWindowHost &host,const Config &cfg);

   virtual ~FontSelectWindow();

   // methods

   Point getMinSize() const;

   // drawing

   virtual void layout();

   virtual void drawBack(DrawBuf buf,bool drag_active) const;

   // user input

   virtual void react(UserAction action);

   // signals

   Signal<StrLen> selected;
 };

/* class FontSelectFrame */

class FontSelectFrame : public FrameOf<FontSelectWindow>
 {
  public:

   FontSelectFrame(Desktop *desktop,const Config &cfg,Signal<> &update);

   virtual ~FontSelectFrame();

   // signals

   Signal<StrLen> &selected;
 };

/* class FontReplaceWindow */

class FontReplaceWindow : public ComboWindow
 {
  public:

   struct FrameConfigApp
    {
     RefVal<String> title = "Font replace"_str ;

     template <class Bag>
     void bindApp(const Bag &bag)
      {
       title.bind(bag.replace_title);
      }
    };

   struct Config
    {
     // user

     RefVal<Coord> space_dxy = 10 ;

     RefVal<VColor> back = Silver ;

     CtorRefVal<RefButtonWindow::ConfigType> btn_cfg;
     CtorRefVal<KnobWindow::ConfigType> knob_cfg;
     CtorRefVal<LineEditWindow::ConfigType> edit_cfg;
     CtorRefVal<FontMapWindow::ConfigType> map_cfg;

     // app

     RefVal<String> text_Find    = "Find"_str ;
     RefVal<String> text_Replace = "Replace"_str ;
     RefVal<String> text_Save    = "Save"_str ;
     RefVal<String> text_Apply   = "Apply"_str ;

     CtorRefVal<FontSelectFrame::ConfigType> select_cfg;

     template <class AppPref>
     Config(const UserPreference &user_pref,const AppPref &app_pref) noexcept
      : select_cfg(user_pref,app_pref)
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
       map_cfg.bind(proxy);
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
   KnobWindow knob_font;

   FontMapWindow map;

   RefButtonWindow btn_save;
   RefButtonWindow btn_apply;

   CacheText<LineEditWindow> cache_face;

   FontSelectFrame select_frame;

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

   void openFont();

   SignalConnector<FontReplaceWindow> connector_font_pressed;

   void fontSelected(StrLen replace);

   SignalConnector<FontReplaceWindow,StrLen> connector_font_selected;

  public:

   FontReplaceWindow(SubWindowHost &host,const Config &cfg,FontReplace &replace,Signal<> &update);

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

class FontReplaceFrame : public FrameOf<FontReplaceWindow>
 {
  public:

   FontReplaceFrame(Desktop *desktop,const Config &cfg,FontReplace &replace,Signal<> &update);

   virtual ~FontReplaceFrame();

   // methods

   void update() { client.update(); }

   // signals

   Signal<> &apply;
 };

} // namespace App

#endif

