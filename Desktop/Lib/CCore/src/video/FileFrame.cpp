/* FileFrame.cpp */
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
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/video/FileFrame.h>

#include <CCore/inc/video/DesktopKey.h>
#include <CCore/inc/video/Desktop.h>

#include <CCore/inc/video/LayoutCombo.h>
#include <CCore/inc/video/FigureLib.h>
#include <CCore/inc/video/FileNameCmp.h>
#include <CCore/inc/video/PrintDDL.h>
#include <CCore/inc/video/HomeFile.h>

#include <CCore/inc/RangeDel.h>
#include <CCore/inc/Path.h>
#include <CCore/inc/Print.h>
#include <CCore/inc/FileSystem.h>
#include <CCore/inc/Exception.h>
#include <CCore/inc/CompactList.h>
#include <CCore/inc/PrintStem.h>

#include <CCore/inc/algon/SortUnique.h>
#include <CCore/inc/algon/BestSearch.h>
#include <CCore/inc/algon/SimpleRotate.h>

#include <CCore/inc/FileName.h>
#include <CCore/inc/FileToMem.h>

#include <CCore/inc/ddl/DDLEngine.h>
#include <CCore/inc/ddl/DDLTypeSet.h>

namespace CCore {
namespace Video {

/* functions */

ulen ParentDir(StrLen dir_name)
 {
  SplitPath split1(dir_name);

  SplitName split2(split1.path);

  if( !split2 )
    {
     return split2.name.len;
    }
  else
    {
     ulen delta=split2.name.len+1;

     if( delta==split1.path.len ) delta--;

     return delta;
    }
 }

/* class DirHitList */

bool DirHitList::Rec::test_and_inc(StrLen dir_name)
 {
  if( Range(dir).equal(dir_name) )
    {
     count++;

     return true;
    }

  return false;
 }

void DirHitList::Rec::init(StrLen dir_name,unsigned count_)
 {
  dir=String(dir_name);
  count=count_;
 }

StrLen DirHitList::Pretext()
 {
  return
"struct HitDirData"
" {"
"  text[] hit_list;"

"  struct Rec { text dir; uint count; } [] last_list;"
" };"_c;
 }

DirHitList::DirHitList() noexcept
 {
 }

DirHitList::~DirHitList()
 {
 }

namespace Private_FileWindow {

#include "HitDirs.TypeDef.gen.h"
#include "HitDirs.TypeSet.gen.h"

} // namespace Private_FileWindow

using namespace Private_FileWindow;

void DirHitList::loadDDL(StrLen file_name)
 {
  hit_len=0;
  last_len=0;

  char temp[512];
  PrintBuf eout(Range(temp));
  DDL::FileEngine<FileName,FileToMem> engine(eout);

  auto result=engine.process(file_name,Pretext());

  if( !result )
    {
     Printf(Exception,"CCore::Video::DirHitList::loadDDL(#.q;) : input file processing error\n#;",file_name,eout.close());
    }
  else
    {
     DDL::TypedMap<TypeSet> map(result);
     MemAllocGuard guard(map.getLen());

     map(guard);

     // populate

     TypeDef::HitDirData hits=map.takeConst<TypeDef::HitDirData>("Hits");

     {
      auto r=hits.hit_list.getRange();

      ulen len=Min(r.len,MaxLen);

      for(ulen i=0; i<len ;i++) hit_list[i]=String(r[i]);

      hit_len=len;
     }

     {
      auto r=hits.last_list.getRange();

      ulen len=Min(r.len,MaxLen);

      for(ulen i=0; i<len ;i++) last_list[i].init(r[i].dir,r[i].count);

      last_len=len;

      Algon::DecrSortBy(Range(last_list,last_len), [] (const Rec &obj) { return obj.count; } );
     }
    }
 }

void DirHitList::saveDDL(StrLen file_name) const
 {
  PrintFile out(file_name);

  Putobj(out,"HitDirData Hits=\n {\n  {");

  PrintFirst stem("\n",",\n");

  for(auto &obj : Range(hit_list,hit_len) )
    {
     Printf(out,"#;   #;",stem,DDLPrintableString(obj));
    }

  Putobj(out,"\n  },\n  {");

  stem.reset();

  for(auto &obj : Range(last_list,last_len) )
    {
     Printf(out,"#;   { #; , #; }",stem,DDLPrintableString(obj.dir),obj.count);
    }

  Putobj(out,"\n  }\n };\n\n");
 }

void DirHitList::load(StrLen hit_file)
 {
  if( !hit_file ) return;

  try
    {
     HomeFile file(HomeKey(),hit_file);

     loadDDL(file.get());
    }
  catch(...)
    {
    }
 }

void DirHitList::save(StrLen hit_file) const
 {
  if( !hit_file ) return;

  try
    {
     HomeFile file(HomeKey(),hit_file);

     file.createDir();

     saveDDL(file.get());
    }
  catch(...)
    {
    }
 }

void DirHitList::add(StrLen dir_name)
 {
  if( hit_len<MaxLen )
    {
     hit_list[hit_len++]=String(dir_name);
    }
 }

void DirHitList::last(StrLen dir_name)
 {
  for(ulen i=0; i<last_len ;i++)
    if( last_list[i].test_and_inc(dir_name) )
      return;

  if( last_len<MaxLen )
    {
     last_list[last_len++].init(dir_name);

     return;
    }

  auto r=Algon::BestSearchLessBy(Range(last_list,last_len), [] (const Rec &a) { return a.count; } );

  r->init(dir_name);
 }

StrLen DirHitList::operator () (int id) const
 {
  ulen ind=(ulen)id;

  if( ind<MaxLen )
    {
     if( ind>=hit_len ) return Empty;

     return Range(hit_list[ind]);
    }
  else
    {
     ind-=MaxLen;

     if( ind>=last_len ) return Empty;

     return Range(last_list[ind].dir);
    }
 }

void DirHitList::del(int id)
 {
  ulen ind=(ulen)id;

  if( ind<MaxLen )
    {
     hit_len-=RangeCopyDel(hit_list,hit_len,ind);
    }
  else
    {
     ind-=MaxLen;

     last_len-=RangeCopyDel(last_list,last_len,ind);
    }
 }

void DirHitList::prepare(MenuData &data)
 {
  data.list.erase();

  for(ulen i=0; i<hit_len ;i++)
    {
     data(MenuTextNoHot,hit_list[i],(int)i);
    }

  data(MenuSeparator);

  for(ulen i=0; i<last_len ;i++)
    {
     data(MenuTextNoHot,last_list[i].dir,(int)(MaxLen+i));
    }

  data.updated.assert();
 }

/* class DirEditShape */

StrLen DirEditShape::SampleDir()
 {
  return "/cygdrive/d/active/home/C++/CCore-2-99/vtools/DDLDisplay"_c;
 }

void DirEditShape::drawText(Font font,const DrawBuf &buf,Pane pane,TextPlace place,PtrLen<const Char> text,ulen,VColor vc) const
 {
  auto &ecfg=static_cast<const Config &>(cfg);

  auto func = [vc,accent=+ecfg.accent] (ulen,Char ch_,Point,Point) -> VColor
                                       {
                                        char ch=ToChar(ch_);

                                        if( PathBase::IsSlash(ch) || PathBase::IsColon(ch) ) return accent;

                                        return vc;

                                       } ;

  auto temp=ToFunction<VColor (ulen,Char,Point,Point)>(func);

  font->text(buf,pane,place,text,temp.function());
 }

Point DirEditShape::getMinSize(unsigned update_flag) const
 {
  return LineEditShape::getMinSize(update_flag,SampleDir());
 }

/* class FileFilterWindow */

void FileFilterWindow::check_changed(bool check)
 {
  pad->check_changed(index,check);
 }

void FileFilterWindow::edit_changed()
 {
  filter.reset();

  check.uncheck();

  pad->check_changed(index,false);
 }

void FileFilterWindow::knob_pressed()
 {
  pad->knob_del_pressed(index);
 }

FileFilterWindow::FileFilterWindow(SubWindowHost &host,const Config &cfg_,ulen index_,SignalPad *pad_,StrLen filter,bool check_)
 : ComboWindow(host),
   cfg(cfg_),
   index(index_),
   pad(pad_),

