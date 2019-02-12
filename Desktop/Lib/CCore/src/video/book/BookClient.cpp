/* BookClient.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.60
//
//  Tag: Desktop
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/video/book/BookClient.h>

#include <CCore/inc/video/LayoutCombo.h>

namespace CCore {
namespace Video {
namespace Book {

/* class ClientWindow */

void ClientWindow::ClientBag::bindItems(ConfigItemBind &binder)
 {
  binder.group("Common"_str);

    binder.item("title"_str,title);

  binder.group("Menu"_str);

    binder.item("File"_str,menu_File);
    binder.item("Options"_str,menu_Options);
    binder.item("New"_str,menu_New);
    binder.item("Open"_str,menu_Open);
    binder.item("Exit"_str,menu_Exit);
    binder.item("Global"_str,menu_Global);
    binder.item("App"_str,menu_App);
 }

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

void ClientWindow::startOpen(Point point)
 {
  fileOff();

  cont=ContinueOpen;

  file_frame.create(getFrame(),point,+cfg.text_LoadFile);

  disableFrameReact();
 }

void ClientWindow::menuAction(int id,Point point)
 {
  switch( id )
    {
     case MenuFileNew :
      {
       sub_win.blank();
      }
     break;

     case MenuFileOpen :
      {
       startOpen(point);
      }
     break;

     case MenuFileExit :
      {
       askFrameClose();
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

     case MenuOptions :
      {
       cascade_menu.create(getFrame(),menu_opt_data,point);
      }
     break;
    }
 }

void ClientWindow::cascade_menu_selected(int id,Point point)
 {
  menuOff();

  sub_win.setFocus();

  menuAction(id,point);
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
          sub_win.load(file_name);
         }
      }
     break;
    }
 }

ClientWindow::ClientWindow(SubWindowHost &host,const Config &cfg_,OptFileName opt,Signal<> &update)
 : ComboWindow(host),
   cfg(cfg_),

   menu(wlist,cfg.menu_cfg,menu_data),
   cascade_menu(host.getFrameDesktop(),cfg.cascade_menu_cfg),
   sub_win(wlist,cfg.sub_win_cfg,opt,update),
   file_frame(host.getFrameDesktop(),cfg.file_cfg,{false}),

   connector_menu_selected(this,&ClientWindow::menu_selected,menu.selected),
   connector_cascade_menu_selected(this,&ClientWindow::cascade_menu_selected,cascade_menu.selected),
   connector_cascade_menu_pressed(this,&ClientWindow::cascade_menu_pressed,cascade_menu.pressed),
   connector_file_destroyed(this,&ClientWindow::file_destroyed,file_frame.destroyed)
 {
  cascade_menu.connectUpdate(update);

  wlist.insTop(menu,sub_win);

  wlist.enableTabFocus(false);

  menu_data(+cfg.menu_File,MenuFile)
           (+cfg.menu_Options,MenuOptions);

  menu_file_data(+cfg.menu_New,MenuFileNew)
                (+cfg.menu_Open,MenuFileOpen)
                (MenuSeparator)
                (+cfg.menu_Exit,MenuFileExit);

  menu_opt_data(+cfg.menu_Global,MenuOptionsUserPref)
               (+cfg.menu_App,MenuOptionsAppPref);

  // file frame

  file_frame.addFilter("*.book.ddl"_c);
  file_frame.addFilter("*.vol"_c);
  file_frame.addFilter("*"_c,false);
 }

ClientWindow::~ClientWindow()
 {
 }

 // methods

Point ClientWindow::getMinSize() const
 {
  LayToBottom lay{Lay(menu),Lay(sub_win)};

  return lay.getMinSize(0);
 }

 // base

void ClientWindow::open()
 {
  wlist.open();

  sub_win.setFocus();
 }

 // drawing

void ClientWindow::layout()
 {
  LayToBottom lay{Lay(menu),Lay(sub_win)};

  lay.setPlace(getPane(),0);

  // action_base

  action_base=Point::Diag( menu.getPlace().dy );
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

       sub_win.setFocus();
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

} // namespace Book
} // namespace Video
} // namespace CCore

