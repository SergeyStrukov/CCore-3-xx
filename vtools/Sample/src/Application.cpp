/* Application.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: Sample 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/Client.h>

#include <CCore/inc/video/ApplicationBase.h>
#include <CCore/inc/video/WindowReport.h>
#include <CCore/inc/video/ConfigEditor.h>
#include <CCore/inc/video/Picture.h>

#include <CCore/inc/video/Layout.h>

#include <CCore/inc/TaskMemStack.h>

namespace App {

/* classes */

struct AppPreferenceBag;

class AppPreference;

struct Param;

class Application;

/* struct AppPreferenceBag */

struct AppPreferenceBag : ConfigItemHost
 {
  // common

  DefString title = "Sample"_def ;

  // menu

  DefString menu_File    = "@File"_def ;
  DefString menu_Options = "@Options"_def ;
  DefString menu_New     = "@New"_def ;
  DefString menu_Open    = "@Open"_def ;
  DefString menu_Save    = "@Save"_def ;
  DefString menu_SaveAs  = "Save @as"_def ;
  DefString menu_Exit    = "E@xit"_def ;
  DefString menu_Global  = "@Global"_def ;
  DefString menu_App     = "@Application"_def ;

  // constructors

  AppPreferenceBag() noexcept {}

  // methods

  template <class Ptr,class Func>
  static void Members(Ptr ptr,Func func);

  virtual void bind(ConfigItemBind &binder);

  void createFonts();
 };

template <class Ptr,class Func>
void AppPreferenceBag::Members(Ptr ptr,Func func)
 {
  func("title"_c,ptr->title);
  func("menu_File"_c,ptr->menu_File);
  func("menu_Options"_c,ptr->menu_Options);
  func("menu_New"_c,ptr->menu_New);
  func("menu_Open"_c,ptr->menu_Open);
  func("menu_Save"_c,ptr->menu_Save);
  func("menu_SaveAs"_c,ptr->menu_SaveAs);
  func("menu_Exit"_c,ptr->menu_Exit);
  func("menu_Global"_c,ptr->menu_Global);
  func("menu_App"_c,ptr->menu_App);
 }

void AppPreferenceBag::bind(ConfigItemBind &binder)
 {
  binder.group("Common"_def);

    binder.item("title"_def,title);

  binder.group("Menu"_def);

    binder.item("File"_def,menu_File);
    binder.item("Options"_def,menu_Options);
    binder.item("New"_def,menu_New);
    binder.item("Open"_def,menu_Open);
    binder.item("Save"_def,menu_Save);
    binder.item("SaveAs"_def,menu_SaveAs);
    binder.item("Exit"_def,menu_Exit);
    binder.item("Global"_def,menu_Global);
    binder.item("App"_def,menu_App);
 }

void AppPreferenceBag::createFonts()
 {
 }

/* class AppPreference */

class AppPreference : public ConfigBinder<AppPreferenceBag>
 {
   static StrLen Key() { return "/Sample-C602A13695888C96BDBD9974F3540726673F4B879C8FB301FC8ED79E84E385A0"_c; }

   static StrLen File() { return "/AppPreference.ddl"_c; }

  public:

   // constructors

   AppPreference() noexcept
    {
    }

   ~AppPreference()
    {
    }

   // methods

   void sync() noexcept
    {
     syncHome(Key(),File());
    }

   void update() noexcept
    {
     updateHome(Key(),File());
    }
 };

/* struct Param */

struct Param
 {
  Desktop *desktop = DefaultDesktop ;
  MSec tick_period = DeferCallQueue::DefaultTickPeriod ;

  UserPreference user_pref;
  AppPreference app_pref;

  const WindowReportConfig &report_cfg;
  const ExceptionWindow::ConfigType &exception_cfg;
  const DragFrame::ConfigType &frame_cfg;

  ClientWindow::ConfigType client_cfg;

  Param() noexcept
   : report_cfg(user_pref.getSmartConfig()),
     exception_cfg(user_pref.getSmartConfig()),
     frame_cfg(user_pref.getSmartConfig()),
     client_cfg(user_pref,app_pref)
   {
   }
 };

