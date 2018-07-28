/* EditWindow.h */
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

#ifndef EditWindow_h
#define EditWindow_h

#include <inc/BookLab.h>

#include <CCore/inc/IntervalTree.h>

namespace App {

/* classes */

class InnerBookLabWindow;

class BookLabWindow;

class EditWindow;

/* class InnerBookLabWindow */

class InnerBookLabWindow : public SubWindow
 {
  public:

   struct Config : BookLab::Config
    {
     // user

     RefVal<Fraction> width = Fraction(6,2) ;

     RefVal<VColor> focus = OrangeRed ;

     // app

     RefVal<Coord> border_dxy = 5 ;

     RefVal<VColor> back = Silver ;

     template <class AppPref>
     Config(const UserPreference &user_pref,const AppPref &app_pref) noexcept
      : BookLab::Config(user_pref,app_pref)
      {
       bindUser(user_pref.get(),user_pref.getSmartConfig());
       bindApp(app_pref.get());
      }

     template <class Bag,class Proxy>
     void bindUser(const Bag &bag,Proxy)
      {
       width.bind(bag.width);
       focus.bind(bag.focus);
      }

     template <class Bag>
     void bindApp(const Bag &bag)
      {
       border_dxy.bind(bag.border_dxy);
       back.bind(bag.back);
      }
    };

   using ConfigType = Config ;

  private:

   const Config &cfg;

   BookLab::Book book;

   bool focus = false ;

   // scroll

   ScrollPos sx;
   ScrollPos sy;

   // layout

   mutable DynArray<BookLab::PaneRef> refs;
   mutable IntervalTree<Coord> tree;

   mutable Point size; // without border

   mutable bool ok = false ;
   mutable bool block_cache = false ;

  private:

   void clean();

   [[nodiscard]] bool cache() const;

   BookLab::PaneRef getRef(Point point) const;

  private:

   static ulen Delta(ulen delta,bool mul_flag) { return mul_flag? 10u*delta : delta ; }

   void addXPos(ulen delta,bool mul_flag);

   void subXPos(ulen delta,bool mul_flag);

   void addYPos(ulen delta,bool mul_flag);

   void subYPos(ulen delta,bool mul_flag);

   void begXPos();

   void endXPos();

   void begYPos();

   void endYPos();

   void addYPosPage();

   void subYPosPage();

  private:

   Point getBase() const { return Point((Coord)sx.pos,(Coord)sy.pos); }

   void posX(ulen pos);

   void posY(ulen pos);

   SignalConnector<InnerBookLabWindow,ulen> connector_posX;
   SignalConnector<InnerBookLabWindow,ulen> connector_posY;

   void updated(unsigned flags);

   SignalConnector<InnerBookLabWindow,unsigned> connector_updated;

  public:

   InnerBookLabWindow(SubWindowHost &host,const Config &cfg);

   virtual ~InnerBookLabWindow();

   // methods

   Point getMinSize(Point cap=Point::Max()) const;

   void collect() { book.collect(); }

   void blank();

   ErrorText load(StrLen file_name,PtrLen<char> ebuf);

   ErrorText save(StrLen file_name,PtrLen<char> ebuf) const;

   ErrorText link(PtrLen<char> ebuf);

   ErrorText bookTo(StrLen file_name,PtrLen<char> ebuf) const;

   // special methods

   bool shortDX() const { return sx.tooShort(); }

   bool shortDY() const { return sy.tooShort();  }

   ScrollPos getScrollXRange() const { return sx; }

   ScrollPos getScrollYRange() const { return sy; }

   void connect(Signal<ulen> &scroll_x,Signal<ulen> &scroll_y)
    {
     connector_posX.connect(scroll_x);
     connector_posY.connect(scroll_y);
    }

   // drawing

   virtual void layout();

   virtual void draw(DrawBuf buf,bool drag_active) const;

   // base

   virtual void open();

   // keyboard

   virtual void gainFocus();

   virtual void looseFocus();

   // mouse

   virtual MouseShape getMouseShape(Point point,KeyMod kmod) const;

   // user input

   virtual void react(UserAction action);

   void react_Key(VKey vkey,KeyMod kmod,unsigned repeat);

   void react_LeftClick(Point point,MouseKey mkey);

   void react_RightClick(Point point,MouseKey mkey);

   void react_Wheel(Point point,MouseKey mkey,Coord delta);

   // signals

   Signal<ulen> scroll_x;
   Signal<ulen> scroll_y;

   Signal<> changed;
   Signal<> modified;
 };

/* class BookLabWindow */

class BookLabWindow : public ScrollableWindow<InnerBookLabWindow>
 {
  public:

   using Base = ScrollableWindow<InnerBookLabWindow> ;

