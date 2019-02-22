/* Editor.h */
//----------------------------------------------------------------------------------------
//
//  Project: ContourLab 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef Editor_h
#define Editor_h

#include <inc/EditAngleWindow.h>
#include <inc/EditLengthWindow.h>
#include <inc/EditRatioWindow.h>
#include <inc/GeometryWindow.h>
#include <inc/ItemListWindow.h>

namespace App {

/* classes */

class EditorWindow;

/* class EditorWindow */

class EditorWindow : public ComboWindow
 {
  public:

   struct Config
    {
     // user

     RefVal<VColor> back = Silver ;

     RefVal<Coord> space_dxy = 10 ;

     RefVal<String> text_Error = "Error"_str ;

     CtorRefVal<TextLineWindow::ConfigType> text_cfg;
     CtorRefVal<XSplitWindow::ConfigType> split_cfg;
     CtorRefVal<MessageFrame::AlertConfigType> msg_cfg;

     // app

     RefVal<String> hint_File   = "The current file"_str ;
     RefVal<String> hint_Angle  = "Set the selected angle"_str ;
     RefVal<String> hint_Length = "Set the selected length"_str ;
     RefVal<String> hint_Ratio  = "Set the selected ratio"_str ;
     RefVal<String> hint_Geom   = "Draw of elements, use to set the selected point"_str ;

     CtorRefVal<EditAngleWindow::ConfigType> edit_angle_cfg;
     CtorRefVal<EditLengthWindow::ConfigType> edit_length_cfg;
     CtorRefVal<EditRatioWindow::ConfigType> edit_ratio_cfg;
     CtorRefVal<GeometryWindow::ConfigType> geom_cfg;
     CtorRefVal<ItemListWindow::ConfigType> ilist_cfg;

     Config() noexcept {}

     template <class AppPref>
     Config(const UserPreference &pref,const AppPref &app_pref) noexcept
      : edit_angle_cfg(pref,app_pref),
        edit_length_cfg(pref,app_pref),
        edit_ratio_cfg(pref,app_pref),
        geom_cfg(pref,app_pref),
        ilist_cfg(pref,app_pref)
      {
       bindUser(pref.get(),pref.getSmartConfig());
       bindApp(app_pref.get());
      }

     template <class Bag,class Proxy>
     void bindUser(const Bag &bag,Proxy proxy)
      {
       back.bind(bag.back);
       space_dxy.bind(bag.space_dxy);
       text_Error.bind(bag.text_Error);

       text_cfg.bind(proxy);
       split_cfg.bind(proxy);
       msg_cfg.bind(proxy);
      }

     template <class Bag>
     void bindApp(const Bag &bag)
      {
       hint_File.bind(bag.hint_File);
       hint_Angle.bind(bag.hint_Angle);
       hint_Length.bind(bag.hint_Length);
       hint_Ratio.bind(bag.hint_Ratio);
       hint_Geom.bind(bag.hint_Geom);
      }
    };

   using ConfigType = Config ;

  private:

   const Config &cfg;

   bool has_file = false ;

   TextLineWindow text_file;

   XSplitWindow split1;

   YSplitWindow split2;

   EditAngleWindow edit_angle;

   EditLengthWindow edit_length;

   EditRatioWindow edit_ratio;

   GeometryWindow geom;

   ItemListWindow list_pad;
   ItemListWindow list_formula;

   MessageFrame msg_frame;

   // layout

   bool layout_first = true ;
   Coord left_dx = 0 ;
   Coord top_dy = 0 ;

  private:

   void deactivate();

   void activate(SubWindow &editor);

   template <class T>
   struct EditorPad
    {
     Contour::Object obj;
     T *ptr = 0 ;

     void select(const Contour::Object &obj_,T &var)
      {
       obj=obj_;
       ptr=&var;
      }

     bool set(T val)
      {
       if( ptr )
         {
          *ptr=val;

          return true;
         }

       return false;
      }
    };

   EditorPad<Geometry::Angle> angle_pad;
   EditorPad<Geometry::Length> length_pad;
   EditorPad<Geometry::Ratio> ratio_pad;

   void select(const Contour::Object &obj,Geometry::Angle &angle);

   void select(const Contour::Object &obj,Geometry::Length &length);

   void select(const Contour::Object &obj,Geometry::Ratio &ratio);

   void select(const Contour::Object &obj,Geometry::Point &point);

