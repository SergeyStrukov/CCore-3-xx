/* ItemListWindow.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: ContourLab 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/ItemListWindow.h>

#include <CCore/inc/video/Layout.h>

namespace App {

/* class InsWindow */

void InsWindow::btn_Insert_pressed()
 {
  ulen select=list.getSelect();

  ulen count=info_ins->getLineCount();

  if( select<count ) selected.assert(info_ins->getLine(select));
 }

void InsWindow::btn_Close_pressed()
 {
  askFrameClose();
 }

InsWindow::InsWindow(SubWindowHost &host,const Config &cfg_)
 : ComboWindow(host),
   cfg(cfg_),

   list(wlist,cfg.list_cfg),
   btn_Insert(wlist,cfg.btn_cfg,cfg.text_Insert),
   btn_Close(wlist,cfg.btn_cfg,cfg.text_Close),

   connector_btn_Insert_pressed(this,&InsWindow::btn_Insert_pressed,btn_Insert.pressed),
   connector_btn_Close_pressed(this,&InsWindow::btn_Close_pressed,btn_Close.pressed)
 {
  wlist.insTop(list,btn_Insert,btn_Close);

  // bind hints

  list.bindHint(cfg.hint_List);
 }

InsWindow::~InsWindow()
 {
 }

 // methods

Point InsWindow::getMinSize(Point cap) const
 {
  Coord space=+cfg.space_dxy;

  Point bs=SupMinSize(btn_Insert,btn_Close);

  Point delta( 2*space , 3*space+bs.y );

  Point s=list.getMinSize(cap-delta);

  return delta+Point( Max_cast(s.x,2*bs.x+space) , s.y );
 }

 // drawing

void InsWindow::layout(unsigned)
 {
  PaneCut pane(getSize(),+cfg.space_dxy);

  pane.shrink();

  pane.placeRow_cutBottom(btn_Insert,btn_Close).place(list);
 }

void InsWindow::drawBack(DrawBuf buf,bool) const
 {
  buf.erase(+cfg.back);
 }

/* class InsFrame */

InsFrame::InsFrame(Desktop *desktop,const Config &cfg)
 : DragFrame(desktop,cfg.drag_cfg),
   client(*this,cfg.ins_cfg),

   selected(client.selected)
 {
  bindClient(client);
 }

InsFrame::~InsFrame()
 {
 }

Pane InsFrame::getPane(StrLen title,Point base) const
 {
  Point screen_size=getScreenSize();

  Point size=getMinSize(false,title,client.getMinSize(screen_size));

  return FitToScreen(base,size,screen_size);
 }

/* class EditFormulaShape */

void EditFormulaShape::drawText(Font font,const DrawBuf &buf,Pane pane,TextPlace place,PtrLen<const Char> text,ulen off,VColor) const
 {
  const Config &cfg=getCfg();

  VColor normal_text=+cfg.text;
  VColor error_text=+cfg.error_text;
  VColor number_text=+cfg.number_text;
  VColor length_text=+cfg.length_text;
  VColor angle_text=+cfg.angle_text;
  VColor name_text=+cfg.name_text;
  VColor punct_text=+cfg.punct_text;

  auto map = [=] (CharAccent accent) -> VColor
                 {
                  switch( accent )
                    {
                     case CharNormal : return normal_text;

                     case CharNumber : return number_text;

                     case CharLength : return length_text;

                     case CharAngle : return angle_text;

                     case CharName : return name_text;

                     case CharPunct : return punct_text;

                     default: return error_text;
                    }
                 } ;

  CharAccent *accent=this->accent;

  auto func = [=] (ulen index,Char,Point,Point) -> VColor { return map(accent[off+index]); } ;

  auto proxy=ToFunction<VColor (ulen index,Char ch,Point base,Point delta)>(func);

  font->text(buf,pane,place,text,proxy.function());
 }

/* class EditFormulaWindow */

void EditFormulaWindow::tick()
 {
  if( time )
    {
     time--;
    }
  else
    {
     defer_tick.stop();

     paused.assert();
    }
 }

void EditFormulaWindow::start()
 {
  const ConfigType &cfg=shape.getCfg();

  time=+cfg.delay;

  defer_tick.start();
 }

