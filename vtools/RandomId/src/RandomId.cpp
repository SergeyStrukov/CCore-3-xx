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

#include <CCore/inc/video/Layout.h>

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

Point RandomIdWindow::getMinSize() const
 {
  Coordinate space_dxy=+cfg.space_dxy;

  Coordinate line_dy=SupDY(radio_Unid,label_Unid);

  Coordinate dx=radio_Unid.getMinSize().dxy;

  Point inner_size(BoxExt(dx)+SupDX(label_Unid,label_Raw)+2*space_dxy,line_dy*2+3*space_dxy);

  Point s1=contour.getMinSize(inner_size);

  Point s2=btn_Roll.getMinSize();
  Point s3=btn_Copy.getMinSize();
  Point s4=text.getMinSize();

  return Point( 3*space_dxy+s1.x+Max_cast( space_dxy+s2.x+s3.x , s4.x ) , 2*space_dxy+Max_cast( space_dxy+s2.y+s4.y , s1.y ) );
 }

 // drawing

void RandomIdWindow::layout(unsigned flags)
 {
  Coord space_dxy=+cfg.space_dxy;

  PaneCut pane(getSize(),space_dxy,flags);

  pane.shrink();

  // contour

  Coord line_dy=SupDY(radio_Unid,label_Unid);

  {
   Coord dx=radio_Unid.getMinSize().dxy;

   Point inner_size(BoxExt(dx)+SupDX(label_Unid,label_Raw)+2*space_dxy,line_dy*2+3*space_dxy);

   Point size=contour.getMinSize(inner_size);

   pane.place_cutLeftTop(contour,size);
  }

  // radio_Unid , radio_Raw , label_Unid , label_Raw

  {
   PaneCut pane(contour.getInner(),space_dxy,flags);

   pane.shrink();

   pane.cutTop(line_dy).place_cutLeft(radio_Unid).place_cutLeftCenter(label_Unid);

   pane.cutTop(line_dy).place_cutLeft(radio_Raw).place_cutLeftCenter(label_Raw);
  }

  // btn_Roll , btn_Copy

  {
   Coord dy=btn_Roll.getMinSize().y;

   pane.cutTop(dy).place_cutLeft(btn_Roll).place_cutLeft(btn_Copy);
  }

  // text

  {
   pane.place_cutTop(text);
  }
 }

void RandomIdWindow::drawBack(DrawBuf buf,bool) const
 {
  buf.erase(+cfg.back);
 }

} // namespace App

