/* MessageFrame.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
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

#include <CCore/inc/video/LayoutCombo.h>

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

struct MessageWindow::BtnRange : PtrLen<const OwnPtr<Btn> >
 {
  BtnRange(const OwnPtr<Btn> *ptr,ulen len) : PtrLen<const OwnPtr<Btn> >(ptr,len) {}

  ulen getLen() const { return len; }

  struct AdapterType
   {
    Btn *ptr;

    AdapterType(const OwnPtr<Btn> &r) : ptr(r.getPtr()) {}

    Point getMinSize(Coord) const
     {
      return ptr->getMinSize();
     }

    void setPlace(Pane pane,Coord) const
     {
      ptr->setPlace(pane);
     }
   };
 };

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
  Coord space=+cfg.space_dxy;

  if( ulen count=btn_list.getLen() )
    {
     auto lay=ExtLayY(LayToTop(LaySupCenterXExt(BtnRange(btn_list.getPtr(),count)),Lay(dline),LayExtXCap(info)));

     return lay.getMinSize(space,cap);
    }
  else
    {
     auto lay=ExtLayY(LayToTop(LayCenterXExt(knob),Lay(dline),LayExtXCap(info)));

     return lay.getMinSize(space,cap);
    }
 }

void MessageWindow::erase()
 {
  btn_list.erase();

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
  Coord space=+cfg.space_dxy;

  if( ulen count=btn_list.getLen() )
    {
     auto lay=ExtLayY(LayToTop(LaySupCenterXExt(BtnRange(btn_list.getPtr(),count)),Lay(dline),LayExtXCap(info)));

     lay.setPlace(getPane(),space);
    }
  else
    {
     auto lay=ExtLayY(LayToTop(LayCenterXExt(knob),Lay(dline),LayExtXCap(info)));

     lay.setPlace(getPane(),space);
    }
 }

void MessageWindow::drawBack(DrawBuf buf,bool) const
 {
  buf.erase(+cfg.back);
 }

 // base

void MessageWindow::open()
 {
  wlist.delAll();

  if( btn_list.getLen() )
    {
     btn_list.apply( [this] (OwnPtr<Btn> &obj) { wlist.insBottom(*obj); } );

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

   client(*this,cfg.msg_cfg),

   connector_pressed(this,&MessageFrame::pressed,client.pressed)
 {
  bindClient(client);
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

  Point size=getMinSize(is_main,title,client.getMinSize(cap));

  return GetWindowPlace(desktop,+cfg.pos_ry,size);
 }

 // methods

void MessageFrame::erase()
 {
  if( isAlive() )
    {
     Printf(Exception,"CCore::Video::MessageFrame::erase() : is alive");
    }

  client.erase();
 }

} // namespace Video
} // namespace CCore


