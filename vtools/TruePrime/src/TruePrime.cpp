/* TruePrime.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: TruePrime 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/TruePrime.h>

#include <CCore/inc/Tuple.h>

#include <CCore/inc/video/LayoutCombo.h>

namespace App {

/* class NumberWindow */

NumberWindow::NumberWindow(SubWindowHost &host,const Config &cfg_)
 : SubWindow(host),
   cfg(cfg_)
 {
 }

NumberWindow::~NumberWindow()
 {
 }

 // methods

Point NumberWindow::getMinSize() const
 {
  return {200,40};
 }

void NumberWindow::setBin(const String &number_)
 {
  number=number_;

  max_span=8;
  max_line=8;

  layout();

  redraw();
 }

void NumberWindow::setDec(const String &number_)
 {
  number=number_;

  max_span=5;
  max_line=10;

  layout();

  redraw();
 }

void NumberWindow::setHex(const String &number_)
 {
  number=number_;

  max_span=4;
  max_line=16;

  layout();

  redraw();
 }

 // drawing

bool NumberWindow::isGoodSize(Point size) const
 {
  return size>=getMinSize();
 }

void NumberWindow::layout()
 {
 }

void NumberWindow::draw(DrawBuf buf,DrawParam draw_param) const
 {
  Used(draw_param);

  buf.erase(Black);
 }

 // keyboard

FocusType NumberWindow::askFocus() const
 {
  return NoFocus;
 }

/* class TruePrimeWindow */

void TruePrimeWindow::updateShow()
 {
  switch( group_base.getRadioId() )
    {
     case ShowBin : num_win.setBin(builder.getBin()); break;

     case ShowDec : num_win.setDec(builder.getDec()); break;

     case ShowHex : num_win.setHex(builder.getHex()); break;
    }
 }

void TruePrimeWindow::nbits_changed(int)
 {
  builder.setBits(getNBits());

  updateShow();
 }

void TruePrimeWindow::msbits_changed(int)
 {
  builder.setMSBits(getMSBits());

  updateShow();
 }

void TruePrimeWindow::lsbits_changed(int)
 {
  builder.setLSBits(getLSBits());

  updateShow();
 }

void TruePrimeWindow::gen_pressed()
 {
  builder.gen();

  updateShow();
 }

void TruePrimeWindow::base_changed(int,int)
 {
  updateShow();
 }

void TruePrimeWindow::wakeup() // TODO
 {
 }

TruePrimeWindow::TruePrimeWindow(SubWindowHost &host,const Config &cfg_)
 : ComboWindow(host),
   cfg(cfg_),

   builder(InterruptFunction(host.getFrameDesktop())),

   lab_nbits(wlist,cfg.lab_cfg,"Number of bits"_str,AlignX_Left),
   spinor_nbits(wlist,cfg.spinor_cfg),

   lab_msbits(wlist,cfg.lab_cfg,"Number of guard MSBits"_str,AlignX_Left),
   spinor_msbits(wlist,cfg.spinor_cfg),

   lab_lsbits(wlist,cfg.lab_cfg,"Number of guard LSBits"_str,AlignX_Left),
   spinor_lsbits(wlist,cfg.spinor_cfg),

   btn_gen(wlist,cfg.btn_cfg,"Gen"_str),
   run_test(wlist,cfg.run_cfg,"Run"_str,"Cancel"_str),

   line1(wlist,cfg.dline_cfg),

   lab_bin(wlist,cfg.lab_cfg,"bin"_str),
   lab_dec(wlist,cfg.lab_cfg,"dec"_str),
   lab_hex(wlist,cfg.lab_cfg,"hex"_str),

   rad_bin(wlist,ShowBin,cfg.rad_cfg),
   rad_dec(wlist,ShowDec,cfg.rad_cfg),
   rad_hex(wlist,ShowHex,cfg.rad_cfg),

   num_win(wlist,cfg.num_cfg),

   connector_nbits_changed(this,&TruePrimeWindow::nbits_changed,spinor_nbits.changed),
   connector_msbits_changed(this,&TruePrimeWindow::msbits_changed,spinor_msbits.changed),
   connector_lsbits_changed(this,&TruePrimeWindow::lsbits_changed,spinor_lsbits.changed),

   connector_gen_pressed(this,&TruePrimeWindow::gen_pressed,btn_gen.pressed),

   connector_base_changed(this,&TruePrimeWindow::base_changed,group_base.changed),

   connector_wakeup(this,&TruePrimeWindow::wakeup,host.getFrameDesktop()->wakeup)
 {
  wlist.insTop(lab_nbits,spinor_nbits,lab_msbits,spinor_msbits,lab_lsbits,spinor_lsbits,btn_gen,run_test,
               line1,lab_bin,rad_bin,lab_dec,rad_dec,lab_hex,rad_hex,num_win);

  group_base.add(rad_bin,rad_dec,rad_hex);

  spinor_nbits.setRange(MinNBits,MaxNBits);
  spinor_msbits.setRange(MinGuardBits,MaxGuardBits);
  spinor_lsbits.setRange(MinGuardBits,MaxGuardBits);

  spinor_nbits.setValue(512);
  spinor_msbits.setValue(32);
  spinor_lsbits.setValue(32);
 }

TruePrimeWindow::~TruePrimeWindow()
 {
 }

 // methods

Point TruePrimeWindow::getMinSize() const
 {
  Coord space=+cfg.space_dxy;

  LayMax laymax{lab_nbits,lab_msbits,lab_lsbits};

  LayToRightCenter lay1{laymax.get<1>(),LayLeft(spinor_nbits)};
  LayToRightCenter lay2{laymax.get<2>(),LayLeft(spinor_msbits)};
  LayToRightCenter lay3{laymax.get<3>(),LayLeft(spinor_lsbits)};
  LayToRightCenter lay4{Lay(btn_gen),LayLeft(run_test)};
  LayToRightCenter lay5{Lay(lab_bin),Lay(rad_bin),
                        Lay(lab_dec),Lay(rad_dec),
                        Lay(lab_hex),LayLeft(rad_hex)};

  LayToBottom lay{lay1,lay2,lay3,lay4,Lay(line1),lay5,Lay(num_win)};

  return ExtLay(lay).getMinSize(space);
 }

 // base

void TruePrimeWindow::open()
 {
  ComboWindow::open();

  builder.setBits(getNBits(),getMSBits(),getLSBits());

  updateShow();
 }

 // drawing

void TruePrimeWindow::layout()
 {
  Coord space=+cfg.space_dxy;

  LayMax laymax{lab_nbits,lab_msbits,lab_lsbits};

  LayToRightCenter lay1{laymax.get<1>(),LayLeft(spinor_nbits)};
  LayToRightCenter lay2{laymax.get<2>(),LayLeft(spinor_msbits)};
  LayToRightCenter lay3{laymax.get<3>(),LayLeft(spinor_lsbits)};
  LayToRightCenter lay4{Lay(btn_gen),LayLeft(run_test)};
  LayToRightCenter lay5{Lay(lab_bin),Lay(rad_bin),
                        Lay(lab_dec),Lay(rad_dec),
                        Lay(lab_hex),LayLeft(rad_hex)};

  LayToBottom lay{lay1,lay2,lay3,lay4,Lay(line1),lay5,Lay(num_win)};

  ExtLay(lay).setPlace(getPane(),space);
 }

void TruePrimeWindow::drawBack(DrawBuf buf,DrawParam &draw_param) const
 {
  draw_param.erase(buf,+cfg.back);
 }

} // namespace App