   check(wlist,cfg.check_cfg,check_),
   edit(wlist,cfg.edit_cfg),
   knob(wlist,cfg.knob_cfg,KnobShape::FaceCross),

   cache(edit),

   connector_check_changed(this,&FileFilterWindow::check_changed,check.changed),
   connector_edit_changed(this,&FileFilterWindow::edit_changed,cache.changed),
   connector_knob_pressed(this,&FileFilterWindow::knob_pressed,knob.pressed)
 {
  wlist.insTop(check,edit,knob);

  if( !edit.setText(filter) )
    {
     Printf(Exception,"CCore::Video::FileFilterWindow::FileFilterWindow(...) : too long filter");
    }

  edit.hideInactiveCursor();

  // set hints

  check.bindHint(cfg.hint_FileEnableFilter);
  edit.bindHint(cfg.hint_FileFilter);
  knob.bindHint(cfg.hint_FileDelFilter);
 }

FileFilterWindow::~FileFilterWindow()
 {
 }

 // methods

Point FileFilterWindow::getMinSize(unsigned flags) const
 {
  LayBox lay1(check);
  LayBox lay2(knob);

  LayToRightCenter lay(lay1,LayToLeftCenter(lay2,Lay(edit)));

  return lay.getMinSize(flags,0);
 }

