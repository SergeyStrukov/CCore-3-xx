/* ConfigEditor.h */
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

#ifndef CCore_inc_video_ConfigEditor_h
#define CCore_inc_video_ConfigEditor_h

#include <CCore/inc/video/WindowLib.h>

#include <CCore/inc/video/pref/CoordEdit.h>
#include <CCore/inc/video/pref/MCoordEdit.h>
#include <CCore/inc/video/pref/PointEdit.h>
#include <CCore/inc/video/pref/RatioEdit.h>
#include <CCore/inc/video/pref/ColorEdit.h>
#include <CCore/inc/video/pref/FontEdit.h>

namespace CCore {
namespace Video {

/* classes */

class ConfigEditorWindow;

class ConfigEditorFrame;

/* class ConfigEditorWindow */

class ConfigEditorWindow : public ComboWindow
 {
  public:

   struct Config
    {
     RefVal<Coord> space_dxy = 10 ;

     RefVal<VColor> back = Silver ;

     RefVal<DefString> text_all      =         "All"_def ;
     RefVal<DefString> text_Coord    =        "size"_def ;
     RefVal<DefString> text_MCoord   =  "milli-size"_def ;
     RefVal<DefString> text_VColor   =       "color"_def ;
     RefVal<DefString> text_Clr      = "color pitch"_def ;
     RefVal<DefString> text_unsigned =       "count"_def ;
     RefVal<DefString> text_String   =        "text"_def ;
     RefVal<DefString> text_Point    =       "point"_def ;
     RefVal<DefString> text_Font     =        "font"_def ;
     RefVal<DefString> text_bool     =        "bool"_def ;
     RefVal<DefString> text_Ratio    =       "ratio"_def ;

     RefVal<DefString> text_Set  =           "Set"_def ;
     RefVal<DefString> text_Back =          "Back"_def ;
     RefVal<DefString> text_Save =          "Save"_def ;
     RefVal<DefString> text_Self = "Apply to self"_def ;

     RefVal<DefString> hint_list = "Configuration parameters list"_def ;

     RefVal<DefString> hint_Set  = "Set the parameter"_def ;
     RefVal<DefString> hint_Back = "Revert back the parameter"_def ;
     RefVal<DefString> hint_Save = "Save the current settings"_def ;
     RefVal<DefString> hint_Self = "Apply parameters to this window"_def ;

     CtorRefVal<ScrollListWindow::ConfigType> list_cfg;
     CtorRefVal<CheckWindow::ConfigType> check_cfg;
     CtorRefVal<RefLabelWindow::ConfigType> label_cfg;
     CtorRefVal<RefButtonWindow::ConfigType> btn_cfg;
     CtorRefVal<LineEditWindow::ConfigType> edit_cfg;
     CtorRefVal<XSplitWindow::ConfigType> split_cfg;

     CtorRefVal<SpinorWindow::ConfigType> spinor_cfg;
     CtorRefVal<CoordEditWindow::ConfigType> coord_cfg;
     CtorRefVal<MCoordEditWindow::ConfigType> mcoord_cfg;
     CtorRefVal<PointEditWindow::ConfigType> point_cfg;
     CtorRefVal<RatioEditWindow::ConfigType> ratio_cfg;
     CtorRefVal<ColorEditWindow::ConfigType> color_cfg;
     CtorRefVal<FontEditWindow::ConfigType> font_cfg;

     Config() noexcept {}

