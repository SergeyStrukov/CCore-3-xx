/* Client.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: DDLDisplay 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/Client.h>

namespace App {

/* class ClientWindow */

void ClientWindow::menuOff()
 {
  if( cascade_menu.isAlive() ) cascade_menu.destroy();

  menu.unselect();
 }

void ClientWindow::menu_selected(int id,Point point)
 {
  if( cascade_menu.isAlive() ) cascade_menu.destroy();

  switch( id )
    {
     case Cmd_File :
      {
       cascade_menu.create(getFrame(),menu_file_data,point);
      }
     break;

     case Cmd_Options :
      {
       cascade_menu.create(getFrame(),menu_options_data,point);
      }
     break;
    }
 }

void ClientWindow::cascade_menu_selected(int id,Point base)
 {
  menuOff();

  display.setFocus();

  switch( id )
    {
     case Cmd_Open :
      {
       if( open_file.isDead() )
         {
          open_file.create(getFrame(),base,"Select a DDL file"_def);
         }
      }
     break;

     case Cmd_Pretext :
      {
       if( open_pretext.isDead() )
         {
          open_pretext.create(getFrame(),base,"Select a DDL pretext"_def);
         }
      }
     break;

     case Cmd_NoPretext :
      {
       display.noPretext();
      }
     break;

     case Cmd_UserPref :
      {
       doUserPref.assert(base);
      }
     break;

     case Cmd_AppPref :
      {
       doAppPref.assert(base);
      }
     break;

     case Cmd_Exit :
      {
       askFrameClose();
      }
     break;
    }
 }

void ClientWindow::cascade_menu_pressed(VKey vkey,KeyMod kmod)
 {
  menu.put_Key(vkey,kmod);
 }

void ClientWindow::open_file_destroyed()
 {
  StrLen file_name=open_file.getFilePath();

  if( +file_name )
    {
     display.open(file_name);
    }
 }

void ClientWindow::open_pretext_destroyed()
 {
  StrLen file_name=open_pretext.getFilePath();

  if( +file_name )
    {
     display.openPretext(file_name);
    }
 }

ClientWindow::ClientWindow(SubWindowHost &host,const Config &cfg_)
 : ComboWindow(host),
   cfg(cfg_),
   menu(wlist,cfg.menu_cfg,menu_data),
   cascade_menu(host.getFrame()->getDesktop(),cfg.cascade_menu_cfg),
   display(wlist,cfg.display_cfg),
   open_file(host.getFrame()->getDesktop(),cfg.file_cfg,{false}),
   open_pretext(host.getFrame()->getDesktop(),cfg.file_cfg,{false}),

   connector_menu_selected(this,&ClientWindow::menu_selected,menu.selected),
   connector_cascade_menu_selected(this,&ClientWindow::cascade_menu_selected,cascade_menu.selected),
   connector_cascade_menu_pressed(this,&ClientWindow::cascade_menu_pressed,cascade_menu.pressed),

   connector_open_file_destroyed(this,&ClientWindow::open_file_destroyed,open_file.destroyed),
   connector_open_pretext_destroyed(this,&ClientWindow::open_pretext_destroyed,open_pretext.destroyed),

   opened(display.opened)
 {
  wlist.insTop(menu,display);

  wlist.enableTabFocus(false);

  menu_data("@File"_def,Cmd_File)
           ("@Options"_def,Cmd_Options);

  menu_file_data("@Open ..."_def,Cmd_Open)
                (MenuSeparator)
                ("E@xit"_def,Cmd_Exit);

  menu_options_data("@Pretext ..."_def,Cmd_Pretext)
                   ("@No Pretext"_def,Cmd_NoPretext)
                   ("@User preferences"_def,Cmd_UserPref)
                   ("@Application preferences"_def,Cmd_AppPref);

  open_file.addFilter("*.ddl"_c);
  open_file.addFilter("*"_c,false);

  open_pretext.addFilter("*.ddl"_c);
  open_pretext.addFilter("*"_c,false);
 }

ClientWindow::~ClientWindow()
 {
 }

void ClientWindow::open()
 {
  wlist.open();

  display.setFocus();
 }

void ClientWindow::layout(unsigned flags)
 {
  Coord dy=menu.getMinSize(flags).dy;

  Pane pane(Null,getSize());

  menu.setPlace(SplitY(dy,pane),flags);
  display.setPlace(pane,flags);
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

       display.setFocus();
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

