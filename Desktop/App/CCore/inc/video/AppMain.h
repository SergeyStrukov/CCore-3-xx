/* AppMain.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Desktop
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_video_AppMain_h
#define CCore_inc_video_AppMain_h

#include <CCore/inc/video/UserPreference.h>

#include <CCore/inc/video/ApplicationBase.h>
#include <CCore/inc/video/WindowReport.h>
#include <CCore/inc/video/ConfigEditor.h>
#include <CCore/inc/video/Picture.h>

#include <CCore/inc/TaskMemStack.h>

namespace CCore {
namespace Video {

/* enum PrepareOpt */

enum PrepareOpt
 {
  PrepareRandom,
  PrepareCenter,
  PreparePersist
 };

/* classes */

template <class AppProp> class AppPreference;

template <class AppProp> struct AppParam;

/* struct AppProp */

#if 0

struct AppProp
 {
  static StrLen Key()
   {
    return "/AppName-Unid"_c;
   }

  static Picture Icon() { return DefaultAppIcon(); }

  using PreferenceBag = ??? ;

  using ClientWindow = ??? ;

  using Opt = ??? ;

  using Persist = ??? ;

  static constexpr PrepareOpt Prepare = ??? ;
 };

#endif

/* class AppPreference<AppProp> */

template <class AppProp>
class AppPreference : public ConfigBinder<typename AppProp::PreferenceBag>
 {
   static StrLen File()
    {
     return "/AppPreference.ddl"_c;
    }

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
     this->syncHome(AppProp::Key(),File());
    }

   void update() noexcept
    {
     this->updateHome(AppProp::Key(),File());
    }
 };

/* struct AppParam<AppProp> */

template <class AppProp>
struct AppParam
 {
  Desktop *desktop = DefaultDesktop ;
  MSec tick_period = DeferCallQueue::DefaultTickPeriod ;

  UserPreference user_pref;
  AppPreference<AppProp> app_pref;

  const WindowReportConfig &report_cfg;
  const ExceptionWindow::ConfigType &exception_cfg;
  const DragFrame::ConfigType &frame_cfg;

  using ClientWindow = typename AppProp::ClientWindow ;

  typename ClientWindow::ConfigType client_cfg;

  AppParam() noexcept
   : report_cfg(user_pref.getSmartConfig()),
     exception_cfg(user_pref.getSmartConfig()),
     frame_cfg(user_pref.getSmartConfig()),
     client_cfg(user_pref,app_pref)
   {
   }
 };

/* class Application<AppProp> */

template <class AppProp>
class Application : public ApplicationBase
 {
   AppParam<AppProp> &param;

   const CmdDisplay cmd_display;

   DragFrame main_frame;

   ExceptionClient exception_client;

   typename AppProp::ClientWindow client;

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

   void prepareMain() requires ( AppProp::Prepare==PrepareRandom )
    {
     main_frame.createMain(cmd_display,param.app_pref.get().title);
    }

   void prepareMain() requires ( AppProp::Prepare==PrepareCenter )
    {
     DefString title=param.app_pref.get().title;
     Ratio frame_pos_ry=param.user_pref.get().frame_pos_ry;

     Point size=main_frame.getMinSize(true,title.str(),client.getMinSize());

     Pane pane=GetWindowPlace(desktop,frame_pos_ry,size);

     main_frame.createMain(cmd_display,pane,param.app_pref.get().title);
    }

   void prepareMain() requires ( AppProp::Prepare==PreparePersist )
    {
     typename AppProp::Persist persist;

     if( persist.load() )
       {
        client.prepare(persist);

        main_frame.createMain(cmd_display,persist.place,param.app_pref.get().title);
       }
     else
       {
        main_frame.createMain(cmd_display,param.app_pref.get().title);
       }
    }

   virtual void prepare()
    {
     prepareMain();
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

   using Opt = typename AppProp::Opt ;

   explicit Application(WindowReportBase &report,AppParam<AppProp> &param_,CmdDisplay cmd_display_,const Opt &opt)
    : ApplicationBase(param_.desktop,param_.tick_period),
      param(param_),
      cmd_display(cmd_display_),
      main_frame(param.desktop,param.frame_cfg,param.user_pref.updated),
      exception_client(main_frame,param.exception_cfg,report),
      client(main_frame,param.client_cfg,opt,param.user_pref.updated),
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

/* AppMain() */

template <class AppProp>
int AppMain(CmdDisplay cmd_display,int argc,const char *argv[])
 {
  try
    {
     TaskMemStack tms(64_KByte);

     AppParam<AppProp> param;
     WindowReport report(param);

     SetAppIcon(AppProp::Icon());

     param.user_pref.sync();
     param.app_pref.sync();

     using Opt = typename AppProp::Opt ;

     Application<AppProp> app(report,param,cmd_display,Opt(argc,argv));

     return app.run();
    }
  catch(CatchType)
    {
     return 1;
    }
 }

} // namespace Video
} // namespace CCore

#endif

