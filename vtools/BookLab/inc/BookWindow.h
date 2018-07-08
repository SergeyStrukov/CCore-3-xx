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

#include <inc/DrawBook.h>

namespace App {

/* classes */

class InnerBookWindow;

class DisplayBookWindow;

class DisplayBookFrame;

class BookWindow;

/* class InnerBookWindow */

class InnerBookWindow : public SubWindow
 {
  public:

   struct Config : DrawBook::Config
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
       face.bind(bag.face);

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

   DrawBook::ExtMap &map;

   PtrLen<Book::TypeDef::Frame> frames;
   VColor back = Book::NoColor ;
   VColor fore = Book::NoColor ;

   VColor book_back = Book::NoColor ;
   VColor book_fore = Book::NoColor ;

   bool focus = false ;

   Ratio scale;

   // scroll

   ScrollPos sx;
   ScrollPos sy;

   // layout

   mutable DynArray<DrawBook::Shape> shapes;

   mutable Point size;

   mutable bool ok = false ;
   mutable Coord cache_wdx = 0 ;

  private:

   void cache() const;

   PtrLen<const DrawBook::Shape> getVisibleShapes(Coord off,Coord lim) const;

   PtrLen<const DrawBook::Shape> getVisibleShapes() const;

   DrawBook::RefType getRef(Point point) const;

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

   void posX(ulen pos);

   void posY(ulen pos);

   SignalConnector<InnerBookWindow,ulen> connector_posX;
   SignalConnector<InnerBookWindow,ulen> connector_posY;

   void updated(unsigned flags);

   SignalConnector<InnerBookWindow,unsigned> connector_updated;

  public:

   InnerBookWindow(SubWindowHost &host,const Config &cfg,DrawBook::ExtMap &map);

   virtual ~InnerBookWindow();

   // methods

   Point getMinSize(Point cap=Point::Max()) const;

   void setPage(Book::TypeDef::Page *page,VColor back,VColor fore); // no layout/redraw

   void setPage(Book::TypeDef::Page *page); // no layout/redraw

   void posFrame(PtrLen<const UIntType> index_list); // no redraw

   void setScale(Ratio scale); // no layout/redraw

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
   Signal<> changed;
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

  private:

   void changed();

   SignalConnector<DisplayBookWindow> connector_changed;

  public:

   DisplayBookWindow(SubWindowHost &host,const ConfigType &cfg,DrawBook::ExtMap &map);

   virtual ~DisplayBookWindow();

   // methods

   void setPage(Book::TypeDef::Page *page,VColor back,VColor fore); // no redraw

   void setPage(Book::TypeDef::Page *page);

   void setPage(Book::TypeDef::Page *page,PtrLen<const UIntType> index_list); // no redraw

   void posFrame(PtrLen<const UIntType> index_list); // no redraw

   void setScale(Ratio scale);

   // signals

   Signal<Book::TypeDef::Link> &link;
   Signal<Book::TypeDef::Page *> &hint;
 };

/* class DisplayBookFrame */

class DisplayBookFrame : public DragFrame
 {
  public:

   struct Config
    {
     // user

     CtorRefVal<DragFrame::ConfigType> frame_cfg;

     // app

     DisplayBookWindow::ConfigType &book_cfg;

     template <class AppPref>
     Config(const UserPreference &user_pref,const AppPref &app_pref,DisplayBookWindow::ConfigType &book_cfg_) noexcept
      : book_cfg(book_cfg_)
      {
       bindUser(user_pref.get(),user_pref.getSmartConfig());
       bindApp(app_pref.get());
      }

     template <class Bag,class Proxy>
     void bindUser(const Bag &bag,Proxy proxy)
      {
       Used(bag);

       frame_cfg.bind(proxy);
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

   DisplayBookWindow client;

   Pane place;
   bool has_place = false ;

  public:

   DisplayBookFrame(Desktop *desktop,const Config &cfg,DrawBook::ExtMap &map,Signal<> &update);

   virtual ~DisplayBookFrame();

   // methods

   void setPage(VColor back,VColor fore);

   void setPage(Book::TypeDef::Page *page);

   void setScale(Ratio scale);

   bool getPlace(Pane &ret) const
    {
     if( has_place )
       {
        ret=place;

        return true;
       }

     return false;
    }

   // base

   virtual void dying();
 };

/* class BackShape */

class BackShape : public ButtonState
 {
   static constexpr Point Aspect = Point(37,20) ;

  public:

   struct Config
    {
     // user

     RefVal<Fraction> width = Fraction(6,2) ;

     RefVal<VColor> border =      Blue ;
     RefVal<VColor> focus  = OrangeRed ;
     RefVal<VColor> gray   =      Gray ;
     RefVal<VColor> snow   =      Snow ;
     RefVal<VColor> snowUp = PaleGreen ;

