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

template <class AppProp,class Param> class ApplicationOf;

template <class AppProp> class Application;

/* struct AppProp */

#if 0

struct AppProp
 {
  static StrLen Key()
   {
    return "/AppName-Unid"_c;
   }

  static StrLen File() // opt
   {
    return "/FileName.ddl"_c;
   }

  static Picture Icon() { return DefaultAppIcon(); }

  using PreferenceBag = ??? ;

  using ClientWindow = ??? ;

  using Opt = ??? ;

  using Persist = ??? ;

  static constexpr PrepareOpt Prepare = ??? ;
 };

#endif

/* concept FindFontsBagType<Bag> */

template <class Bag>
concept bool FindFontsBagType = requires(Bag &bag) { bag.findFonts(); } ;

/* concept AppPropHasFile<AppProp> */

template <class AppProp>
concept bool AppPropHasFile = requires() { { AppProp::File() } -> StrLen ; } ;

/* class AppPreference<AppProp> */

template <class AppProp>
class AppPreference : public ConfigBinder<typename AppProp::PreferenceBag>
 {
   StrLen File() requires( AppPropHasFile<AppProp> )
    {
     return AppProp::File();
    }

   StrLen File() requires( !AppPropHasFile<AppProp> )
    {
     return "/AppPreference.ddl"_c;
    }

   void findFonts() requires( FindFontsBagType<typename AppProp::PreferenceBag> )
    {
     this->ref().findFonts();

     update();
    }

   void findFonts() requires( !FindFontsBagType<typename AppProp::PreferenceBag> )
    {
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
     if( !this->syncHome(AppProp::Key(),File()) )
       {
        findFonts();
       }
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

  void sync()
   {
    user_pref.sync();
    app_pref.sync();
   }
 };

/* class ApplicationOf<AppProp,Param> */

template <class AppProp,class Param>
class ApplicationOf : public ApplicationBase
 {
  protected:

   Param &param;

   const CmdDisplay cmd_display;

   DragFrame main_frame;

   ExceptionClient exception_client;

   typename AppProp::ClientWindow client;

   UserPreference editor_pref;
   ConfigEditorFrame user_frame;
   ConfigEditorFrame app_frame;

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
     String title=param.app_pref.get().title;

     main_frame.createMain(cmd_display,title);
    }

   void prepareMain() requires ( AppProp::Prepare==PrepareCenter )
    {
     String title=param.app_pref.get().title;
     Ratio frame_pos_ry=param.user_pref.get().frame_pos_ry;

     Point size=main_frame.getMinSize(true,Range(title),client.getMinSize());

     Pane pane=GetWindowPlace(desktop,frame_pos_ry,size);

     main_frame.createMain(cmd_display,pane,title);
    }

   void prepareMain() requires ( AppProp::Prepare==PreparePersist )
    {
     String title=param.app_pref.get().title;

     typename AppProp::Persist persist;

     if( persist.load() )
       {
        client.prepare(persist);

        main_frame.createMain(cmd_display,persist.place,title);
       }
     else
       {
        main_frame.createMain(cmd_display,title);
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

   SignalConnector<ApplicationOf,Point> connector_userPref;
   SignalConnector<ApplicationOf,Point> connector_appPref;

   void appUpdated()
    {
     param.user_pref.updated.assert();
    }

   void appSave()
    {
     param.app_pref.update();
    }

   SignalConnector<ApplicationOf> connector_app_updated;
   SignalConnector<ApplicationOf> connector_app_save;

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

   SignalConnector<ApplicationOf> connector_user_updated;
   SignalConnector<ApplicationOf> connector_user_save;
   SignalConnector<ApplicationOf> connector_user_self;

  public:

   using Opt = typename AppProp::Opt ;

   ApplicationOf(WindowReportBase &report,Param &param_,CmdDisplay cmd_display_,const Opt &opt)
    : ApplicationBase(param_.desktop,param_.tick_period),

      param(param_),
      cmd_display(cmd_display_),

      main_frame(param.desktop,param.frame_cfg,param.user_pref.updated),
      exception_client(main_frame,param.exception_cfg,report),
      client(main_frame,param.client_cfg,opt,param.user_pref.updated),
      user_frame(param.desktop,editor_pref.getSmartConfig(),true),
      app_frame(param.desktop,param.user_pref.getSmartConfig(),false),

      connector_userPref(this,&ApplicationOf::userPref,client.doUserPref),
      connector_appPref(this,&ApplicationOf::appPref,client.doAppPref),

      connector_app_updated(this,&ApplicationOf::appUpdated,app_frame.updated),
      connector_app_save(this,&ApplicationOf::appSave,app_frame.doSave),

      connector_user_updated(this,&ApplicationOf::userUpdate,user_frame.updated),
      connector_user_save(this,&ApplicationOf::userSave,user_frame.doSave),
      connector_user_self(this,&ApplicationOf::userSelf,user_frame.doSelf)
    {
     main_frame.bindAlertClient(exception_client);
     main_frame.bindClient(client);

     editor_pref.ref()=param.user_pref.get();

     user_frame.bindConfig(param.user_pref);
     user_frame.connectUpdate(editor_pref.updated);

     app_frame.bindConfig(param.app_pref);
     app_frame.connectUpdate(param.user_pref.updated);
    }

   ~ApplicationOf()
    {
    }
 };

/* class Application<AppProp> */

template <class AppProp>
class Application : public ApplicationOf<AppProp,AppParam<AppProp> >
 {
  public:

   using ApplicationOf<AppProp,AppParam<AppProp> >::ApplicationOf;
 };

/* AppMainOf() */

template <class AppProp,class Param,class Application>
int AppMainOf(CmdDisplay cmd_display,int argc,const char *argv[])
 {
  try
    {
     TaskMemStack tms(64_KByte);

     Param param;
     WindowReport report(param);

     SetAppIcon(AppProp::Icon());

     param.sync();

     using Opt = typename AppProp::Opt ;

     Application app(report,param,cmd_display,Opt(argc,argv));

     return app.run();
    }
  catch(CatchType)
    {
     return 1;
    }
 }

/* AppMain() */

template <class AppProp>
int AppMain(CmdDisplay cmd_display,int argc,const char *argv[])
 {
  return AppMainOf<AppProp,AppParam<AppProp>,Application<AppProp> >(cmd_display,argc,argv);
 }

} // namespace Video
} // namespace CCore

#endif

