/* WindowReport.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.01
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

#ifndef CCore_inc_video_WindowReport_h
#define CCore_inc_video_WindowReport_h

#include <CCore/inc/video/WindowLib.h>

#include <CCore/inc/Exception.h>

namespace CCore {
namespace Video {

/* classes */

class ExceptionStore;

class ExceptionWindow;

class WindowReportBase;

template <class Frame> struct WindowReportConfigOf;

template <class Frame> struct WindowReportParamOf;

template <class Frame> class WindowReportOf;

class ExceptionClient;

/* class ExceptionStore */

class ExceptionStore : NoCopy
 {
   static constexpr ulen MaxMsgLen = Align(512) ;
   static constexpr ulen MaxMsgCount = 100 ;

   struct Header
    {
     Header *next;
     ulen index;
     ulen len;
     bool done;
     bool divide; // after this message
    };

   static constexpr ulen Delta = Align(sizeof (Header)) ;

   static StrLen GetStr(Header *ptr) { return StrLen(PlaceAt(ptr)+Delta,ptr->len); }

   static PtrLen<char> GetBuf(Header *ptr) { return PtrLen<char>(PlaceAt(ptr)+Delta,ptr->len); }

   static void * GetNext(Header *ptr) { return PlaceAt(ptr)+Delta+Align(ptr->len); }

  private:

   void *mem;
   void *lim;

   Header *head;
   Header *tail;

   ulen index = 1 ;

  private:

   Header * try_alloc();

   Header * alloc();

   void free();

  protected:

   PtrLen<char> startMsg();

   void endMsg(PtrLen<char> rest);

   void divide();

  public:

   ExceptionStore();

   ~ExceptionStore();

   bool nonEmpty() const { return head!=0; }

   void apply(FuncArgType<ulen,StrLen,bool> func) const
    {
     for(Header *ptr=head; ptr ;ptr=ptr->next) if( ptr->done ) func(ptr->index,GetStr(ptr),ptr->divide);
    }
 };

/* class ExceptionWindow */

class ExceptionWindow : public SubWindow
 {
  public:

   struct Config
    {
     RefVal<MCoord> width = Fraction(6,2) ;

     RefVal<VColor> back    = Black ;
     RefVal<VColor> text    = Green ;
     RefVal<VColor> divider =   Red ;

     RefVal<Font> font;

     CtorRefVal<XScrollWindow::ConfigType> scroll_cfg;

     Config() noexcept {}

     template <class Bag,class Proxy>
     void bind(const Bag &bag,Proxy proxy)
      {
       width.bind(bag.width);

       back.bind(bag.exception_back);
       text.bind(bag.exception_text);
       divider.bind(bag.exception_divider);

       font.bind(bag.info_font.font);

       scroll_cfg.bind(proxy);
      }
    };

   using ConfigType = Config ;

  protected:

   WindowReportBase &report;

  private:

   const Config &cfg;

   WindowList wlist;

   XScrollWindow xscroll;
   YScrollWindow yscroll;

  private:

   bool opened = false ;

   ulen lines = 0 ;
   ulen page = 1 ;

   Pane ptext;

   Coord text_dy = 1 ;
   Coord text_by = 0 ;
   Coord delta_dx = 0 ;

   Coord total_dx = 0 ;

  private:

   static ulen CountLines(StrLen text);

   static Coord TotalDX(Font font,ulen index,StrLen text);

   void setScrollPage();

   void setLines();

   void drawText(DrawBuf buf,Pane pane,Coord xoff) const;

   void subYPos(ulen delta);

   void addYPos(ulen delta);

   void subXPos(ulen delta);

   void addXPos(ulen delta);

  private:

   void update();

   SignalConnector<ExceptionWindow> connector_update;

   void setXPos(ulen pos);

   void setYPos(ulen pos);

   SignalConnector<ExceptionWindow,ulen> connector_xscroll_changed;
   SignalConnector<ExceptionWindow,ulen> connector_yscroll_changed;

  public:

   ExceptionWindow(SubWindowHost &host,const Config &cfg,WindowReportBase &report);

   virtual ~ExceptionWindow();

   // methods

   void reposition() noexcept;

   // drawing

   virtual void layout(unsigned flags);

   virtual void draw(DrawBuf buf,bool drag_active) const;

   // base

   virtual void open();

   virtual void close();

   // user input

   virtual void react(UserAction action);

   void react_other(UserAction action);

   void react_Key(VKey vkey,KeyMod kmod,unsigned repeat);

   void react_Wheel(Point point,MouseKey mkey,Coord delta);
 };

