/* SubWindow.cpp */
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

#include <CCore/inc/video/SubWindow.h>

#include <CCore/inc/Exception.h>

namespace CCore {
namespace Video {

/* struct AliveControl */

const Unid AliveControl::TypeUnid={{0x9E69'313D,0x4224'80B3,0x07C8'56A4,0xEDEE'48BC,0x755F'B369,0xA322'6252,0x5495'352E,0xEA70'2BF5}};

AliveControl AliveControl::Default CCORE_INITPRI_3 ;

/* class SubWindow */

const Unid SubWindow::TypeUnid={{0x481F'20C2,0x2D18'4DF6,0x65BB'3A86,0x3B27'6E54,0x73F3'B26C,0xCFF3'9083,0xDDD3'D794,0x129C'3D4B}};

SubWindow::~SubWindow()
 {
  if( list ) list->del(this);
 }

AliveControl * SubWindow::getAliveControl()
 {
  if( AliveControl *ret=pickInterface<AliveControl>() ) return ret;

  return &AliveControl::Default;
 }

/* class WindowList */

SubWindow * WindowList::find(Point point) const
 {
  for(auto cur=list.start(); +cur ;++cur) if( cur->place.contains(point) ) return cur.ptr;

  return 0;
 }

SubWindow * WindowList::pick(Point point) const
 {
  if( capture ) return capture;

  return find(point);
 }

SubWindow * WindowList::next(SubWindow *sub_win)
 {
  if( SubWindow *ret=Algo::Link(sub_win).next ) return ret;

  return list.first;
 }

SubWindow * WindowList::prev(SubWindow *sub_win)
 {
  if( SubWindow *ret=Algo::Link(sub_win).prev ) return ret;

  return list.last;
 }

WindowList::~WindowList()
 {
  for(auto cur=list.start(); +cur ;++cur) cur->list=0;
 }

 // methods

bool WindowList::insTop(SubWindow *sub_win)
 {
  if( sub_win->list )
    {
     if( sub_win->list!=this )
       {
        Printf(Exception,"CCore::Video::WindowList::insTop(...) : sub-window is already included in another list");
       }

     return false;
    }

  list.ins_first(sub_win);

  sub_win->list=this;

  if( is_opened ) sub_win->open();

  return true;
 }

bool WindowList::insBottom(SubWindow *sub_win)
 {
  if( sub_win->list )
    {
     if( sub_win->list!=this )
       {
        Printf(Exception,"CCore::Video::WindowList::insBottom(...) : sub-window is already included in another list");
       }

     return false;
    }

  list.ins_last(sub_win);

  sub_win->list=this;

  if( is_opened ) sub_win->open();

  return true;
 }

bool WindowList::del(SubWindow *sub_win)
 {
  if( !sub_win->list ) return false;

  if( sub_win->list!=this )
    {
     Printf(Exception,"CCore::Video::WindowList::del(...) : sub-window from another list");
    }

  list.del(sub_win);

  sub_win->list=0;

  if( sub_win==focus )
    {
     focus=0;
    }

  if( sub_win==capture )
    {
     capture=0;

     parent.releaseMouse();
    }

  if( sub_win==enter )
    {
     enter=0;
    }

  if( is_opened ) sub_win->close();

  return true;
 }

void WindowList::moveTop(SubWindow *sub_win)
 {
  if( sub_win->list!=this )
    {
     Printf(Exception,"CCore::Video::WindowList::moveTop(...) : sub-window from another list");
    }

  list.del(sub_win);
  list.ins_first(sub_win);
 }

void WindowList::moveBottom(SubWindow *sub_win)
 {
  if( sub_win->list!=this )
    {
     Printf(Exception,"CCore::Video::WindowList::moveBottom(...) : sub-window from another list");
    }

  list.del(sub_win);
  list.ins_last(sub_win);
 }

void WindowList::insAfter(SubWindow *that,SubWindow *sub_win)
 {
  if( that->list!=this )
    {
     Printf(Exception,"CCore::Video::WindowList::insAfter(that,...) : that is not from this list");
    }

  if( sub_win->list )
    {
     if( sub_win->list!=this )
       {
        Printf(Exception,"CCore::Video::WindowList::insAfter(...) : sub-window is already included in another list");
       }

     list.del(sub_win);
     list.ins_after(that,sub_win);
    }
  else
    {
     list.ins_after(that,sub_win);

     sub_win->list=this;

     if( is_opened ) sub_win->open();
    }
 }

void WindowList::insBefore(SubWindow *that,SubWindow *sub_win)
 {
  if( that->list!=this )
    {
     Printf(Exception,"CCore::Video::WindowList::insBefore(that,...) : that is not from this list");
    }

  if( sub_win->list )
    {
     if( sub_win->list!=this )
       {
        Printf(Exception,"CCore::Video::WindowList::insBefore(...) : sub-window is already included in another list");
       }

     list.del(sub_win);
     list.ins_before(that,sub_win);
    }
  else
    {
     list.ins_before(that,sub_win);

     sub_win->list=this;

     if( is_opened ) sub_win->open();
    }
 }

void WindowList::delAll()
 {
  for(auto cur=list.start(); +cur ;++cur) cur->list=0;

  if( is_opened )
    {
     for(auto cur=list.start(); +cur ;++cur) try { cur->close(); } catch(...) {}
    }

  list.init();

  focus=0;
  enter=0;

  if( capture )
    {
     capture=0;

     parent.releaseMouse();
    }
 }

