/* BookWindow.h */
//----------------------------------------------------------------------------------------
//
//  Project: BookLab 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef BookWindow_h
#define BookWindow_h

#include <inc/Book.h>

namespace App {

/* classes */

class InnerBookWindow;

class DisplayBookWindow;

class BookWindow;

/* class InnerBookWindow */

class InnerBookWindow : public SubWindow
 {
  public:

   struct Config
    {
     // user

     RefVal<MCoord> width = Fraction(6,2) ;

     RefVal<VColor> line = Gray ;
     RefVal<VColor> gray = Gray ;
     RefVal<VColor> snow = Snow ;

     RefVal<VColor> focus = OrangeRed ;

     // app

     RefVal<VColor> back = Silver ;
     RefVal<VColor> fore = Black ;

     RefVal<Font> font;
     RefVal<Font> codefont;

     Config() noexcept {}

     template <class AppPref>
     Config(const UserPreference &user_pref,const AppPref &app_pref) noexcept
      {
       bindUser(user_pref.get(),user_pref.getSmartConfig());
       bindApp(app_pref.get());
      }

     template <class Bag,class Proxy>
     void bindUser(const Bag &bag,Proxy)
      {
       width.bind(bag.width);

       line.bind(bag.line);
       gray.bind(bag.gray);
       snow.bind(bag.snow);

       focus.bind(bag.focus);
      }

     template <class Bag>
     void bindApp(const Bag &bag)
      {
       back.bind(bag.back);
       fore.bind(bag.fore);

       font.bind(bag.font.font);
       codefont.bind(bag.codefont.font);
      }
    };

   using ConfigType = Config ;

  private:

   const Config &cfg;

   PtrLen<Book::TypeDef::Frame> frames;
   VColor back = Book::NoColor ;
   VColor fore = Book::NoColor ;

   bool focus = false ;

   // scroll

   struct Scroll
    {
     ulen total = 0 ;
     ulen page  = 1 ;
     ulen pos   = 0 ;

     bool tooShort() const { return page<total; }

     ulen getPos() const { return Min<ulen>(pos,total-page); }
    };

   Scroll sx;
   Scroll sy;

   // layout

   struct Size
    {
     ulen dx;
     ulen dy;

     Size() : dx(0),dy(0) {}

     Size(ulen dx_,ulen dy_) : dx(dx_),dy(dy_) {}

     Size(Point s) : Size((ulen)s.x,(ulen)s.y) {}

     friend Size StackY(Size a,Size b) { return { Max(a.dx,b.dx) , LenAdd(a.dy,b.dy) }; }
    };

   class Shape
    {
      Point size;

     public:

      Shape() noexcept {}

      Size getSize() const { return size; }

      void set(const Config &cfg,const Book::TypeDef::Frame &frame,Coordinate dx);

      void draw(const Config &cfg,DrawBuf buf,const Book::TypeDef::Frame &frame,ulen pos_x,ulen pos_y,bool posflag) const;

     private:

      Point body(const Config &cfg,const Book::TypeDef::Text *obj,Coordinate dx);

      Point body(const Config &cfg,const Book::TypeDef::FixedText *obj,Coordinate dx);

      Point body(const Config &cfg,const Book::TypeDef::Bitmap *obj,Coordinate dx);

      Point body(const Config &cfg,const Book::TypeDef::Frame &frame,Coordinate dx);

      void draw(const Config &cfg,DrawBuf buf,const Book::TypeDef::Frame &frame,Point base) const;
    };

   mutable DynArray<Shape> shapes;

   mutable Size size;

   mutable bool ok = false ;

  private:

   void cache(unsigned update_flag) const;

  private:

   void posX(ulen pos);

   void posY(ulen pos);

   SignalConnector<InnerBookWindow,ulen> connector_posX;
   SignalConnector<InnerBookWindow,ulen> connector_posY;

  public:

   InnerBookWindow(SubWindowHost &host,const Config &cfg);

   virtual ~InnerBookWindow();

   // methods

