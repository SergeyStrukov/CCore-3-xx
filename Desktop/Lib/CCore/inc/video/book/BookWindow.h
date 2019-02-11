/* BookWindow.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.60
//
//  Tag: Desktop
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_video_book_BookWindow_h
#define CCore_inc_video_book_BookWindow_h

#include <CCore/inc/video/book/DrawBookTools.h>

#include <CCore/inc/video/MessageFrame.h>

#include <CCore/inc/video/AppOpt.h>

namespace CCore {
namespace Video {
namespace Book {

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

     template <class UserPref,class AppPref>
     Config(const UserPref &user_pref,const AppPref &app_pref) noexcept
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

   class Shape;

   mutable DynArray<Shape> shapes;

   mutable Point size;

   mutable bool ok = false ;
   mutable Coord cache_wdx = 0 ;

   mutable bool block_cache = false ;

  private:

   [[nodiscard]] bool cache() const;

   PtrLen<const Shape> getVisibleShapes(Coord off,Coord lim) const;

   PtrLen<const Shape> getVisibleShapes() const;

   DrawBook::RefList getRef(Point point) const;

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

   void setPage(Book::TypeDef::Page *page,VColor book_back,VColor book_fore); // no layout/redraw

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

   Signal<Book::TypeDef::Link,RefArray<ulen> > link;
   Signal<Book::TypeDef::Page *> hint;
   Signal<> changed;
   mutable Signal<> updateReplace;
 };

/* class DisplayBookWindow */