EditFormulaWindow::EditFormulaWindow(SubWindowHost &host,const ConfigType &cfg)
 : LineEditWindowOf<EditFormulaShape>(host,cfg),
   storage(DefBufLen),

   connector_changed(this,&EditFormulaWindow::start,changed)
 {
  shape.accent=storage.getPtr();

  defer_tick=input.create(static_cast<void (LineEditWindowOf<EditFormulaShape>::*)()>(&EditFormulaWindow::tick));
 }

EditFormulaWindow::~EditFormulaWindow()
 {
 }

void EditFormulaWindow::normalAccent()
 {
  if( Change(flag,true) ) Range(shape.accent,shape.len).set(CharNormal);
 }

/* class ItemListWindow */

void ItemListWindow::list_selected(ulen index)
 {
  ulen count=list.getInfo()->getLineCount();

  knob_down.enable( index<count-1 );

  knob_up.enable( index>0 );

  knob_del.enable();

  check_show.enable();
  check_gray.enable();
  check_name.enable();

  selected.assert(index);
 }

void ItemListWindow::knob_down_pressed()
 {
  command_down.assert(list.getSelect());
 }

void ItemListWindow::knob_up_pressed()
 {
  command_up.assert(list.getSelect());
 }

void ItemListWindow::knob_del_pressed()
 {
  command_del.assert(list.getSelect());
 }

void ItemListWindow::knob_add_pressed()
 {
  command_add.assert(list.getSelect());
 }

void ItemListWindow::check_show_changed(bool check)
 {
  show_changed.assert(list.getSelect(),check);
 }

void ItemListWindow::check_gray_changed(bool check)
 {
  gray_changed.assert(list.getSelect(),check);
 }

void ItemListWindow::check_name_changed(bool check)
 {
  name_changed.assert(list.getSelect(),check);
 }

void ItemListWindow::knob_ins_pressed()
 {
  Point base(getSize().x,0);

  ins_frame.create(getFrame(),toScreen(base),+cfg.title_Ins);

  knob_ins.disable();
 }

void ItemListWindow::ins_frame_destroyed()
 {
  knob_ins.enable();
 }

void ItemListWindow::ins_frame_selected(StrLen text)
 {
  edit.insText(text);
 }

ItemListWindow::ItemListWindow(SubWindowHost &host,const Config &cfg_)
 : ComboWindow(host),
   cfg(cfg_),

   list(wlist,cfg.list_cfg),
   edit(wlist,cfg.edit_cfg),

   knob_down(wlist,cfg.knob_cfg,KnobShape::FaceDown),
   knob_up(wlist,cfg.knob_cfg,KnobShape::FaceUp),
   knob_del(wlist,cfg.knob_cfg,KnobShape::FaceCross),
   knob_add(wlist,cfg.knob_cfg,KnobShape::FacePlus),
   knob_ins(wlist,cfg.knob_cfg,KnobShape::FaceList),

   label_show(wlist,cfg.label_cfg,cfg.text_show),
   label_gray(wlist,cfg.label_cfg,cfg.text_gray),
   label_name(wlist,cfg.label_cfg,cfg.text_name),

   check_show(wlist,cfg.check_cfg),
   check_gray(wlist,cfg.check_cfg),
   check_name(wlist,cfg.check_cfg),

   ins_frame(host.getFrameDesktop(),cfg.ins_cfg),

   connector_list_selected(this,&ItemListWindow::list_selected,list.selected),
   connector_edit_entered(this,&ItemListWindow::knob_add_pressed,edit.entered),
   connector_knob_down_pressed(this,&ItemListWindow::knob_down_pressed,knob_down.pressed),
   connector_knob_up_pressed(this,&ItemListWindow::knob_up_pressed,knob_up.pressed),
   connector_knob_del_pressed(this,&ItemListWindow::knob_del_pressed,knob_del.pressed),
   connector_knob_add_pressed(this,&ItemListWindow::knob_add_pressed,knob_add.pressed),

   connector_check_show_changed(this,&ItemListWindow::check_show_changed,check_show.changed),
   connector_check_gray_changed(this,&ItemListWindow::check_gray_changed,check_gray.changed),
   connector_check_name_changed(this,&ItemListWindow::check_name_changed,check_name.changed),

   connector_knob_ins_pressed(this,&ItemListWindow::knob_ins_pressed,knob_ins.pressed),
   connector_ins_frame_destroyed(this,&ItemListWindow::ins_frame_destroyed,ins_frame.destroyed),
   connector_ins_frame_selected(this,&ItemListWindow::ins_frame_selected,ins_frame.selected),

   text_changed(edit.changed),
   text_paused(edit.paused)
 {
  wlist.insTop(knob_down,knob_up,knob_del,list,label_show,label_gray,label_name,check_show,check_gray,check_name,edit,knob_add);

  noItem();

  enableAdd(false);

  knob_ins.disable();

  // bind hints

  list.bindHint(cfg.hint_List);
  edit.bindHint(cfg.hint_Edit);

  knob_down.bindHint(cfg.hint_Down);
  knob_up.bindHint(cfg.hint_Up);
  knob_del.bindHint(cfg.hint_Del);
  knob_add.bindHint(cfg.hint_Add);
  knob_ins.bindHint(cfg.hint_Ins);

  check_show.bindHint(cfg.hint_Show);
  check_gray.bindHint(cfg.hint_Gray);
  check_name.bindHint(cfg.hint_Name);
 }

