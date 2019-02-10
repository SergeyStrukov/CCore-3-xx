/* TestFrame.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: UserPreference 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/TestFrame.h>

#include <CCore/inc/video/LayoutCombo.h>

//#include <CCore/inc/Print.h>

namespace App {

/* class TestWindow */

String TestWindow::InfoText()
 {
  return
"This is a test control panel.\n"
"You can see user preferences here.\n"
"Use main window to adjust sizes, colors etc..."_str;
 }

String TestWindow::ListText()
 {
  return
"button\n"
"check box\n"
"radio button\n"
"text line\n"
"light\n"
"scroll\n"
"line edit"_str;
 }

void TestWindow::changeColor(int new_id,int)
 {
  switch( new_id )
    {
     case 1 : light.setFace(Red); break;

     case 2 : light.setFace(Green); break;

     case 3 : light.setFace(Blue); break;
    }
 }

void TestWindow::lightOnOff(bool check)
 {
  light.turn(check);

  edit.alert(check);
 }

void TestWindow::knobPressed()
 {
  text.setText(String(edit.getText()));
 }

void TestWindow::enableAll(bool en)
 {
  btn.enable(en);
  alt.enable(en);
  knob.enable(en);
  check.enable(en);
  rad1.enable(en);
  rad2.enable(en);
  rad3.enable(en);
  xscroll.enable(en);
  info.enable(en);
  edit.enable(en);
  text_list.enable(en);

  label1.enable(en);
  label2.enable(en);
  label3.enable(en);
  label.enable(en);
  text.enable(en);
 }

void TestWindow::setFace(ulen index)
 {
  knob.setFace(KnobShape::FaceType(index));
 }

void TestWindow::push()
 {
  auto pos=progress.getPos();

  if( pos<progress.getTotal() )
    {
     progress.setPosPing(pos+1);
    }
  else
    {
     progress.setPos(0);
     progress.stopPing();
    }
 }

void TestWindow::shade()
 {
  if( enable_frame.isDead() ) enable_frame.create(getFrame(),"TestFrame enable"_str);

  disableFrameReact();
 }

void TestWindow::unshade()
 {
  enableFrameReact();
 }

TestWindow::TestWindow(SubWindowHost &host,const UserPreference &pref_)
 : ComboWindow(host),
   pref(pref_),

   btn(wlist,pref.getSmartConfig(),"Push"_str),
   knob(wlist,pref.getSmartConfig(),KnobShape::FaceOk),
   check(wlist,pref.getSmartConfig()),
   swtch(wlist,pref.getSmartConfig(),true),
   swtch1(wlist,pref.getSmartConfig()),
   swtch2(wlist,pref.getSmartConfig()),
   alt(wlist,pref.getSmartConfig()),
   rad1(wlist,1,pref.getSmartConfig()),
   rad2(wlist,2,pref.getSmartConfig()),
   rad3(wlist,3,pref.getSmartConfig()),
   xscroll(wlist,pref.getSmartConfig()),
   info(wlist,pref.getSmartConfig(),InfoFromString(InfoText())),
   edit(wlist,pref.getSmartConfig()),
   text_list(wlist,pref.getSmartConfig(),InfoFromString(ListText())),

   label1(wlist,pref.getSmartConfig(),"Red"_str,AlignX_Left),
   label2(wlist,pref.getSmartConfig(),"Green"_str,AlignX_Left),
   label3(wlist,pref.getSmartConfig(),"Blue"_str,AlignX_Left),
   label(wlist,pref.getSmartConfig(),"On/Off"_str,AlignX_Left),
   text(wlist,pref.getSmartConfig(),"<none>"_str),
   xsingle(wlist,pref.getSmartConfig()),
   ysingle(wlist,pref.getSmartConfig()),
   xdouble(wlist,pref.getSmartConfig()),
   ydouble(wlist,pref.getSmartConfig()),
   contour(wlist,pref.getSmartConfig()),
   text_contour(wlist,pref.getSmartConfig(),"Select color"_str),
   light(wlist,pref.getSmartConfig(),Red),
   progress(wlist,pref.getSmartConfig()),
   btn_shade(wlist,pref.getSmartConfig(),"Shade"_str),

   enable_frame(host.getFrameDesktop(),pref.getSmartConfig(),pref.updated),

   connector_group_changed(this,&TestWindow::changeColor,group.changed),
   connector_check_changed(this,&TestWindow::lightOnOff,check.changed),
   connector_knob_pressed(this,&TestWindow::knobPressed,knob.pressed),
   connector_swtch_changed(this,&TestWindow::enableAll,swtch.changed),
   connector_xscroll_changed(this,&TestWindow::setFace,xscroll.changed),
   connector_btn_pressed(this,&TestWindow::push,btn.pressed),
   connector_btn_shade_pressed(this,&TestWindow::shade,btn_shade.pressed),
   connector_enable_frame_destoyed(this,&TestWindow::unshade,enable_frame.destroyed)
 {
  wlist.insTop(swtch,btn,alt,rad1,rad2,rad3,check,
               edit,knob,xscroll,info,text_list,
               label1,label2,label3,label,text,xsingle,ysingle,xdouble,ydouble,
               contour,text_contour,light,swtch1,swtch2,progress,btn_shade);

  group.add(rad1,rad2,rad3);

  xscroll.setRange(KnobShape::FaceLim,1);

  edit.setText("To find our long-forgotten gold."_c);

  enable_frame.add("Ok"_str,Button_Ok).setInfo(InfoFromString("Press Ok to enable"_str));
 }