 // drawing

void FileFilterWindow::layout(unsigned flags)
 {
  LayBox lay1(check);
  LayBox lay2(knob);

  LayToRightCenter lay(lay1,LayToLeftCenter(lay2,Lay(edit)));

  lay.setPlace(getPane(),flags,0);
 }

/* class FileFilterListWindow */

void FileFilterListWindow::purge()
 {
  ulen len=filter_list.getLen();

  if( filter_count<len ) filter_list.shrink(len-filter_count);
 }

void FileFilterListWindow::knob_add_pressed()
 {
  add("*"_c,false);
 }

void FileFilterListWindow::check_changed(ulen index,bool check)
 {
  Used(check);

  if( index<filter_count ) changed.assert();
 }

void FileFilterListWindow::knob_del_pressed(ulen index)
 {
  auto list=getList();

  if( RangeSwapDel(list,index) )
    {
     filter_count--;

     for(ulen i=index; i<list.len ;i++) list[i]->setIndex(i);

     wlist.del(list[list.len-1].getPtr());

     layout(LayoutUpdate);

     redraw();

     changed.assert();
    }
 }

FileFilterListWindow::FileFilterListWindow(SubWindowHost &host,const ConfigType &cfg_)
 : ComboWindow(host),
   cfg(cfg_),

   knob(wlist,cfg.knob_cfg,KnobShape::FacePlus),

   connector_knob_add_pressed(this,&FileFilterListWindow::knob_add_pressed,knob.pressed)
 {
  wlist.insTop(knob);

  // set hints

  knob.bindHint(cfg.hint_FileAddFilter);
 }

FileFilterListWindow::~FileFilterListWindow()
 {
 }

 // methods

Point FileFilterListWindow::getMinSize(unsigned flags) const
 {
  if( ulen count=filter_count )
    {
     Coord knob_dxy=knob.getMinSize(flags).dxy;

     Point size=filter_list[0]->getMinSize(flags);

     Coord delta=BoxExt(size.y);

     return Point( Sup(size.x,knob_dxy) , delta*CountToCoordinate(count)+knob_dxy );
    }
  else
    {
     return GetMinSize(flags,knob);
    }
 }

void FileFilterListWindow::add(StrLen filter,bool check)
 {
  ulen index=filter_count;

  auto *obj=filter_list.append_fill(OwnPtr<FileFilterWindow>(new FileFilterWindow(wlist,cfg,index,this,filter,check)));

  wlist.insBefore(knob,**obj);

  Algon::RangeRotateRight(Range(filter_list).part(index));

  filter_count++;

  if( getFrame()->isAlive() )
    {
     layout(LayoutUpdate);

     redraw();
    }
 }

 // drawing

void FileFilterListWindow::layout(unsigned flags)
 {
  Point size=getSize();

  if( filter_count )
    {
     Coord dy=filter_list[0]->getMinSize(flags).y;

     PaneCut pane(size,BoxSpace(dy),flags);

     for(auto &ptr : getList() ) pane.place_cutTop(*ptr,dy);

     pane.place_cutTopLeft(knob);
    }
  else
    {
     PaneCut pane(size,0,flags);

     pane.place_cutTopLeft(knob);
    }
 }

 // user input

void FileFilterListWindow::react(UserAction action)
 {
  wlist.react(action);

  purge();
 }

/* class FileCheckShape */

SizeBox FileCheckShape::getMinSize() const
 {
  return +cfg.dxy;
 }

void FileCheckShape::draw(const DrawBuf &buf) const
 {
  KnobShape::Config temp_cfg;

  temp_cfg.width=cfg.width;
  temp_cfg.border=cfg.border;
  temp_cfg.focus=cfg.focus;
  temp_cfg.gray=cfg.gray;
  temp_cfg.snow=cfg.snow;
  temp_cfg.snowUp=cfg.snowUp;
  temp_cfg.face=check?cfg.faceRight:cfg.faceDown;

  KnobShape temp(temp_cfg,check?KnobShape::FaceRight:KnobShape::FaceDown);

  temp.pane=pane;

  temp.enable=enable;
  temp.focus=focus;
  temp.mover=mover;

  temp.draw(buf);
 }

/* class FileWindow::Distributor */

class FileWindow::Distributor : NoCopy
 {
   struct Basket : NoCopy
    {
     StrLen filter_text;
     const FileNameFilter &filter;
     CompactList2<StrLen> file_list;

