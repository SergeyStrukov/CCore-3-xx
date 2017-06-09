/* FileFrame.h */
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
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_video_FileFrame_h
#define CCore_inc_video_FileFrame_h

#include <CCore/inc/video/WindowLib.h>
#include <CCore/inc/video/Menu.h>
#include <CCore/inc/video/FileBoss.h>

#include <CCore/inc/FunctorType.h>
#include <CCore/inc/MakeFileName.h>
#include <CCore/inc/FileNameMatch.h>

namespace CCore {
namespace Video {

/* classes */

class DirHitList;

class DirEditShape;

class FileFilterWindow;

class FileFilterListWindow;

class FileCheckShape;

struct FileWindowParam;

class FileWindow;

class FileFrame;

/* class DirHitList */

class DirHitList : NoCopy
 {
   static const ulen MaxLen = 10 ;

   String hit_list[MaxLen];
   ulen hit_len = 0 ;

   struct Rec
    {
     String dir;
     unsigned count = 0 ;

     bool test_and_inc(StrLen dir_name);

     void init(StrLen dir_name,unsigned count_=1);
    };

   Rec last_list[MaxLen];
   ulen last_len = 0 ;

  private:

   static StrLen Pretext();

  public:

   DirHitList() noexcept;

   ~DirHitList();

   void loadDDL(StrLen file_name);

   void saveDDL(StrLen file_name) const;

   void load(StrLen hit_file);

   void save(StrLen hit_file) const;

   void add(StrLen dir_name);

   void last(StrLen dir_name);

   StrLen operator () (int id) const;

   void del(int id);

   void prepare(MenuData &data);
 };

/* class DirEditShape */

class DirEditShape : public LineEditShape
 {
   struct Func : public Funchor
    {
     VColor vc;
     VColor accent;

     Func(VColor vc_,VColor accent_) : vc(vc_),accent(accent_) {}

     VColor color(ulen index,char ch,Point base,Point delta);

     CharFunction function_color() { return FunctionOf(this,&Func::color); }
    };

   virtual void drawText(Font font,const DrawBuf &buf,Pane pane,TextPlace place,StrLen text,ulen off,VColor vc) const;

  public:

   struct Config : LineEditShape::Config
    {
     RefVal<VColor> accent = Black ;

     Config() noexcept {}

     template <class Bag>
     void bind(const Bag &bag)
      {
       LineEditShape::Config::bind(bag);

       accent.bind(bag.file_accent);
      }
    };

   DirEditShape(PtrLen<char> text_buf,const Config &cfg) : LineEditShape(text_buf,cfg) {}
 };

using DirEditWindow = LineEditWindowOf<DirEditShape> ;

/* class FileFilterWindow */

class FileFilterWindow : public ComboWindow
 {
  public:

   struct Config
    {
     RefVal<DefString> hint_FileEnableFilter = "Enable/disable this filter"_def ;
     RefVal<DefString> hint_FileDelFilter = "Delete this filter"_def ;
     RefVal<DefString> hint_FileFilter = "Filename filter, use * or ?"_def ;

     CtorRefVal<CheckWindow::ConfigType> check_cfg;
     CtorRefVal<LineEditWindow::ConfigType> edit_cfg;
     CtorRefVal<KnobWindow::ConfigType> knob_cfg;

     Config() noexcept {}

     template <class Bag,class Proxy>
     void bind(const Bag &bag,Proxy proxy)
      {
       hint_FileEnableFilter.bind(bag.hint_FileEnableFilter);
       hint_FileDelFilter.bind(bag.hint_FileDelFilter);
       hint_FileFilter.bind(bag.hint_FileFilter);

       check_cfg.bind(proxy);
       knob_cfg.bind(proxy);

       auto &cfg=edit_cfg.refVal();

       cfg.bind(bag);
       cfg.text.bind(bag.file_filter_text);
       cfg.font.bind(bag.file_filter_font.font);
      }
    };

   using ConfigType = Config ;

   struct SignalPad
    {
     virtual void check_changed(ulen index,bool check)=0;

     virtual void knob_del_pressed(ulen index)=0;
    };

  private:

   const Config &cfg;

   ulen index;

   SignalPad *pad;

   CheckWindow check;
   LineEditWindow edit;
   KnobWindow knob;

   mutable FileNameFilter filter;

  private:

   void check_changed(bool check);

   void edit_changed();

   void knob_pressed();

   SignalConnector<FileFilterWindow,bool> connector_check_changed;
   SignalConnector<FileFilterWindow> connector_edit_changed;
   SignalConnector<FileFilterWindow> connector_knob_pressed;

