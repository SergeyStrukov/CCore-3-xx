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
  data.place = BookLab::InsPlace(group_place.getRadioId()) ;

  data.type = BookLab::ElementType(group_type.getRadioId()) ;

  data.text=edit_text.getString();

  askFrameClose();
 }

void InsWindow::closeCancel()
 {
  askFrameClose();
 }

void InsWindow::checkName()
 {
  bool ok;

  int id=group_type.getRadioId();

  if( id==BookLab::ElementSection || id==BookLab::ElementInclude )
    {
     ok=true;
    }
  else
    {
     ok=BookLab::TestName(edit_text.getText());
    }

  edit_text.alert(!ok);

  btn_Ok.enable(ok);
 }

void InsWindow::typeChanged(int new_id,int)
 {
  checkName();

  if( new_id==BookLab::ElementSection )
    lab_text.setText("Comment"_str);
  else
    lab_text.setText("Name"_str);
 }

InsWindow::InsWindow(SubWindowHost &host,const Config &cfg_)
 : ComboWindow(host),
   cfg(cfg_),

   lab_before(wlist,cfg.lab_cfg,"before"_str,AlignX_Left),
   rad_before(wlist,BookLab::InsBefore,cfg.rad_cfg),
   lab_after(wlist,cfg.lab_cfg,"after"_str,AlignX_Left),
   rad_after(wlist,BookLab::InsAfter,cfg.rad_cfg),
   lab_inside(wlist,cfg.lab_cfg,"inside"_str,AlignX_Left),
   rad_inside(wlist,BookLab::InsInside,cfg.rad_cfg),

   lab_text(wlist,cfg.lab_cfg,"Name/Comment"_str,AlignX_Left),
   edit_text(wlist,cfg.edit_cfg),

   lab1(wlist,cfg.lab_cfg,"Font"_str,AlignX_Left),
   rad1(wlist,BookLab::ElementFont,cfg.rad_cfg),

   lab2(wlist,cfg.lab_cfg,"Format"_str,AlignX_Left),
   rad2(wlist,BookLab::ElementFormat,cfg.rad_cfg),

   lab3(wlist,cfg.lab_cfg,"SingleLine"_str,AlignX_Left),
   rad3(wlist,BookLab::ElementSingleLine,cfg.rad_cfg),

   lab4(wlist,cfg.lab_cfg,"DoubleLine"_str,AlignX_Left),
   rad4(wlist,BookLab::ElementDoubleLine,cfg.rad_cfg),

   lab5(wlist,cfg.lab_cfg,"Page"_str,AlignX_Left),
   rad5(wlist,BookLab::ElementPage,cfg.rad_cfg),

   lab6(wlist,cfg.lab_cfg,"Scope"_str,AlignX_Left),
   rad6(wlist,BookLab::ElementScope,cfg.rad_cfg),

   lab7(wlist,cfg.lab_cfg,"Section"_str,AlignX_Left),
   rad7(wlist,BookLab::ElementSection,cfg.rad_cfg),

   lab8(wlist,cfg.lab_cfg,"Bitmap"_str,AlignX_Left),
   rad8(wlist,BookLab::ElementBitmap,cfg.rad_cfg),

   lab9(wlist,cfg.lab_cfg,"Collapse"_str,AlignX_Left),
   rad9(wlist,BookLab::ElementCollapse,cfg.rad_cfg),

   lab10(wlist,cfg.lab_cfg,"TextList"_str,AlignX_Left),
   rad10(wlist,BookLab::ElementTextList,cfg.rad_cfg),

   lab11(wlist,cfg.lab_cfg,"Border"_str,AlignX_Left),
   rad11(wlist,BookLab::ElementBorder,cfg.rad_cfg),

   lab12(wlist,cfg.lab_cfg,"Cell"_str,AlignX_Left),
   rad12(wlist,BookLab::ElementCell,cfg.rad_cfg),

   lab13(wlist,cfg.lab_cfg,"Table"_str,AlignX_Left),
   rad13(wlist,BookLab::ElementTable,cfg.rad_cfg),

   lab14(wlist,cfg.lab_cfg,"Link"_str,AlignX_Left),
   rad14(wlist,BookLab::ElementLink,cfg.rad_cfg),

   lab15(wlist,cfg.lab_cfg,"FixedText"_str,AlignX_Left),
   rad15(wlist,BookLab::ElementFixedText,cfg.rad_cfg),

   lab16(wlist,cfg.lab_cfg,"OneLine"_str,AlignX_Left),
   rad16(wlist,BookLab::ElementOneLine,cfg.rad_cfg),

   lab17(wlist,cfg.lab_cfg,"MultiLine"_str,AlignX_Left),
   rad17(wlist,BookLab::ElementMultiLine,cfg.rad_cfg),

   lab18(wlist,cfg.lab_cfg,"Text"_str,AlignX_Left),
   rad18(wlist,BookLab::ElementText,cfg.rad_cfg),

   lab19(wlist,cfg.lab_cfg,"Include"_str,AlignX_Left),
   rad19(wlist,BookLab::ElementInclude,cfg.rad_cfg),

   line1(wlist,cfg.dline_cfg),

   btn_Ok(wlist,cfg.btn_cfg,cfg.text_Ok),
   btn_Cancel(wlist,cfg.btn_cfg,cfg.text_Cancel),

   connector_Ok_pressed(this,&InsWindow::closeOk,btn_Ok.pressed),
   connector_Cancel_pressed(this,&InsWindow::closeCancel,btn_Cancel.pressed),
   connector_text_changed(this,&InsWindow::checkName,edit_text.changed),
   connector_type_changed(this,&InsWindow::typeChanged,group_type.changed)
 {
  wlist.insTop(edit_text,lab_text,
               lab_before,rad_before,lab_after,rad_after,lab_inside,rad_inside,
               lab1,rad1,
               lab2,rad2,
               lab3,rad3,
               lab4,rad4,
               lab5,rad5,
               lab6,rad6,
               lab7,rad7,
               lab8,rad8,
               lab9,rad9,
               lab10,rad10,
               lab11,rad11,
               lab12,rad12,
               lab13,rad13,
               lab14,rad14,
               lab15,rad15,
               lab16,rad16,
               lab17,rad17,
               lab18,rad18,
               lab19,rad19,
               line1,btn_Ok,btn_Cancel);

  group_place.add(rad_after,rad_before,rad_inside);

  group_type.add(rad1,rad2,rad3,rad4,rad5,rad6,rad7,rad8,rad9,rad10,rad11,rad12,rad13,rad14,rad15,rad16,rad17,rad18,rad19);
 }

