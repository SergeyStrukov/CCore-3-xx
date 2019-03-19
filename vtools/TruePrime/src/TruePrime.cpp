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

/* class TruePrimeWindow */

void TruePrimeWindow::updateShow() // TODO
 {
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

   blank(wlist,Black),

   connector_nbits_changed(this,&TruePrimeWindow::nbits_changed,spinor_nbits.changed),
   connector_msbits_changed(this,&TruePrimeWindow::msbits_changed,spinor_msbits.changed),
   connector_lsbits_changed(this,&TruePrimeWindow::lsbits_changed,spinor_lsbits.changed),

   connector_gen_pressed(this,&TruePrimeWindow::gen_pressed,btn_gen.pressed),

   connector_wakeup(this,&TruePrimeWindow::wakeup,host.getFrameDesktop()->wakeup)
 {
  wlist.insTop(lab_nbits,spinor_nbits,lab_msbits,spinor_msbits,lab_lsbits,spinor_lsbits,btn_gen,run_test,blank);

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

template <class ... WW>
class TruePrimeWindow::LayMax
 {
   Tuple<WW & ...> list;
   Point size;

  public:

   explicit LayMax(WW & ... ww)
    : list(ww...)
    {
     size=Sup( ww.getMinSize() ... );
    }

   template <class W>
   class Item
    {
      W &obj;
      Point size;

     public:

      Item(W &obj_,Point size_) : obj(obj_),size(size_) {}

      Point getMinSize(Coord) const { return size; }

      void setPlace(Pane pane,Coord) const { obj.setPlace(pane); }
    };

   template <int Ind>
   auto get()
    {
     return Item(list.template ref<Ind>(),size);
    }
 };

Point TruePrimeWindow::getMinSize() const
 {
  Coord space=+cfg.space_dxy;

  LayMax laymax{lab_nbits,lab_msbits,lab_lsbits};

  LayToRightCenter lay1{laymax.get<1>(),LayLeft(spinor_nbits)};
  LayToRightCenter lay2{laymax.get<2>(),LayLeft(spinor_msbits)};
  LayToRightCenter lay3{laymax.get<3>(),LayLeft(spinor_lsbits)};
  LayToRightCenter lay4{Lay(btn_gen),LayLeft(run_test)};

  LayToBottom lay{lay1,lay2,lay3,lay4,Lay(blank)};

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

  LayToBottom lay{lay1,lay2,lay3,lay4,Lay(blank)};

  ExtLay(lay).setPlace(getPane(),space);
 }

void TruePrimeWindow::drawBack(DrawBuf buf,DrawParam &draw_param) const
 {
  draw_param.erase(buf,+cfg.back);
 }

} // namespace App

