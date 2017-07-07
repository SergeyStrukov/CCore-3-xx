/* Application.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: ContourLab 1.00
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

/* classes */

struct AppPreferenceBag;

class AppPreference;

struct Param;

class Application;

/* struct AppPreferenceBag */

struct AppPreferenceBag : ConfigItemHost
 {
  // common

  MCoord arrow_size = Fraction(5) ;

  Coord shade_dxy = 8 ;

  VColor back    =     White ;
  VColor border  =     Black ;
  VColor face    =     Black ;
  VColor gray    =      Gray ;
  VColor text    =      Blue ;
  VColor hilight =     Green ;
  VColor focus   = OrangeRed ;

  FontCouple font;

  // edit angle

  Coord edit_angle_dxy = 100 ;

  // edit length

  Coord edit_length_dx = 500 ;
  Coord edit_length_dy = 100 ;

  // edit ratio

  Coord edit_ratio_dx = 500 ;
  Coord edit_ratio_dy = 100 ;

  // edit formula

  VColor edit_text        =     Black ;
  VColor edit_error_text  =       Red ;
  VColor edit_number_text = DarkGreen ;
  VColor edit_length_text = DarkGreen ;
  VColor edit_angle_text  = DarkGreen ;
  VColor edit_name_text   =      Blue ;
  VColor edit_punct_text  =     Black ;

  unsigned edit_delay = 1_sectick ;

  // geometry

  Coord geometry_dxy = 300 ;

  // item list

  DefString text_show = "show"_def ;
  DefString text_gray = "gray"_def ;
  DefString text_name = "name"_def ;

  DefString title_Ins = "Function list"_def ;

  // menu

  DefString menu_File    = "@File"_def ;
  DefString menu_Options = "@Options"_def ;
  DefString menu_New     = "@New"_def ;
  DefString menu_Open    = "@Open ..."_def ;
  DefString menu_Save    = "@Save"_def ;
  DefString menu_SaveAs  = "Save @as ..."_def ;
  DefString menu_Exit    = "E@xit"_def ;
  DefString menu_Global  = "@Global ..."_def ;
  DefString menu_App     = "@Application ..."_def ;

  // hints

  DefString hint_File   = "The current file"_def ;
  DefString hint_Angle  = "Set the selected angle"_def ;
  DefString hint_Length = "Set the selected length"_def ;
  DefString hint_Ratio  = "Set the selected ratio"_def ;
  DefString hint_Geom   = "Draw of elements, use to set the selected point"_def ;

  DefString hint_function_List = "Select a function to be inserted into the cursor position"_def ;

  DefString hint_item_List = "Geometry object list"_def ;
  DefString hint_item_Edit = "Enter a formula to create a new object"_def ;

  DefString hint_item_Down = "Move the object down in the list"_def ;
  DefString hint_item_Up   = "Move the object up in the list"_def ;
  DefString hint_item_Del  = "Delete the object"_def ;
  DefString hint_item_Add  = "Add a new object"_def ;
  DefString hint_item_Ins  = "Open the Function list window"_def ;

  DefString hint_item_Show = "Show this object"_def ;
  DefString hint_item_Gray = "Gray this object if not selected"_def ;
  DefString hint_item_Name = "Show the name of this object"_def ;

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
  func("arrow_size"_c,ptr->arrow_size);

  func("shade_dxy"_c,ptr->shade_dxy);

  func("back"_c,ptr->back);
  func("border"_c,ptr->border);
  func("face"_c,ptr->face);
  func("gray"_c,ptr->gray);
  func("vtext"_c,ptr->text);
  func("hilight"_c,ptr->hilight);
  func("focus"_c,ptr->focus);

  func("font"_c,ptr->font.param);

  func("edit_angle_dxy"_c,ptr->edit_angle_dxy);

  func("edit_length_dx"_c,ptr->edit_length_dx);
  func("edit_length_dy"_c,ptr->edit_length_dy);

  func("edit_ratio_dx"_c,ptr->edit_ratio_dx);
  func("edit_ratio_dy"_c,ptr->edit_ratio_dy);

  func("edit_text"_c,ptr->edit_text);
  func("edit_error_text"_c,ptr->edit_error_text);
  func("edit_number_text"_c,ptr->edit_number_text);
  func("edit_length_text"_c,ptr->edit_length_text);
  func("edit_angle_text"_c,ptr->edit_angle_text);
  func("edit_name_text"_c,ptr->edit_name_text);
  func("edit_punct_text"_c,ptr->edit_punct_text);

  func("edit_delay"_c,ptr->edit_delay);

  func("geometry_dxy"_c,ptr->geometry_dxy);

  func("text_show"_c,ptr->text_show);
  func("text_gray"_c,ptr->text_gray);
  func("text_name"_c,ptr->text_name);

  func("title_Ins"_c,ptr->title_Ins);

  func("menu_File"_c,ptr->menu_File);
  func("menu_Options"_c,ptr->menu_Options);
  func("menu_New"_c,ptr->menu_New);
  func("menu_Open"_c,ptr->menu_Open);
  func("menu_Save"_c,ptr->menu_Save);
  func("menu_SaveAs"_c,ptr->menu_SaveAs);
  func("menu_Exit"_c,ptr->menu_Exit);
  func("menu_Global"_c,ptr->menu_Global);
  func("menu_App"_c,ptr->menu_App);

  func("hint_File"_c,ptr->hint_File);
  func("hint_Angle"_c,ptr->hint_Angle);
  func("hint_Length"_c,ptr->hint_Length);
  func("hint_Ratio"_c,ptr->hint_Ratio);
  func("hint_Geom"_c,ptr->hint_Geom);

  func("hint_function_List"_c,ptr->hint_function_List);

  func("hint_item_List"_c,ptr->hint_item_List);
  func("hint_item_Edit"_c,ptr->hint_item_Edit);

  func("hint_item_Down"_c,ptr->hint_item_Down);
  func("hint_item_Up"_c,ptr->hint_item_Up);
  func("hint_item_Del"_c,ptr->hint_item_Del);
  func("hint_item_Add"_c,ptr->hint_item_Add);
  func("hint_item_Ins"_c,ptr->hint_item_Ins);

  func("hint_item_Show"_c,ptr->hint_item_Show);
  func("hint_item_Gray"_c,ptr->hint_item_Gray);
  func("hint_item_Name"_c,ptr->hint_item_Name);
 }

