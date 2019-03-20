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
#include <CCore/inc/ForLoop.h>

#include <CCore/inc/video/LayoutCombo.h>

#include <CCore/inc/video/FigureLib.h>

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
  const Font &font=cfg.font.get();

  Coord dx=font->text("12345678 "_c).full_dx;

  Coord dy=font->getSize().dy;

  Point space=+cfg.space;

  return 2*space+Point(8*dx,9*dy);
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

class NumberWindow::Cursor
 {
   const char *ptr;
   unsigned span;
   ulen count;
   ulen rest;

  public:

   Cursor(StrLen text,unsigned span_)
    : span(span_)
    {
     ptr=text.ptr;
     count=text.len/span;
     rest=text.len%span;
    }

   ulen operator + () const { return count|rest; }

   StrLen operator * () const
    {
     if( rest ) return StrLen(ptr,rest);

     return StrLen(ptr,span);
    }

   void operator ++ ()
    {
     if( rest )
       {
        ptr+=rest;

        rest=0;
       }
     else
       {
        ptr+=span;

        count--;
       }
    }
 };

void NumberWindow::layout()
 {
  const Font &font=cfg.font.get();

  delta.x=0;

  for(StrLen str : ForLoop(Cursor(Range(number),max_span)) )
    {
     Coord dx=font->text(str," "_c).full_dx;

     Replace_max(delta.x,dx);
    }

  FontSize fs=font->getSize();

  delta.y=fs.dy;

  Point space=+cfg.space;

  base=space+Point(fs.dx0,fs.by);

  Coord dx=getSize().x-2*space.x;

  if( dx<delta.x )
    line=1;
  else
    line=Cap<unsigned>(1,dx/delta.x,max_line);
 }

void NumberWindow::draw(DrawBuf buf,DrawParam draw_param) const
 {
  draw_param.erase(buf,+cfg.back);

  MPane p(getPane());

  if( !p ) return;

  SmoothDrawArt art(buf);

  MCoord width=+cfg.width;

  // decor

  {
   FigureTopBorder fig1(p,width);

   FigureBottomBorder fig2(p,width);

   fig1.solid(art,+cfg.gray);

   fig2.solid(art,+cfg.snow);
  }

  // number

  if( number.isEmpty() ) return;

  {
   Pane pane=getPane();

   DrawBuf tbuf=buf.cut(pane.shrink(RoundUpLen(width)));

   const Font &font=cfg.font.get();

   VColor text=+cfg.text;

   auto printSpan = [&] (Point pos,StrLen str)
                        {
                         Coord dx=font->text(str," "_c).full_dx;

                         pos.x+=delta.x-dx;

                         font->text(tbuf,pane,pos,str,text);

                        } ;

   Point pos=base;

   unsigned i=0;

   for(StrLen str : ForLoop(Cursor(Range(number),max_span)) )
     {
      printSpan(pos,str);

      i++;

      if( i<line )
        {
         pos.x+=delta.x;
        }
      else
        {
         i=0;

         pos.x=base.x;
         pos.y+=delta.y;
        }
     }
  }
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

void TruePrimeWindow::showStatus(BuilderState state,String text)
 {
  if( state==BuilderDoneReject )
    {
     restart=true;
    }

  info.setInfo(InfoFromString(text));
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

void TruePrimeWindow::test_changed(bool on)
 {
  btn_gen.enable(!on);

  if( on )
    {
     restart=false;

     builder.runTest();

     light.turnOn();
    }
  else
    {
     builder.cancelTest();
    }
 }

void TruePrimeWindow::wakeup()
 {
  auto status=builder.getStatus();

  if( status.ok )
    {
     showStatus(status.state,status.text);
    }

  light.turn(status.running);

  if( run_test.isOn() && !status.running )
    {
     if( Change(restart,false) )
       {
        builder.gen();

        updateShow();

        builder.runTest();

        light.turnOn();
       }
     else
       {
        run_test.turn(false);

        btn_gen.enable();
       }
    }
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

   light(wlist,cfg.light_cfg,Red),

   line1(wlist,cfg.dline_cfg),

   lab_bin(wlist,cfg.lab_cfg,"bin"_str),
   lab_dec(wlist,cfg.lab_cfg,"dec"_str),
   lab_hex(wlist,cfg.lab_cfg,"hex"_str),

   rad_bin(wlist,ShowBin,cfg.rad_cfg),
   rad_dec(wlist,ShowDec,cfg.rad_cfg),
   rad_hex(wlist,ShowHex,cfg.rad_cfg),

   num_win(wlist,cfg.num_cfg),
   info(wlist,cfg.info_cfg),

   connector_nbits_changed(this,&TruePrimeWindow::nbits_changed,spinor_nbits.changed),
   connector_msbits_changed(this,&TruePrimeWindow::msbits_changed,spinor_msbits.changed),
   connector_lsbits_changed(this,&TruePrimeWindow::lsbits_changed,spinor_lsbits.changed),

   connector_gen_pressed(this,&TruePrimeWindow::gen_pressed,btn_gen.pressed),

   connector_base_changed(this,&TruePrimeWindow::base_changed,group_base.changed),

   connector_test_changed(this,&TruePrimeWindow::test_changed,run_test.changed),

   connector_wakeup(this,&TruePrimeWindow::wakeup,host.getFrameDesktop()->wakeup)
 {
  wlist.insTop(lab_nbits,spinor_nbits,lab_msbits,spinor_msbits,lab_lsbits,spinor_lsbits,btn_gen,run_test,light,
               line1,rad_bin,lab_bin,rad_dec,lab_dec,rad_hex,lab_hex,num_win,info);

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
  LayToRightCenter lay4{Lay(btn_gen),Lay(run_test),LayLeft(light)};
  LayToRightCenter lay5{LayBox(rad_bin),Lay(lab_bin),
                        LayBox(rad_dec),Lay(lab_dec),
                        LayBox(rad_hex),LayLeft(lab_hex)};

  LayToTop lay6{LaySpecial(info,5),Lay(num_win)};

  LayToBottom lay{lay1,lay2,lay3,lay4,Lay(line1),lay5,lay6};

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
  LayToRightCenter lay4{Lay(btn_gen),Lay(run_test),LayLeft(light)};
  LayToRightCenter lay5{LayBox(rad_bin),Lay(lab_bin),
                        LayBox(rad_dec),Lay(lab_dec),
                        LayBox(rad_hex),LayLeft(lab_hex)};

  LayToTop lay6{LaySpecial(info,5),Lay(num_win)};

  LayToBottom lay{lay1,lay2,lay3,lay4,Lay(line1),lay5,lay6};

  ExtLay(lay).setPlace(getPane(),space);
 }

void TruePrimeWindow::drawBack(DrawBuf buf,DrawParam &draw_param) const
 {
  draw_param.erase(buf,+cfg.back);
 }

} // namespace App

