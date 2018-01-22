/* RandomId.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: RandomId 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/CharProp.h>

#include <CCore/inc/video/LayoutCombo.h>

#include <inc/RandomId.h>

namespace App {

/* class RandomIdWindow */

void RandomIdWindow::type_changed(int,int)
 {
  roll();
 }

void RandomIdWindow::rollUnid()
 {
  uint32 temp[8];

  random.fill(Range(temp));

  text.printf("{{#10.xi;,#10.xi;,#10.xi;,#10.xi;,#10.xi;,#10.xi;,#10.xi;,#10.xi;}}",temp[0],temp[1],temp[2],temp[3],temp[4],temp[5],temp[6],temp[7]);
 }

void RandomIdWindow::rollRaw()
 {
  char temp[64];

  const char *Hex="0123456789ABCDEF";

  for(char &t : temp ) t=Hex[ random.next()&15u ];

  text.setText(String(Range(temp)));
 }

void RandomIdWindow::roll()
 {
  switch( group_type.getRadioId() )
    {
     case Radio_Unid : rollUnid(); break;

     case Radio_Raw : rollRaw(); break;
    }
 }

void RandomIdWindow::copy()
 {
  getFrameHost()->textToClipboard(text.getText().str());
 }

RandomIdWindow::RandomIdWindow(SubWindowHost &host,const Config &cfg_)
 : ComboWindow(host),
   cfg(cfg_),

   radio_Unid(wlist,Radio_Unid,cfg.radio_cfg),
   radio_Raw(wlist,Radio_Raw,cfg.radio_cfg),

   label_Unid(wlist,cfg.label_cfg,cfg.text_Unid),
   label_Raw(wlist,cfg.label_cfg,cfg.text_Raw),

   contour(wlist,cfg.contour_cfg),

   btn_Roll(wlist,cfg.btn_cfg,cfg.text_Roll),
   btn_Copy(wlist,cfg.btn_cfg,cfg.text_Copy),

   text(wlist,cfg.text_cfg),

   connector_type_changed(this,&RandomIdWindow::type_changed,group_type.changed),
   connector_btn_Roll_pressed(this,&RandomIdWindow::roll,btn_Roll.pressed),
   connector_btn_Copy_pressed(this,&RandomIdWindow::copy,btn_Copy.pressed)
 {
  wlist.insTop(radio_Unid,radio_Raw,label_Unid,label_Raw,contour,btn_Roll,btn_Copy,text);

  group_type.add(radio_Unid,radio_Raw);
 }

RandomIdWindow::~RandomIdWindow()
 {
 }

 // methods

Point RandomIdWindow::getMinSize(unsigned flags) const
 {
  Coord space=+cfg.space_dxy;

  // radio_Unid , radio_Raw , label_Unid , label_Raw

  LayToBottomLeft lay1(BoxedWindow(radio_Unid,label_Unid),BoxedWindow(radio_Raw,label_Raw));

  // contour

  LayInner lay2(contour,lay1);

  // btn_Roll , btn_Copy , text

  StrLen sample="{{0x6D0A4149,0x3A24E175,0x3ACA61C3,0x584F5410,0x06470018,0xAE5EB153,0x6EB7FE0F,0x62C3FEE9}}"_c;

  LayToBottom lay3{LayToRight(Lay(btn_Roll),LayLeft(btn_Copy)),LaySpecial(text,sample)};

  // lay

  LayToRightTop lay(lay2,lay3);

  return ExtLay(lay).getMinSize(flags,space);
 }

 // drawing

void RandomIdWindow::layout(unsigned flags)
 {
  Coord space=+cfg.space_dxy;

  // radio_Unid , radio_Raw , label_Unid , label_Raw

  LayToBottomLeft lay1(BoxedWindow(radio_Unid,label_Unid),BoxedWindow(radio_Raw,label_Raw));

  // contour

  LayInner lay2(contour,lay1);

  // btn_Roll , btn_Copy , text

  LayToBottom lay3{LayToRight(Lay(btn_Roll),LayLeft(btn_Copy)),Lay(text)};

  // lay

  LayToRightTop lay(lay2,lay3);

  ExtLay(lay).setPlace(getPane(),flags,space);
 }

void RandomIdWindow::drawBack(DrawBuf buf,bool) const
 {
  buf.erase(+cfg.back);
 }

} // namespace App

