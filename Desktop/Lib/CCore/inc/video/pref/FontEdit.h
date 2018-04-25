/* FontEdit.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Desktop
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_video_pref_FontEdit_h
#define CCore_inc_video_pref_FontEdit_h

#include <CCore/inc/video/WindowLib.h>

#include <CCore/inc/video/FontParam.h>
#include <CCore/inc/video/FontDatabase.h>
#include <CCore/inc/video/FreeTypeFont.h>

#include <CCore/inc/video/ConfigBinder.h>

namespace CCore {
namespace Video {

/* classes */

class CharTableWindow;

class FontEditWindow;

/* class CharTableWindow */

class CharTableWindow : public SubWindow
 {
  public:

   struct Config
    {
     RefVal<Fraction> width = Fraction(6,2) ;

     RefVal<VColor> text = Black ;

     RefVal<Font> font;

     Config() noexcept {}

     template <class Bag>
     void bind(const Bag &bag)
      {
       width.bind(bag.width);
       text.bind(bag.info_text);
      }
    };

   using ConfigType = Config ;

  private:

   const Config &cfg;

   bool drag = false ;
   Point drag_base;

   Point off;
   Point max_off;

#ifdef CCORE_UTF8

   CharMapHook map;

#endif

  private:

   static Coord Cell(Coord fdy) { return fdy+fdy/4; }

   void startDrag(Point point);

   void dragTo(Point point);

   void endDrag(Point point);

   void endDrag();

  public:

   CharTableWindow(SubWindowHost &host,const Config &cfg);

   virtual ~CharTableWindow();

   // methods

   Point getMinSize() const;

   // drawing

   virtual bool isGoodSize(Point size) const;

   virtual void layout();

   virtual void draw(DrawBuf buf,bool) const;

   // base

   virtual void open();

   // keyboard

   virtual FocusType askFocus() const;

   // mouse

   virtual void looseCapture();

   virtual MouseShape getMouseShape(Point,KeyMod) const;

   // user input

   virtual void react(UserAction action);

   void react_LeftClick(Point point,MouseKey);

   void react_LeftUp(Point point,MouseKey);

   void react_Move(Point point,MouseKey);
 };

/* class FontEditWindow */

