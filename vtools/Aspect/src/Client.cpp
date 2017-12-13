/* Client.cpp */
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

namespace App {

/* struct RecentList */

void RecentList::setInd(ulen ind)
 {
  for(ulen lim=list.getLen(); ind<lim ;ind++) list[ind].id=int(first_id+ind);
 }

RecentList::RecentList(int first_id_,int max_count_)
 : first_id(first_id_),
   max_count(max_count_)
 {
 }

RecentList::~RecentList()
 {
 }

void RecentList::add(String file_name)
 {
  if( list.getLen()>=(ulen)max_count ) list.shrink_one();

  if( ArrayCopyIns(list,0,MenuTextNoHot,file_name,first_id) ) setInd(1);
 }

void RecentList::del(int id)
 {
  if( id<first_id ) return;

  ulen ind=id-first_id;

  if( ArrayCopyDel(list,ind) ) setInd(ind);
 }

StrLen RecentList::get(int id) const
 {
  if( id<first_id ) return Null;

  ulen ind=id-first_id;

  if( ind>=list.getLen() ) return Null;

  return list[ind].text.str();
 }

void RecentList::save(DynArray<String> &ret) const
 {
  ret.erase();

  for(const MenuPoint &point : list ) ret.append_copy(point.text.getDynamic());
 }

/* class ClientWindow */

void ClientWindow::menuOff()
 {
  if( cascade_menu.isAlive() ) cascade_menu.destroy();

  menu.unselect();
 }

void ClientWindow::fileOff()
 {
  if( file_frame.isAlive() )
    {
     cont=ContinueNone;

     file_frame.destroy();
    }
 }

void ClientWindow::dirOff()
 {
  if( dir_frame.isAlive() )
    {
     cont=ContinueNone;

     dir_frame.destroy();
    }
 }

void ClientWindow::msgOff()
 {
  if( msg_frame.isAlive() )
    {
     cont=ContinueNone;

     msg_frame.destroy();
    }
 }

void ClientWindow::askSave(Continue cont_)
 {
  msgOff();

  cont=cont_;

  msg_frame.create(getFrame(),+cfg.text_Alert);

  disableFrameReact();
 }

void ClientWindow::startNew(Point point)
 {
  dirOff();

  cont=ContinueNew2;

  dir_frame.create(getFrame(),point,+cfg.text_SelectPath);

  disableFrameReact();
 }

void ClientWindow::startOpen(Point point)
 {
  fileOff();

  file_frame.setNewFile(false);

  cont=ContinueOpen;

  file_frame.create(getFrame(),point,+cfg.text_LoadFile);

  disableFrameReact();
 }

void ClientWindow::startSave(Point point)
 {
  fileOff();

  file_frame.setNewFile(true);

  cont=ContinueSaveAs;

  file_frame.create(getFrame(),point,+cfg.text_SaveFile);

  disableFrameReact();
 }

void ClientWindow::openRecent(int id)
 {
  StrLen file_name=menu_recent_data.get(id);

  if( +file_name )
    {
     aspect.load(file_name);
    }
 }

void ClientWindow::menuAction(int id,Point point)
 {
  switch( id )
    {
     case MenuFileNew :
      {
       if( aspect.isModified() )
         {
          file_point=point;

          askSave(ContinueNew);
         }
       else
         {
          startNew(point);
         }
      }
     break;

     case MenuFileOpen :
      {
       if( aspect.isModified() )
         {
          file_point=point;

          askSave(ContinueStartOpen);
         }
       else
         {
          startOpen(point);
         }
      }
     break;

     case MenuFileSave :
      {
       if( !aspect.save() ) startSave(point);
      }
     break;

     case MenuFileSaveAs :
      {
       startSave(point);
      }
     break;

     case MenuFileExit :
      {
       askFrameClose();
      }
     break;

     case MenuCollect :
      {
       aspect.collect();
      }
     break;

     case MenuOptionsUserPref :
      {
       doUserPref.assert(point);
      }
     break;

     case MenuOptionsAppPref :
      {
       doAppPref.assert(point);
      }
     break;

     default:
      {
       if( id>=MenuRecentFirst && id<MenuRecentLim )
         {
          if( aspect.isModified() )
            {
             recent_id=id;

             askSave(ContinueOpenRecent);
            }
          else
            {
             openRecent(id);
            }
         }
      }
    }
 }

void ClientWindow::menuAction(int id)
 {
  menuAction(id,toScreen(action_base));
 }

void ClientWindow::menu_selected(int id,Point point)
 {
  if( cascade_menu.isAlive() ) cascade_menu.destroy();

  switch( id )
    {
     case MenuFile :
      {
       cascade_menu.create(getFrame(),menu_file_data,point);
      }
     break;

     case MenuActions :
      {
       cascade_menu.create(getFrame(),menu_act_data,point);
      }
     break;

     case MenuOptions :
      {
       cascade_menu.create(getFrame(),menu_opt_data,point);
      }
     break;

     case MenuRecent :
      {
       cascade_menu.create(getFrame(),menu_recent_data,point);
      }
     break;
    }
 }

void ClientWindow::cascade_menu_selected(int id,Point point)
 {
  menuOff();

  aspect.setFocus();

  menuAction(id,point);
 }

void ClientWindow::cascade_menu_deleted(int id)
 {
  if( id>=MenuRecentFirst && id<MenuRecentLim )
    {
     menu_recent_data.del(id);

     menu_recent_data.updated.assert();
    }
 }

void ClientWindow::cascade_menu_pressed(VKey vkey,KeyMod kmod)
 {
  menu.put_Key(vkey,kmod);
 }

void ClientWindow::file_destroyed()
 {
  enableFrameReact();

  switch( Replace(cont,ContinueNone) )
    {
     case ContinueOpen :
      {
       StrLen file_name=file_frame.getFilePath();

       if( +file_name )
         {
          aspect.load(file_name);

          menu_recent_data.add(file_name);

          menu_recent_data.updated.assert();
         }
      }
     break;

     case ContinueSaveAs :
      {
       StrLen file_name=file_frame.getFilePath();

       if( +file_name )
         {
          aspect.save(file_name);

          menu_recent_data.add(file_name);

          menu_recent_data.updated.assert();
         }
      }
     break;
    }
 }

void ClientWindow::dir_destroyed()
 {
  enableFrameReact();

  switch( Replace(cont,ContinueNone) )
    {
     case ContinueNew2 :
      {
       StrLen dir_name=dir_frame.getPath();

       if( +dir_name )
         {
          aspect.blank(dir_name);
         }
      }
     break;
    }
 }

void ClientWindow::msg_destroyed()
 {
  enableFrameReact();

  switch( msg_frame.getButtonId() )
    {
     case Button_Yes :
      {
       aspect.save();
      }
     break;

     case Button_Cancel :
      {
       cont=ContinueNone;
      }
     return;
    }

  switch( Replace(cont,ContinueNone) )
    {
     case ContinueNew :
      {
       startNew(file_point);
      }
     break;

     case ContinueStartOpen :
      {
       startOpen(file_point);
      }
     break;

     case ContinueExit :
      {
       destroyFrame();
      }
     break;

     case ContinueOpenRecent :
      {
       openRecent(recent_id);
      }
     break;
    }
 }

ClientWindow::ClientWindow(SubWindowHost &host,const Config &cfg_,const char *open_file_name)
 : ComboWindow(host),
   cfg(cfg_),