     template <class Bag,class Proxy>
     void bind(const Bag &bag,Proxy proxy)
      {
       space_dxy.bind(bag.space_dxy);
       back.bind(bag.back);

       text_all.bind(bag.text_cfg_all);
       text_Coord.bind(bag.text_cfg_Coord);
       text_MCoord.bind(bag.text_cfg_MCoord);
       text_VColor.bind(bag.text_cfg_VColor);
       text_Clr.bind(bag.text_cfg_Clr);
       text_unsigned.bind(bag.text_cfg_unsigned);
       text_String.bind(bag.text_cfg_String);
       text_Point.bind(bag.text_cfg_Point);
       text_Font.bind(bag.text_cfg_Font);
       text_bool.bind(bag.text_cfg_bool);
       text_Ratio.bind(bag.text_cfg_Ratio);

       text_Set.bind(bag.text_cfg_Set);
       text_Back.bind(bag.text_cfg_Back);
       text_Save.bind(bag.text_cfg_Save);
       text_Self.bind(bag.text_cfg_Self);

       hint_list.bind(bag.hint_cfg_list);
       hint_Set.bind(bag.hint_cfg_Set);
       hint_Back.bind(bag.hint_cfg_Back);
       hint_Save.bind(bag.hint_cfg_Save);
       hint_Self.bind(bag.hint_cfg_Self);

       list_cfg.bind(proxy);
       check_cfg.bind(proxy);
       label_cfg.bind(proxy);
       btn_cfg.bind(proxy);
       edit_cfg.bind(proxy);
       split_cfg.bind(proxy);

       spinor_cfg.bind(proxy);
       coord_cfg.bind(proxy);
       mcoord_cfg.bind(proxy);
       point_cfg.bind(proxy);
       ratio_cfg.bind(proxy);
       color_cfg.bind(proxy);
       font_cfg.bind(proxy);
      }
    };

   using ConfigType = Config ;

  private:

   const Config &cfg;

   bool use_self;

   ScrollListWindow item_list;

   CheckWindow check_all;
   CheckWindow check_Coord;
   CheckWindow check_MCoord;
   CheckWindow check_VColor;
   CheckWindow check_Clr;
   CheckWindow check_unsigned;
   CheckWindow check_String;
   CheckWindow check_Point;
   CheckWindow check_Font;
   CheckWindow check_bool;
   CheckWindow check_Ratio;

   RefLabelWindow label_all;
   RefLabelWindow label_Coord;
   RefLabelWindow label_MCoord;
   RefLabelWindow label_VColor;
   RefLabelWindow label_Clr;
   RefLabelWindow label_unsigned;
   RefLabelWindow label_String;
   RefLabelWindow label_Point;
   RefLabelWindow label_Font;
   RefLabelWindow label_bool;
   RefLabelWindow label_Ratio;

   RefButtonWindow btn_Set;
   RefButtonWindow btn_Back;
   RefButtonWindow btn_Save;
   RefButtonWindow btn_Self;

   Coord min_list_dx = 0 ;
   Coord max_list_dx = 0 ;
   Coord list_split_dx = 0 ;
   bool split_on = false ;

   XSplitWindow split;

   class PrefInfo : public ComboInfo
    {
      class Base;

     private:

      Base * getBase();

     public:

      PrefInfo();

      ~PrefInfo();

      class Binder;

      Binder getBinder();

      bool enable_all(bool on);

      bool enable_Coord(bool on);

      bool enable_MCoord(bool on);

      bool enable_VColor(bool on);

      bool enable_Clr(bool on);

      bool enable_unsigned(bool on);

      bool enable_String(bool on);

      bool enable_Point(bool on);

      bool enable_Font(bool on);

      bool enable_bool(bool on);

      bool enable_Ratio(bool on);

      template <class Func>
      void select(ulen index,Func func);
    };

   PrefInfo info;

   struct BackSet
    {
     virtual bool back()=0;

     virtual void set()=0;
    };

   template <class T>
   class BackPadBase : public NoCopyBase<BackSet>
    {
      T *var = 0 ;
      T backup;
      bool flag = false ;

     private:

      virtual void propagate(T val)=0;

     public:

      BackPadBase() : backup{} {}

      T * operator + () const { return var; }

      void bind(T &var_)
       {
        var=&var_;
        flag=false;

        propagate(var_);
       }

      bool update(T val)
       {
        if( var )
          {
           if( !flag )
             {
              backup=*var;

              flag=true;
             }

           *var=val;

           return true;
          }

        return false;
       }

      virtual bool back()
       {
        if( var && flag )
          {
           *var=backup;

           propagate(backup);

           flag=false;

           return true;
          }

        flag=false;

        return false;
       }

      virtual void set()
       {
        flag=false;
       }
    };

   template <class T,class E,class S,void (E::*Set)(S val)>
   class BackPad : public BackPadBase<T>
    {
      E &editor;

     private:

      virtual void propagate(T val)
       {
        (editor.*Set)((S)val);
       }

