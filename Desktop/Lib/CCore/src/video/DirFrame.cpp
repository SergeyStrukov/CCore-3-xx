/* DirFrame.cpp */
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

#include <CCore/inc/video/DirFrame.h>

#include <CCore/inc/Path.h>

#include <CCore/inc/Exception.h>

#include <CCore/inc/video/FileNameCmp.h>

#include <CCore/inc/video/LayoutCombo.h>

namespace CCore {
namespace Video {

/* class DirWindow */

void DirWindow::eraseLists()
 {
  list_dir.setInfo(ComboInfo());

  btn_Ok.disable();
 }

void DirWindow::fillLists()
 {
  try
    {
     ComboInfoBuilder dir_builder;

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
                        }

                     } ;

     auto temp=ToFunction<void (StrLen name,FileType type)>(func);

     param.file_boss->enumDir(cache_dir.getText(),temp.function());

     dir_builder.sortGroups(ExtNameLess);

     list_dir.setInfo(dir_builder.complete());

     enableOk();
    }
  catch(...)
    {
     eraseLists();
    }
 }

void DirWindow::setDir(StrLen dir_name)
 {
  char temp[MaxPathLen+1];

  StrLen path=param.file_boss->pathOf(dir_name,temp);

  if( param.file_boss->getFileType(path)==FileType_dir )
    {
     list_dir.enable();

     edit_dir.setText(path);
     edit_dir.alert(false);

     fillLists();
    }
  else
    {
     list_dir.disable();

     edit_dir.alert(true);

     eraseLists();

     Printf(NoException,"CCore::Video::DirWindow::setDir(#.q;) : #.q; is not a directory",dir_name,path);
    }
 }

void DirWindow::setSubDir(StrLen sub_dir)
 {
  MakeFileName temp(cache_dir.getText(),sub_dir);

  setDir(temp.get());
 }

void DirWindow::enableOk()
 {
  btn_Ok.enable( list_dir.isEnabled() );
 }

void DirWindow::handleDir(FuncArgType<StrLen> func)
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

void DirWindow::mkdir(StrLen dir_name)
 {
  {
   ExceptionFrame frame(exbuf);

   param.file_boss->createDir(dir_name);
  }

  setDir(dir_name);
 }

void DirWindow::rmdir(StrLen sub_dir)
 {
  MakeFileName temp(cache_dir.getText(),sub_dir);

  {
   ExceptionFrame frame(exbuf);

   param.file_boss->deleteDir(temp.get());
  }

  fillLists();
 }

void DirWindow::dir_list_entered()
 {
  handleDir( [this] (StrLen dir_name) { setSubDir(dir_name); } );
 }

void DirWindow::dir_entered()
 {
  setDir(cache_dir.getText());
 }

void DirWindow::dir_changed()
 {
  list_dir.disable();
  btn_Ok.disable();
 }

void DirWindow::btn_Ok_pressed()
 {
  hit_list.last(cache_dir.getText());

  buf.reset();

  buf.add(cache_dir.getText());

  if( +buf ) path=buf.get();

  askFrameClose();
 }

void DirWindow::btn_Cancel_pressed()
 {
  askFrameClose();
 }

void DirWindow::knob_hit_pressed()
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

void DirWindow::knob_add_pressed()
 {
  hit_list.add(cache_dir.getText());

  hit_list.prepare(hit_data);
 }

void DirWindow::knob_back_pressed()
 {
  StrLen dir_name=cache_dir.getText();

  if( ulen delta=ParentDir(dir_name) )
    {
     dir_name.len-=delta;

     setDir(dir_name);
    }
 }

void DirWindow::knob_mkdir_pressed()
 {
  if( !list_dir.isEnabled() ) mkdir(cache_dir.getText());
 }

void DirWindow::knob_rmdir_pressed()
 {
  handleDir( [this] (StrLen dir_name) { rmdir(dir_name); } );
 }

void DirWindow::hit_menu_destroyed()
 {
  knob_hit.setFace(KnobShape::FaceDown);
 }

void DirWindow::hit_menu_selected(int id,Point)
 {
  setDir(hit_list(id));

  hit_menu.destroy();
 }

void DirWindow::hit_menu_deleted(int id)
 {
  hit_list.del(id);

  hit_list.prepare(hit_data);
 }

