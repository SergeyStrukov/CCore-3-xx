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

#include <inc/Shape.h>

namespace App {

/* classes */

class InnerBookWindow;

class DisplayBookWindow;

class BookWindow;

/* class InnerBookWindow */

class InnerBookWindow : public SubWindow
 {
  public:

   struct Config : Shape::Config
    {
     // user

     RefVal<VColor> border = Blue ;
     RefVal<VColor> focus = OrangeRed ;

     // app

     RefVal<VColor> back = Silver ;
     RefVal<VColor> fore = Black ;

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

       border.bind(bag.border);
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

   FontMap &font_map;
   mutable BitmapMap bmp_map;

   PtrLen<Book::TypeDef::Frame> frames;
   VColor back = Book::NoColor ;
   VColor fore = Book::NoColor ;

   bool focus = false ;

   // scroll

   ScrollPos sx;
   ScrollPos sy;

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

   mutable DynArray<Shape> shapes;

   mutable Size size;

   mutable bool ok = false ;
   mutable Coord cache_dx;

  private:

   static Coord CapSize(ulen dx,Coord cap) { return (Coord)Min(dx,(ulen)cap); }

   void cache() const;

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

   PtrLen<const Shape> getVisibleShapes(ulen off,ulen lim) const;

   PtrLen<const Shape> getVisibleShapes() const;

   AnyPtr<Book::TypeDef::Link,Book::TypeDef::Page> getRef(Point point) const;

  private:

   void posX(ulen pos);

   void posY(ulen pos);

   SignalConnector<InnerBookWindow,ulen> connector_posX;
   SignalConnector<InnerBookWindow,ulen> connector_posY;

   void updated(unsigned flags);

   SignalConnector<InnerBookWindow,unsigned> connector_updated;

  public:

   InnerBookWindow(SubWindowHost &host,const Config &cfg,FontMap &font_map);

   virtual ~InnerBookWindow();

   // methods

   Point getMinSize(Point cap=Point::Max()) const;

   void setPage(StrLen file_name,Book::TypeDef::Page *page,VColor back,VColor fore);

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

   void react_LeftClick(Point point,MouseKey);

   void react_Wheel(Point,MouseKey,Coord delta);

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

   DisplayBookWindow(SubWindowHost &host,const ConfigType &cfg,FontMap &font_map);

   virtual ~DisplayBookWindow();

   // methods

   void setPage(StrLen file_name,Book::TypeDef::Page *page,VColor back,VColor fore);

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
     CtorRefVal<ArrowProgressWindow::ConfigType> progress_cfg;
     CtorRefVal<MessageFrame::AlertConfigType> msg_cfg;

     // app

     RefVal<DefString> text_Title = "Title"_def ;
     RefVal<DefString> text_Page = "Page"_def ;
     RefVal<DefString> text_NotReady = "Font database is not ready yet"_def ;

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
       progress_cfg.bind(proxy);
       msg_cfg.bind(proxy);
      }

     template <class Bag>
     void bindApp(const Bag &bag)
      {
       text_Title.bind(bag.text_Title);
       text_Page.bind(bag.text_Page);
       text_NotReady.bind(bag.text_NotReady);
      }
    };

   using ConfigType = Config ;

  private:

   const Config &cfg;

   // data

   Book::BookMap book_map;
   FontMap font_map;

   // subwindows

   RefLabelWindow label_title;
   TextLineWindow text_title;

   RefLabelWindow label_page;
   TextLineWindow text_page;

   DisplayBookWindow book;

   ArrowProgressWindow progress;

   // frames

   MessageFrame msg;

   // incremental

   class ProgressControl : public IncrementalProgress
    {
      ArrowProgressWindow &window;

     public:

      explicit ProgressControl(ArrowProgressWindow &window);

      ~ProgressControl();

      // IncrementalProgress

      virtual void start();

      virtual void setTotal(unsigned total);

      virtual bool setPos(unsigned pos);

      virtual void stop() noexcept;
    };

   ProgressControl progress_control;

   FontLookup::Incremental font_inc;
   bool font_flag = true ;

  private:

   void error(DefString etext);

   void enableFrame();

   SignalConnector<BookWindow> connector_msg_destroyed;

   void font_completed(bool ok);

   SignalConnector<BookWindow,bool> connector_font_completed;

  public:

   BookWindow(SubWindowHost &host,const Config &cfg,Signal<> &update);

   virtual ~BookWindow();

   // methods

   Point getMinSize() const;

   void blank();

   void load(StrLen file_name);

   // drawing

   virtual void layout();

   virtual void drawBack(DrawBuf buf,bool drag_active) const;

   // base

   virtual void open();
 };

} // namespace App

#endif