  public:

   FileFilterWindow(SubWindowHost &host,const Config &cfg,ulen index,SignalPad *pad,StrLen filter,bool check);

   virtual ~FileFilterWindow();

   // methods

   Point getMinSize() const;

   bool isChecked() const { return check.isChecked(); }

   StrLen getFilterText() const { return edit.getText(); }

   const FileNameFilter & getFilter() const
    {
     if( !filter )
       {
        filter.reset(getFilterText());
       }

     return filter;
    }

   void setIndex(ulen index_) { index=index_; }

   // drawing

   virtual void layout();
 };

/* class FileFilterListWindow */

class FileFilterListWindow : public ComboWindow , FileFilterWindow::SignalPad
 {
  public:

   struct Config : FileFilterWindow::ConfigType
    {
     RefVal<DefString> hint_FileAddFilter = "Add a filter"_def ;

     Config() noexcept {}

     template <class Bag,class Proxy>
     void bind(const Bag &bag,Proxy proxy)
      {
       FileFilterWindow::ConfigType::bind(bag,proxy);

       hint_FileAddFilter.bind(bag.hint_FileAddFilter);
      }
    };

   using ConfigType = Config ;

  private:

   const ConfigType &cfg;

   DynArray<OwnPtr<FileFilterWindow> > filter_list;

   ulen filter_count = 0 ;

   KnobWindow knob;

  private:

   void purge();

   auto getList() { return Range(filter_list.getPtr(),filter_count); }

   auto getList() const { return Range(filter_list.getPtr(),filter_count); }

  private:

   void knob_add_pressed();

   SignalConnector<FileFilterListWindow> connector_knob_add_pressed;

   // FileFilterWindow::SignalPad

   virtual void check_changed(ulen index,bool check);

   virtual void knob_del_pressed(ulen index);

  public:

   FileFilterListWindow(SubWindowHost &host,const ConfigType &cfg);

   virtual ~FileFilterListWindow();

   // methods

   Point getMinSize() const;

   void add(StrLen filter,bool check);

   template <FuncInitArgType<StrLen,const FileNameFilter &> FuncInit>
   void apply(FuncInit func_init) const
    {
     FunctorTypeOf<FuncInit> func(func_init);

     for(auto &obj : getList() ) if( obj->isChecked() ) func(obj->getFilterText(),obj->getFilter());
    }

   // drawing

   virtual void layout();

   // user input

   virtual void react(UserAction action);

   // signals

   Signal<> changed;
 };

/* class FileCheckShape */

class FileCheckShape
 {
  public:

   struct Config
    {
     RefVal<MCoord> width = Fraction(6,2) ;

     RefVal<VColor> border    =      Blue ;
     RefVal<VColor> focus     = OrangeRed ;

     RefVal<VColor> gray      =      Gray ;
     RefVal<VColor> snow      =      Snow ;
     RefVal<VColor> snowUp    = PaleGreen ;

     RefVal<VColor> faceRight =     Green ;
     RefVal<VColor> faceDown  =       Red ;

     RefVal<Coord> dxy = 40 ;

     Config() noexcept {}

     template <class Bag>
     void bind(const Bag &bag)
      {
       width.bind(bag.width);
       border.bind(bag.border);
       focus.bind(bag.focus);
       gray.bind(bag.gray);
       snow.bind(bag.snow);
       snowUp.bind(bag.snowUp);

       faceRight.bind(bag.file_faceRight);
       faceDown.bind(bag.file_faceDown);
       dxy.bind(bag.file_alt_dxy);
      }
    };

   const Config &cfg;
   Pane pane;

   // state

   bool enable =  true ;
   bool focus  = false ;
   bool mover  = false ;
   bool check  = false ;

   // methods

   explicit FileCheckShape(const Config &cfg_,bool check_=false) : cfg(cfg_),check(check_) {}

   SizeBox getMinSize() const;

   bool isGoodSize(Point size) const { return size>=getMinSize(); }

   void draw(const DrawBuf &buf) const;
 };

/* struct FileWindowParam */

struct FileWindowParam
 {
  bool new_file = false ;
  DefString auto_ext;
  FileBoss file_boss;
 };

/* class FileWindow */

class FileWindow : public ComboWindow
 {
   using AltWindow = CheckWindowOf<FileCheckShape> ;

  public:

   struct Config
    {
     RefVal<Coord> space_dxy = 10 ;

     RefVal<VColor> back = Silver ;