   menu_recent_data(MenuRecentFirst,MenuRecentLim-MenuRecentFirst),
   menu(wlist,cfg.menu_cfg,menu_data),
   cascade_menu(host.getFrameDesktop(),cfg.cascade_menu_cfg),
   aspect(wlist,cfg.aspect_cfg,open_file_name),
   file_frame(host.getFrameDesktop(),cfg.file_cfg,{true,".aspect.ddl"_def}),
   dir_frame(host.getFrameDesktop(),cfg.dir_cfg),
   msg_frame(host.getFrameDesktop(),cfg.msg_cfg),

   connector_menu_selected(this,&ClientWindow::menu_selected,menu.selected),
   connector_cascade_menu_selected(this,&ClientWindow::cascade_menu_selected,cascade_menu.selected),
   connector_cascade_menu_deleted(this,&ClientWindow::cascade_menu_deleted,cascade_menu.deleted),
   connector_cascade_menu_pressed(this,&ClientWindow::cascade_menu_pressed,cascade_menu.pressed),
   connector_file_destroyed(this,&ClientWindow::file_destroyed,file_frame.destroyed),
   connector_dir_destroyed(this,&ClientWindow::dir_destroyed,dir_frame.destroyed),
   connector_msg_destroyed(this,&ClientWindow::msg_destroyed,msg_frame.destroyed)
 {
  wlist.insTop(menu,aspect);

  wlist.enableTabFocus(false);

  // menu

  menu_data(+cfg.menu_File,MenuFile)
           (+cfg.menu_Actions,MenuActions)
           (+cfg.menu_Options,MenuOptions)
           (+cfg.menu_Recent,MenuRecent);

  menu_file_data(+cfg.menu_New,MenuFileNew)
                (+cfg.menu_Open,MenuFileOpen)
                (MenuSeparator)
                (+cfg.menu_Save,MenuFileSave)
                (+cfg.menu_SaveAs,MenuFileSaveAs)
                (MenuSeparator)
                (+cfg.menu_Exit,MenuFileExit);

  menu_act_data(+cfg.menu_Collect,MenuCollect);

  menu_opt_data(+cfg.menu_Global,MenuOptionsUserPref)
               (+cfg.menu_App,MenuOptionsAppPref);

  // file frame

  file_frame.addFilter("*.aspect.ddl"_c);
  file_frame.addFilter("*"_c,false);

  // msg frame

  msg_frame.setInfo(+cfg.text_AskSave)
           .add(+cfg.text_Yes,Button_Yes)
           .add(+cfg.text_No,Button_No)
           .add(+cfg.text_Cancel,Button_Cancel);
 }

ClientWindow::~ClientWindow()
 {
 }