 // focus

void WindowList::focusTop()
 {
  if( SubWindow *sub_win=list.first ) sub_win->setFocus();
 }

void WindowList::focusBottom()
 {
  if( SubWindow *sub_win=list.last ) sub_win->setFocus();
 }

void WindowList::focusNext()
 {
  if( focus )
    {
     if( focus->askFocus()==FocusTab && focus->nextTabFocus() )
       {
        // keep focus
       }
     else
       {
        for(SubWindow *sub_win=next(focus); sub_win!=focus ;sub_win=next(sub_win))
          switch( sub_win->askFocus() )
            {
             case FocusOk : sub_win->setFocus(); return;

             case FocusTab : sub_win->setFocus(); sub_win->topTabFocus(); return;
            }
       }
    }
 }

void WindowList::focusPrev()
 {
  if( focus )
    {
     if( focus->askFocus()==FocusTab && focus->prevTabFocus() )
       {
        // keep focus
       }
     else
       {
        for(SubWindow *sub_win=prev(focus); sub_win!=focus ;sub_win=prev(sub_win))
          switch( sub_win->askFocus() )
            {
             case FocusOk : sub_win->setFocus(); return;

             case FocusTab : sub_win->setFocus(); sub_win->bottomTabFocus(); return;
            }
       }
    }
 }

void WindowList::focusOn(Point point)
 {
  for(auto cur=list.start(); +cur ;++cur)
    if( cur->place.contains(point) )
      {
       SubWindow *sub_win=cur.ptr;

       if( sub_win->askFocus() )
         {
          sub_win->setFocus();

          return;
         }
      }
 }

 // hint

Hint WindowList::getHint(Point point) const
 {
  Point base=parent.getPlace().getBase();
  Point p=point-base;

  for(auto cur=list.start(); +cur ;++cur)
    {
     Hint ret=cur->getHint(p);

     if( +ret )
       {
        ret.pane+=base;

        return ret;
       }
    }

  return parent.SubWindow::getHint(point);
 }

 // draw

bool WindowList::hasGoodSize() const
 {
  for(auto cur=list.start(); +cur ;++cur) if( !cur->hasGoodSize() ) return false;

  return true;
 }

void WindowList::draw(const DrawBuf &buf,bool drag_active) const
 {
  for(auto cur=list.start_rev(); +cur ;++cur) cur->forward_draw(buf,drag_active);
 }

void WindowList::draw(const DrawBuf &buf,Pane pane,bool drag_active) const
 {
  for(auto cur=list.start_rev(); +cur ;++cur) cur->forward_draw(buf,pane,drag_active);
 }

