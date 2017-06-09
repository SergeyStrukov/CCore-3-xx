/* wintest.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Desktop
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_test_wintest_h
#define CCore_test_wintest_h

#include <CCore/inc/video/ApplicationBase.h>
#include <CCore/inc/video/WindowReport.h>
#include <CCore/inc/video/Picture.h>

#include <CCore/inc/TaskMemStack.h>

namespace App {

/* using */

using namespace CCore;
using namespace CCore::Video;

/* functions */

template <int XXXX>
int TestMain(CmdDisplay display);

/* Ping() */

template <class T>
concept bool Has_objPing = requires(T &obj)
 {
  obj.ping();
 } ;

template <class T>
concept bool No_objPing = !Has_objPing<T> ;

void Ping(Has_objPing &obj)
 {
  obj.ping();
 }

void Ping(No_objPing &)
 {
  // do nothing
 }

/* classes */

template <class Window> struct ClientApplication;

class BufReport;

class ResultBuilder;

class ResultWindow;

/* struct ClientApplication<Window> */

template <class Window>
struct ClientApplication
 {
  struct Param : WindowReportParam
   {
    typename Window::ConfigType client_cfg;
   };

  class Application : public ApplicationBase
   {
     const CmdDisplay cmd_display;

     DefString title;

     DragFrame main_frame;

     ExceptionClient exception_client;

     Window client;

    private:

     virtual void clearException() noexcept
      {
       exception_client.clear();
      }

     virtual void guardException()
      {
       exception_client.guard();
      }

     virtual void showException() noexcept
      {
       exception_client.show();
      }

     virtual void prepare()
      {
       main_frame.createMain(cmd_display,title);
      }

     virtual void beforeLoop() noexcept
      {
       exception_client.beforeLoop();
      }

     virtual void afterLoop() noexcept
      {
       exception_client.afterLoop();
      }

     virtual void final()
      {
       // do nothing
      }

     virtual void afterWait()
      {
       Ping(client);
      }

    public:

     template <class ... TT>
     Application(Param &param,WindowReportBase &report,CmdDisplay cmd_display_,const DefString &title_,TT && ... tt)
      : ApplicationBase(param.desktop,param.tick_period),
        cmd_display(cmd_display_),
        title(title_),
        main_frame(param.desktop,param.report_cfg),
        exception_client(main_frame,param.exception_cfg,report),
        client(main_frame,param.client_cfg, std::forward<TT>(tt)... )
      {
       main_frame.bindAlertClient(exception_client);
       main_frame.bindClient(client);
      }

     template <class P,class ... TT>
     Application(P &param,WindowReportBase &report,CmdDisplay cmd_display_,const DefString &title_,Signal<> &update,TT && ... tt)
      : ApplicationBase(param.desktop,param.tick_period),
        cmd_display(cmd_display_),
        title(title_),
        main_frame(param.desktop,param.report_cfg,update),
        exception_client(main_frame,param.exception_cfg,report),
        client(main_frame,update, std::forward<TT>(tt)... )
      {
       main_frame.bindAlertClient(exception_client);
       main_frame.bindClient(client);
      }

     ~Application()
      {
      }
   };

  static int Main(CmdDisplay cmd_display,const DefString &title)
   {
    try
      {
       TaskMemStack tms(64_KByte);

       Param param;
       WindowReport report(param);

       SetAppIcon(DefaultAppIcon());

       Application app(param,report,cmd_display,title);

       return app.run();
      }
    catch(CatchType)
      {
       return 1;
      }
   }

  template <class T>
  static int MainExtra(CmdDisplay cmd_display,const DefString &title)
   {
    try
      {
       TaskMemStack tms(64_KByte);

       Param param;
       WindowReport report(param);

       SetAppIcon(DefaultAppIcon());

       T extra(InterruptFunction(param.desktop));

       Application app(param,report,cmd_display,title,extra);

       return app.run();
      }
    catch(CatchType)
      {
       return 1;
      }
   }

  static int MainFrame(CmdDisplay cmd_display,const DefString &title)
   {
    try
      {
       TaskMemStack tms(64_KByte);

       WindowReportParam param;
       Signal<> updated;
       WindowReport report(param);

       SetAppIcon(DefaultAppIcon());

       Application app(param,report,cmd_display,title,updated,param.report_cfg);

       return app.run();
      }
    catch(CatchType)
      {
       return 1;
      }
   }
 };

/* class BufReport */

class BufReport : public ReportException
 {
   static const ulen BufLen = 2_KByte ;

   char buf[BufLen];
   PrintBuf out;

  private:

   virtual void print(StrLen str)
    {
     Putobj(out,str);
    }

   virtual void end()
    {
     Printf(out,"\n\n#;\n\n",TextDivider());
    }

  public:

   BufReport() : out(Range(buf)) {}

   ~BufReport() {}

   StrLen close() { return out.close(); }
 };

/* class ResultBuilder */

class ResultBuilder : Task
 {
   Function<void (void)> interrupt;

   Atomic ready;
   Atomic cancel;

   Sem stop_sem;

   mutable Mutex mutex;

   unsigned total;
   unsigned current = 0 ;
   bool done = false ;
   Info result;

  private:

   virtual void work()=0;

   virtual void entry(); // define in a derived class

   virtual void exit();

  protected:

   bool getCancel() const { return cancel; }

   void setCurrent(unsigned current);

   void setResult(const Info &result);

   void setResult(DefString str) { setResult(InfoFromString(str)); }

  public:

   ResultBuilder(Function<void (void)> interrupt,unsigned total_);

   ~ResultBuilder();

   void start();

   void stop();

   unsigned getTotal() const;

   unsigned getCurrent() const;

   bool getDone() const;

   Info getResult() const;
 };

/* class ResultWindow */

class ResultWindow : public ComboWindow
 {
  public:

   struct ConfigType
    {
     RefVal<VColor> back = Silver ;

     RefVal<Coord> split_dy = 40 ;
     RefVal<Coord> delta_dx = 20 ;
     RefVal<Coord> delta_dy = 10 ;

     RefVal<ProgressWindow::ConfigType> progress_cfg;
     RefVal<InfoWindow::ConfigType> info_cfg;

     ConfigType() {}
    };

  private:

   const ConfigType &cfg;

   ResultBuilder &builder;

   ProgressWindow progress;
   InfoWindow info;

  public:

   ResultWindow(SubWindowHost &host,const ConfigType &cfg,ResultBuilder &builder);

   ~ResultWindow();

   // methods

   void ping();

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