     Basket(StrLen filter_text_,const FileNameFilter &filter_) : filter_text(filter_text_),filter(filter_) {}

     bool tryAdd(StrLen file)
      {
       if( filter(file) )
         {
          file_list.insLast(file);

          return true;
         }

       return false;
      }

     void addTo(ComboInfoBuilder &builder)
      {
       if( +file_list )
         {
          builder.addTitle(filter_text);

          file_list.apply( [&builder] (StrLen file) { builder.add(file); } );
         }
      }
    };

   CompactList2<Basket> basket_list;

  public:

   Distributor()
    {
    }

   ~Distributor()
    {
    }

   void addFilter(StrLen filter_text,const FileNameFilter &filter)
    {
     basket_list.insLast(filter_text,filter);
    }

   void addFile(StrLen file)
    {
     basket_list.apply( [file] (Basket &obj) -> bool { return !obj.tryAdd(file); } );
    }

   ComboInfo build()
    {
     ComboInfoBuilder builder;

     basket_list.apply( [&builder] (Basket &obj) { obj.addTo(builder); } );

     builder.sortGroups(ExtNameLess);

     return builder.complete();
    }
 };

/* class FileWindow */

void FileWindow::applyFilters()
 {
  try
    {
     Distributor obj;

     filter_list.apply( [&obj] (StrLen filter_text,const FileNameFilter &filter) { obj.addFilter(filter_text,filter); } );

     ulen count=file_info->getLineCount();

     for(ulen i=0; i<count ;i++) obj.addFile(file_info->getLine(i));

     list_file.setInfo(obj.build());
    }
  catch(...)
    {
     list_file.setInfo(ComboInfo());
    }
 }

void FileWindow::eraseLists()
 {
  list_dir.setInfo(ComboInfo());

  file_info=Info();

  list_file.setInfo(ComboInfo());

  btn_Ok.disable();

  if( param.new_file ) edit_new_file.alert(false);
 }

void FileWindow::fillLists()
 {
  try
    {
     ComboInfoBuilder dir_builder;
     InfoBuilder file_builder;

     auto func = [&] (StrLen name,FileType type)
                     {
                      switch( type )
                        {
                         case FileType_dir :
                          {
                           if( PathBase::IsDot(name) ) break;

                           dir_builder.add(name);
                          }
                         break;

                         case FileType_file :
                          {
                           file_builder.add(name);
                          }
                         break;
                        }

                     } ;

     auto temp=ToFunction<void (StrLen name,FileType type)>(func);

     param.file_boss->enumDir(cache_dir.getText(),temp.function());

     dir_builder.sortGroups(ExtNameLess);

     list_dir.setInfo(dir_builder.complete());

     file_info=file_builder.complete();

     applyFilters();

     enableOk();
    }
  catch(...)
    {
     eraseLists();
    }
 }

void FileWindow::setDir(StrLen dir_name)
 {
  char temp[MaxPathLen+1];

  StrLen path=param.file_boss->pathOf(dir_name,temp);

  if( param.file_boss->getFileType(path)==FileType_dir )
    {
     list_dir.enable();
     list_file.enable( !param.new_file || !alt_new_file.isChecked() );

     edit_dir.setText(path);
     edit_dir.alert(false);

     fillLists();
    }
  else
    {
     list_dir.disable();
     list_file.disable();

     edit_dir.alert(true);

     eraseLists();

     Printf(NoException,"CCore::Video::FileWindow::setDir(#.q;) : #.q; is not a directory",dir_name,path);
    }
 }

void FileWindow::setSubDir(StrLen sub_dir)
 {
  MakeFileName temp(cache_dir.getText(),sub_dir);

  setDir(temp.get());
 }

void FileWindow::buildFilePath()
 {
  if( param.new_file && alt_new_file.isChecked() )
    {
     file_path=file_buf(cache_dir.getText(),cache_new_file.getText(),param.auto_ext.str());
    }
  else
    {
     const ComboInfo &info=list_file.getInfo();
     ulen index=list_file.getSelect();

     if( index<info->getLineCount() )
       {
        ComboInfoItem item=info->getLine(index);

        if( item.type==ComboInfoText )
          {
           file_path=file_buf(cache_dir.getText(),item.text);
          }
       }
    }
 }

void FileWindow::enableOk()
 {
  if( !list_dir.isEnabled() )
    {
     if( param.new_file ) edit_new_file.alert(false);

     btn_Ok.disable();

     return;
    }

  bool en=false;

  if( param.new_file && alt_new_file.isChecked() )
    {
     en=isGoodFileName(cache_new_file.getText());

     edit_new_file.alert(!en);
    }
  else
    {
     const ComboInfo &info=list_file.getInfo();
     ulen index=list_file.getSelect();

     if( index<info->getLineCount() )
       {
        ComboInfoItem item=info->getLine(index);

        if( item.type==ComboInfoText )
          {
           en=true;
          }
       }
    }

  btn_Ok.enable(en);
 }

bool FileWindow::isGoodFileName(StrLen file_name)
 {
  if( !file_name ) return false;

  MakeFileName temp(cache_dir.getText(),file_name,param.auto_ext.str());

  return param.file_boss->getFileType(temp.get())==FileType_none;
 }

void FileWindow::handleDir(FuncArgType<StrLen> func)
 {
  const ComboInfo &info=list_dir.getInfo();
  ulen index=list_dir.getSelect();

  if( index<info->getLineCount() )
    {
     ComboInfoItem item=info->getLine(index);

     if( item.type==ComboInfoText )
       {
        func(item.text);
       }
    }
 }

void FileWindow::mkdir(StrLen dir_name)
 {
  {
   ExceptionFrame frame(exbuf);

   param.file_boss->createDir(dir_name);
  }

  setDir(dir_name);
 }

void FileWindow::rmdir(StrLen sub_dir)
 {
  MakeFileName temp(cache_dir.getText(),sub_dir);

  {
   ExceptionFrame frame(exbuf);

   param.file_boss->deleteDir(temp.get());
  }

  fillLists();
 }

Coord FileWindow::CapTop(Coord t,Coord total)
 {
  Coord a=total/4;
  Coord b=3*a;

  return Cap<Coord>(a,t,b);
 }

void FileWindow::splitSize(Coord tdy)
 {
  if( total_dy!=tdy )
    {
     Coord t;

     if( total_dy )
       t=Div(top_dy,total_dy)*tdy;
     else
       t=Div(1,3)*tdy;

     total_dy=tdy;
     top_dy=CapTop(t,tdy);
    }
 }

void FileWindow::file_list_entered()
 {
  buildFilePath();

  askFrameClose();
 }

void FileWindow::filter_list_changed()
 {
  applyFilters();
 }

void FileWindow::dir_list_entered()
 {
  handleDir( [this] (StrLen dir_name) { setSubDir(dir_name); } );
 }

void FileWindow::dir_entered()
 {
  setDir(cache_dir.getText());
 }

void FileWindow::dir_changed()
 {
  list_dir.disable();
  list_file.disable();
  btn_Ok.disable();

  if( param.new_file ) edit_new_file.alert(false);
 }

void FileWindow::btn_Ok_pressed()
 {
  hit_list.last(cache_dir.getText());

  buildFilePath();

  askFrameClose();
 }

void FileWindow::btn_Cancel_pressed()
 {
  askFrameClose();
 }

void FileWindow::knob_hit_pressed()
 {
  if( hit_menu.isDead() )
    {
     hit_menu.create(getFrame(),hit_data,toScreen(knob_hit.getPlace().addDY()));

     knob_hit.setFace(KnobShape::FaceCross);
    }
  else
    {
     hit_menu.destroy();
    }
 }

void FileWindow::knob_add_pressed()
 {
  hit_list.add(cache_dir.getText());

  hit_list.prepare(hit_data);
 }

void FileWindow::knob_back_pressed()
 {
  StrLen dir_name=cache_dir.getText();

  if( ulen delta=ParentDir(dir_name) )
    {
     dir_name.len-=delta;

     setDir(dir_name);
    }
 }

void FileWindow::knob_mkdir_pressed()
 {
  if( !list_dir.isEnabled() ) mkdir(cache_dir.getText());
 }

void FileWindow::knob_rmdir_pressed()
 {
  handleDir( [this] (StrLen dir_name) { rmdir(dir_name); } );
 }

void FileWindow::hit_menu_destroyed()
 {
  knob_hit.setFace(KnobShape::FaceDown);
 }

void FileWindow::hit_menu_selected(int id,Point)
 {
  setDir(hit_list(id));

  hit_menu.destroy();
 }

void FileWindow::hit_menu_deleted(int id)
 {
  hit_list.del(id);

  hit_list.prepare(hit_data);
 }

void FileWindow::check_new_file_changed(bool check)
 {
  edit_new_file.enable(check);

  list_file.enable( !check && list_dir.isEnabled() );

  enableOk();
 }

void FileWindow::edit_new_file_changed()
 {
  if( list_dir.isEnabled() )
    {
     if( isGoodFileName(cache_new_file.getText()) )
       {
        edit_new_file.alert(false);

        btn_Ok.enable();
       }
     else
       {
        edit_new_file.alert(true);

        btn_Ok.disable();
       }
    }
 }

void FileWindow::edit_new_file_entered()
 {
  if( btn_Ok.isEnabled() ) btn_Ok_pressed();
 }

void FileWindow::split_dragged(Point delta)
 {
  if( Change(top_dy, CapTop(top_dy+delta.y,total_dy) ) )
    {
     layout(LayoutResize);

     redraw();
    }
 }

FileWindow::FileWindow(SubWindowHost &host,const Config &cfg_,const FileWindowParam &param_)
 : ComboWindow(host),
   cfg(cfg_),
   param(param_),

