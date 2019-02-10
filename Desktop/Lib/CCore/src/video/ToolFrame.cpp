/* ToolFrame.cpp */
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

#include <CCore/inc/video/ToolFrame.h>

namespace CCore {
namespace Video {

/* class ToolFrame */

void ToolFrame::guardClient()
 {
  if( !client ) GuardNoClient();
 }

void ToolFrame::guardDead()
 {
  if( isAlive() ) GuardNotDead();
 }

void ToolFrame::reset()
 {
  size=Null;
  client_enter=false;
  client_capture=false;
  delay_draw=false;
  enable_react=true;

  redraw_set.pop();
 }

SubWindow & ToolFrame::getClient()
 {
  guardClient();

  return *client;
 }

void ToolFrame::shade(FrameBuf<DesktopColor> &buf)
 {
  if( !enable_react ) buf.erase(+cfg.shadeColor,+cfg.shadeAlpha);
 }

void ToolFrame::shade(FrameBuf<DesktopColor> &buf,Pane pane)
 {
  if( !enable_react ) buf.block_safe(pane,+cfg.shadeColor,+cfg.shadeAlpha);
 }

void ToolFrame::redrawBuf(FuncArgType<FrameBuf<DesktopColor> &> func)
 {
  if( host->isDead() ) return;

  if( host->getToken() )
    {
     delay_draw=true;

     return;
    }

  FrameBuf<DesktopColor> buf(host->getDrawPlane());

  if( size<=buf.getSize() )
    {
     func(buf);
    }
  else
    {
     buf.erase(Black);

     host->invalidate(1);
    }
 }

void ToolFrame::redrawAll(unsigned flags)
 {
  if( flags )
    {
     BitClear(flags,LayoutResize);

     if( flags ) updated.assert(flags);

     if( client ) client->setPlace(Pane(Null,size));
    }

  redraw_set.pop();

  redrawBuf( [this] (FrameBuf<DesktopColor> &buf)
                    {
                     getClient().forward_draw(buf,false);

                     shade(buf);

                     host->invalidate(1);

                    } );
 }

void ToolFrame::redrawSet()
 {
  auto r=redraw_set.pop();

  if( !r ) return;

  auto &client=getClient();

  redrawBuf( [this,r,&client] (FrameBuf<DesktopColor> &buf_)
                              {
                               DrawBuf buf(buf_);

                               for(Pane pane : r )
                                 {
                                  client.forward_draw(buf.cut(pane),pane,false);

                                  shade(buf_,pane);

                                  host->invalidate(pane,1);
                                 }

                              } );
 }

ToolFrame::ToolFrame(Desktop *desktop,const Config &cfg_)
 : FrameWindow(desktop),
   cfg(cfg_),
   input(this),

   connector_update(this,&ToolFrame::update)
 {
 }

ToolFrame::ToolFrame(Desktop *desktop,const Config &cfg,Signal<> &update)
 : ToolFrame(desktop,cfg)
 {
  connector_update.connect(update);
 }

ToolFrame::~ToolFrame()
 {
 }

 // methods

void ToolFrame::bindClient(SubWindow &client_)
 {
  guardDead();

  client=&client_;
  client_ac=client_.getAliveControl();
 }

void ToolFrame::connectUpdate(Signal<> &update)
 {
  connector_update.connect(update);
 }

void ToolFrame::createMain(Pane pane,const DefString &title)
 {
  guardClient();
  guardDead();

  has_focus=false;

  host->createMain(pane,pane.getSize());
  host->setTitle(Range(title));
  host->display(CmdDisplay_Normal);
 }

void ToolFrame::create(Pane pane)
 {
  guardClient();
  guardDead();

  has_focus=false;

  host->create(pane,pane.getSize());
  host->show();
 }

void ToolFrame::create(FrameWindow *parent,Pane pane)
 {
  guardClient();
  guardDead();

  has_focus=false;

  host->create(parent->getHost(),pane,pane.getSize());
  host->show();
 }

 // SubWindowHost

FrameWindow * ToolFrame::getFrame() noexcept
 {
  return this;
 }

Point ToolFrame::getScreenOrigin() noexcept
 {
  try { return host->getPlace().getBase(); } catch(...) { return Null; }
 }

void ToolFrame::redraw(Pane pane) noexcept
 {
  try { if( redraw_set.add(pane) ) input.redrawSet(); } catch(...) {}
 }

void ToolFrame::setFocus(SubWindow *) noexcept
 {
  if( has_focus )
    {
     try { getClient().gainFocus(); } catch(...) {}
    }
 }

void ToolFrame::captureMouse(SubWindow *) noexcept
 {
  if( !client_capture )
    {
     client_capture=true;

     try { host->captureMouse(); } catch(...) {}
    }
 }

void ToolFrame::releaseMouse(SubWindow *) noexcept
 {
  if( client_capture )
    {
     client_capture=false;

     try { host->releaseMouse(); } catch(...) {}
    }
 }

 // base

void ToolFrame::alive()
 {
  reset();

  host->trackMouseHover();
  host->trackMouseLeave();

  client_ac->alive();

  getClient().open();
 }

void ToolFrame::dying()
 {
  client_ac->dying();
 }

void ToolFrame::dead()
 {
  getClient().close();

  client_ac->dead();
 }

void ToolFrame::askClose()
 {
  if( client_ac->askDestroy() ) destroy();
 }

void ToolFrame::setSize(Point size_,bool buf_dirty)
 {
  if( ( size_!=Null && size!=size_ ) || buf_dirty )
    {
     size=size_;

     redrawAll(LayoutResize);
    }
 }

void ToolFrame::paintDone(unsigned)
 {
  if( delay_draw )
    {
     delay_draw=false;

     redrawAll();
    }
 }

 // keyboard

void ToolFrame::gainFocus()
 {
  if( Change(has_focus,true) )
    {
     getClient().gainFocus();
    }
 }

void ToolFrame::looseFocus()
 {
  if( Change(has_focus,false) )
    {
     getClient().looseFocus();
    }
 }

 // mouse

void ToolFrame::looseCapture()
 {
  if( client_capture )
    {
     client_capture=false;

     getClient().looseCapture();
    }
 }

void ToolFrame::setMouseShape(Point point,KeyMod kmod)
 {
  host->setMouseShape(getClient().forward_getMouseShape(point,kmod));
 }

 // user input

void ToolFrame::disableReact()
 {
  if( Change(enable_react,false) ) redrawAll();
 }

void ToolFrame::enableReact()
 {
  if( Change(enable_react,true) ) redrawAll();
 }

void ToolFrame::react(UserAction action)
 {
  if( enable_react ) action.dispatch(*this);
 }

void ToolFrame::react_other(UserAction action)
 {
  if( action.fromKeyboard() )
    {
     getClient().react(action);
    }
  else
    {
     Point point=action.getPoint();

     if( client_capture || Pane(Null,size).contains(point) )
       {
        getClient().forward_react(action);
       }
    }
 }

void ToolFrame::react_Move(Point point,MouseKey mkey)
 {
  if( Pane(Null,size).contains(point) )
    {
     client_enter=true;

     getClient().forward().put_Move(point,mkey);
    }
  else
    {
     if( client_capture ) getClient().forward().put_Move(point,mkey);

     if( client_enter )
       {
        client_enter=false;

        getClient().put_Leave();
       }
    }
 }

void ToolFrame::react_Leave()
 {
  if( client_enter )
    {
     client_enter=false;

     getClient().put_Leave();
    }
 }

void ToolFrame::update()
 {
  input.redrawAll(LayoutUpdate);
 }

} // namespace Video
} // namespace CCore