DirWindow::DirWindow(SubWindowHost &host,const Config &cfg_,const DirWindowParam &param_)
 : ComboWindow(host),
   cfg(cfg_),
   param(param_),

   edit_dir(wlist,MaxPathLen,cfg.edit_cfg),
   knob_hit(wlist,cfg.knob_cfg,KnobShape::FaceDown),
   knob_add(wlist,cfg.knob_cfg,KnobShape::FacePlus),
   knob_back(wlist,cfg.knob_cfg,KnobShape::FaceLeft),
   line1(wlist,cfg.line_cfg),
   list_dir(wlist,cfg.list_cfg),
   knob_mkdir(wlist,cfg.knob_cfg,KnobShape::FacePlus),
   knob_rmdir(wlist,cfg.knob_cfg,KnobShape::FaceMinus),
   line2(wlist,cfg.line_cfg),
   btn_Ok(wlist,cfg.btn_cfg,cfg.text_Ok),
   btn_Cancel(wlist,cfg.btn_cfg,cfg.text_Cancel),

   hit_menu(host.getFrameDesktop(),cfg.hit_menu_cfg),

   cache_dir(edit_dir),

   exbuf(host.getFrame(),cfg.exbuf_cfg),

   connector_dir_list_entered(this,&DirWindow::dir_list_entered,list_dir.entered),
   connector_dir_list_dclicked(this,&DirWindow::dir_list_entered,list_dir.dclicked),
   connector_dir_entered(this,&DirWindow::dir_entered,edit_dir.entered),
   connector_dir_changed(this,&DirWindow::dir_changed,cache_dir.changed),
   connector_btn_Ok_pressed(this,&DirWindow::btn_Ok_pressed,btn_Ok.pressed),
   connector_btn_Cancel_pressed(this,&DirWindow::btn_Cancel_pressed,btn_Cancel.pressed),
   connector_knob_hit_pressed(this,&DirWindow::knob_hit_pressed,knob_hit.pressed),
   connector_knob_add_pressed(this,&DirWindow::knob_add_pressed,knob_add.pressed),
   connector_knob_back_pressed(this,&DirWindow::knob_back_pressed,knob_back.pressed),
   connector_knob_mkdir_pressed(this,&DirWindow::knob_mkdir_pressed,knob_mkdir.pressed),
   connector_knob_rmdir_pressed(this,&DirWindow::knob_rmdir_pressed,knob_rmdir.pressed),
   connector_hit_menu_destroyed(this,&DirWindow::hit_menu_destroyed,hit_menu.destroyed),
   connector_hit_menu_selected(this,&DirWindow::hit_menu_selected,hit_menu.selected),
   connector_hit_menu_deleted(this,&DirWindow::hit_menu_deleted,hit_menu.deleted)
 {
  wlist.insTop(knob_add,knob_hit,edit_dir,knob_back,line1,list_dir,knob_mkdir,knob_rmdir,line2,btn_Ok,btn_Cancel);

  edit_dir.hideInactiveCursor();

  // bind hints

  edit_dir.bindHint(cfg.hint_FileCurdir);
  knob_hit.bindHint(cfg.hint_FileHitList);
  knob_add.bindHint(cfg.hint_FileAddHit);
  knob_back.bindHint(cfg.hint_FileUpdir);
  list_dir.bindHint(cfg.hint_FileDirList);
  knob_mkdir.bindHint(cfg.hint_FileMakeDir);
  knob_rmdir.bindHint(cfg.hint_FileRemoveDir);
 }

DirWindow::~DirWindow()
 {
 }

 // methods

Point DirWindow::getMinSize() const
 {
  Coord space=+cfg.space_dxy;

  // knob_add , knob_hit , dir , knob_back

  LayToRightCenter lay1{ LayBox(knob_add) , LayBox(knob_hit) , LayToLeftCenter(Lay(knob_back),Lay(edit_dir)) };

  // list_dir , knob_mkdir , knob_rmdir

  LayToLeft lay2{ LayToBottom(Lay(knob_mkdir),LayAlignTop(Lay(knob_rmdir))) , LaySpecial(list_dir,12u) };

  // lay

  LayToBottom lay{ ExtLayX(lay1) , Lay(line1) , LayToTop(LaySupCenterXExt(Lay(btn_Ok),Lay(btn_Cancel)),Lay(line2),ExtLayX(lay2)) };

  return ExtLayY(lay).getMinSize(space);
 }

 // drawing

void DirWindow::layout()
 {
  Coord space=+cfg.space_dxy;

  // knob_add , knob_hit , dir , knob_back

  LayToRightCenter lay1{ LayBox(knob_add) , LayBox(knob_hit) , LayToLeftCenter(Lay(knob_back),Lay(edit_dir)) };

  // list_dir , knob_mkdir , knob_rmdir

  LayToLeft lay2{ LayToBottom(Lay(knob_mkdir),LayAlignTop(Lay(knob_rmdir))) , Lay(list_dir) };

  // lay

  LayToBottom lay{ ExtLayX(lay1) , Lay(line1) , LayToTop(LaySupCenterXExt(Lay(btn_Ok),Lay(btn_Cancel)),Lay(line2),ExtLayX(lay2)) };

  ExtLayY(lay).setPlace(getPane(),space);
 }

void DirWindow::drawBack(DrawBuf buf,DrawParam &draw_param) const
 {
  draw_param.erase(buf,+cfg.back);
 }

 // base

void DirWindow::open()
 {
  ComboWindow::open();

  path=Empty;

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

void DirWindow::close()
 {
  hit_list.save(param.file_boss->getHitDirFile());

  ComboWindow::close();
 }

/* class DirFrame */

DirFrame::DirFrame(Desktop *desktop,const Config &cfg,const DirWindowParam &param)
 : FrameClient<DirWindow>(desktop,cfg,param)
 {
 }

DirFrame::DirFrame(Desktop *desktop,const Config &cfg,Signal<> &update,const DirWindowParam &param)
 : DirFrame(desktop,cfg,param)
 {
  connectUpdate(update);
 }

DirFrame::~DirFrame()
 {
 }

} // namespace Video
} // namespace CCore