   edit_dir(wlist,MaxPathLen,cfg.edit_cfg),
   knob_hit(wlist,cfg.knob_cfg,KnobShape::FaceDown),
   knob_add(wlist,cfg.knob_cfg,KnobShape::FacePlus),
   knob_back(wlist,cfg.knob_cfg,KnobShape::FaceLeft),
   line1(wlist,cfg.line_cfg),
   list_dir(wlist,cfg.list_cfg),
   split(wlist,cfg.split_cfg),
   list_file(wlist,cfg.list_cfg),
   filter_list(wlist,cfg.filter_list_cfg),
   knob_mkdir(wlist,cfg.knob_cfg,KnobShape::FacePlus),
   knob_rmdir(wlist,cfg.knob_cfg,KnobShape::FaceMinus),
   line2(wlist,cfg.line_cfg),
   btn_Ok(wlist,cfg.btn_cfg,cfg.text_Ok),
   btn_Cancel(wlist,cfg.btn_cfg,cfg.text_Cancel),

   hit_menu(host.getFrameDesktop(),cfg.hit_menu_cfg),

   alt_new_file(wlist,cfg.alt_cfg,true),
   label_new_file(wlist,cfg.label_cfg,cfg.text_New_file),
   edit_new_file(wlist,cfg.edit_cfg),

