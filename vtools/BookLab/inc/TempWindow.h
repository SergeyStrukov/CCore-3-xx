/* TempWindow.h */
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

#ifndef TempWindow_h
#define TempWindow_h

#include <inc/BookLab.h>
#include <inc/AppState.h>

namespace App {

/* classes */

struct TempSlot;

class SlotWindow;

class TempWindow;

class TempFrame;

/* struct TempSlot */

struct TempSlot : MemBase_nocopy
 {
  BookLab::TempData data;
  String name;

  explicit TempSlot(BookLab::Book &book) : data(book) {}

  bool notEmpty() const { return name.getLen() || data.notEmpty() ; }

  void erase()
   {
    data.del();
    name=Null;
   }
 };

/* class SlotWindow */

class SlotWindow : public SubWindow
 {
  public:

   struct Config
    {
     // user

     // app

     RefVal<Fraction> line_width = Fraction(6,2) ;

     RefVal<Coord> table_dxy = 3 ;

     RefVal<VColor> table       = Black ;
     RefVal<VColor> text        = Blue ;
     RefVal<VColor> cursor      = Yellow ;
     RefVal<VColor> gray_cursor = Gray ;

     RefVal<Font> text_font;

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
       line_width.bind(bag.line_width);

       table_dxy.bind(bag.table_dxy);

       table.bind(bag.table);
       text.bind(bag.text);
       cursor.bind(bag.cursor);
       gray_cursor.bind(bag.gray_cursor);

       text_font.bind(bag.text_font.font);
      }
    };

   using ConfigType = Config ;

  private:

   const Config &cfg;
   BookLab::Book &book;

   bool focus = false ;

   DynArray<OwnPtr<TempSlot> > list;
   ulen off = 0 ;
   ulen len = 1 ;
   ulen cur = 0 ;

   Coord cell_dx = 0 ;
   Coord cell_dy = 0 ;

  private:

   ulen getMaxPos() const { return PosSub(list.getLen(),len); }

   TempSlot * ref(ulen slot);

   void append();

  private:

   void moveUp();

   void moveDown();

   void curUp();

   void curDown();

  public:

   SlotWindow(SubWindowHost &host,const Config &cfg,BookLab::Book &book);

   virtual ~SlotWindow();

   // methods

   Point getMinSize() const;

   void setPos(ulen pos);

   BookLab::TempData & refSlot(ulen slot);

   BookLab::TempData & freeSlot();

   ulen getCurSlot() const { return cur; }

   void setCurName(String name);

   void delCurSlot();

   // drawing

   virtual void layout();

   virtual void draw(DrawBuf buf,DrawParam draw_param) const;

   // keyboard

   virtual void gainFocus();

   virtual void looseFocus();

   // user input

   virtual void react(UserAction action);

   void react_Key(VKey vkey,KeyMod kmod,unsigned repeat);

   void react_LeftClick(Point point,MouseKey mkey);

   void react_Wheel(Point point,MouseKey mkey,Coord delta);

   // signals

   Signal<ScrollPos> reposed;
   Signal<> slotChanged;
 };

/* class TempWindow */