   Point getMinSize(unsigned flags,Point cap=Point::Max()) const;

   void setPage(Book::TypeDef::Page *page,VColor back,VColor fore);

   // special methods

   bool shortDX() const { return sx.tooShort(); }

   bool shortDY() const { return sy.tooShort();  }

   template <class W>
   void setScrollXRange(W &window) const { window.setRange(sx.total,sx.page,sx.pos); }

   template <class W>
   void setScrollYRange(W &window) const { window.setRange(sy.total,sy.page,sy.pos); }

   void connect(Signal<ulen> &scroll_x,Signal<ulen> &scroll_y)
    {
     connector_posX.connect(scroll_x);
     connector_posY.connect(scroll_y);
    }

   // drawing

   virtual void layout(unsigned flags);

   virtual void draw(DrawBuf buf,bool drag_active) const;

   // base

   virtual void open();

   // keyboard

   virtual void gainFocus();

   virtual void looseFocus();

   // mouse

   virtual MouseShape getMouseShape(Point point,KeyMod kmod) const;

   // signals

   Signal<ulen> scroll_x;
   Signal<ulen> scroll_y;

   Signal<Book::TypeDef::Link> link;
   Signal<Book::TypeDef::Page *> hint;
 };

/* class DisplayBookWindow */

class DisplayBookWindow : public ScrollableWindow<InnerBookWindow>
 {
  public:

   using Base = ScrollableWindow<InnerBookWindow> ;

   struct Config : Base::Config
    {
     Config() noexcept {}

     template <class AppPref>
     Config(const UserPreference &user_pref,const AppPref &app_pref) noexcept
      : Base::Config(user_pref,app_pref)
      {
       bindScroll(user_pref.get(),user_pref.getSmartConfig());
      }
    };

   using ConfigType = Config ;

  public:

   DisplayBookWindow(SubWindowHost &host,const ConfigType &cfg);

   virtual ~DisplayBookWindow();

   // methods

   void setPage(Book::TypeDef::Page *page,VColor back,VColor fore);

   // signals

   Signal<Book::TypeDef::Link> &link;
   Signal<Book::TypeDef::Page *> &hint;
 };

/* class BookWindow */

class BookWindow : public ComboWindow
 {
  public:

   struct Config
    {
     // user

     RefVal<Coord> space_dxy = 10 ;

     RefVal<VColor> back = Silver ;

     RefVal<DefString> text_Error = "Error"_def ;

     CtorRefVal<LabelWindow::ConfigType> label_cfg;
     CtorRefVal<TextLineWindow::ConfigType> text_cfg;
     CtorRefVal<MessageFrame::AlertConfigType> msg_cfg;

     // app

     RefVal<DefString> text_Title = "Title"_def ;
     RefVal<DefString> text_Page = "Page"_def ;

     DisplayBookWindow::ConfigType book_cfg;

     Config() noexcept {}

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

       label_cfg.bind(proxy);
       text_cfg.bind(proxy);
       msg_cfg.bind(proxy);
      }

     template <class Bag>
     void bindApp(const Bag &bag)
      {
       text_Title.bind(bag.text_Title);
       text_Page.bind(bag.text_Page);
      }
    };

   using ConfigType = Config ;

  private:

   const Config &cfg;

   RefLabelWindow label_title;
   TextLineWindow text_title;

   RefLabelWindow label_page;
   TextLineWindow text_page;

   DisplayBookWindow book;

   // data

   Book::BookMap book_map;

   // frames

   MessageFrame msg;

  private:

   void error(StrLen etext);

   void enableFrame();

   SignalConnector<BookWindow> connector_msg_destroyed;

  public:

   BookWindow(SubWindowHost &host,const Config &cfg,Signal<> &update);

   virtual ~BookWindow();

   // methods

   Point getMinSize(unsigned flags) const;

   void blank();

   void load(StrLen file_name);

   // drawing

   virtual void layout(unsigned flags);

   virtual void drawBack(DrawBuf buf,bool drag_active) const;
 };

} // namespace App

#endif

