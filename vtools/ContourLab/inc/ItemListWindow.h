/* ItemListWindow.h */
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

#ifndef ItemListWindow_h
#define ItemListWindow_h

#include <inc/Contour.h>

namespace App {

/* classes */

class InsWindow;

class InsFrame;

class EditFormulaShape;

class EditFormulaWindow;

class ItemListWindow;

/* class InsWindow */

class InsWindow : public ComboWindow
 {
  public:

   struct Config
    {
     // user

     RefVal<Coord> space_dxy = 10 ;

     RefVal<VColor> back = Silver ;

     RefVal<String> text_Close  = "Close"_str ;
     RefVal<String> text_Insert = "Insert"_str ;

     CtorRefVal<ScrollListWindow::ConfigType> list_cfg;
     CtorRefVal<RefButtonWindow::ConfigType> btn_cfg;

     // app

     RefVal<String> hint_List = "Select a function to be inserted into the cursor position"_str ;

     Config() noexcept {}

     template <class AppPref>
     Config(const UserPreference &pref,const AppPref &app_pref) noexcept
      {
       bindUser(pref.get(),pref.getSmartConfig());
       bindApp(app_pref.get());
      }

     template <class Bag,class Proxy>
     void bindUser(const Bag &bag,Proxy proxy)
      {
       space_dxy.bind(bag.space_dxy);
       back.bind(bag.back);

       text_Close.bind(bag.text_Close);
       text_Insert.bind(bag.text_Insert);

       list_cfg.bind(proxy);
       btn_cfg.bind(proxy);
      }

     template <class Bag>
     void bindApp(const Bag &bag)
      {
       hint_List.bind(bag.hint_function_List);
      }
    };

   using ConfigType = Config ;

  private:

   const Config &cfg;

   ScrollListWindow list;

   RefButtonWindow btn_Insert;
   RefButtonWindow btn_Close;

   Info info_ins;

  private:

   void btn_Insert_pressed();

   void btn_Close_pressed();

   SignalConnector<InsWindow> connector_btn_Insert_pressed;
   SignalConnector<InsWindow> connector_btn_Close_pressed;

  public:

   InsWindow(SubWindowHost &host,const Config &cfg);

   virtual ~InsWindow();

   // methods

   Point getMinSize(Point cap=Point::Max()) const;

   class Builder : NoCopy
    {
      ComboInfoBuilder list;
      InfoBuilder ins;

     public:

      Builder() {}

      ~Builder() {}

      void add(StrLen line,StrLen ins_text)
       {
        list.add(line);
        ins.add(ins_text);
       }

      struct Result
       {
        ComboInfo info_list;
        Info info_ins;
       };

      Result complete() { return {list.complete(),ins.complete()}; }
    };

   void set(Builder::Result result)
    {
     list.setInfo(result.info_list);

     info_ins=result.info_ins;
    }

   // drawing

   virtual void layout();

   virtual void drawBack(DrawBuf buf,bool drag_active) const;

   // signals

   Signal<StrLen> selected;
 };

/* class InsFrame */

class InsFrame : public DragFrame
 {
  public:

   struct Config
    {
     // user

     CtorRefVal<DragFrame::ConfigType> drag_cfg;

     // app

     CtorRefVal<InsWindow::ConfigType> ins_cfg;

     Config() noexcept {}

     template <class AppPref>
     Config(const UserPreference &pref,const AppPref &app_pref) noexcept
      : ins_cfg(pref,app_pref)
      {
       bindUser(pref.get(),pref.getSmartConfig());
       bindApp(app_pref.get());
      }

     template <class Bag,class Proxy>
     void bindUser(const Bag &bag,Proxy proxy)
      {
       Used(bag);

       drag_cfg.bind(proxy);
      }

     template <class Bag>
     void bindApp(const Bag &bag)
      {
       Used(bag);
      }
    };

   using ConfigType = Config ;

  private:

   InsWindow client;

  public:

   InsFrame(Desktop *desktop,const Config &cfg);

   virtual ~InsFrame();

   // methods

   void set(InsWindow::Builder::Result result) { client.set(result); }

   // create

   Pane getPane(StrLen title,Point base) const;

   using DragFrame::create;

   void create(FrameWindow *parent,Point base,const String &title)
    {
     create(parent,getPane(Range(title),base),title);
    }

   // signals

   Signal<StrLen> &selected;
 };

/* class EditFormulaShape */

class EditFormulaShape : public LineEditShape
 {
  public:

   struct Config : LineEditShape::Config
    {
     // app

