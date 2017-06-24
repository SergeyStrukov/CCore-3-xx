/* Application.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: Aspect 1.01
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

#include <CCore/inc/TaskMemStack.h>

namespace App {

/* AppKey() */

StrLen AppKey()
 {
  return "/5399CEC08CD81156F71679107FBC42A596486B06FDE5AAE7C17475ADA6DB9A2C"_c;
 }

/* classes */

struct AppPreferenceBag;

class AppPreference;

struct Param;

class Application;

/* struct AppPreferenceBag */

struct AppPreferenceBag : ConfigItemHost
 {
  // common

  DefString title = "Aspect"_def ;

  DefString text_Path   = "Path"_def ;
  DefString text_Aspect = "Aspect"_def ;

  DefString text_Nothing = "Nothing to save!"_def ;
  DefString text_Save    = "Save"_def ;

  // menu

  DefString text_SelectPath = "Select a project path"_def ;

  DefString menu_File    = "@File"_def ;
  DefString menu_Actions = "@Actions"_def ;
  DefString menu_Options = "@Options"_def ;
  DefString menu_New     = "@New ..."_def ;
  DefString menu_Open    = "@Open ..."_def ;
  DefString menu_Save    = "@Save"_def ;
  DefString menu_SaveAs  = "Save @as ..."_def ;
  DefString menu_Exit    = "E@xit"_def ;
  DefString menu_Collect = "@Collect"_def ;
  DefString menu_Global  = "@Global ..."_def ;
  DefString menu_App     = "@Application ..."_def ;

  // hide

  Coord status_dxy = 30 ;

  DefString text_Hide    = "Hide"_def ;
  DefString text_ShowAll = "Show all"_def ;

  // count

  Coord count_status_dxy = 15 ;

  // item

  Coord item_dxy = 30 ;
  Coord item_rxy = 20 ;
  Coord item_rin =  2 ;
  Coord item_kxy = 20 ;

  VColor item_text = Black ;

  FontCouple item_font;

  VColor item_face1 = Black ;
  VColor item_face2 =  Gray ;
  VColor item_line  =  Navy ;

  // status

  VColor status_New    = SkyBlue ;
  VColor status_Ignore = Gray ;
  VColor status_Red    = Red ;
  VColor status_Yellow = Yellow ;
  VColor status_Green  = Green ;

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

  func("text_Path"_c,ptr->text_Path);
  func("text_Aspect"_c,ptr->text_Aspect);

  func("text_Nothing"_c,ptr->text_Nothing);
  func("text_Save"_c,ptr->text_Save);

  func("text_SelectPath"_c,ptr->text_SelectPath);

  func("menu_File"_c,ptr->menu_File);
  func("menu_Actions"_c,ptr->menu_Actions);
  func("menu_Options"_c,ptr->menu_Options);
  func("menu_New"_c,ptr->menu_New);
  func("menu_Open"_c,ptr->menu_Open);
  func("menu_Save"_c,ptr->menu_Save);
  func("menu_SaveAs"_c,ptr->menu_SaveAs);
  func("menu_Exit"_c,ptr->menu_Exit);
  func("menu_Collect"_c,ptr->menu_Collect);
  func("menu_Global"_c,ptr->menu_Global);
  func("menu_App"_c,ptr->menu_App);

  func("status_dxy"_c,ptr->status_dxy);
  func("text_Hide"_c,ptr->text_Hide);
  func("text_ShowAll"_c,ptr->text_ShowAll);

  func("count_status_dxy"_c,ptr->count_status_dxy);

  func("item_dxy"_c,ptr->item_dxy);
  func("item_rxy"_c,ptr->item_rxy);
  func("item_rin"_c,ptr->item_rin);
  func("item_kxy"_c,ptr->item_kxy);
  func("item_text"_c,ptr->item_text);
  func("item_font"_c,ptr->item_font.param);
  func("item_face1"_c,ptr->item_face1);
  func("item_face2"_c,ptr->item_face2);
  func("item_line"_c,ptr->item_line);

  func("status_New"_c,ptr->status_New);
  func("status_Ignore"_c,ptr->status_Ignore);
  func("status_Red"_c,ptr->status_Red);
  func("status_Yellow"_c,ptr->status_Yellow);
  func("status_Green"_c,ptr->status_Green);
 }