 // methods

void ClientWindow::prepare(const AppState &app_state)
 {
  menu_recent_data.erase();

  for(const String &f : app_state.recent_files ) menu_recent_data.add(f);

  menu_recent_data.updated.assert();
 }

 // base

void ClientWindow::open()
 {
  wlist.open();

  aspect.setFocus();
 }

 // drawing

void ClientWindow::layout(unsigned)
 {
  Coord dy=menu.getMinSize().dy;

  action_base=Point(dy,dy);

  Pane pane(Null,getSize());

  menu.setPlace(SplitY(dy,pane));
  aspect.setPlace(pane);
 }

 // user input

void ClientWindow::react(UserAction action)
 {
  action.dispatch(*this);
 }

void ClientWindow::react_Key(VKey vkey,KeyMod kmod)
 {
  switch( vkey )
    {
     case VKey_F2 :
      {
       menuAction(MenuFileSave);
      }
     break;

     case VKey_F3 :
      {
       menuAction(MenuFileOpen);
      }
     break;

     case VKey_F10 :
      {
       menu.setFocus();
      }
     break;

     case VKey_Esc :
      {
       menuOff();

       aspect.setFocus();
      }
     break;

     default:
      {
       wlist.put_Key(vkey,kmod);
      }
    }
 }

void ClientWindow::react_LeftClick(Point point,MouseKey mkey)
 {
  menuOff();

  wlist.put_LeftClick(point,mkey);
 }

void ClientWindow::react_RightClick(Point point,MouseKey mkey)
 {
  menuOff();

  wlist.put_RightClick(point,mkey);
 }

void ClientWindow::react_other(UserAction action)
 {
  wlist.react(action);
 }

 // AliveControl

void ClientWindow::dying()
 {
  AppState app_state;

  app_state.place=getFrameHost()->getPlace();

  menu_recent_data.save(app_state.recent_files);

  app_state.save();
 }

bool ClientWindow::askDestroy()
 {
  if( aspect.isModified() )
    {
     askSave(ContinueExit);

     return false;
    }

  return true;
 }

} // namespace App