     public:

      explicit BackPad(E &editor_) : editor(editor_) {}
    };

   class BackPad_string : public BackPadBase<DefString>
    {
      LineEditWindow &editor;

     private:

      virtual void propagate(DefString val)
       {
        editor.setText(val.str());
       }

     public:

      explicit BackPad_string(LineEditWindow &editor_) : editor(editor_) {}
    };

   LineEditWindow string_edit;
   BackPad_string string_pad;

   CoordEditWindow coord_edit;
   BackPad<Coord,CoordEditWindow,Coord,&CoordEditWindow::setCoord> coord_pad;

   MCoordEditWindow mcoord_edit;
   BackPad<MCoord,MCoordEditWindow,MCoord,&MCoordEditWindow::setMCoord> mcoord_pad;

   FontEditWindow font_edit;
   BackPad<FontCouple,FontEditWindow,const FontCouple &,&FontEditWindow::setCouple> font_pad;

   SpinorWindow unsigned_edit;
   BackPad<unsigned,SpinorWindow,int,&SpinorWindow::setValue> unsigned_pad;

   SpinorWindow clr_edit;
   BackPad<Clr,SpinorWindow,int,&SpinorWindow::setValue> clr_pad;

   PointEditWindow point_edit;
   BackPad<Point,PointEditWindow,Point,&PointEditWindow::setPoint> point_pad;

   ColorEditWindow color_edit;
   BackPad<VColor,ColorEditWindow,VColor,&ColorEditWindow::setColor> color_pad;

   CheckWindow bool_edit;
   BackPad<bool,CheckWindow,bool,&CheckWindow::check> bool_pad;

   RatioEditWindow ratio_edit;
   BackPad<Ratio,RatioEditWindow,Ratio,&RatioEditWindow::setRatio> ratio_pad;

   SubWindow *active_editor = 0 ;
   BackSet *active_backset = 0 ;

  private:

   void switchTo(SubWindow *editor,BackSet *backset=0);

   void switchTo(SubWindow &editor) { switchTo(&editor); }

   void switchTo(SubWindow &editor,BackSet &backset) { switchTo(&editor,&backset); }

  private:

   void newList();

   // dragged

   void split_dragged(Point delta);

   SignalConnector<ConfigEditorWindow,Point> connector_split_dragged;

   // enable

   void enable_all(bool on);

   void enable_Coord(bool on);

   void enable_MCoord(bool on);

   void enable_VColor(bool on);

   void enable_Clr(bool on);

   void enable_unsigned(bool on);

   void enable_String(bool on);

   void enable_Point(bool on);

   void enable_Font(bool on);

   void enable_bool(bool on);

   void enable_Ratio(bool on);

   SignalConnector<ConfigEditorWindow,bool> connector_check_all_changed;
   SignalConnector<ConfigEditorWindow,bool> connector_check_Coord_changed;
   SignalConnector<ConfigEditorWindow,bool> connector_check_MCoord_changed;
   SignalConnector<ConfigEditorWindow,bool> connector_check_VColor_changed;
   SignalConnector<ConfigEditorWindow,bool> connector_check_Clr_changed;
   SignalConnector<ConfigEditorWindow,bool> connector_check_unsigned_changed;
   SignalConnector<ConfigEditorWindow,bool> connector_check_String_changed;
   SignalConnector<ConfigEditorWindow,bool> connector_check_Point_changed;
   SignalConnector<ConfigEditorWindow,bool> connector_check_Font_changed;
   SignalConnector<ConfigEditorWindow,bool> connector_check_bool_changed;
   SignalConnector<ConfigEditorWindow,bool> connector_check_Ratio_changed;

   // buttons

   void setPref();

   SignalConnector<ConfigEditorWindow> connector_btnSet_pressed;

   void backPref();

   SignalConnector<ConfigEditorWindow> connector_btnBack_pressed;

   void savePref();

   SignalConnector<ConfigEditorWindow> connector_btnSave_pressed;

   void selfPref();

   SignalConnector<ConfigEditorWindow> connector_btnSelf_pressed;

   // select

   void select(Coord &var);

   void select(MCoord &var);

   void select(VColor &var);

   void select(Clr &var);

   void select(unsigned &var);