     RefVal<VColor> text        =     Black ;
     RefVal<VColor> error_text  =       Red ;
     RefVal<VColor> number_text = DarkGreen ;
     RefVal<VColor> length_text = DarkGreen ;
     RefVal<VColor> angle_text  = DarkGreen ;
     RefVal<VColor> name_text   =      Blue ;
     RefVal<VColor> punct_text  =     Black ;

     RefVal<unsigned> delay = 1_sectick ;

     Config() noexcept {}

     template <class AppPref>
     Config(const UserPreference &pref,const AppPref &app_pref) noexcept
      {
       bind(pref.get());

       font.bind(pref.get().code_font.font);

       bindApp(app_pref.get());
      }

     template <class Bag>
     void bindApp(const Bag &bag)
      {
       text.bind(bag.edit_text);
       error_text.bind(bag.edit_error_text);
       number_text.bind(bag.edit_number_text);
       length_text.bind(bag.edit_length_text);
       angle_text.bind(bag.edit_angle_text);
       name_text.bind(bag.edit_name_text);
       punct_text.bind(bag.edit_punct_text);
       delay.bind(bag.edit_delay);
      }
    };

   CharAccent *accent = 0 ;

   const Config & getCfg() const { return static_cast<const Config &>(cfg); }

   virtual void drawText(Font font,const DrawBuf &buf,Pane pane,TextPlace place,PtrLen<const Char> text,ulen off,VColor vc) const;

   EditFormulaShape(PtrLen<Char> text_buf,const Config &cfg) : LineEditShape(text_buf,cfg) {}
 };

/* class EditFormulaWindow */

class EditFormulaWindow : public LineEditWindowOf<EditFormulaShape>
 {
   SimpleArray<CharAccent> storage;

   DeferTick defer_tick;

   unsigned time = 0 ;

   bool flag = false ;

  private:

   void tick();

   void start();

   SignalConnector<EditFormulaWindow> connector_changed;

  public:

   EditFormulaWindow(SubWindowHost &host,const ConfigType &cfg);

   ~EditFormulaWindow();

   // methods

   CharAccent * getAccentBuf() { return shape.accent; }

   void clearAccentFlag() { flag=false; }

   void normalAccent();

   // signals

   Signal<> paused;
 };

/* class ItemListWindow */

class ItemListWindow : public ComboWindow
 {
  public:

   struct Config
    {
     // user

     RefVal<Coord> space_dxy = 10 ;

     CtorRefVal<ScrollListWindow::ConfigType> list_cfg;
     CtorRefVal<KnobWindow::ConfigType> knob_cfg;

     CtorRefVal<RefLabelWindow::ConfigType> label_cfg;
     CtorRefVal<CheckWindow::ConfigType> check_cfg;

     // app

     CtorRefVal<EditFormulaWindow::ConfigType> edit_cfg;
     CtorRefVal<InsFrame::ConfigType> ins_cfg;

     RefVal<String> text_show = "show"_str ;
     RefVal<String> text_gray = "gray"_str ;
     RefVal<String> text_name = "name"_str ;

     RefVal<String> title_Ins = "Function list"_str ;

     RefVal<String> hint_List = "Geometry object list"_str ;
     RefVal<String> hint_Edit = "Enter a formula to create a new object"_str ;

     RefVal<String> hint_Down = "Move the object down in the list"_str ;
     RefVal<String> hint_Up   = "Move the object up in the list"_str ;
     RefVal<String> hint_Del  = "Delete the object"_str ;
     RefVal<String> hint_Add  = "Add a new object"_str ;
     RefVal<String> hint_Ins  = "Open the Function list window"_str ;

     RefVal<String> hint_Show = "Show this object"_str ;
     RefVal<String> hint_Gray = "Gray this object if not selected"_str ;
     RefVal<String> hint_Name = "Show the name of this object"_str ;

     Config() noexcept {}

     template <class AppPref>
     Config(const UserPreference &pref,const AppPref &app_pref) noexcept
      : edit_cfg(pref,app_pref),
        ins_cfg(pref,app_pref)
      {
       bindUser(pref.get(),pref.getSmartConfig());
       bindApp(app_pref.get());
      }

     template <class Bag,class Proxy>
     void bindUser(const Bag &bag,Proxy proxy)
      {
       space_dxy.bind(bag.space_dxy);

       list_cfg.bind(proxy);
       knob_cfg.bind(proxy);

       label_cfg.bind(proxy);
       check_cfg.bind(proxy);
      }

