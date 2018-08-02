/* InsWindow.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: BookLab 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/InsWindow.h>

#include <CCore/inc/video/LayoutCombo.h>

namespace App {

/* class InsWindow */

void InsWindow::closeOk()
 {
  data.before = ( group_place.getRadioId() == 1 ) ;

  data.type = BookLab::ElementType(group_type.getRadioId()) ;

  data.text=edit_text.getString();

  askFrameClose();
 }

void InsWindow::closeCancel()
 {
  askFrameClose();
 }

InsWindow::InsWindow(SubWindowHost &host,const Config &cfg_)
 : ComboWindow(host),
   cfg(cfg_),

   lab_before(wlist,cfg.lab_cfg,"Before"_def,AlignX_Left),
   rad_before(wlist,1,cfg.rad_cfg),
   lab_after(wlist,cfg.lab_cfg,"After"_def,AlignX_Left),
   rad_after(wlist,2,cfg.rad_cfg),

   lab_text(wlist,cfg.lab_cfg,"Name/Comment"_def,AlignX_Left),
   edit_text(wlist,cfg.edit_cfg),

   lab1(wlist,cfg.lab_cfg,"Font"_def,AlignX_Left),
   rad1(wlist,BookLab::ElementFont,cfg.rad_cfg),

   lab2(wlist,cfg.lab_cfg,"Format"_def,AlignX_Left),
   rad2(wlist,BookLab::ElementFormat,cfg.rad_cfg),

   line1(wlist,cfg.dline_cfg),

   btn_Ok(wlist,cfg.btn_cfg,cfg.text_Ok),
   btn_Cancel(wlist,cfg.btn_cfg,cfg.text_Cancel),

   connector_Ok_pressed(this,&InsWindow::closeOk,btn_Ok.pressed),
   connector_Cancel_pressed(this,&InsWindow::closeCancel,btn_Cancel.pressed)
 {
  wlist.insTop(edit_text,lab_text,lab_before,rad_before,lab_after,rad_after,
               lab1,rad1,
               lab2,rad2,
               line1,btn_Ok,btn_Cancel);

  group_place.add(rad_after,rad_before);

  group_type.add(rad1,rad2);
 }

InsWindow::~InsWindow()
 {
 }

 // methods

Point InsWindow::getMinSize() const
 {
  Coord space=+cfg.space_dxy;

  LayToRightCenter lay0{LayBox(rad_before),Lay(lab_before),LayBox(rad_after),LayLeft(lab_after)};

  LayToRightCenter lay_edit{Lay(lab_text),Lay(edit_text)};

  LayToRightCenter lay1{LayBox(rad1),LayLeft(lab1)};
  LayToRightCenter lay2{LayBox(rad2),LayLeft(lab2)};

  LaySupCenterXExt lay_btn{Lay(btn_Ok),LayLeft(btn_Cancel)};

  LayToBottom lay{lay0,lay_edit,
                  lay1,lay2,
                  LayToTop{lay_btn,LayBottom(line1)}};

  return ExtLay(lay).getMinSize(space);
 }

 // base

void InsWindow::open()
 {
  ComboWindow::open();

  data={};
 }

 // drawing

void InsWindow::layout()
 {
  Coord space=+cfg.space_dxy;

  LayToRightCenter lay0{LayBox(rad_before),Lay(lab_before),LayBox(rad_after),LayLeft(lab_after)};

  LayToRightCenter lay_edit{Lay(lab_text),Lay(edit_text)};

  LayToRightCenter lay1{LayBox(rad1),LayLeft(lab1)};
  LayToRightCenter lay2{LayBox(rad2),LayLeft(lab2)};

  LaySupCenterXExt lay_btn{Lay(btn_Ok),LayLeft(btn_Cancel)};

  LayToBottom lay{lay0,lay_edit,
                  lay1,lay2,
                  LayToTop{lay_btn,LayBottom(line1)}};

  ExtLay(lay).setPlace(getPane(),space);
 }

void InsWindow::drawBack(DrawBuf buf,bool) const
 {
  buf.erase(+cfg.back);
 }

/* class InsFrame */

InsFrame::InsFrame(Desktop *desktop,const Config &cfg_,Signal<> &update)
 : DragFrame(desktop,cfg_.frame_cfg,update),
   cfg(cfg_),

   client(*this,cfg.client_cfg)
 {
  bindClient(client);
 }

InsFrame::~InsFrame()
 {
 }

 // base

void InsFrame::dying()
 {
  DragFrame::dying();

  place=host->getPlace();
  has_place=true;
 }

 // create

Pane InsFrame::getPane(StrLen title) const
 {
  Point size=getMinSize(false,title,client.getMinSize());

  if( has_place ) return Pane(place.getBase(),Sup(place.getSize(),size));

  return GetWindowPlace(desktop,+cfg.pos_ry,size);
 }

} // namespace App


