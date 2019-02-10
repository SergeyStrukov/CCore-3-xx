/* Application.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: UserPreference 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/TestFrame.h>

#include <CCore/inc/video/ApplicationBase.h>
#include <CCore/inc/video/WindowReport.h>
#include <CCore/inc/video/Picture.h>
#include <CCore/inc/video/ConfigEditor.h>
#include <CCore/inc/video/Layout.h>

#include <CCore/inc/TaskMemStack.h>

namespace App {

/* classes */

struct Param;

class Application;

/* struct Param */

struct Param
 {
  Desktop *desktop = DefaultDesktop ;
  MSec tick_period = DeferCallQueue::DefaultTickPeriod ;

  UserPreference pref;

  const WindowReportConfig &report_cfg;
  const ExceptionWindow::ConfigType &exception_cfg;
  const DragFrame::ConfigType &frame_cfg;
  const ConfigEditorFrame::ConfigType &editor_cfg;

  Param() noexcept
   : report_cfg(pref.getSmartConfig()),
     exception_cfg(pref.getSmartConfig()),
     frame_cfg(pref.getSmartConfig()),
     editor_cfg(pref.getSmartConfig())
   {
   }
 };

/* class Application */

class Application : public ApplicationBase
 {
   UserPreference &self_pref;

   const CmdDisplay cmd_display;

   UserPreference pref;

   ConfigEditorFrame main_frame;

   ExceptionClient exception_client;

   TestFrame test_frame;

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
     pref.sync();

     main_frame.bindConfig(pref.ref());

     Point size=desktop->getScreenSize();

     Coord y=Div(1,6)*size.y;
     Coord dy=Div(2,3)*size.y;

     Coord x1=Div(1,12)*size.x;
     Coord dx1=Div(1,2)*size.x;

     Coord x2=x1+dx1+10;
     Coord dx2=Div(1,3)*size.x;

     Pane pane1(x1,y,dx1,dy);
     Pane pane2(x2,y,dx2,dy);

     main_frame.createMain(cmd_display,pane1,"User Preferences"_str);

     test_frame.create(&main_frame,pane2,"Test frame"_str);
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

  private:

   void pref_updated()
    {
     pref.updated.assert();
    }

   void pref_save()
    {
     pref.update();
    }

   void pref_self()
    {
     self_pref.ref()=pref.get();

     self_pref.updated.assert();
    }

   SignalConnector<Application> connector_updated;
   SignalConnector<Application> connector_doSave;
   SignalConnector<Application> connector_doSelf;

   void test_destroyed()
    {
     main_frame.askClose();
    }

   SignalConnector<Application> connector_test_destroyed;

  public:

   explicit Application(WindowReportBase &report,Param &param,CmdDisplay cmd_display_)
    : ApplicationBase(param.desktop,param.tick_period),
      self_pref(param.pref),
      cmd_display(cmd_display_),
      main_frame(param.desktop,param.editor_cfg,true),
      exception_client(main_frame,param.exception_cfg,report),
      test_frame(param.desktop,pref,pref.updated),

      connector_updated(this,&Application::pref_updated,main_frame.updated),
      connector_doSave(this,&Application::pref_save,main_frame.doSave),
      connector_doSelf(this,&Application::pref_self,main_frame.doSelf),
      connector_test_destroyed(this,&Application::test_destroyed,test_frame.destroyed)
    {
     main_frame.bindAlertClient(exception_client);
     main_frame.connectUpdate(param.pref.updated);
    }

   ~Application()
    {
    }
 };

/* Main() */

int Main(CmdDisplay cmd_display)
 {
  try
    {
     TaskMemStack tms(64_KByte);

     Param param;
     WindowReport report(param);

     SetAppIcon(DefaultAppIcon());

     Application app(report,param,cmd_display);

     return app.run();
    }
  catch(CatchType)
    {
     return 1;
    }
 }

} // namespace App