     // app

     RefVal<VColor> pict = Black ;

     RefVal<Coord> dy = 30 ;

     template <class AppPref>
     Config(const UserPreference &user_pref,const AppPref &app_pref)
      {
       bindUser(user_pref.get(),user_pref.getSmartConfig());
       bindApp(app_pref.get());
      }

     template <class Bag,class Proxy>
     void bindUser(const Bag &bag,Proxy)
      {
       width.bind(bag.width);
       border.bind(bag.border);
       focus.bind(bag.focus);
       gray.bind(bag.gray);
       snow.bind(bag.snow);
       snowUp.bind(bag.snowUp);
      }

     template <class Bag>
     void bindApp(const Bag &bag)
      {
       pict.bind(bag.back_pict);
       dy.bind(bag.back_dy);
      }
    };

   // parameters

   enum FaceType
    {
     BackDir,
     ForeDir
    };

   const Config &cfg;
   FaceType face;
   Pane pane;

   // methods

   BackShape(const Config &cfg_,FaceType face_) : cfg(cfg_),face(face_) {}

   Point getMinSize() const;

   bool isGoodSize(Point size) const { return size>=getMinSize(); }

   void draw(const DrawBuf &buf) const;
 };

using BackButtonWindow = ButtonWindowOf<BackShape> ;

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
     CtorRefVal<KnobWindow::ConfigType> knob_cfg;
     CtorRefVal<SpinorWindow::ConfigType> spinor_cfg;
     CtorRefVal<YDoubleLineWindow::ConfigType> line_cfg;

     // app

     RefVal<DefString> text_Title = "Title"_def ;
     RefVal<DefString> text_Page = "Page"_def ;
     RefVal<DefString> text_NotReady = "Font database is not ready yet"_def ;

     RefVal<Ratio> defscale = Ratio(1,0) ;

     DisplayBookWindow::ConfigType book_cfg;

     DisplayBookFrame::ConfigType popup_cfg;

     BackButtonWindow::ConfigType back_cfg;

     template <class AppPref>
     Config(const UserPreference &user_pref,const AppPref &app_pref) noexcept
      : book_cfg(user_pref,app_pref),
        popup_cfg(user_pref,app_pref,book_cfg),
        back_cfg(user_pref,app_pref)
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
       knob_cfg.bind(proxy);
       spinor_cfg.bind(proxy);
       line_cfg.bind(proxy);
      }

     template <class Bag>
     void bindApp(const Bag &bag)
      {
       text_Title.bind(bag.text_Title);
       text_Page.bind(bag.text_Page);
       text_NotReady.bind(bag.text_NotReady);
       defscale.bind(bag.defscale);
      }
    };

   using ConfigType = Config ;

  private:

   const Config &cfg;

   // data

   Book::BookMap book_map;
   DrawBook::ExtMap ext_map;

   Book::TypeDef::Page *cur  = 0 ;
   Book::TypeDef::Page *prev = 0 ;
   Book::TypeDef::Page *up   = 0 ;
   Book::TypeDef::Page *next = 0 ;

   // subwindows

   RefLabelWindow label_title;
   TextLineWindow text_title;

   RefLabelWindow label_page;
   TextLineWindow text_page;

   YDoubleLineWindow line1;

   KnobWindow knob_prev;
   KnobWindow knob_up;
   KnobWindow knob_next;

   YDoubleLineWindow line2;

   SpinorWindow spinor;

   YDoubleLineWindow line3;

   BackButtonWindow back_btn;
   BackButtonWindow fore_btn;

   DisplayBookWindow book;

   ArrowProgressWindow progress;

   // frames

   MessageFrame msg;

   DisplayBookFrame popup;

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

   void setNav(Book::TypeDef::Page *page);

   void enableFrame();

   SignalConnector<BookWindow> connector_msg_destroyed;

   void font_completed(bool ok);

   SignalConnector<BookWindow,bool> connector_font_completed;

   void link(Book::TypeDef::Link dst);

   SignalConnector<BookWindow,Book::TypeDef::Link> connector_link;

   void hint(Book::TypeDef::Page *page);

   SignalConnector<BookWindow,Book::TypeDef::Page *> connector_hint;

   void gotoPrev();

   void gotoUp();

   void gotoNext();

   SignalConnector<BookWindow> connector_prev_pressed;

   SignalConnector<BookWindow> connector_up_pressed;

   SignalConnector<BookWindow> connector_next_pressed;

   void setScale(int scale);

   SignalConnector<BookWindow,int> connector_scale_changed;

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

   // user input

   virtual void react(UserAction action);

   void react_Key(VKey vkey,KeyMod kmod);
 };

} // namespace App

#endif

