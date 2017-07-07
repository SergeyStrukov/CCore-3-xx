/* Application.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: DDLDisplay 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/Client.h>

#include <CCore/inc/video/ApplicationBase.h>
#include <CCore/inc/video/WindowReport.h>
#include <CCore/inc/video/FreeTypeFont.h>
#include <CCore/inc/video/Picture.h>

#include <CCore/inc/TaskMemStack.h>
#include <CCore/inc/Path.h>

namespace App {

/* classes */

struct AppPreferenceBag;

class AppPreference;

struct Param;

class Application;

/* struct AppPreferenceBag */

struct AppPreferenceBag : ConfigItemHost
 {
  Coord space_dxy = 3 ;

  Point space = Point(6,4) ;

  VColor text   =     Black ;
  VColor ptr    =      Blue ;
  VColor select = OrangeRed ;

  FontCouple title_font;
  FontCouple font;

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
  func("space_dxy"_c,ptr->space_dxy);
  func("space"_c,ptr->space);
  func("vc_text"_c,ptr->text);
  func("vc_ptr"_c,ptr->ptr);
  func("select"_c,ptr->select);
  func("title_font"_c,ptr->title_font.param);
  func("font"_c,ptr->font.param);
 }

void AppPreferenceBag::bind(ConfigItemBind &binder)
 {
  binder.group("DDL"_def);

   binder.item("space length"_def,space_dxy);
   binder.item("text space"_def,space);
   binder.item("text"_def,text);
   binder.item("pointer"_def,ptr);
   binder.item("select"_def,select);
   binder.item("title font"_def,title_font);
   binder.item("text font"_def,font);
 }

void AppPreferenceBag::createFonts()
 {
  title_font.create();
  font.create();
 }

/* class AppPreference */

class AppPreference : public ConfigBinder<AppPreferenceBag>
 {
   static StrLen Key() { return "/DDLDisplay-F7BEB23B4D025F4D0BB7C3033139083269233409EA11AD076E2B7DDBB90A4CBF"_c;  }

   static StrLen File() { return "/AppPreference.ddl"_c;  }

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

  UserPreference pref;
  AppPreference app_pref;

  const WindowReportConfig &report_cfg;
  const ExceptionWindow::ConfigType &exception_cfg;
  const DragFrame::ConfigType &frame_cfg;

  ClientWindow::ConfigType client_cfg;

  Param()
   : report_cfg(pref.getSmartConfig()),
     exception_cfg(pref.getSmartConfig()),
     frame_cfg(pref.getSmartConfig()),
     client_cfg(pref,app_pref)
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
        user_frame.create(main_frame.getFrame(),base,param.pref.get().title_UserPref);
       }
    }

   void appPref(Point base)
    {
     if( app_frame.isDead() )
       {
        app_frame.create(main_frame.getFrame(),base,param.pref.get().title_AppPref);
       }
    }

   SignalConnector<Application,Point> connector_userPref;
   SignalConnector<Application,Point> connector_appPref;

   void appUpdated()
    {
     client.updateCfg();

     param.pref.updated.assert();
    }

   void appSave()
    {
     param.app_pref.update();
    }

   SignalConnector<Application> connector_app_updated;
   SignalConnector<Application> connector_app_save;

   void userUpdate()
    {
     client.updateCfg();

     param.pref.updated.assert();
    }

   void userSave()
    {
     param.pref.update();
    }

   void userSelf()
    {
     editor_pref.ref()=param.pref.get();

     editor_pref.updated.assert();
    }

   SignalConnector<Application> connector_user_updated;
   SignalConnector<Application> connector_user_save;
   SignalConnector<Application> connector_user_self;

   void clientOpened(StrLen file_name,bool ok)
    {
     if( ok )
       {
        SplitPath path(file_name);
        SplitName name(path.path);

        main_frame.setTitle(String("DDL file: ")+name.name);
       }
     else
       {
        main_frame.setTitle("DDLDisplay"_def);
       }
    }

   SignalConnector<Application,StrLen,bool> connector_client_opened;

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
     main_frame.createMain(cmd_display,"DDLDisplay"_def);
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
      main_frame(param.desktop,param.frame_cfg,param.pref.updated),
      exception_client(main_frame,param.exception_cfg,report),
      client(main_frame,param.client_cfg),
      user_frame(param.desktop,editor_pref.getSmartConfig(),true),
      app_frame(param.desktop,param.pref.getSmartConfig(),false),

      connector_userPref(this,&Application::userPref,client.doUserPref),
      connector_appPref(this,&Application::appPref,client.doAppPref),
      connector_app_updated(this,&Application::appUpdated,app_frame.updated),
      connector_app_save(this,&Application::appSave,app_frame.doSave),
      connector_user_updated(this,&Application::userUpdate,user_frame.updated),
      connector_user_save(this,&Application::userSave,user_frame.doSave),
      connector_user_self(this,&Application::userSelf,user_frame.doSelf),
      connector_client_opened(this,&Application::clientOpened,client.opened)
    {
     main_frame.bindAlertClient(exception_client);
     main_frame.bindClient(client);

     editor_pref.ref()=param.pref.get();

     user_frame.bindConfig(param.pref.ref());
     user_frame.connectUpdate(editor_pref.updated);

     app_frame.bindConfig(param.app_pref.ref());
     app_frame.connectUpdate(param.pref.updated);
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

     param.pref.sync();
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