class DisplayBookWindow : public ScrollableWindow<InnerBookWindow>
 {
   void changed();

   SignalConnector<DisplayBookWindow> connector_changed;

  public:

   DisplayBookWindow(SubWindowHost &host,const ConfigType &cfg,DrawBook::ExtMap &map);

   virtual ~DisplayBookWindow();

   // methods

   void setPage(Book::TypeDef::Page *page,VColor book_back,VColor book_fore); // no redraw

   void setPage(Book::TypeDef::Page *page);

   void setPage(Book::TypeDef::Page *page,PtrLen<const UIntType> index_list); // no redraw

   void posFrame(PtrLen<const UIntType> index_list); // no redraw

   void setScale(Ratio scale);

   // signals

   Signal<Book::TypeDef::Link,RefArray<ulen> > &link;
   Signal<Book::TypeDef::Page *> &hint;
   Signal<> &updateReplace;
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

     template <class UserPref,class AppPref>
     Config(const UserPref &user_pref,const AppPref &app_pref,DisplayBookWindow::ConfigType &book_cfg_) noexcept
      : book_cfg(book_cfg_)
      {
       bindUser(user_pref.get(),user_pref.getSmartConfig());
       bindApp(app_pref.get());
      }

     template <class Bag,class Proxy>
     void bindUser(const Bag &,Proxy proxy)
      {
       frame_cfg.bind(proxy);
      }

     template <class Bag>
     void bindApp(const Bag &)
      {
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

   void setPage(VColor book_back,VColor book_fore);

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

   // signals

   Signal<> &updateReplace;
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

     template <class UserPref,class AppPref>
     Config(const UserPref &user_pref,const AppPref &app_pref)
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

     RefVal<String> text_Error = "Error"_str ;

     CtorRefVal<LabelWindow::ConfigType> label_cfg;
     CtorRefVal<TextLineWindow::ConfigType> text_cfg;
     CtorRefVal<ArrowProgressWindow::ConfigType> progress_cfg;
     CtorRefVal<MessageFrame::AlertConfigType> msg_cfg;
     CtorRefVal<KnobWindow::ConfigType> knob_cfg;
     CtorRefVal<SpinorWindow::ConfigType> spinor_cfg;
     CtorRefVal<YDoubleLineWindow::ConfigType> line_cfg;
     CtorRefVal<FontReplaceFrame::ConfigType> replace_cfg;

     RefButtonWindow::ConfigType btn_cfg;

     // app

     RefVal<String> text_Title = "Title"_str ;
     RefVal<String> text_Page = "Page"_str ;
     RefVal<String> text_NotReady = "Font database is not ready yet"_str ;
     RefVal<String> text_Font = "Fonts"_str ;

     RefVal<Ratio> defscale = Ratio(1,0) ;

     RefVal<String> hint_PrevPage   = "Go to the previous page"_str ;
     RefVal<String> hint_ParentPage = "Go to the parent page"_str ;
     RefVal<String> hint_NextPage   = "Go to the next page"_str ;
     RefVal<String> hint_Scale      = "Set the display scale"_str ;
     RefVal<String> hint_Font       = "Font replacement table"_str ;
     RefVal<String> hint_Reload     = "Reload book"_str ;
     RefVal<String> hint_GotoBack   = "Jump back"_str ;
     RefVal<String> hint_GotoFore   = "Jump fore"_str ;

     DisplayBookWindow::ConfigType book_cfg;

     DisplayBookFrame::ConfigType popup_cfg;

     BackButtonWindow::ConfigType back_cfg;

     template <class UserPref,class AppPref>
     Config(const UserPref &user_pref,const AppPref &app_pref) noexcept
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
       replace_cfg.bind(proxy);

       btn_cfg.bind(bag);
      }

     template <class Bag>
     void bindApp(const Bag &bag)
      {
       text_Title.bind(bag.text_Title);
       text_Page.bind(bag.text_Page);
       text_NotReady.bind(bag.text_NotReady);
       text_Font.bind(bag.text_Font);

       defscale.bind(bag.defscale);

       hint_PrevPage.bind(bag.hint_PrevPage);
       hint_ParentPage.bind(bag.hint_ParentPage);
       hint_NextPage.bind(bag.hint_NextPage);
       hint_Scale.bind(bag.hint_Scale);
       hint_Font.bind(bag.hint_Font);
       hint_Reload.bind(bag.hint_Reload);
       hint_GotoBack.bind(bag.hint_GotoBack);
       hint_GotoFore.bind(bag.hint_GotoFore);

       btn_cfg.font.bind(bag.decorfont.font);
      }
    };

   using ConfigType = Config ;

  private:

   const Config &cfg;

   OptFileName opt;

   // data

   String source_file;

   FontReplaceMap replace_map;

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

   RefButtonWindow btn_replace;
   KnobWindow knob_reload;

   YDoubleLineWindow line4;

   BackButtonWindow back_btn;
   BackButtonWindow fore_btn;

   DisplayBookWindow book;

   ArrowProgressWindow progress;

   // frames

   MessageFrame msg;

   DisplayBookFrame popup;

   FontReplaceFrame replace_frame;

   // incremental

   ProgressTo<ArrowProgressWindow> progress_control;

   FontLookup::Incremental font_inc;
   bool font_flag = true ;

   // history

   static constexpr ulen HistoryCap = 1000 ;

   struct History
    {
     Book::TypeDef::Page *page = 0 ;
     RefArray<ulen> index_list;
    };

   DynArray<History> history;
   ulen history_index = 0 ;

  private:

   void error(String etext);

   void setNav(Book::TypeDef::Page *page);

   void enableFrame();

   SignalConnector<BookWindow> connector_msg_destroyed;

   void font_completed(bool ok);

   SignalConnector<BookWindow,bool> connector_font_completed;

   void push(Book::TypeDef::Page *page,RefArray<ulen> index_list);

   void link(Book::TypeDef::Page *page,PtrLen<const UIntType> index_list);

   void link(Book::TypeDef::Link dst,RefArray<ulen> index_list);

   SignalConnector<BookWindow,Book::TypeDef::Link,RefArray<ulen> > connector_link;

   void link(History obj);

   void back();

   void fore();

   SignalConnector<BookWindow> connector_back_pressed;

   SignalConnector<BookWindow> connector_fore_pressed;

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

   void updateReplace();

   SignalConnector<BookWindow> connector_book_updateReplace;

   SignalConnector<BookWindow> connector_popup_updateReplace;

   void openReplace();

   SignalConnector<BookWindow> connector_knob_replace_pressed;

   void replaceApply();

   SignalConnector<BookWindow> connector_replace_apply;

   SignalConnector<BookWindow> connector_knob_reload_pressed;

  public:

   BookWindow(SubWindowHost &host,const Config &cfg,OptFileName opt,Signal<> &update);

   virtual ~BookWindow();

   // methods

   Point getMinSize() const;

   void blank();

   void load(StrLen file_name,bool set_source=true);

   void reload();

   // drawing

   virtual void layout();

   virtual void drawBack(DrawBuf buf,bool drag_active) const;

   // base

   virtual void open();

   // user input

   virtual void react(UserAction action);

   void react_Key(VKey vkey,KeyMod kmod);
 };

} // namespace Book
} // namespace Video
} // namespace CCore

#endif