   void select(DefString &var);

   void select(Point &var);

   void select(FontCouple &var);

   void select(bool &var);

   void select(Ratio &var);

   void select();

   struct FuncSelect;

   void selectVar(ulen index);

   SignalConnector<ConfigEditorWindow,ulen> connector_item_list_selected;

   // changed

   void changed();

   void string_edit_changed();

   SignalConnector<ConfigEditorWindow> connector_string_edit_changed;

   void coord_edit_changed(Coord value);

   SignalConnector<ConfigEditorWindow,Coord> connector_coord_edit_changed;

   void mcoord_edit_changed(MCoord value);

   SignalConnector<ConfigEditorWindow,MCoord> connector_mcoord_edit_changed;

   void font_edit_changed();

   SignalConnector<ConfigEditorWindow> connector_font_edit_changed;

   void unsigned_edit_changed(int value);

   SignalConnector<ConfigEditorWindow,int> connector_unsigned_edit_changed;

   void clr_edit_changed(int value);

   SignalConnector<ConfigEditorWindow,int> connector_clr_edit_changed;

   void point_edit_changed(Point value);

   SignalConnector<ConfigEditorWindow,Point> connector_point_edit_changed;

   void color_edit_changed(VColor value);

   SignalConnector<ConfigEditorWindow,VColor> connector_color_edit_changed;

   void bool_edit_changed(bool value);

   SignalConnector<ConfigEditorWindow,bool> connector_bool_edit_changed;

   void ratio_edit_changed(Ratio value);

   SignalConnector<ConfigEditorWindow,Ratio> connector_ratio_edit_changed;

  public:

   ConfigEditorWindow(SubWindowHost &host,const Config &cfg,bool use_self);

   virtual ~ConfigEditorWindow();

   // methods

   Point getMinSize(unsigned flags,Point cap=Point::Max()) const;

   void bindConfig(ConfigItemHost &host);

   // drawing

   virtual void layout(unsigned flags);

   virtual void drawBack(DrawBuf buf,bool drag_active) const;

   // signals

   Signal<> updated;

   Signal<> doSave;
   Signal<> doSelf;
 };

/* class ConfigEditorFrame */

class ConfigEditorFrame : public DragFrame
 {
 public:

  struct Config
   {
    RefVal<Ratio> pos_ry = Div(5,12) ;

    CtorRefVal<DragFrame::ConfigType> frame_cfg;
    CtorRefVal<ConfigEditorWindow::ConfigType> editor_cfg;

    Config() noexcept {}

    template <class Bag,class Proxy>
    void bind(const Bag &bag,Proxy proxy)
     {
      pos_ry.bind(bag.frame_pos_ry);

      frame_cfg.bind(proxy);
      editor_cfg.bind(proxy);
     }
   };

   using ConfigType = Config ;

  private:

   const Config &cfg;

   ConfigEditorWindow client;

  public:

   ConfigEditorFrame(Desktop *desktop,const Config &cfg,bool use_self);

   virtual ~ConfigEditorFrame();

   // methods

   void bindConfig(ConfigItemHost &host) { client.bindConfig(host); }

   // create

   Pane getPane(StrLen title,Point base) const;

   Pane getPane(bool is_main,StrLen title) const;

   void create(Point base,const DefString &title)
    {
     DragFrame::create(getPane(title.str(),base),title);
    }

   void create(FrameWindow *parent,Point base,const DefString &title)
    {
     DragFrame::create(parent,getPane(title.str(),base),title);
    }

   void create(const DefString &title)
    {
     DragFrame::create(getPane(false,title.str()),title);
    }

   void create(FrameWindow *parent,const DefString &title)
    {
     DragFrame::create(parent,getPane(false,title.str()),title);
    }

   void createMain(const DefString &title)
    {
     DragFrame::createMain(CmdDisplay_Normal,getPane(true,title.str()),title);
    }

   void createMain(CmdDisplay cmd_display,Pane pane,const DefString &title)
    {
     DragFrame::createMain(cmd_display,pane,title);
    }

   // signals

   Signal<> &updated;

   Signal<> &doSave;
   Signal<> &doSelf;
 };

} // namespace Video
} // namespace CCore

#endif