   struct Config : Base::Config
    {
     template <class AppPref>
     Config(const UserPreference &user_pref,const AppPref &app_pref) noexcept
      : Base::Config(user_pref,app_pref)
      {
       bindScroll(user_pref.get(),user_pref.getSmartConfig());
      }
    };

   using ConfigType = Config ;

  private:

   void changed();

   SignalConnector<BookLabWindow> connector_changed;

  public:

   BookLabWindow(SubWindowHost &host,const ConfigType &cfg);

   virtual ~BookLabWindow();

   // methods

   void collect() { window.collect(); }

   void blank() { window.blank(); }

   ErrorText load(StrLen file_name,PtrLen<char> ebuf) { return window.load(file_name,ebuf); }

   ErrorText save(StrLen file_name,PtrLen<char> ebuf) const { return window.save(file_name,ebuf); }

   ErrorText link(PtrLen<char> ebuf) { return window.link(ebuf); }

   ErrorText book(StrLen file_name,PtrLen<char> ebuf) const { return window.bookTo(file_name,ebuf); }

   // signals

   Signal<> &modified;
 };

/* class EditWindow */

class EditWindow : public ComboWindow
 {
  public:

   struct Config
    {
     // user

     RefVal<Coord> space_dxy = 10 ;

     RefVal<VColor> back = Silver ;

     CtorRefVal<RefLabelWindow::ConfigType> label_cfg;
     CtorRefVal<TextLineWindow::ConfigType> text_cfg;
     CtorRefVal<RefButtonWindow::ConfigType> btn_cfg;
     CtorRefVal<MessageFrame::AlertConfigType> msg_cfg;
     CtorRefVal<FileFrame::ConfigType> file_cfg;

     RefVal<DefString> text_Error = "Error"_def ;
     RefVal<DefString> text_SaveFile = "Select a file to save to"_def ;

     // app

     RefVal<DefString> text_NoFile = "<No file>"_def ;
     RefVal<DefString> text_File = "File"_def ;
     RefVal<DefString> text_Link = "Link"_def ;
     RefVal<DefString> text_Book = "Book"_def ;

     BookLabWindow::ConfigType book_cfg;

     template <class AppPref>
     Config(const UserPreference &user_pref,const AppPref &app_pref) noexcept
      : book_cfg(user_pref,app_pref)
      {
       bindUser(user_pref.get(),user_pref.getSmartConfig());
       bindApp(app_pref.get());
      }

     template <class Bag,class Proxy>
     void bindUser(const Bag &bag,Proxy proxy)
      {
       space_dxy.bind(bag.space_dxy);
       back.bind(bag.back);
       text_Error.bind(bag.text_Error);
       text_SaveFile.bind(bag.text_SaveFile);

       label_cfg.bind(proxy);
       text_cfg.bind(proxy);
       btn_cfg.bind(proxy);
       msg_cfg.bind(proxy);
       file_cfg.bind(proxy);
      }

     template <class Bag>
     void bindApp(const Bag &bag)
      {
       text_NoFile.bind(bag.text_NoFile);
       text_File.bind(bag.text_File);
       text_Link.bind(bag.text_Link);
       text_Book.bind(bag.text_Book);
      }
    };

   using ConfigType = Config ;

  private:

   const Config &cfg;

   RefLabelWindow label_file;
   TextLineWindow text_file;
   RefButtonWindow btn_link;
   RefButtonWindow btn_book;

   BookLabWindow book;

   bool has_file = false ;

   unsigned tick_count = 0 ;

   // frames

   MessageFrame msg_frame;
   FileFrame file_frame;

  private:

   void clearModified() { text_file.alert(false); }

   void errorMsg(StrLen etext);

   bool saveFile(StrLen file_name);

   void book_modified();

   SignalConnector<EditWindow> connector_book_modified;

   void link_pressed() { link(); }

   SignalConnector<EditWindow> connector_link_pressed;

   SignalConnector<EditWindow> connector_book_pressed;

   void msg_destroyed();

   SignalConnector<EditWindow> connector_msg_destroyed;

   void file_destroyed();

   SignalConnector<EditWindow> connector_file_destroyed;

   DeferInput<EditWindow> input;

   void tick();

   DeferTick defer_tick;

  public:

   EditWindow(SubWindowHost &host,const Config &cfg,Signal<> &update);

   virtual ~EditWindow();

   // methods

   Point getMinSize() const;

   bool isModified() const;

   void blank();

   void load(StrLen file_name);

   bool save();

   void save(StrLen file_name);

   bool link();

   void saveBook();

   // drawing

   virtual void layout();

   virtual void drawBack(DrawBuf buf,bool drag_active) const;

   // base

   virtual void open();

   virtual void close();
 };

} // namespace App

#endif