void AppPreferenceBag::bind(ConfigItemBind &binder)
 {
  binder.group("Common"_def);

    binder.item("title"_def,title);
    binder.space();
    binder.item("path"_def,text_Path);
    binder.item("aspect"_def,text_Aspect);
    binder.space();
    binder.item("nothing"_def,text_Nothing);
    binder.item("save"_def,text_Save);

  binder.group("Menu"_def);

    binder.item("path title"_def,text_SelectPath);
    binder.space();
    binder.item("'File'"_def,menu_File);
    binder.item("'Actions'"_def,menu_Actions);
    binder.item("'Options'"_def,menu_Options);
    binder.item("'New'"_def,menu_New);
    binder.item("'Open'"_def,menu_Open);
    binder.item("'Save'"_def,menu_Save);
    binder.item("'SaveAs'"_def,menu_SaveAs);
    binder.item("'Exit'"_def,menu_Exit);
    binder.item("'Collect'"_def,menu_Collect);
    binder.item("'Global'"_def,menu_Global);
    binder.item("'App'"_def,menu_App);

  binder.group("Hide"_def);

    binder.item("status dxy"_def,status_dxy);
    binder.space();
    binder.item("'Hide'"_def,text_Hide);
    binder.item("'ShowAll'"_def,text_ShowAll);

  binder.group("Count"_def);

    binder.item("count_status_dxy"_def,count_status_dxy);

  binder.group("Item"_def);

    binder.item("cell size"_def,item_dxy);
    binder.item("radio size"_def,item_rxy);
    binder.item("radio inner"_def,item_rin);
    binder.item("knob size"_def,item_kxy);
    binder.item("text"_def,item_text);
    binder.item("font"_def,item_font);
    binder.item("face1"_def,item_face1);
    binder.item("face2"_def,item_face2);
    binder.item("line"_def,item_line);

  binder.group("Status"_def);

    binder.item("New"_def,status_New);
    binder.item("Ignore"_def,status_Ignore);
    binder.item("Red"_def,status_Red);
    binder.item("Yellow"_def,status_Yellow);
    binder.item("Green"_def,status_Green);
 }

void AppPreferenceBag::createFonts()
 {
  item_font.create();
 }

/* class AppPreference */

class AppPreference : public ConfigBinder<AppPreferenceBag>
 {
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
     syncHome(AppKey(),File());
    }

   void update() noexcept
    {
     updateHome(AppKey(),File());
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

   void updated()
    {
     client.update(false);
    }

   SignalConnector<Application> connector_updated;

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
     AppState app_state;

     if( app_state.load() )
       {
        client.prepare(app_state);

        main_frame.createMain(cmd_display,app_state.place,param.app_pref.get().title);
       }
     else
       {
        main_frame.createMain(cmd_display,param.app_pref.get().title);
       }
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

   explicit Application(WindowReportBase &report,Param &param_,CmdDisplay cmd_display_,const char *open_file_name)
    : ApplicationBase(param_.desktop,param_.tick_period),
      param(param_),
      cmd_display(cmd_display_),
      main_frame(param.desktop,param.frame_cfg,param.user_pref.updated),
      exception_client(main_frame,param.exception_cfg,report),
      client(main_frame,param.client_cfg,open_file_name),
      user_frame(param.desktop,editor_pref.getSmartConfig(),true),
      app_frame(param.desktop,param.user_pref.getSmartConfig(),false),

      connector_userPref(this,&Application::userPref,client.doUserPref),
      connector_appPref(this,&Application::appPref,client.doAppPref),
      connector_app_updated(this,&Application::appUpdated,app_frame.updated),
      connector_app_save(this,&Application::appSave,app_frame.doSave),
      connector_user_updated(this,&Application::userUpdate,user_frame.updated),
      connector_user_save(this,&Application::userSave,user_frame.doSave),
      connector_user_self(this,&Application::userSelf,user_frame.doSelf),
      connector_updated(this,&Application::updated,param.user_pref.updated)
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

int Main(CmdDisplay cmd_display,const char *open_file_name)
 {
  try
    {
     TaskMemStack tms(64_KByte);

     Param param;
     WindowReport report(param);

     SetAppIcon(DefaultAppIcon());

     param.user_pref.sync();
     param.app_pref.sync();

     Application app(report,param,cmd_display,open_file_name);

     return app.run();
    }
  catch(CatchType)
    {
     return 1;
    }
 }

} // namespace App