/* class WindowReportBase */

class WindowReportBase : public ExceptionStore , public ReportException
 {
   PtrLen<char> buf;
   bool msg = false ;

   bool enable = true ;
   bool non_cleared = false ;

  protected:

   Desktop *desktop;
   MSec tick_period;
   const ExceptionWindow::ConfigType &cfg;

  private:

   virtual void print(StrLen str);

   virtual void end();

  private:

   void boxShow() noexcept;

   virtual DefString getTitle()=0;

   virtual void modalLoop()=0;

   class TempQueue;

  protected:

   void lastShow(); // must be called in a destructor of a derived class

  public:

   WindowReportBase(Desktop *desktop,MSec tick_period,const ExceptionWindow::ConfigType &cfg);

   ~WindowReportBase();

   void clear() noexcept;

   void show() noexcept;

   Signal<> updated;
 };

/* struct WindowReportConfigOf<Frame> */

template <class Frame>
struct WindowReportConfigOf : Frame::ConfigType
 {
  RefVal<DefString> text_Fatal_error = "Fatal error"_def ;

  WindowReportConfigOf() noexcept {}

  template <class Bag>
  void bind(const Bag &bag)
   {
    Frame::ConfigType::bind(bag);

    text_Fatal_error.bind(bag.text_Fatal_error);
   }
 };

/* type WindowReportConfig */

using WindowReportConfig = WindowReportConfigOf<DragFrame> ;

/* struct WindowReportParamOf<Frame> */

template <class Frame>
struct WindowReportParamOf
 {
  Desktop *desktop = DefaultDesktop ;
  MSec tick_period = DeferCallQueue::DefaultTickPeriod ;

  WindowReportConfigOf<Frame> report_cfg;
  ExceptionWindow::ConfigType exception_cfg;

  WindowReportParamOf() {}
 };

/* type WindowReportParam */

using WindowReportParam = WindowReportParamOf<DragFrame> ;

/* class WindowReportOf<Frame> */

template <class Frame>
class WindowReportOf : public WindowReportBase
 {
   const WindowReportConfigOf<Frame> &report_cfg;

  private:

   virtual DefString getTitle();

   virtual void modalLoop();

  public:

   template <class Param>
   explicit WindowReportOf(const Param &param)
    : WindowReportBase(param.desktop,param.tick_period,param.exception_cfg),
      report_cfg(param.report_cfg)
    {
    }

   ~WindowReportOf()
    {
     lastShow();
    }
 };

template <class Frame>
DefString WindowReportOf<Frame>::getTitle()
 {
  return report_cfg.text_Fatal_error.get();
 }

template <class Frame>
void WindowReportOf<Frame>::modalLoop()
 {
  Frame main_frame(desktop,report_cfg);

  ExceptionWindow sub_win(main_frame,cfg,*this);

  main_frame.bindClient(sub_win);

  main_frame.createMain(CmdDisplay_Normal,getTitle());

  DeferCallQueue::Loop();
 }

/* type WindowReport */

using WindowReport = WindowReportOf<DragFrame> ;

/* class ExceptionClient */

class ExceptionClient : public ExceptionWindow , public AliveControl
 {
   bool in_loop = false ;

   Signal<> alert;

  public:

   template <class W>
   ExceptionClient(W &parent,const ExceptionWindow::ConfigType &cfg,WindowReportBase &report)
    : ExceptionWindow(parent,cfg,report)
    {
     parent.connectAlert(alert);
    }

   ~ExceptionClient();

   // methods

   void clear() noexcept;

   void guard();

   void show() noexcept;

   void beforeLoop() noexcept;

   void afterLoop() noexcept;

   // AliveControl

   virtual void alive();
 };

} // namespace Video
} // namespace CCore

#endif


