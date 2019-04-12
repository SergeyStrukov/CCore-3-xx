/* Client.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: WinLab 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/Client.h>

#include <CCore/inc/video/LayoutCombo.h>

namespace App {

/* class ClientWindow */

void ClientWindow::menuOff()
 {
  if( cascade_menu.isAlive() ) cascade_menu.destroy();

  menu.unselect();
 }

void ClientWindow::menuAction(int id,Point point)
 {
  switch( id )
    {
     case MenuFileNew :
      {
      }
     break;

     case MenuFileOpen :
      {
      }
     break;

     case MenuFileSave :
      {
      }
     break;

     case MenuFileSaveAs :
      {
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

ClientWindow::ClientWindow(SubWindowHost &host,const Config &cfg_,OptNone,Signal<> &update)
 : ComboWindow(host),
   cfg(cfg_),

   menu(wlist,cfg.menu_cfg,menu_data),
   cascade_menu(host.getFrameDesktop(),cfg.cascade_menu_cfg),
   sub_win(wlist,cfg.sub_win_cfg),

   connector_menu_selected(this,&ClientWindow::menu_selected,menu.selected),
   connector_cascade_menu_selected(this,&ClientWindow::cascade_menu_selected,cascade_menu.selected),
   connector_cascade_menu_pressed(this,&ClientWindow::cascade_menu_pressed,cascade_menu.pressed)
 {
  cascade_menu.connectUpdate(update);

  wlist.insTop(menu,sub_win);

  wlist.enableTabFocus(false);

  menu_data(+cfg.menu_File,MenuFile)
           (+cfg.menu_Options,MenuOptions);

  menu_file_data(+cfg.menu_New,MenuFileNew)
                (+cfg.menu_Open,MenuFileOpen)
                (MenuSeparator)
                (+cfg.menu_Save,MenuFileSave)
                (+cfg.menu_SaveAs,MenuFileSaveAs)
                (MenuSeparator)
                (+cfg.menu_Exit,MenuFileExit);

  menu_opt_data(+cfg.menu_Global,MenuOptionsUserPref)
               (+cfg.menu_App,MenuOptionsAppPref);
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
 }

void ClientWindow::drawBack(DrawBuf buf,DrawParam &draw_param) const
 {
  draw_param.erase(buf,+cfg.back);
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

} // namespace App