InsWindow::~InsWindow()
 {
 }

 // methods

Point InsWindow::getMinSize() const
 {
  Coord space=+cfg.space_dxy;

  LayToRightCenter lay0{LayBox(rad_before),Lay(lab_before),LayBox(rad_after),Lay(lab_after),LayBox(rad_inside),LayLeft(lab_inside)};

  LayToRightCenter lay_edit{LaySpecial(lab_text,"Name/Comment"_c),Lay(edit_text)};

  LayToRightCenter lay1{LayBox(rad1),LayLeft(lab1)};
  LayToRightCenter lay2{LayBox(rad2),LayLeft(lab2)};
  LayToRightCenter lay3{LayBox(rad3),LayLeft(lab3)};
  LayToRightCenter lay4{LayBox(rad4),LayLeft(lab4)};
  LayToRightCenter lay5{LayBox(rad5),LayLeft(lab5)};
  LayToRightCenter lay6{LayBox(rad6),LayLeft(lab6)};
  LayToRightCenter lay7{LayBox(rad7),LayLeft(lab7)};
  LayToRightCenter lay8{LayBox(rad8),LayLeft(lab8)};
  LayToRightCenter lay9{LayBox(rad9),LayLeft(lab9)};
  LayToRightCenter lay10{LayBox(rad10),LayLeft(lab10)};
  LayToRightCenter lay11{LayBox(rad11),LayLeft(lab11)};
  LayToRightCenter lay12{LayBox(rad12),LayLeft(lab12)};
  LayToRightCenter lay13{LayBox(rad13),LayLeft(lab13)};
  LayToRightCenter lay14{LayBox(rad14),LayLeft(lab14)};
  LayToRightCenter lay15{LayBox(rad15),LayLeft(lab15)};
  LayToRightCenter lay16{LayBox(rad16),LayLeft(lab16)};
  LayToRightCenter lay17{LayBox(rad17),LayLeft(lab17)};
  LayToRightCenter lay18{LayBox(rad18),LayLeft(lab18)};
  LayToRightCenter lay19{LayBox(rad19),LayLeft(lab19)};

  LayToBottom col1{lay1,lay2,lay3,lay4,lay5,lay6,lay7,lay8,lay9,LayAlignTop(lay19)};
  LayToBottom col2{lay10,lay11,lay12,lay13,lay14,lay15,lay16,lay17,LayAlignTop(lay18)};

  LayToRight rad{col1,LayAlignLeft(col2)};

  LaySupCenterXExt lay_btn{Lay(btn_Ok),LayLeft(btn_Cancel)};

  LayToBottom lay{lay0,lay_edit,rad,LayToTop{lay_btn,LayBottom(line1)}};

  return ExtLay(lay).getMinSize(space);
 }

