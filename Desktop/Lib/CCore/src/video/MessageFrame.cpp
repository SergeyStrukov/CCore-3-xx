/* MessageFrame.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: Desktop
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/video/MessageFrame.h>

#include <CCore/inc/video/Layout.h>

#include <CCore/inc/Exception.h>

namespace CCore {
namespace Video {

/* class MessageWindow::Btn */

void MessageWindow::Btn::assertOwner()
 {
  owner->pressed.assert(btn_id);
 }

MessageWindow::Btn::Btn(SubWindowHost &host,const ButtonWindow::ConfigType &cfg,const DefString &name,int btn_id_,MessageWindow *owner_)
 : ButtonWindow(host,cfg,name),
   btn_id(btn_id_),
   owner(owner_),
   connector_pressed(this,&Btn::assertOwner,pressed)
 {
 }

MessageWindow::Btn::~Btn()
 {
 }

/* class MessageWindow */

void MessageWindow::knob_pressed()
 {
  pressed.assert(Button_Ok);
 }

MessageWindow::MessageWindow(SubWindowHost &host,const Config &cfg_)
 : ComboWindow(host),
   cfg(cfg_),
   btn_cfg(cfg.btn_cfg),

   info(wlist,cfg.info_cfg),
   dline(wlist,cfg.dline_cfg),
   knob(wlist,cfg.knob_cfg,KnobShape::FaceOk),

   connector_knob_pressed(this,&MessageWindow::knob_pressed,knob.pressed)
 {
 }

MessageWindow::~MessageWindow()
 {
 }

 // methods

Point MessageWindow::getMinSize(Point cap) const
 {
  Coordinate space_dxy=+cfg.space_dxy;

  Coordinate space2=2*space_dxy;

  Coordinate line_dy=dline.getMinSize().dy;

  Point btn;

  if( ulen count_=btn_list.getLen() )
    {
     auto list=Range(btn_list.getPtr(),count_);

     Point bs=BtnSize(list);

     auto count=CountToCoordinate(count_);

     auto total=count*bs.x+(count-1)*space_dxy;

     btn.x=+total;
     btn.y=bs.y;
    }
  else
    {
     btn=Point::Diag(+cfg.knob_dxy);
    }

  Point bottom=btn.addXY(+space2);

  Point delta(0,bottom.y+line_dy);

  Point top=info.getMinSize(cap-delta).addXY(+space2);

  return Point( Max(bottom.x,top.x) , delta.y+top.y );
 }

void MessageWindow::erase()
 {
  btn_list.erase();

  btn_count=0;

  setInfo(Info());
 }

MessageWindow & MessageWindow::setInfo(const Info &info_)
 {
  info.setInfo(info_);

  return *this;
 }

MessageWindow & MessageWindow::add(const DefString &name,int btn_id)
 {
  btn_list.append_fill(OwnPtr<Btn>( new Btn(wlist,btn_cfg,name,btn_id,this) ));

  return *this;
 }

 // drawing

void MessageWindow::layout()
 {
  Coord space_dxy=+cfg.space_dxy;

  PaneCut pane(getSize(),0);

  pane.cutBottom(space_dxy);

  if( ulen count=btn_count )
    {
     auto list=Range(btn_list.getPtr(),count);

     Point bs=BtnSize(list);

     PlaceRow row(pane.cutBottom(bs.y),bs,space_dxy,count);

     for(OwnPtr<Btn> &obj : list )
       {
        obj->setPlace(*row);

        ++row;
       }
    }
  else
    {
     Coord knob_dxy=+cfg.knob_dxy;

     knob.setPlace( pane.cutBottomCenter(knob_dxy,knob_dxy) );
    }

  pane.cutBottom(space_dxy);

  Pane top=pane.place_cutBottom(dline);

  info.setPlace( top.shrink(space_dxy) );
 }

void MessageWindow::drawBack(DrawBuf buf,bool) const
 {
  buf.erase(+cfg.back);
 }

 // base

void MessageWindow::open()
 {
  wlist.delAll();

  btn_count=btn_list.getLen();

  if( btn_count )
    {
     btn_list.apply( [this] (OwnPtr<Btn> &obj) { wlist.insBottom(obj.getPtr()); } );

     wlist.insBottom(info);
    }
  else
    {
     wlist.insTop(knob,info);
    }

  wlist.insBottom(dline);

  wlist.open();

  wlist.focusTop();
 }

/* class MessageFrame */

void MessageFrame::pressed(int btn_id_)
 {
  btn_id=btn_id_;

  destroy();
 }

MessageFrame::MessageFrame(Desktop *desktop,const Config &cfg_)
 : FixedFrame(desktop,cfg_.frame_cfg),
   cfg(cfg_),

   sub_win(*this,cfg.msg_cfg),

   connector_pressed(this,&MessageFrame::pressed,sub_win.pressed)
 {
  bindClient(sub_win);
 }

MessageFrame::MessageFrame(Desktop *desktop,const Config &cfg,Signal<> &update)
 : MessageFrame(desktop,cfg)
 {
  connectUpdate(update);
 }

MessageFrame::~MessageFrame()
 {
 }

void MessageFrame::alive()
 {
  FixedFrame::alive();

  btn_id=Button_Cancel;
 }

Pane MessageFrame::getPane(bool is_main,StrLen title) const
 {
  Point screen_size=getScreenSize();

  Point cap=Div(9,10)*screen_size-getDeltaSize();

  Point size=getMinSize(is_main,title,sub_win.getMinSize(cap));

  return GetWindowPlace(desktop,+cfg.pos_ry,size);
 }

 // methods

void MessageFrame::erase()
 {
  if( isAlive() )
    {
     Printf(Exception,"CCore::Video::MessageFrame::erase() : is alive");
    }

  sub_win.erase();
 }

} // namespace Video
} // namespace CCore