     template <class Bag>
     void bindApp(const Bag &bag)
      {
       text_show.bind(bag.text_show);
       text_gray.bind(bag.text_gray);
       text_name.bind(bag.text_name);
       title_Ins.bind(bag.title_Ins);
       hint_List.bind(bag.hint_item_List);
       hint_Edit.bind(bag.hint_item_Edit);
       hint_Down.bind(bag.hint_item_Down);
       hint_Up.bind(bag.hint_item_Up);
       hint_Del.bind(bag.hint_item_Del);
       hint_Add.bind(bag.hint_item_Add);
       hint_Ins.bind(bag.hint_item_Ins);
       hint_Show.bind(bag.hint_item_Show);
       hint_Gray.bind(bag.hint_item_Gray);
       hint_Name.bind(bag.hint_item_Name);
      }
    };

   using ConfigType = Config ;

  private:

   const Config &cfg;

   ScrollListWindow list;

   EditFormulaWindow edit;

   KnobWindow knob_down;
   KnobWindow knob_up;
   KnobWindow knob_del;
   KnobWindow knob_add;
   KnobWindow knob_ins;

   RefLabelWindow label_show;
   RefLabelWindow label_gray;
   RefLabelWindow label_name;

   CheckWindow check_show;
   CheckWindow check_gray;
   CheckWindow check_name;

   InsFrame ins_frame;
   bool ins_set = false ;

  private:

   void list_selected(ulen index);

   SignalConnector<ItemListWindow,ulen> connector_list_selected;

   void knob_down_pressed();

   void knob_up_pressed();

   void knob_del_pressed();

   void knob_add_pressed();

   SignalConnector<ItemListWindow> connector_edit_entered;

   SignalConnector<ItemListWindow> connector_knob_down_pressed;
   SignalConnector<ItemListWindow> connector_knob_up_pressed;
   SignalConnector<ItemListWindow> connector_knob_del_pressed;
   SignalConnector<ItemListWindow> connector_knob_add_pressed;

   void check_show_changed(bool check);

   void check_gray_changed(bool check);

   void check_name_changed(bool check);

   SignalConnector<ItemListWindow,bool> connector_check_show_changed;
   SignalConnector<ItemListWindow,bool> connector_check_gray_changed;
   SignalConnector<ItemListWindow,bool> connector_check_name_changed;

   void knob_ins_pressed();

   void ins_frame_destroyed();

   void ins_frame_selected(StrLen text);

   SignalConnector<ItemListWindow> connector_knob_ins_pressed;
   SignalConnector<ItemListWindow> connector_ins_frame_destroyed;
   SignalConnector<ItemListWindow,StrLen> connector_ins_frame_selected;

  public:

   ItemListWindow(SubWindowHost &host,const Config &cfg);

   virtual ~ItemListWindow();

   // methods

   Point getMinSize(Point cap=Point::Max()) const;

   void setInfo(const ComboInfo &info) { list.setInfo(info); }

   void set(InsWindow::Builder::Result result)
    {
     ins_frame.set(result);
     ins_set=true;
     wlist.insBefore(edit,knob_ins);
     knob_ins.enable();
    }

   bool select(ulen index) { return list.select(index); }

   bool reselect() { return list.reselect(); }

   void ping() { list.ping(); }

   void updateList()
    {
     list.update();
    }

   void setCheck(bool show,bool gray,bool name);

   void setCheck(const Label &label) { setCheck(label.show,label.gray,label.show_name); }

   void noItem();

   PtrLen<const Char> getText() const { return edit.getText(); }

   CharAccent * getAccentBuf() { return edit.getAccentBuf(); }

   void clearAccentFlag() { edit.clearAccentFlag(); }

   void normalAccent() { edit.normalAccent(); }

   void enableAdd(bool ok)
    {
     edit.alert(!ok);

     knob_add.enable(ok);
    }

   // drawing

   virtual void layout();

   // user input

   virtual void react(UserAction action);

   void react_Key(VKey vkey,KeyMod kmod);

   void react_Key(VKey vkey,KeyMod kmod,unsigned repeat);

   void react_other(UserAction action);

   // signals

   Signal<ulen> command_up;
   Signal<ulen> command_down;
   Signal<ulen> command_del;
   Signal<ulen> command_add;

   Signal<ulen> selected;

   Signal<ulen,bool> show_changed;
   Signal<ulen,bool> gray_changed;
   Signal<ulen,bool> name_changed;

   Signal<> &text_changed;
   Signal<> &text_paused;
 };

} // namespace App

#endif