   struct SelectPad;

   void selectPad(ulen index);

   void unselectPad();

   void selectFormula(ulen index);

   void unselectFormula();

   void setModified() { text_file.alert(true); }

   void clearModified() { text_file.alert(false); }

  private:

   void angle_changed(Geometry::Angle angle);

   void length_changed(Geometry::Length length);

   void ratio_changed(Geometry::Ratio ratio);

   void geom_changed();

   SignalConnector<EditorWindow,Geometry::Angle> connector_angle_changed;
   SignalConnector<EditorWindow,Geometry::Length> connector_length_changed;
   SignalConnector<EditorWindow,Geometry::Ratio> connector_ratio_changed;
   SignalConnector<EditorWindow> connector_geom_changed;

  private:

   Coord getMinDXY() const;

   Coord getMaxLeftDX() const;

   Coord getMaxTopDY() const;

   bool adjustSplitX(Coord dx);

   bool adjustSplitY(Coord dy);

   void adjustSplit(Point point);

  private:

   void split1_dragged(Point point);

   void split2_dragged(Point point);

   SignalConnector<EditorWindow,Point> connector_split1_dragged;
   SignalConnector<EditorWindow,Point> connector_split2_dragged;

  private:

   void pad_up(ulen ind);

   void pad_down(ulen ind);

   void pad_del(ulen ind);

   void pad_add(ulen ind);

   void pad_selected(ulen ind);

   void pad_show_changed(ulen ind,bool check);

   void pad_gray_changed(ulen ind,bool check);

   void pad_name_changed(ulen ind,bool check);

   void pad_text_changed();

   bool pad_test();

   void pad_text_paused();

   SignalConnector<EditorWindow,ulen> connector_list_pad_command_up;
   SignalConnector<EditorWindow,ulen> connector_list_pad_command_down;
   SignalConnector<EditorWindow,ulen> connector_list_pad_command_del;
   SignalConnector<EditorWindow,ulen> connector_list_pad_command_add;
   SignalConnector<EditorWindow,ulen> connector_list_pad_command_selected;

   SignalConnector<EditorWindow,ulen,bool> connector_list_pad_show_changed;
   SignalConnector<EditorWindow,ulen,bool> connector_list_pad_gray_changed;
   SignalConnector<EditorWindow,ulen,bool> connector_list_pad_name_changed;

   SignalConnector<EditorWindow> connector_list_pad_text_changed;
   SignalConnector<EditorWindow> connector_list_pad_text_paused;

  private:

   void formula_up(ulen ind);

   void formula_down(ulen ind);

   void formula_del(ulen ind);

   void formula_add(ulen ind);

   void formula_selected(ulen ind);

   void formula_show_changed(ulen ind,bool check);

   void formula_gray_changed(ulen ind,bool check);

   void formula_name_changed(ulen ind,bool check);

   void formula_text_changed();

   bool formula_test();

   void formula_text_paused();

   SignalConnector<EditorWindow,ulen> connector_list_formula_command_up;
   SignalConnector<EditorWindow,ulen> connector_list_formula_command_down;
   SignalConnector<EditorWindow,ulen> connector_list_formula_command_del;
   SignalConnector<EditorWindow,ulen> connector_list_formula_command_add;
   SignalConnector<EditorWindow,ulen> connector_list_formula_command_selected;

   SignalConnector<EditorWindow,ulen,bool> connector_list_formula_show_changed;
   SignalConnector<EditorWindow,ulen,bool> connector_list_formula_gray_changed;
   SignalConnector<EditorWindow,ulen,bool> connector_list_formula_name_changed;

   SignalConnector<EditorWindow> connector_list_formula_text_changed;
   SignalConnector<EditorWindow> connector_list_formula_text_paused;

  private:

   void errorMsg(StrLen text);

   void msg_destroyed();

   SignalConnector<EditorWindow> connector_msg_destroyed;

  public:

   EditorWindow(SubWindowHost &host,const Config &cfg);

   virtual ~EditorWindow();

   // methods

   Point getMinSize() const;

   bool isModified() const { return text_file.isAlerted(); }

   void blank();

   void load(StrLen file_name);

   bool save();

   void save(StrLen file_name);

   // drawing

   virtual void layout();

   virtual void drawBack(DrawBuf buf,DrawParam &draw_param) const;
 };

} // namespace App

#endif