   cache_dir(edit_dir),
   cache_new_file(edit_new_file),

   exbuf(host.getFrame(),cfg.exbuf_cfg),

   connector_file_list_entered(this,&FileWindow::file_list_entered,list_file.entered),
   connector_file_list_dclicked(this,&FileWindow::file_list_entered,list_file.dclicked),
   connector_filter_list_changed(this,&FileWindow::filter_list_changed,filter_list.changed),
   connector_dir_list_entered(this,&FileWindow::dir_list_entered,list_dir.entered),
   connector_dir_list_dclicked(this,&FileWindow::dir_list_entered,list_dir.dclicked),
   connector_dir_entered(this,&FileWindow::dir_entered,edit_dir.entered),
   connector_dir_changed(this,&FileWindow::dir_changed,cache_dir.changed),
   connector_btn_Ok_pressed(this,&FileWindow::btn_Ok_pressed,btn_Ok.pressed),
   connector_btn_Cancel_pressed(this,&FileWindow::btn_Cancel_pressed,btn_Cancel.pressed),
   connector_knob_hit_pressed(this,&FileWindow::knob_hit_pressed,knob_hit.pressed),
   connector_knob_add_pressed(this,&FileWindow::knob_add_pressed,knob_add.pressed),
   connector_knob_back_pressed(this,&FileWindow::knob_back_pressed,knob_back.pressed),
   connector_knob_mkdir_pressed(this,&FileWindow::knob_mkdir_pressed,knob_mkdir.pressed),
   connector_knob_rmdir_pressed(this,&FileWindow::knob_rmdir_pressed,knob_rmdir.pressed),
   connector_hit_menu_destroyed(this,&FileWindow::hit_menu_destroyed,hit_menu.destroyed),
   connector_hit_menu_selected(this,&FileWindow::hit_menu_selected,hit_menu.selected),
   connector_hit_menu_deleted(this,&FileWindow::hit_menu_deleted,hit_menu.deleted),
   connector_check_new_file_changed(this,&FileWindow::check_new_file_changed,alt_new_file.changed),
   connector_edit_new_file_changed(this,&FileWindow::edit_new_file_changed,cache_new_file.changed),
   connector_edit_new_file_entered(this,&FileWindow::edit_new_file_entered,edit_new_file.entered),
   connector_split_dragged(this,&FileWindow::split_dragged,split.dragged)
 {
  wlist.insTop(knob_add,knob_hit,edit_dir,knob_back,line1,list_dir,split,list_file,filter_list,line2,btn_Ok,btn_Cancel);

  if( param.new_file )
    {
     wlist.insAfter(list_dir,knob_mkdir,knob_rmdir,alt_new_file,label_new_file,edit_new_file);

     list_file.disable();

     edit_new_file.alert(true);

     btn_Ok.disable();
    }

  edit_dir.hideInactiveCursor();
  edit_new_file.hideInactiveCursor();

  // bind hints

  edit_dir.bindHint(cfg.hint_FileCurdir);
  knob_hit.bindHint(cfg.hint_FileHitList);
  knob_add.bindHint(cfg.hint_FileAddHit);
  knob_back.bindHint(cfg.hint_FileUpdir);
  list_dir.bindHint(cfg.hint_FileDirList);
  list_file.bindHint(cfg.hint_FileList);
  knob_mkdir.bindHint(cfg.hint_FileMakeDir);
  knob_rmdir.bindHint(cfg.hint_FileRemoveDir);
  alt_new_file.bindHint(cfg.hint_FileAlt);
 }

FileWindow::~FileWindow()
 {
 }