TestWindow::~TestWindow()
 {
 }

 // drawing

void TestWindow::layout()
 {
  Coord space=pref.get().space_dxy;

  // swtch , btn , alt , progress

  LayToRightCenter lay1{Lay(swtch),Lay(btn),Lay(alt),Lay(progress)};

  // text_contour , label , rad

  LayInner lay2(text_contour,LayToBottomLeft(BoxedWindow(rad1,label1),BoxedWindow(rad2,label2),BoxedWindow(rad3,label3)));

  // check , label , light , swtch1 , swtch2

  LayToRightCenter lay3(BoxedWindow(check,label),Lay(light),Lay(swtch1),LayLeft(swtch2));

  // ysingle , knob , ydouble , xscroll

  LayToRight lay4{Lay(ysingle),LayCenterY(knob),Lay(ydouble),LayCenterY(xscroll)};

  // contour , info

  LayInnerSpace lay5(contour,Lay(info),0);

  // lay

  LayToBottom lay(lay1,
                  LayAlignLeft(lay2),
                  lay3,
                  Lay(xsingle),
                  Lay(edit),
                  Lay(text),
                  Lay(xdouble),
                  lay4,
                  LayAlignLeft(lay5),
                  LayLeft(text_list),
                  LayAlignTop(LayLeft(btn_shade)));

  ExtLay(lay).setPlace(getPane(),space);
 }

void TestWindow::drawBack(DrawBuf buf,bool) const
 {
  VColor back=pref.get().back;

  buf.erase(back);
 }

/* class TestClient */

void TestClient::menuOff()
 {
  if( cascade_menu.isAlive() ) cascade_menu.destroy();

  menu.unselect();
 }

void TestClient::menu_selected(int id,Point point)
 {
  if( cascade_menu.isAlive() ) cascade_menu.destroy();

  switch( id )
    {
     case 1 :
      {
       cascade_menu.create(getFrame(),menu_file_data,point);
      }
     break;

     case 2 :
      {
       cascade_menu.create(getFrame(),menu_edit_data,point);
      }
     break;

     case 3 :
      {
       cascade_menu.create(getFrame(),menu_options_data,point);
      }
     break;

     case 5 :
      {
       cascade_menu.create(getFrame(),menu_window_data,point);
      }
     break;

     case 6 :
      {
       cascade_menu.create(getFrame(),menu_long_data,point);
      }
     break;
    }
 }

