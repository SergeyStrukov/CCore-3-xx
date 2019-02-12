/* BookFrame.cpp */
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

#include <CCore/inc/video/BookFrame.h>

#include <CCore/inc/video/LayoutCombo.h>

namespace CCore {
namespace Video {

/* class ShowBookClient */

void ShowBookClient::menuOff()
 {
  if( cascade_menu.isAlive() ) cascade_menu.destroy();

  menu.unselect();
 }

void ShowBookClient::menuAction(int id,Point point)
 {
  switch( id )
    {
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

void ShowBookClient::menu_selected(int id,Point point)
 {
  if( cascade_menu.isAlive() ) cascade_menu.destroy();

  switch( id )
    {
     case MenuOptions :
      {
       cascade_menu.create(getFrame(),menu_opt_data,point);
      }
     break;
    }
 }

void ShowBookClient::cascade_menu_selected(int id,Point point)
 {
  menuOff();

  sub_win.setFocus();

  menuAction(id,point);
 }

void ShowBookClient::cascade_menu_pressed(VKey vkey,KeyMod kmod)
 {
  menu.put_Key(vkey,kmod);
 }

ShowBookClient::ShowBookClient(SubWindowHost &host,const Config &cfg_,Signal<> &update)
 : ComboWindow(host),
   cfg(cfg_),

   menu(wlist,cfg.menu_cfg,menu_data),
   cascade_menu(host.getFrameDesktop(),cfg.cascade_menu_cfg),
   sub_win(wlist,cfg.sub_win_cfg,OptFileName(),update),

   connector_menu_selected(this,&ShowBookClient::menu_selected,menu.selected),
   connector_cascade_menu_selected(this,&ShowBookClient::cascade_menu_selected,cascade_menu.selected),
   connector_cascade_menu_pressed(this,&ShowBookClient::cascade_menu_pressed,cascade_menu.pressed)
 {
  cascade_menu.connectUpdate(update);

  wlist.insTop(menu,sub_win);

  wlist.enableTabFocus(false);

  menu_data(+cfg.menu_Options,MenuOptions);

  menu_opt_data(+cfg.menu_Global,MenuOptionsUserPref)
               (+cfg.menu_App,MenuOptionsAppPref);
 }

ShowBookClient::~ShowBookClient()
 {
 }

 // methods

Point ShowBookClient::getMinSize() const
 {
  LayToBottom lay{Lay(menu),Lay(sub_win)};

  return lay.getMinSize(0);
 }

 // base

void ShowBookClient::open()
 {
  wlist.open();

  sub_win.setFocus();
 }

 // drawing

void ShowBookClient::layout()
 {
  LayToBottom lay{Lay(menu),Lay(sub_win)};

  lay.setPlace(getPane(),0);
 }

 // user input

void ShowBookClient::react(UserAction action)
 {
  action.dispatch(*this);
 }

void ShowBookClient::react_Key(VKey vkey,KeyMod kmod)
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

void ShowBookClient::react_LeftClick(Point point,MouseKey mkey)
 {
  menuOff();

  wlist.put_LeftClick(point,mkey);
 }

void ShowBookClient::react_RightClick(Point point,MouseKey mkey)
 {
  menuOff();

  wlist.put_RightClick(point,mkey);
 }

void ShowBookClient::react_other(UserAction action)
 {
  wlist.react(action);
 }

/* class BookFrame */


} // namespace Video
} // namespace CCore