void AppPreferenceBag::bind(ConfigItemBind &binder)
 {
  binder.group("Common"_def);

    binder.item("arrow size"_def,arrow_size);
    binder.item("shade dxy"_def,shade_dxy);
    binder.space();
    binder.item("back"_def,back);
    binder.item("border"_def,border);
    binder.item("face"_def,face);
    binder.item("gray"_def,gray);
    binder.item("text"_def,text);
    binder.item("hilight"_def,hilight);
    binder.item("focus"_def,focus);
    binder.space();
    binder.item("font"_def,font);

  binder.group("Edit"_def);

    binder.item("angle dxy"_def,edit_angle_dxy);
    binder.item("length dx"_def,edit_length_dx);
    binder.item("length dy"_def,edit_length_dy);
    binder.item("ratio dx"_def,edit_ratio_dx);
    binder.item("ratio dy"_def,edit_ratio_dy);
    binder.item("text"_def,edit_text);
    binder.item("error text"_def,edit_error_text);
    binder.item("number text"_def,edit_number_text);
    binder.item("length text"_def,edit_length_text);
    binder.item("angle text"_def,edit_angle_text);
    binder.item("name text"_def,edit_name_text);
    binder.item("punct text"_def,edit_punct_text);
    binder.item("delay"_def,edit_delay);
    binder.item("geometry dxy"_def,geometry_dxy);

  binder.group("Item list"_def);

    binder.item("'show'"_def,text_show);
    binder.item("'gray'"_def,text_gray);
    binder.item("'name'"_def,text_name);

    binder.item("'Ins'"_def,title_Ins);

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

  binder.group("Hints"_def);

    binder.item("?'File'"_def,hint_File);
    binder.item("?'Angle'"_def,hint_Angle);
    binder.item("?'Length'"_def,hint_Length);
    binder.item("?'Ration'"_def,hint_Ratio);
    binder.item("?'Geom'"_def,hint_Geom);
    binder.item("?'Function List'"_def,hint_function_List);
    binder.item("?'List'"_def,hint_item_List);
    binder.item("?'Edit'"_def,hint_item_Edit);
    binder.item("?'Down'"_def,hint_item_Down);
    binder.item("?'Up'"_def,hint_item_Up);
    binder.item("?'Del'"_def,hint_item_Del);
    binder.item("?'Add'"_def,hint_item_Add);
    binder.item("?'Ins'"_def,hint_item_Ins);
    binder.item("?'Show'"_def,hint_item_Show);
    binder.item("?'Gray'"_def,hint_item_Gray);
    binder.item("?'Name'"_def,hint_item_Name);
 }

void AppPreferenceBag::createFonts()
 {
  font.create();
 }

/* class AppPreference */

class AppPreference : public ConfigBinder<AppPreferenceBag>
 {
   static StrLen Key() { return "/ContourLab-5C73F691B5ED963C3580A06131FD2D6EC57ECE3349028B3986554636EC1A70B8"_c;  }

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

  Param() noexcept
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
     main_frame.createMain(cmd_display,"ContourLab"_def);
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
      connector_user_self(this,&Application::userSelf,user_frame.doSelf)
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