void InsWindow::enablePlace(bool all,bool inside)
 {
  if( all )
    {
     lab_before.enable();
     rad_before.enable();

     lab_after.enable();
     rad_after.enable();

     lab_inside.enable(inside);
     rad_inside.enable(inside);

     if( !inside && rad_inside.isChecked() )
       {
        rad_after.check();
       }
    }
  else
    {
     lab_before.disable();
     rad_before.disable();

     lab_after.disable();
     rad_after.disable();

     lab_inside.disable();
     rad_inside.disable();
    }
 }

 // base

void InsWindow::open()
 {
  ComboWindow::open();

  data={};

  typeChanged(group_type.getRadioId(),-1);
 }

 // drawing

void InsWindow::layout()
 {
  Coord space=+cfg.space_dxy;

  LayToRightCenter lay0{LayBox(rad_before),Lay(lab_before),LayBox(rad_after),Lay(lab_after),LayBox(rad_inside),LayLeft(lab_inside)};

  LayToRightCenter lay_edit{LaySpecial(lab_text,"Name/Comment"_c),Lay(edit_text)};

  LayToRightCenter lay1{LayBox(rad1),LayLeft(lab1)};
  LayToRightCenter lay2{LayBox(rad2),LayLeft(lab2)};
  LayToRightCenter lay3{LayBox(rad3),LayLeft(lab3)};
  LayToRightCenter lay4{LayBox(rad4),LayLeft(lab4)};
  LayToRightCenter lay5{LayBox(rad5),LayLeft(lab5)};
  LayToRightCenter lay6{LayBox(rad6),LayLeft(lab6)};
  LayToRightCenter lay7{LayBox(rad7),LayLeft(lab7)};
  LayToRightCenter lay8{LayBox(rad8),LayLeft(lab8)};
  LayToRightCenter lay9{LayBox(rad9),LayLeft(lab9)};
  LayToRightCenter lay10{LayBox(rad10),LayLeft(lab10)};
  LayToRightCenter lay11{LayBox(rad11),LayLeft(lab11)};
  LayToRightCenter lay12{LayBox(rad12),LayLeft(lab12)};
  LayToRightCenter lay13{LayBox(rad13),LayLeft(lab13)};
  LayToRightCenter lay14{LayBox(rad14),LayLeft(lab14)};
  LayToRightCenter lay15{LayBox(rad15),LayLeft(lab15)};
  LayToRightCenter lay16{LayBox(rad16),LayLeft(lab16)};
  LayToRightCenter lay17{LayBox(rad17),LayLeft(lab17)};
  LayToRightCenter lay18{LayBox(rad18),LayLeft(lab18)};
  LayToRightCenter lay19{LayBox(rad19),LayLeft(lab19)};

  LayToBottom col1{lay1,lay2,lay3,lay4,lay5,lay6,lay7,lay8,lay9,LayAlignTop(lay19)};
  LayToBottom col2{lay10,lay11,lay12,lay13,lay14,lay15,lay16,lay17,LayAlignTop(lay18)};

  LayToRight rad{col1,LayAlignLeft(col2)};

  LaySupCenterXExt lay_btn{Lay(btn_Ok),LayLeft(btn_Cancel)};

  LayToBottom lay{lay0,lay_edit,rad,LayToTop{lay_btn,LayBottom(line1)}};

  ExtLay(lay).setPlace(getPane(),space);
 }

void InsWindow::drawBack(DrawBuf buf,DrawParam &draw_param) const
 {
  draw_param.erase(buf,+cfg.back);
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