     RefVal<DefString> text_Ok       = "Ok"_def ;
     RefVal<DefString> text_Cancel   = "Cancel"_def ;
     RefVal<DefString> text_New_file = "New file"_def ;

     RefVal<DefString> hint_FileHitList   = "Open/close the hit directory list"_def ;
     RefVal<DefString> hint_FileAddHit    = "Add the current directory to the hit list"_def ;
     RefVal<DefString> hint_FileUpdir     = "Goto the parent directory"_def ;
     RefVal<DefString> hint_FileCurdir    = "Current directory"_def ;
     RefVal<DefString> hint_FileDirList   = "Subdirectory list"_def ;
     RefVal<DefString> hint_FileList      = "File list"_def ;
     RefVal<DefString> hint_FileMakeDir   = "Create a new directory"_def ;
     RefVal<DefString> hint_FileRemoveDir = "Delete the selected directory"_def ;
     RefVal<DefString> hint_FileAlt       = "Choose between a new file or an existing file"_def ;

     CtorRefVal<DirEditWindow::ConfigType> edit_cfg;
     CtorRefVal<ScrollListWindow::ConfigType> list_cfg;
     CtorRefVal<FileFilterListWindow::ConfigType> filter_list_cfg;
     CtorRefVal<RefButtonWindow::ConfigType> btn_cfg;
     CtorRefVal<KnobWindow::ConfigType> knob_cfg;

     CtorRefVal<SimpleCascadeMenu::ConfigType> hit_menu_cfg;

     CtorRefVal<RefLabelWindow::ConfigType> label_cfg;
     CtorRefVal<AltWindow::ConfigType> alt_cfg;

     CtorRefVal<XDoubleLineWindow::ConfigType> line_cfg;
     CtorRefVal<YSplitWindow::ConfigType> split_cfg;

     Config() noexcept {}

     template <class Bag,class Proxy>
     void bind(const Bag &bag,Proxy proxy)
      {
       space_dxy.bind(bag.space_dxy);
       back.bind(bag.back);
       text_Ok.bind(bag.text_Ok);
       text_Cancel.bind(bag.text_Cancel);
       text_New_file.bind(bag.text_New_file);

       hint_FileHitList.bind(bag.hint_FileHitList);
       hint_FileAddHit.bind(bag.hint_FileAddHit);
       hint_FileUpdir.bind(bag.hint_FileUpdir);
       hint_FileCurdir.bind(bag.hint_FileCurdir);
       hint_FileDirList.bind(bag.hint_FileDirList);
       hint_FileList.bind(bag.hint_FileList);
       hint_FileMakeDir.bind(bag.hint_FileMakeDir);
       hint_FileRemoveDir.bind(bag.hint_FileRemoveDir);
       hint_FileAlt.bind(bag.hint_FileAlt);

       edit_cfg.bind(proxy);
       list_cfg.bind(proxy);
       filter_list_cfg.bind(proxy);
       btn_cfg.bind(proxy);
       knob_cfg.bind(proxy);
       hit_menu_cfg.bind(proxy);

       label_cfg.bind(proxy);
       alt_cfg.bind(proxy);
       line_cfg.bind(proxy);
       split_cfg.bind(proxy);
      }
    };

   using ConfigType = Config ;

  private:

   const Config &cfg;

   FileWindowParam param;

   // subs

   DirEditWindow edit_dir;
   KnobWindow knob_hit;
   KnobWindow knob_add;
   KnobWindow knob_back;

   XDoubleLineWindow line1;

   ScrollListWindow list_dir;

   YSplitWindow split;

   ScrollListWindow list_file;

   FileFilterListWindow filter_list;

   KnobWindow knob_mkdir;
   KnobWindow knob_rmdir;

   XDoubleLineWindow line2;

   RefButtonWindow btn_Ok;
   RefButtonWindow btn_Cancel;

   DirHitList hit_list;
   MenuData hit_data;
   SimpleCascadeMenu hit_menu;

   AltWindow alt_new_file;
   RefLabelWindow label_new_file;
   LineEditWindow edit_new_file;

   // work

   bool first_open = true ;

   Info file_info;

   MakeFileName file_buf;
   StrLen file_path;

   // layout

   Coord top_dy = 0 ;
   Coord total_dy = 0 ;

  private:

   class Distributor;

   void applyFilters();

   void eraseLists();

   void fillLists();

   void setDir(StrLen dir_name);

   void setSubDir(StrLen sub_dir);

   void buildFilePath();

   void enableOk();

   bool isGoodFileName(StrLen file_name);