 // SubWindowHost

FrameWindow * WindowList::getFrame()
 {
  return parent.getFrame();
 }

Point WindowList::getScreenOrigin()
 {
  return parent.getScreenOrigin();
 }

void WindowList::redraw(Pane pane)
 {
  parent.redraw(pane);
 }

void WindowList::setFocus(SubWindow *sub_win)
 {
  if( sub_win->list!=this )
    {
     Printf(Exception,"CCore::Video::WindowList::setFocus(...) : sub-window from another list");
    }

  if( focus!=sub_win )
    {
     if( focus && has_focus ) focus->looseFocus();

     focus=sub_win;
    }

  parent.setFocus();
 }

void WindowList::captureMouse(SubWindow *sub_win)
 {
  if( sub_win->list!=this )
    {
     Printf(Exception,"CCore::Video::WindowList::captureMouse(...) : sub-window from another list");
    }

  capture=sub_win;

  parent.captureMouse();
 }

void WindowList::releaseMouse(SubWindow *sub_win)
 {
  if( sub_win->list!=this )
    {
     Printf(Exception,"CCore::Video::WindowList::releaseMouse(...) : sub-window from another list");
    }

  if( sub_win==capture )
    {
     capture=0;

     parent.releaseMouse();
    }
 }

 // base

void WindowList::open()
 {
  capture=0;
  enter=0;
  has_focus=false;
  is_opened=true;

  for(auto cur=list.start(); +cur ;++cur) try { cur->open(); } catch(...) {}
 }

void WindowList::close()
 {
  is_opened=false;

  for(auto cur=list.start(); +cur ;++cur) try { cur->close(); } catch(...) {}
 }

 // keyboard

void WindowList::gainFocus()
 {
  has_focus=true;

  if( focus ) focus->gainFocus();
 }

void WindowList::looseFocus()
 {
  has_focus=false;

  if( focus ) focus->looseFocus();
 }

 // tab focus

void WindowList::topTabFocus()
 {
  for(auto cur=list.start(); +cur ;++cur)
    switch( cur->askFocus() )
      {
       case FocusOk : cur->setFocus(); return;

       case FocusTab : cur->setFocus(); cur->topTabFocus(); return;
      }
 }

bool WindowList::nextTabFocus()
 {
  if( focus )
    {
     if( focus->askFocus()==FocusTab && focus->nextTabFocus() )
       {
        // keep focus

        return true;
       }
     else
       {
        for(SubWindow *sub_win=Algo::Link(focus).next; sub_win ;sub_win=Algo::Link(sub_win).next)
          switch( sub_win->askFocus() )
            {
             case FocusOk : sub_win->setFocus(); return true;

             case FocusTab : sub_win->setFocus(); sub_win->topTabFocus(); return true;
            }
       }
    }

  return false;
 }

void WindowList::bottomTabFocus()
 {
  for(auto cur=list.start_rev(); +cur ;++cur)
    switch( cur->askFocus() )
      {
       case FocusOk : cur->setFocus(); return;

       case FocusTab : cur->setFocus(); cur->bottomTabFocus(); return;
      }
 }

bool WindowList::prevTabFocus()
 {
  if( focus )
    {
     if( focus->askFocus()==FocusTab && focus->prevTabFocus() )
       {
        // keep focus

        return true;
       }
     else
       {
        for(SubWindow *sub_win=Algo::Link(focus).prev; sub_win ;sub_win=Algo::Link(sub_win).prev)
          switch( sub_win->askFocus() )
            {
             case FocusOk : sub_win->setFocus(); return true;

             case FocusTab : sub_win->setFocus(); sub_win->bottomTabFocus(); return true;
            }
       }
    }

  return false;
 }

 // mouse

void WindowList::looseCapture()
 {
  if( capture ) Replace_null(capture)->looseCapture();
 }

MouseShape WindowList::getMouseShape(Point point,KeyMod kmod,MouseShape def_shape) const
 {
  if( SubWindow *sub_win=pick(point) ) return sub_win->forward_getMouseShape(point,kmod);

  return def_shape;
 }

 // user input

void WindowList::react(UserAction action)
 {
  react(action, [] (UserAction) {} );
 }

} // namespace Video
} // namespace CCore