class TempWindow : public ComboWindow
 {
  public:

   struct Config
    {
     // user

     RefVal<Coord> space_dxy = 10 ;

     RefVal<VColor> back = Silver ;

     CtorRefVal<RefButtonWindow::ConfigType> btn_cfg;
     CtorRefVal<LineEditWindow::ConfigType> edit_cfg;
     CtorRefVal<YScrollWindow::ConfigType> scroll_cfg;

     // app

     RefVal<String> text_Copy = "Copy"_str ;
     RefVal<String> text_Past = "Past"_str ;
     RefVal<String> text_Del  =  "Del"_str ;
     RefVal<String> text_Name = "Name"_str ;

     SlotWindow::ConfigType slot_cfg;

     template <class AppPref>
     Config(const UserPreference &user_pref,const AppPref &app_pref) noexcept
      : slot_cfg(user_pref,app_pref)
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
       edit_cfg.bind(proxy);
       scroll_cfg.bind(proxy);
      }

     template <class Bag>
     void bindApp(const Bag &bag)
      {
       text_Copy.bind(bag.text_Copy);
       text_Past.bind(bag.text_Past);
       text_Del.bind(bag.text_Del);
       text_Name.bind(bag.text_Name);
      }
    };

   using ConfigType = Config ;

  private:

   const Config &cfg;

   // subs

   RefButtonWindow btn_copy;
   RefButtonWindow btn_past;
   RefButtonWindow btn_del;
   RefButtonWindow btn_name;

   LineEditWindow edit;

   YScrollWindow scroll;
   SlotWindow slots;

  private:

   void copy_pressed();

   void past_pressed();

   void del_pressed();

   void name_pressed();

   void slots_reposed(ScrollPos pos);

   void scroll_changed(ulen pos);

   void slot_changed();

   SignalConnector<TempWindow> connector_copy_pressed;

   SignalConnector<TempWindow> connector_past_pressed;

   SignalConnector<TempWindow> connector_del_pressed;

   SignalConnector<TempWindow> connector_name_pressed;

   SignalConnector<TempWindow,ScrollPos> connector_slots_reposed;

   SignalConnector<TempWindow,ulen> connector_scroll_changed;

   SignalConnector<TempWindow> connector_slot_changed;

  public:

   TempWindow(SubWindowHost &host,const Config &cfg,BookLab::Book &book);

   virtual ~TempWindow();

   // methods

   Point getMinSize() const;

   bool copy(BookLab::Ref cursor);

   bool copy(ulen slot,BookLab::Ref cursor);

   bool past(ulen slot,BookLab::Ref cursor);

   void probe(BookLab::Ref cursor);

   // drawing

   virtual void layout();

   virtual void drawBack(DrawBuf buf,DrawParam &draw_param) const;

   // user input

   virtual void react(UserAction action);

   void react_Key(VKey vkey,KeyMod kmod,unsigned repeat);

   // signals

   Signal<ulen> askCopy;
   Signal<ulen> askPast;
   Signal<> askProbe;
 };

/* class TempFrame */

class TempFrame : public DragFrame
 {
  public:

   struct Config
    {
     // user

     RefVal<Ratio> pos_ry = Div(5,12) ;

     CtorRefVal<DragFrame::ConfigType> frame_cfg;

     // app

     RefVal<String> title = "Temp pad"_str ;

     TempWindow::ConfigType client_cfg;

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
       title.bind(bag.temp_title);
      }
    };

   using ConfigType = Config ;

  private:

   const Config &cfg;

   TempWindow client;

   FramePlace place;

  private:

   void setPlace();

  public:

   TempFrame(Desktop *desktop,const Config &cfg,BookLab::Book &book,Signal<> &update);

   virtual ~TempFrame();

   // methods

   void prepare(const AppState &app_state) { place=app_state.temp_place; }

   void save(AppState &app_state) { if( isAlive() ) setPlace(); app_state.temp_place=place; }

   bool copy(BookLab::Ref cursor) { return client.copy(cursor); }

   bool copy(ulen slot,BookLab::Ref cursor) { return client.copy(slot,cursor); }

   bool past(ulen slot,BookLab::Ref cursor) { return client.past(slot,cursor); }

   void probe(BookLab::Ref cursor) { client.probe(cursor); }

   // base

   virtual void dying();

   // create

   Pane getPane(StrLen title) const;

   void create(FrameWindow *parent)
    {
     String title=+cfg.title;

     DragFrame::create(parent,getPane(Range(title)),title);
    }

   // signals

   Signal<ulen> &askCopy;
   Signal<ulen> &askPast;
   Signal<> &askProbe;
 };

} // namespace App

#endif


