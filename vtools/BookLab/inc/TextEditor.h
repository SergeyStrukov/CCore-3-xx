/* TextEditor.h */
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

#ifndef TextEditor_h
#define TextEditor_h

#include <inc/BookLab.h>

namespace App {

/* classes */

class TextBuf;

class TextWindow;

class ScrollTextWindow;

class TextEditor;

/* class TextBuf */

class TextBuf : NoCopy
 {
   DynArray<BookLab::TextLine> *pad = 0 ;

  public:

   TextBuf();

   ~TextBuf();

   // data

   ulen getLineCount() const
    {
     return pad? pad->getLen() : 0 ;
    }

   BookLab::TextLine & getLine(ulen index) const
    {
     if( !pad ) GuardIndex(index,0);

     return pad->at(index);
    }

   void addLine()
    {
     if( pad ) pad->append_default();
    }

   // methods

   void blank();

   void load(DynArray<BookLab::TextLine> *pad);

   void save() const;
 };

/* class TextWindow */

class TextWindow : public SubWindow
 {
  public:

   struct Config
    {
     // user

     RefVal<Coord> cursor_dx = 3 ;

     RefVal<unsigned> period = 10_tick ;

     // app

     RefVal<Fraction> width = Fraction(6,2) ;

     RefVal<VColor> text    =  Black ;
     RefVal<VColor> endspan = GrayColor(0xD0) ;
     RefVal<VColor> line    =   Blue ;
     RefVal<VColor> alert   =    Red ;
     RefVal<VColor> cursor  =   Blue ;
     RefVal<VColor> select  = Yellow ;

     RefVal<Font> font;

     template <class AppPref>
     Config(const UserPreference &user_pref,const AppPref &app_pref) noexcept
      {
       bindUser(user_pref.get(),user_pref.getSmartConfig());
       bindApp(app_pref.get());
      }

     template <class Bag,class Proxy>
     void bindUser(const Bag &bag,Proxy proxy)
      {
       Used(proxy);

       cursor_dx.bind(bag.text_cursor_dx);

       period.bind(bag.line_edit_period);
      }

     template <class Bag>
     void bindApp(const Bag &bag)
      {
       width.bind(bag.textedit_width);

       text.bind(bag.textedit_text);
       endspan.bind(bag.textedit_endspan);
       line.bind(bag.textedit_line);
       alert.bind(bag.textedit_alert);
       cursor.bind(bag.textedit_cursor);
       select.bind(bag.textedit_select);

       font.bind(bag.textedit_font.font);
      }
    };

   using ConfigType = Config ;

  private:

   const Config &cfg;

   TextBuf text;

   // scroll

   ScrollPos sx;
   ScrollPos sy;

   // cursor

   bool focus = false ;
   bool cursor_on = false ;

   struct Cursor
    {
     ulen y = 0 ;
     ulen span = 0 ;
     ulen x = 0 ;
    };

   Cursor cursor;

   SimpleArray<Char> spanbuf;
   ulen spanlen = 0 ;

   // layout

   mutable bool ok = false ;
   mutable bool block_cache = false ;

   struct SizeData
    {
     FontSize fs;
     Coord text_dx = 0 ;
     Coord space_dx = 0 ;

     void prepare(const Font &font);

     void update(const Font &font,BookLab::TextLine &line);

     void update(BookLab::TextLine &line);
    };

   mutable SizeData data;

  private:

   void clean();

   static Coord Cache(const Font &font,BookLab::Span &span);

   static Coord Cache(const Font &font,BookLab::TextLine &line,Coord space_dx);

   static Coord Cache(BookLab::TextLine &line,Coord space_dx);

   [[nodiscard]] bool cache() const;

   static bool HasSpec(BookLab::Span &span);

   static bool Alert(BookLab::Span &span);

  private:

   void posX(ulen pos);

   void posY(ulen pos);

   SignalConnector<TextWindow,ulen> connector_posX;
   SignalConnector<TextWindow,ulen> connector_posY;

   void updated(unsigned flags);

   SignalConnector<TextWindow,unsigned> connector_updated;

  private:

   unsigned tick_count = 0 ;

   void tick();

   void tickStart();

   void tickStop();

   DeferInput<TextWindow> input;

   DeferTick defer_tick;

  private:

   PtrLen<const Char> getCurSpan() const { return Range(spanbuf.getPtr(),spanlen); }

   template <class Func>
   bool applyToSpan(Func func);

   template <class Func>
   bool applyToSpan(Func func) const;

   void fill(StrLen str);

   void cleanNames();

   void fill();

   void flush() const;

  private:

   void setPosX(ulen x);

   void setPosY(ulen y);

   ulen getSpanCount() const;

   struct Split;

   void changeSpan(ulen span);

   void showCursor();

   void moveLeft(ulen delta);

   bool moveRight(ulen delta);

   void moveHome();

   void moveEnd();

   void moveTab();

   ulen getPosX() const;

   void setPos(ulen x,ulen y);

   void moveUp(ulen delta);

   void moveDown(ulen delta);

   void moveTop();

   void moveBottom();

  private:

   void makeNonEmpty();

   void insSpanChar(BookLab::TextLine &line,Char ch);

   void insChar(Char ch);

   void splitSpan();

   void splitLine();

   class Draw;

  public:

   TextWindow(SubWindowHost &host,const Config &cfg);

   virtual ~TextWindow();

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

   // methods

   Point getMinSize(Point cap) const;

   void blank();

   void load(DynArray<BookLab::TextLine> *pad);

   void save() const;

   void setFormat(String name);

   void setLink(String name);

   void link();

   // drawing

   virtual void layout();

   virtual void draw(DrawBuf buf,bool drag_active) const;

   // base

   virtual void open();

   virtual void close();

   // keyboard

   virtual void gainFocus();

   virtual void looseFocus();

   // mouse

   virtual void looseCapture();

   virtual MouseShape getMouseShape(Point point,KeyMod kmod) const;

   // user input

   virtual void react(UserAction action);

   void react_Key(VKey vkey,KeyMod kmod,unsigned repeat);

   void react_Char(Char ch);

   void react_LeftClick(Point point,MouseKey mkey);

   void react_LeftUp(Point point,MouseKey);

   void react_Move(Point point,MouseKey mkey);

   void react_Leave();

   void react_Wheel(Point point,MouseKey mkey,Coord delta);

   // signals

   Signal<> changed;

   Signal<ulen> scroll_x;
   Signal<ulen> scroll_y;

   Signal<String,bool> showFormat;
   Signal<String,bool> showLink;
 };

/* class ScrollTextWindow */

class ScrollTextWindow : public ScrollableWindow<TextWindow>
 {
  public:

   using Base = ScrollableWindow<TextWindow> ;

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

   SignalConnector<ScrollTextWindow> connector_changed;

  public:

   ScrollTextWindow(SubWindowHost &host,const ConfigType &cfg);

   virtual ~ScrollTextWindow();

   // methods

   void blank() { window.blank(); }

   void load(DynArray<BookLab::TextLine> *pad) { window.load(pad); }

   void save() const { window.save(); }

   void setFormat(String name) { window.setFormat(name); }

   void setLink(String name) { window.setLink(name); }

   void link() { window.link(); }

   // signals

   Signal<String,bool> &showFormat;
   Signal<String,bool> &showLink;
 };

/* class TextEditor */

class TextEditor : public ComboWindow
 {
  public:

   struct Config
    {
     // user

     RefVal<Coord> space_dxy = 10 ;

     RefVal<VColor> back = Silver ;

     CtorRefVal<ButtonWindow::ConfigType> btn_cfg;
     CtorRefVal<LineEditWindow::ConfigType> edit_cfg;
     CtorRefVal<ContourWindow::ConfigType> cont_cfg;

     CtorRefVal<ScrollTextWindow::ConfigType> text_cfg;

     // app

     template <class AppPref>
     Config(const UserPreference &user_pref,const AppPref &app_pref) noexcept
      : text_cfg(user_pref,app_pref)
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
       cont_cfg.bind(proxy);
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

   ButtonWindow btn_format;
   ButtonWindow btn_link;

   LineEditWindow edit_format;
   LineEditWindow edit_link;

   ContourWindow cont;

   ScrollTextWindow edit_text;

  private:

   void format_pressed();

   void link_pressed();

   SignalConnector<TextEditor> connector_format_pressed;
   SignalConnector<TextEditor> connector_link_pressed;

   void show_format(String name,bool alert);

   void show_link(String name,bool alert);

   SignalConnector<TextEditor,String,bool> connector_show_format;
   SignalConnector<TextEditor,String,bool> connector_show_link;

  public:

   TextEditor(SubWindowHost &host,const Config &cfg);

   virtual ~TextEditor();

   // methods

   Point getMinSize() const;

   void blank();

   void load(DynArray<BookLab::TextLine> *pad);

   void save() const;

   void link() { edit_text.link(); }

   // base

   virtual void open();

   // drawing

   virtual void layout();

   virtual void drawBack(DrawBuf buf,bool drag_active) const;
 };

} // namespace App

#endif