   static ulen PrevDir(StrLen dir_name);

   void handleDir(FuncArgType<StrLen> func);

   void mkdir(StrLen dir_name);

   void rmdir(StrLen sub_dir);

   static Coord CapTop(Coord t,Coord total);

  private:

   void file_list_entered();

   SignalConnector<FileWindow> connector_file_list_entered;
   SignalConnector<FileWindow> connector_file_list_dclicked;

   void filter_list_changed();

   SignalConnector<FileWindow> connector_filter_list_changed;

   void dir_list_entered();

   SignalConnector<FileWindow> connector_dir_list_entered;
   SignalConnector<FileWindow> connector_dir_list_dclicked;

   void dir_entered();

   void dir_changed();

   SignalConnector<FileWindow> connector_dir_entered;
   SignalConnector<FileWindow> connector_dir_changed;

   void btn_Ok_pressed();

   void btn_Cancel_pressed();

   SignalConnector<FileWindow> connector_btn_Ok_pressed;
   SignalConnector<FileWindow> connector_btn_Cancel_pressed;

   void knob_hit_pressed();

   void knob_add_pressed();

   void knob_back_pressed();

   SignalConnector<FileWindow> connector_knob_hit_pressed;
   SignalConnector<FileWindow> connector_knob_add_pressed;
   SignalConnector<FileWindow> connector_knob_back_pressed;

   void knob_mkdir_pressed();

   void knob_rmdir_pressed();

   SignalConnector<FileWindow> connector_knob_mkdir_pressed;
   SignalConnector<FileWindow> connector_knob_rmdir_pressed;

   void hit_menu_destroyed();

   void hit_menu_selected(int id,Point base);

   void hit_menu_deleted(int id);

   SignalConnector<FileWindow> connector_hit_menu_destroyed;
   SignalConnector<FileWindow,int,Point> connector_hit_menu_selected;
   SignalConnector<FileWindow,int> connector_hit_menu_deleted;

   void check_new_file_changed(bool check);

   void edit_new_file_changed();

   void edit_new_file_entered();

   SignalConnector<FileWindow,bool> connector_check_new_file_changed;
   SignalConnector<FileWindow> connector_edit_new_file_changed;
   SignalConnector<FileWindow> connector_edit_new_file_entered;

   void split_dragged(Point delta);

   SignalConnector<FileWindow,Point> connector_split_dragged;

  public:

   FileWindow(SubWindowHost &host,const Config &cfg,const FileWindowParam &param);

   virtual ~FileWindow();

   // methods

   Point getMinSize(StrLen sample_text) const;

   StrLen getFilePath() const { return file_path; }

   void setNewFile(bool on,DefString auto_ext);

   void setNewFile(bool on);

   void addFilter(StrLen filter,bool check) { filter_list.add(filter,check); }

   // drawing

   virtual void layout();

   virtual void drawBack(DrawBuf buf,bool drag_active) const;

   // base

   virtual void open();

   virtual void close();
 };

/* class FileFrame */

class FileFrame : public DragFrame
 {
  public:

   struct Config
    {
     CtorRefVal<DragFrame::ConfigType> frame_cfg;
     CtorRefVal<FileWindow::ConfigType> file_cfg;

     RefVal<Ratio> pos_ry = Div(5,12) ;

     Config() noexcept {}

     template <class Bag,class Proxy>
     void bind(const Bag &bag,Proxy proxy)
      {
       frame_cfg.bind(proxy);
       file_cfg.bind(proxy);

       pos_ry.bind(bag.frame_pos_ry);
      }
    };

   using ConfigType = Config ;

  private:

   const Config &cfg;

   FileWindow sub_win;

   static StrLen SampleDir();

  public:

   FileFrame(Desktop *desktop,const Config &cfg,const FileWindowParam &param={false});

   FileFrame(Desktop *desktop,const Config &cfg,const FileWindowParam &param,Signal<> &update);

   virtual ~FileFrame();

   // methods

   void setNewFile(bool on,DefString auto_ext) { sub_win.setNewFile(on,auto_ext); }

   void setNewFile(bool on) { sub_win.setNewFile(on); }

   void addFilter(StrLen filter,bool check=true) { sub_win.addFilter(filter,check); }

   void addFilters(StrLen filter) { addFilter(filter); }

   template <class ... TT>
   void addFilters(StrLen filter,TT ... filters)
    {
     addFilter(filter);

     addFilters(filters...);
    }

   StrLen getFilePath() const { return sub_win.getFilePath(); } // available after the signal "destroyed"

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