 // methods

Point FileWindow::getMinSize(unsigned flags) const
 {
  Coord space=+cfg.space_dxy;

  if( param.new_file )
    {
     // knob_add , knob_hit , dir , knob_back

     LayToRightCenter lay1{ LayBox(knob_add) , LayBox(knob_hit) , LayToLeftCenter(Lay(knob_back),Lay(edit_dir)) };

     // list_dir , knob_mkdir , knob_rmdir

     LayToLeft lay2{ LayToBottom(Lay(knob_mkdir),LayAlignTop(Lay(knob_rmdir))) , LaySpecial(list_dir,6u) };

     // check_new , label_new_file , edit_new_file

     LayToRightCenter lay3{ Lay(alt_new_file) , Lay(label_new_file) , Lay(edit_new_file) };

     // list_file , filter_list

     LayDivX lay4{ LaySpecial(list_file,12u) , Lay(filter_list) , Div(2,3) };

     // btn_Ok , btn_Cancel

     LaySupCenterXExt lay5{ Lay(btn_Ok) , Lay(btn_Cancel) };

     // lay_dir

     LayToBottom lay_dir{ ExtLayX(lay1) , Lay(line1) , ExtLayX(lay2) };

     // lay_file

     LayToBottom lay_file{ LayNoSpace(split) , ExtLayX(lay3) , LayToTop(lay5,Lay(line2),ExtLayX(lay4)) };

     // lay

     Point s1=lay_dir.getMinSize(flags,space);
     Point s2=lay_file.getMinSize(flags,space);

     return StackYSize(s1,s2)+2*Point(0,space);
    }
  else
    {
     // knob_add , knob_hit , dir , knob_back

     LayToRightCenter lay1{ LayBox(knob_add) , LayBox(knob_hit) , LayToLeftCenter(Lay(knob_back),Lay(edit_dir)) };

     // list_dir

     LaySpecial lay2(list_dir,6u);

     // list_file , filter_list

     LayDivX lay4{ LaySpecial(list_file,12u) , Lay(filter_list) , Div(2,3) };

     // btn_Ok , btn_Cancel

     LaySupCenterXExt lay5{ Lay(btn_Ok) , Lay(btn_Cancel) };

     // lay_dir

     LayToBottom lay_dir{ ExtLayX(lay1) , Lay(line1) , ExtLayX(lay2) };

     // lay_file

     LayToBottom lay_file{ LayNoSpace(split) , LayToTop(lay5,Lay(line2),ExtLayX(lay4)) };

     // lay

     Point s1=lay_dir.getMinSize(flags,space);
     Point s2=lay_file.getMinSize(flags,space);

     return StackYSize(s1,s2)+2*Point(0,space);
    }
 }

void FileWindow::setNewFile(bool on,DefString auto_ext)
 {
  param.auto_ext=auto_ext;

  setNewFile(on);
 }

void FileWindow::setNewFile(bool on)
 {
  if( Change(param.new_file,on) )
    {
     if( param.new_file )
       {
        wlist.insAfter(list_dir,knob_mkdir,knob_rmdir,alt_new_file,label_new_file,edit_new_file);

        alt_new_file.check(true);

        edit_new_file.enable();

        list_file.disable();

        edit_new_file_changed();
       }
     else
       {
        wlist.del(alt_new_file,label_new_file,edit_new_file,knob_mkdir,knob_rmdir);

        list_file.enable( list_dir.isEnabled() );
       }

     enableOk();

     layout(LayoutUpdate);

     redraw();
    }
 }