void TestClient::cascade_menu_selected(int id,Point point)
 {
  menuOff();

  test.setFocus();

  switch( id )
    {
     case 101 :
      {
       if( !file_window.isAlive() )
         {
          file_window.setNewFile(true);

          file_window.create(point,"Select file"_str);
         }
      }
     break;

     case 102 :
      {
       if( !file_window.isAlive() )
         {
          file_window.setNewFile(false);

          file_window.create(point,"Select file"_str);
         }
      }
     break;

     case 105 :
      {
       askFrameClose();
      }
     break;
    }
 }

void TestClient::cascade_menu_pressed(VKey vkey,KeyMod kmod)
 {
  menu.put_Key(vkey,kmod);
 }

TestClient::TestClient(SubWindowHost &host,const UserPreference &pref,Signal<> &update)
 : ComboWindow(host),

   menu(wlist,pref.getSmartConfig(),menu_data),
   cascade_menu(host.getFrameDesktop(),pref.getSmartConfig()),
   test(wlist,pref),
   file_window(host.getFrameDesktop(),pref.getSmartConfig(),{true},update),

   connector_menu_selected(this,&TestClient::menu_selected,menu.selected),
   connector_cascade_menu_selected(this,&TestClient::cascade_menu_selected,cascade_menu.selected),
   connector_cascade_menu_pressed(this,&TestClient::cascade_menu_pressed,cascade_menu.pressed)
 {
  cascade_menu.connectUpdate(update);

  wlist.insTop(menu,test);

  wlist.enableTabFocus(false);

  menu_data("@File"_str,1)
           ("@Edit"_str,2)
           (MenuSeparator)
           ("@Options"_str,3)
           (MenuDisabled,"@Modules"_str,4)
           ("@Window"_str,5)
           ("@Long menu"_str,6);

  menu_file_data("@New"_str,101)
                ("@Open"_str,102)
                (MenuDisabled,"@Save"_str,103)
                (MenuDisabled,"Save @as"_str,104)
                (MenuSeparator)
                ("E@xit"_str,105);

  menu_edit_data("@Undo"_str,201)
                ("@Check"_str,202)
                (MenuSeparator)
                ("Cut"_str,203)
                ("Copy"_str,204)
                ("Paste"_str,205)
                (MenuSeparator)
                ("@Run"_str,206);

  menu_options_data("@Colors"_str,301)
                   ("@Fonts"_str,302)
                   ("@Targets"_str,303);

  menu_window_data("@Split"_str,501)
                  ("@Close all"_str,502)
                  ("S@tack"_str,503);

  for(int i=1; i<100 ;i++)
    {
     menu_long_data(Stringf("menu item #;",i),600+i);
    }

  file_window.addFilter("*.h"_c);
  file_window.addFilter("*.cpp"_c);
  file_window.addFilter("*"_c);
 }

TestClient::~TestClient()
 {
 }

 // base

void TestClient::open()
 {
  wlist.open();

  test.setFocus();
 }

 // drawing

void TestClient::layout()
 {
  LayToBottom lay{Lay(menu),Lay(test)};

  lay.setPlace(getPane(),0);
 }

 // user input

void TestClient::react(UserAction action)
 {
  action.dispatch(*this);
 }

void TestClient::react_Key(VKey vkey,KeyMod kmod)
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

       test.setFocus();
      }
     break;

     default:
      {
       wlist.put_Key(vkey,kmod);
      }
    }
 }

void TestClient::react_LeftClick(Point point,MouseKey mkey)
 {
  menuOff();

  wlist.put_LeftClick(point,mkey);
 }

void TestClient::react_RightClick(Point point,MouseKey mkey)
 {
  menuOff();

  wlist.put_RightClick(point,mkey);
 }

void TestClient::react_other(UserAction action)
 {
  wlist.react(action);
 }

/* class TestFrame */

TestFrame::TestFrame(Desktop *desktop,const UserPreference &pref,Signal<> &update)
 : DragFrame(desktop,pref.getSmartConfig(),update),
   client(*this,pref,update)
 {
  bindClient(client);
 }

TestFrame::~TestFrame()
 {
 }

} // namespace App

