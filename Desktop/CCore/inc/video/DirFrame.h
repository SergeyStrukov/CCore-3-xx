/* DirFrame.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
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

#ifndef CCore_inc_video_DirFrame_h
#define CCore_inc_video_DirFrame_h

#include <CCore/inc/video/FileFrame.h>

namespace CCore {
namespace Video {

/* classes */

struct DirWindowParam;

class DirWindow;

class DirFrame;

/* struct DirWindowParam */

struct DirWindowParam
 {
  FileBoss file_boss;
 };

/* class DirWindow */

class DirWindow : public ComboWindow
 {
  public:

   struct Config
    {
     RefVal<Coord> space_dxy = 10 ;

     RefVal<VColor> back = Silver ;

     RefVal<DefString> text_Ok       = "Ok"_def ;
     RefVal<DefString> text_Cancel   = "Cancel"_def ;

     RefVal<DefString> hint_FileHitList   = "Open/close the hit directory list"_def ;
     RefVal<DefString> hint_FileAddHit    = "Add the current directory to the hit list"_def ;
     RefVal<DefString> hint_FileUpdir     = "Goto the parent directory"_def ;
     RefVal<DefString> hint_FileCurdir    = "Current directory"_def ;
     RefVal<DefString> hint_FileDirList   = "Subdirectory list"_def ;
     RefVal<DefString> hint_FileMakeDir   = "Create a new directory"_def ;
     RefVal<DefString> hint_FileRemoveDir = "Delete the selected directory"_def ;

     CtorRefVal<DirEditWindow::ConfigType> edit_cfg;
     CtorRefVal<ScrollListWindow::ConfigType> list_cfg;
     CtorRefVal<RefButtonWindow::ConfigType> btn_cfg;
     CtorRefVal<KnobWindow::ConfigType> knob_cfg;

     CtorRefVal<SimpleCascadeMenu::ConfigType> hit_menu_cfg;

     CtorRefVal<XDoubleLineWindow::ConfigType> line_cfg;

     Config() noexcept {}

     template <class Bag,class Proxy>
     void bind(const Bag &bag,Proxy proxy)
      {
       space_dxy.bind(bag.space_dxy);
       back.bind(bag.back);
       text_Ok.bind(bag.text_Ok);
       text_Cancel.bind(bag.text_Cancel);

       hint_FileHitList.bind(bag.hint_FileHitList);
       hint_FileAddHit.bind(bag.hint_FileAddHit);
       hint_FileUpdir.bind(bag.hint_FileUpdir);
       hint_FileCurdir.bind(bag.hint_FileCurdir);
       hint_FileDirList.bind(bag.hint_FileDirList);
       hint_FileMakeDir.bind(bag.hint_FileMakeDir);
       hint_FileRemoveDir.bind(bag.hint_FileRemoveDir);

       edit_cfg.bind(proxy);
       list_cfg.bind(proxy);
       btn_cfg.bind(proxy);
       knob_cfg.bind(proxy);
       hit_menu_cfg.bind(proxy);

       line_cfg.bind(proxy);
      }
    };

   using ConfigType = Config ;

  private:

   const Config &cfg;

   DirWindowParam param;

   // subs

   DirEditWindow edit_dir;
   KnobWindow knob_hit;
   KnobWindow knob_add;
   KnobWindow knob_back;

   XDoubleLineWindow line1;

   ScrollListWindow list_dir;

   KnobWindow knob_mkdir;
   KnobWindow knob_rmdir;

   XDoubleLineWindow line2;

   RefButtonWindow btn_Ok;
   RefButtonWindow btn_Cancel;

   DirHitList hit_list;
   MenuData hit_data;
   SimpleCascadeMenu hit_menu;

   // work

   bool first_open = true ;

   MakeString<MaxPathLen> buf;
   StrLen path;

  private:

   void eraseLists();

   void fillLists();

   void setDir(StrLen dir_name);

   void setSubDir(StrLen sub_dir);

   void enableOk();

   static ulen PrevDir(StrLen dir_name);

   void handleDir(FuncArgType<StrLen> func);

   void mkdir(StrLen dir_name);

   void rmdir(StrLen sub_dir);

  private:

   void dir_list_entered();

   SignalConnector<DirWindow> connector_dir_list_entered;
   SignalConnector<DirWindow> connector_dir_list_dclicked;

   void dir_entered();

   void dir_changed();

   SignalConnector<DirWindow> connector_dir_entered;
   SignalConnector<DirWindow> connector_dir_changed;

   void btn_Ok_pressed();

   void btn_Cancel_pressed();

   SignalConnector<DirWindow> connector_btn_Ok_pressed;
   SignalConnector<DirWindow> connector_btn_Cancel_pressed;

   void knob_hit_pressed();

   void knob_add_pressed();

   void knob_back_pressed();

   SignalConnector<DirWindow> connector_knob_hit_pressed;
   SignalConnector<DirWindow> connector_knob_add_pressed;
   SignalConnector<DirWindow> connector_knob_back_pressed;

   void knob_mkdir_pressed();

   void knob_rmdir_pressed();

   SignalConnector<DirWindow> connector_knob_mkdir_pressed;
   SignalConnector<DirWindow> connector_knob_rmdir_pressed;

   void hit_menu_destroyed();

   void hit_menu_selected(int id,Point base);

   void hit_menu_deleted(int id);

   SignalConnector<DirWindow> connector_hit_menu_destroyed;
   SignalConnector<DirWindow,int,Point> connector_hit_menu_selected;
   SignalConnector<DirWindow,int> connector_hit_menu_deleted;

  public:

   DirWindow(SubWindowHost &host,const Config &cfg,const DirWindowParam &param);

   virtual ~DirWindow();

   // methods

   Point getMinSize(StrLen sample_text) const;

   StrLen getPath() const { return path; }

   // drawing

   virtual void layout();

   virtual void drawBack(DrawBuf buf,bool drag_active) const;

   // base

   virtual void open();

   virtual void close();
 };

/* class DirFrame */

class DirFrame : public DragFrame
 {
  public:

   struct Config
    {
     CtorRefVal<DragFrame::ConfigType> frame_cfg;
     CtorRefVal<DirWindow::ConfigType> dir_cfg;

     RefVal<Ratio> pos_ry = Div(5,12) ;

     Config() noexcept {}

     template <class Bag,class Proxy>
     void bind(const Bag &bag,Proxy proxy)
      {
       frame_cfg.bind(proxy);
       dir_cfg.bind(proxy);

       pos_ry.bind(bag.frame_pos_ry);
      }
    };

   using ConfigType = Config ;

  private:

   const Config &cfg;

   DirWindow sub_win;

   static StrLen SampleDir();

  public:

   DirFrame(Desktop *desktop,const Config &cfg,const DirWindowParam &param={});

   DirFrame(Desktop *desktop,const Config &cfg,const DirWindowParam &param,Signal<> &update);

   virtual ~DirFrame();

   // methods

   StrLen getPath() const { return sub_win.getPath(); } // available after the signal "destroyed"

   // create

   Pane getPane(StrLen title,Point base) const;

   Pane getPane(StrLen title) const;

   using DragFrame::create;

   void create(Point base,const DefString &title)
    {
     create(getPane(title.str(),base),title);
    }

   void create(FrameWindow *parent,Point base,const DefString &title)
    {
     create(parent,getPane(title.str(),base),title);
    }

   void create(const DefString &title)
    {
     create(getPane(title.str()),title);
    }

   void create(FrameWindow *parent,const DefString &title)
    {
     create(parent,getPane(title.str()),title);
    }
 };

} // namespace Video
} // namespace CCore

#endif