 // drawing

void FileWindow::layout(unsigned flags)
 {
  Coord space=+cfg.space_dxy;

  if( param.new_file )
    {
     // knob_add , knob_hit , dir , knob_back

     LayToRightCenter lay1{ LayBox(knob_add) , LayBox(knob_hit) , LayToLeftCenter(Lay(knob_back),Lay(edit_dir)) };

     // list_dir , knob_mkdir , knob_rmdir

     LayToLeft lay2{ LayToBottom(Lay(knob_mkdir),LayAlignTop(Lay(knob_rmdir))) , Lay(list_dir) };

     // check_new , label_new_file , edit_new_file

     LayToRightCenter lay3{ Lay(alt_new_file) , Lay(label_new_file) , Lay(edit_new_file) };

     // list_file , filter_list

     LayDivX lay4{ Lay(list_file) , Lay(filter_list) , Div(2,3) };

     // btn_Ok , btn_Cancel

     LaySupCenterXExt lay5{ Lay(btn_Ok) , Lay(btn_Cancel) };

     // lay_dir

     LayToBottom lay_dir{ ExtLayX(lay1) , Lay(line1) , ExtLayX(lay2) };

     // lay_file

     LayToBottom lay_file{ LayNoSpace(split) , ExtLayX(lay3) , LayToTop(lay5,Lay(line2),ExtLayX(lay4)) };

     // lay

     Pane pane=getPane().shrink(0,space);

     splitSize(pane.getSize().y);

     Pane top=SplitY(top_dy,pane);

     lay_dir.setPlace(top,flags,space);
     lay_file.setPlace(pane,flags,space);
    }
  else
    {
     // knob_add , knob_hit , dir , knob_back

     LayToRightCenter lay1{ LayBox(knob_add) , LayBox(knob_hit) , LayToLeftCenter(Lay(knob_back),Lay(edit_dir)) };

     // list_dir

     Lay lay2(list_dir);

     // list_file , filter_list

     LayDivX lay4{ Lay(list_file) , Lay(filter_list) , Div(2,3) };

     // btn_Ok , btn_Cancel

     LaySupCenterXExt lay5{ Lay(btn_Ok) , Lay(btn_Cancel) };

     // lay_dir

     LayToBottom lay_dir{ ExtLayX(lay1) , Lay(line1) , ExtLayX(lay2) };

     // lay_file

     LayToBottom lay_file{ LayNoSpace(split) , LayToTop(lay5,Lay(line2),ExtLayX(lay4)) };

     // lay

     Pane pane=getPane().shrink(0,space);

     splitSize(pane.getSize().y);

     Pane top=SplitY(top_dy,pane);

     lay_dir.setPlace(top,flags,space);
     lay_file.setPlace(pane,flags,space);
    }
 }

void FileWindow::drawBack(DrawBuf buf,bool) const
 {
  buf.erase(+cfg.back);
 }

 // base

void FileWindow::open()
 {
  ComboWindow::open();

  file_path=Empty;

  if( param.new_file && !alt_new_file.isChecked() )
    {
     alt_new_file.check(true);

     check_new_file_changed(true);
    }

  if( Change(first_open,false) )
    {
     setDir("."_c);
    }
  else
    {
     if( list_dir.isEnabled() ) fillLists();
    }

  hit_list.load(param.file_boss->getHitDirFile());

  hit_list.prepare(hit_data);
 }

void FileWindow::close()
 {
  hit_list.save(param.file_boss->getHitDirFile());
 }

/* class FileFrame */

FileFrame::FileFrame(Desktop *desktop,const Config &cfg_,const FileWindowParam &param)
 : DragFrame(desktop,cfg_.frame_cfg),
   cfg(cfg_),
   sub_win(*this,cfg_.file_cfg,param)
 {
  bindClient(sub_win);
 }

FileFrame::FileFrame(Desktop *desktop,const Config &cfg,const FileWindowParam &param,Signal<> &update)
 : FileFrame(desktop,cfg,param)
 {
  connectUpdate(update);
 }

FileFrame::~FileFrame()
 {
 }

 // create

Pane FileFrame::getPane(StrLen title,Point base) const
 {
  Point size=getMinSize(false,title,sub_win.getMinSize(LayoutUpdate));

  Point screen_size=getScreenSize();

  return FitToScreen(base,size,screen_size);
 }

Pane FileFrame::getPane(StrLen title) const
 {
  Point size=getMinSize(false,title,sub_win.getMinSize(LayoutUpdate));

  return GetWindowPlace(getDesktop(),+cfg.pos_ry,size);
 }

} // namespace Video
} // namespace CCore