/* class Application */

class Application : public ApplicationBase
 {
   Param &param;

   const CmdDisplay cmd_display;

   DragFrame main_frame;

   ExceptionClient exception_client;

   ClientWindow client;

   UserPreference editor_pref;
   ConfigEditorFrame user_frame;
   ConfigEditorFrame app_frame;

  private:

   void userPref(Point base)
    {
     if( user_frame.isDead() )
       {
        user_frame.create(main_frame.getFrame(),base,param.user_pref.get().title_UserPref);
       }
    }

   void appPref(Point base)
    {
     if( app_frame.isDead() )
       {
        app_frame.create(main_frame.getFrame(),base,param.user_pref.get().title_AppPref);
       }
    }

   SignalConnector<Application,Point> connector_userPref;
   SignalConnector<Application,Point> connector_appPref;

   void appUpdated()
    {
     param.user_pref.updated.assert();
    }

   void appSave()
    {
     param.app_pref.update();
    }

   SignalConnector<Application> connector_app_updated;
   SignalConnector<Application> connector_app_save;

   void userUpdate()
    {
     param.user_pref.updated.assert();
    }

   void userSave()
    {
     param.user_pref.update();
    }

   void userSelf()
    {
     editor_pref.ref()=param.user_pref.get();

     editor_pref.updated.assert();
    }

   SignalConnector<Application> connector_user_updated;
   SignalConnector<Application> connector_user_save;
   SignalConnector<Application> connector_user_self;

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
#if 1

     DefString title=param.app_pref.get().title;
     Ratio frame_pos_ry=param.user_pref.get().frame_pos_ry;

     Point size=main_frame.getMinSize(true,title.str(),client.getMinSize(LayoutUpdate));

     Pane pane=GetWindowPlace(desktop,frame_pos_ry,size);

     main_frame.createMain(cmd_display,pane,title);

#else

     main_frame.createMain(cmd_display,param.app_pref.get().title);

#endif
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

  public:

   explicit Application(WindowReportBase &report,Param &param_,CmdDisplay cmd_display_)
    : ApplicationBase(param_.desktop,param_.tick_period),
      param(param_),
      cmd_display(cmd_display_),
      main_frame(param.desktop,param.frame_cfg,param.user_pref.updated),
      exception_client(main_frame,param.exception_cfg,report),
      client(main_frame,param.client_cfg,param.user_pref.updated),
      user_frame(param.desktop,editor_pref.getSmartConfig(),true),
      app_frame(param.desktop,param.user_pref.getSmartConfig(),false),

      connector_userPref(this,&Application::userPref,client.doUserPref),
      connector_appPref(this,&Application::appPref,client.doAppPref),
      connector_app_updated(this,&Application::appUpdated,app_frame.updated),
      connector_app_save(this,&Application::appSave,app_frame.doSave),
      connector_user_updated(this,&Application::userUpdate,user_frame.updated),
      connector_user_save(this,&Application::userSave,user_frame.doSave),
      connector_user_self(this,&Application::userSelf,user_frame.doSelf)
    {
     main_frame.bindAlertClient(exception_client);
     main_frame.bindClient(client);

     editor_pref.ref()=param.user_pref.get();

     user_frame.bindConfig(param.user_pref.ref());
     user_frame.connectUpdate(editor_pref.updated);

     app_frame.bindConfig(param.app_pref.ref());
     app_frame.connectUpdate(param.user_pref.updated);
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

     param.user_pref.sync();
     param.app_pref.sync();

     Application app(report,param,cmd_display);

     return app.run();
    }
  catch(CatchType)
    {
     return 1;
    }
 }

} // namespace App