class FontEditWindow : public ComboWindow
 {
  public:

   struct Config
    {
     RefVal<Coord> space_dxy = 10 ;
     RefVal<Coord> progress_dy = 24 ;
     RefVal<Coord> check_dxy = 20 ;
     RefVal<Coord> light_dxy = 20 ;

     RefVal<DefString> text_none = "<none>"_def ;

     RefVal<DefString> text_scalable    = "scalable"_def ;
     RefVal<DefString> text_monospace   = "monospace"_def ;
     RefVal<DefString> text_bold        = "bold"_def ;
     RefVal<DefString> text_italic      = "italic"_def ;

     RefVal<DefString> text_Hint = "Hint"_def ;

     RefVal<DefString> text_no_hint     = "No hint"_def ;
     RefVal<DefString> text_native_hint = "Native hint"_def ;
     RefVal<DefString> text_auto_hint   = "Auto hint"_def ;

     RefVal<DefString> text_Smooth = "Smooth"_def ;

     RefVal<DefString> text_no_smooth   = "No smooth"_def ;
     RefVal<DefString> text_smooth      = "Smooth"_def ;
     RefVal<DefString> text_RGB         = "LCD RGB"_def ;
     RefVal<DefString> text_BGR         = "LCD BGR"_def ;

     RefVal<DefString> text_kerning     = "Kerning"_def ;
     RefVal<DefString> text_strength    = "Strength"_def ;
     RefVal<DefString> text_sample      = "sample"_def ;
     RefVal<DefString> text_table       = "table"_def ;

     RefVal<DefString> hint_list          = "Font file list"_def ;
     RefVal<DefString> hint_height        = "Font height"_def ;
     RefVal<DefString> hint_length_enable = "Enable font length"_def ;
     RefVal<DefString> hint_length        = "Font length"_def ;

     CtorRefVal<ProgressWindow::ConfigType> progress_cfg;
     CtorRefVal<ScrollListWindow::ConfigType> list_cfg;
     CtorRefVal<XSplitWindow::ConfigType> split_cfg;
     CtorRefVal<TextWindow::ConfigType> text_cfg;
     CtorRefVal<LightWindow::ConfigType> light_cfg;
     CtorRefVal<RefLabelWindow::ConfigType> label_cfg;
     CtorRefVal<XDoubleLineWindow::ConfigType> dline_cfg;
     CtorRefVal<CheckWindow::ConfigType> check_cfg;
     CtorRefVal<RadioWindow::ConfigType> radio_cfg;
     CtorRefVal<RefTextContourWindow::ConfigType> text_contour_cfg;
     CtorRefVal<ContourWindow::ConfigType> contour_cfg;
     CtorRefVal<SpinorWindow::ConfigType> spin_cfg;
     CtorRefVal<InfoWindow::ConfigType> info_cfg;
     CtorRefVal<CharTableWindow::ConfigType> table_cfg;

     Config() noexcept {}

     template <class Bag,class Proxy>
     void bind(const Bag &bag,Proxy proxy)
      {
       space_dxy.bind(bag.space_dxy);
       progress_dy.bind(bag.progress_dy);
       check_dxy.bind(bag.check_dxy);
       light_dxy.bind(bag.light_dxy);
       text_none.bind(bag.text_none);

       text_scalable.bind(bag.text_cfg_scalable);
       text_monospace.bind(bag.text_cfg_monospace);
       text_bold.bind(bag.text_cfg_bold);
       text_italic.bind(bag.text_cfg_italic);

       text_Hint.bind(bag.text_cfg_Hint);

       text_no_hint.bind(bag.text_cfg_no_hint);
       text_native_hint.bind(bag.text_cfg_native_hint);
       text_auto_hint.bind(bag.text_cfg_auto_hint);

       text_Smooth.bind(bag.text_cfg_Smooth);

       text_no_smooth.bind(bag.text_cfg_no_smooth);
       text_smooth.bind(bag.text_cfg_smooth);
       text_RGB.bind(bag.text_cfg_RGB);
       text_BGR.bind(bag.text_cfg_BGR);

       text_kerning.bind(bag.text_cfg_kerning);
       text_strength.bind(bag.text_cfg_strength);
       text_sample.bind(bag.text_cfg_sample);
       text_table.bind(bag.text_cfg_table);

       hint_list.bind(bag.hint_cfg_font_list);
       hint_height.bind(bag.hint_cfg_height);
       hint_length_enable.bind(bag.hint_cfg_length_enable);
       hint_length.bind(bag.hint_cfg_length);

       progress_cfg.bind(proxy);
       list_cfg.bind(proxy);
       split_cfg.bind(proxy);
       text_cfg.bind(proxy);
       light_cfg.bind(proxy);
       label_cfg.bind(proxy);
       dline_cfg.bind(proxy);
       check_cfg.bind(proxy);
       radio_cfg.bind(proxy);
       text_contour_cfg.bind(proxy);
       contour_cfg.bind(proxy);
       spin_cfg.bind(proxy);
       info_cfg.bind(proxy);
       table_cfg.bind(proxy);
      }
    };

   using ConfigType = Config ;

  private:

   static DefString TestText();

   const Config &cfg;

   Coord def_dy = 20 ;
   FontCouple font;

   ProgressWindow progress;

   class ProgressControl : public IncrementalProgress
    {
      WindowList &wlist;
      ProgressWindow &window;

     public:

      ProgressControl(WindowList &wlist,ProgressWindow &window);

      ~ProgressControl();

      // IncrementalProgress

      virtual void start();

      virtual void setTotal(unsigned total);

      virtual bool setPos(unsigned pos);

      virtual void stop() noexcept;
    };

   ProgressControl progress_control;

   FontDatabase fdb;
   FontDatabase::Incremental fdb_inc;
   bool fdb_flag = true ;

   class FDBInfo : public ComboInfo
    {
      class Base;

     private:

      Base * getBase() const;

     public:

      FDBInfo();

      ~FDBInfo();

      void build(FontDatabase &fdb);

      const FontInfo * get(ulen index) const;

      DefString getFamily(ulen index) const;

      ulen getIndex(StrLen file_name) const;
    };

   FDBInfo info;

   ScrollListWindow list;
   XSplitWindow split;
   TextWindow text_file_name;
   TextWindow text_family;

   LightWindow light_scalable;
   LightWindow light_monospace;
   LightWindow light_bold;
   LightWindow light_italic;

   RefLabelWindow label_scalable;
   RefLabelWindow label_monospace;
   RefLabelWindow label_bold;
   RefLabelWindow label_italic;

   XDoubleLineWindow line1;

   SpinorWindow spin_fdy;
   CheckWindow check_fdx;
   SpinorWindow spin_fdx;

   XDoubleLineWindow line2;

   RadioGroup group_hint;

   RadioWindow radio_no_hint;
   RadioWindow radio_native_hint;
   RadioWindow radio_auto_hint;

   RefLabelWindow label_no_hint;
   RefLabelWindow label_native_hint;
   RefLabelWindow label_auto_hint;

   RefTextContourWindow contour_hint;

   RadioGroup group_smooth;

   RadioWindow radio_no_smooth;
   RadioWindow radio_smooth;
   RadioWindow radio_RGB;
   RadioWindow radio_BGR;

   RefLabelWindow label_no_smooth;
   RefLabelWindow label_smooth;
   RefLabelWindow label_RGB;
   RefLabelWindow label_BGR;

   RefTextContourWindow contour_smooth;

   CheckWindow check_kerning;

   RefLabelWindow label_kerning;

   SpinorWindow spin_strength;

   RefLabelWindow label_strength;

   XDoubleLineWindow line3;

   RadioGroup group_sample;

   RadioWindow radio_sample;
   RadioWindow radio_table;

   RefLabelWindow label_sample;
   RefLabelWindow label_table;

   enum UpdateMask : unsigned { SampleMask = 4 };

   InfoWindow::ConfigType info_cfg;

   InfoWindow info_test;

   CharTableWindow::ConfigType table_cfg;

   CharTableWindow table;

   ContourWindow contour_test;

   Coord min_list_dx = 0 ;
   Coord max_list_dx = 0 ;
   Coord list_split_dx = 0 ;
   bool split_on = false ;

  private:

   static int GetMaxIndex(Font font);

   void updateSample();

   void updateFont();

   void showFont(ulen select);

   void showFont();

   void noSize();

   void setSize();

   void setConfig();

   void setCouple();

  private:

   void split_dragged(Point delta);

   SignalConnector<FontEditWindow,Point> connector_split_dragged;

   void fdb_completed(bool ok);

   SignalConnector<FontEditWindow,bool> connector_fdb_completed;

   void list_selected(ulen select);

   SignalConnector<FontEditWindow,ulen> connector_list_selected;

   void check_fdx_changed(bool enable);

   SignalConnector<FontEditWindow,bool> connector_check_fdx_changed;

   void spin_fdxy_changed(int);

   SignalConnector<FontEditWindow,int> connector_spin_fdy_changed;
   SignalConnector<FontEditWindow,int> connector_spin_fdx_changed;

   void group_hint_changed(int new_id,int old_id);

   SignalConnector<FontEditWindow,int,int> connector_group_hint_changed;

   void group_smooth_changed(int new_id,int old_id);

   SignalConnector<FontEditWindow,int,int> connector_group_smooth_changed;

   void check_kerning_changed(bool check);

   SignalConnector<FontEditWindow,bool> connector_check_kerning_changed;

   void spin_strength_changed(int strength);

   SignalConnector<FontEditWindow,int> connector_spin_strength_changed;

   void group_sample_changed(int new_id,int old_id);

   SignalConnector<FontEditWindow,int,int> connector_group_sample_changed;

  public:

   FontEditWindow(SubWindowHost &host,const ConfigType &cfg);

   virtual ~FontEditWindow();

   // methods

   Point getMinSize(Point cap=Point::Max()) const;

   const FontParam & getParam() const { return font.param; }

   const Font & getFont() const { return font.font; }

   const FontCouple & getCouple() const { return font; }

   void setCouple(const FontCouple &font);

   // drawing

   virtual void layout();

   // base

   virtual void open();

   // signals

   Signal<> changed;
 };

} // namespace Video
} // namespace CCore

#endif