ItemListWindow::~ItemListWindow()
 {
 }

 // methods

Point ItemListWindow::getMinSize(Point cap) const
 {
  Coord space=+cfg.space_dxy;

  Coord knob_dxy=knob_down.getMinSize().dxy;
  Coord kspace=BoxSpace(knob_dxy);

  Coord check_dxy=check_show.getMinSize().dxy;
  Coord label_dy=label_show.getMinSize().y;

  Point edit_size=edit.getMinSize();

  Coord dy=3*space+knob_dxy+Max(edit_size.y,knob_dxy)+Max(check_dxy,label_dy);

  Point list_size=list.getMinSize(Point(cap.x,cap.y-dy));

  return Point( Max_cast( list_size.x , edit_size.x+knob_dxy+kspace , 3*knob_dxy+2*kspace ) , list_size.y+dy );
 }

void ItemListWindow::setCheck(bool show,bool gray,bool name)
 {
  check_show.check(show);
  check_gray.check(gray);
  check_name.check(name);
 }

void ItemListWindow::noItem()
 {
  knob_down.disable();
  knob_up.disable();
  knob_del.disable();

  setCheck(false,false,false);

  check_show.disable();
  check_gray.disable();
  check_name.disable();
 }

 // drawing

void ItemListWindow::layout(unsigned)
 {
  Coord space=+cfg.space_dxy;

  PaneCut pane(getSize(),space);

  // knob_down , knob_up , knob_del

  {
   Coord dy=knob_down.getMinSize().dxy;

   PaneCut p=pane.cutTop(dy);

   p.place_cutLeft(knob_down).place_cutLeft(knob_up).place_cutRight(knob_del);
  }

  // edit , knob_add

  {
   auto knob__add=CutBox(knob_add);
   auto edit_=CutPoint(edit);

   Coord dy=SupDY(knob__add,edit_);

   PaneCut p=pane.cutBottom(dy);

   if( ins_set )
     p.place_cutRight(knob__add).place_cutLeft(knob_ins).place(edit_);
   else
     p.place_cutRight(knob__add).place(edit_);
  }

  // label... , check...

  {
   auto check__show=CutBox(check_show);
   auto label__show=CutPoint(label_show);

   Coord dy=SupDY(check__show,label__show);

   PaneCut p=pane.cutBottom(dy);

   p.place_cutLeft(check__show).place_cutLeft(label__show)
    .place_cutLeft(check_gray).place_cutLeft(label_gray)
    .place_cutLeft(check_name).place_cutLeft(label_name);
  }

  // list

  {
   pane.place(list);
  }
 }

 // user input

void ItemListWindow::react(UserAction action)
 {
  action.dispatch(*this);
 }

void ItemListWindow::react_Key(VKey vkey,KeyMod kmod)
 {
  switch( vkey )
    {
     case VKey_F8 :
      {
       knob_del_pressed();
      }
     break;

     default: wlist.put_Key(vkey,kmod);
    }
 }

void ItemListWindow::react_Key(VKey vkey,KeyMod kmod,unsigned repeat)
 {
  switch( vkey )
    {
     case VKey_F8 :
      {
       knob_del_pressed();
      }
     break;

     default: wlist.put_Key(vkey,kmod,repeat);
    }
 }

void ItemListWindow::react_other(UserAction action)
 {
  wlist.react(action);
 }

} // namespace App


