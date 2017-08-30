/* InternalHost.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.01
//
//  Tag: Target/LIN64
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/video/InternalHost.h>
#include <CCore/inc/video/InternalDesktop.h>

#include <CCore/inc/CapString.h>

#include <CCore/inc/Exception.h>

namespace CCore {
namespace Video {
namespace Internal {

/* class DClickDetector */

bool DClickDetector::detect(Point point_,MSec timeout)
 {
  if( flag )
    {
     if( Change(point,point_) )
       {
        timer.reset();
       }
     else
       {
        if( timer.less(+timeout)  )
          {
           flag=false;

           return true;
          }
        else
          {
           timer.reset();
          }
       }
    }
  else
    {
     flag=true;

     point=point_;

     timer.reset();
    }

  return false;
 }

void DClickDetector::ping(MSec timeout)
 {
  if( flag )
    {
     if( timer.exceed(+timeout) ) flag=false;
    }
 }

/* class HoverDetector */

void HoverDetector::start(Point point_,MouseKey mkey_)
 {
  if( enable )
    {
     if( flag )
       {
        if( Change(point,point_) ) timer.reset();

        mkey=mkey_;
       }
     else
       {
        flag=true;
        point=point_;
        mkey=mkey_;
        timer.reset();
       }
    }
 }

void HoverDetector::test(FrameWindow *frame)
 {
  if( flag )
    {
     if( timer.exceed(+timeout) )
       {
        flag=false;

        frame->put_Hover(point,mkey);
       }
    }
 }

/* class X11Host */

PlatformRandom X11Host::Random CCORE_INITPRI_3 ;

Cursor X11Host::CursorTable[15]={};

X11Host * X11Host::MainWindow = 0 ;

 // reset()

void X11Host::reset()
 {
  expose_flag=true;
  show_flag=false;
  parent_show=true;
  mouse_shape=Mouse_Null;
  user_flag=true;
  leave_flag=false;
  motion_flag=true;
  stack_changed=true;
  origin=Null;
  size=Null;
  buf_dirty=true;
  max_flag=false;
  hover.reset();
  left_dclick.reset();
  right_dclick.reset();

  clipboard.erase();
 }

 // utils

void X11Host::guardAlive(const char *format)
 {
  if( window==None )
    {
     Printf(Exception,format,"window is dead");
    }
 }

void X11Host::guardDead(const char *format)
 {
  if( window!=None )
    {
     Printf(Exception,format,"window is alive");
    }
 }

void X11Host::GuardMaxSize(const char *format,Point max_size)
 {
  if( max_size<=Null )
    {
     Printf(Exception,format,"bad max_size");
    }
 }

void X11Host::GuardPane(const char *format,Pane pane,Point max_size)
 {
  if( !(pane.getSize()<=max_size) )
    {
     Printf(Exception,format,"bad pane size");
    }
 }

void X11Host::guardCreate(const char *format,Point max_size)
 {
  guardDead(format);

  GuardMaxSize(format,max_size);
 }

void X11Host::guardCreate(const char *format,Pane pane,Point max_size)
 {
  guardDead(format);

  GuardMaxSize(format,max_size);

  GuardPane(format,pane,max_size);
 }

Coord X11Host::RandomLen(Coord len)
 {
  int percent=Random.select(128);

  return Coord( (len/2)+((len/4)*percent)/128 );
 }

Coord X11Host::RandomPos(Coord len)
 {
  int percent=Random.select(128);

  return Coord( (len*percent)/128 );
 }

Bool X11Host::MatchSelection(Display *,XEvent *event,XPointer)
 {
  return event->type==SelectionNotify || event->type==SelectionRequest ;
 }

 // cursor

Cursor X11Host::GetCursor(Display *display,MouseShape mshape)
 {
  if( !mshape ) return None;

  Cursor ret=CursorTable[mshape];

  if( ret==None )
    {
     static const unsigned Table[]=
      {
       0, // Mouse_Null

       XC_left_ptr,            // Mouse_Arrow
       XC_xterm,               // Mouse_IBeem
       XC_watch,               // Mouse_Wait
       XC_crosshair,           // Mouse_Cross
       XC_hand2,               // Mouse_Hand
       XC_pirate,              // Mouse_Stop
       XC_question_arrow,      // Mouse_Help
       XC_sb_h_double_arrow,   // Mouse_SizeLeftRight
       XC_sb_v_double_arrow,   // Mouse_SizeUpDown
       XC_bottom_right_corner, // Mouse_SizeUpLeft  // to DownRight
       XC_bottom_left_corner,  // Mouse_SizeUpRight // to DownLeft
       XC_fleur,               // Mouse_SizeAll
       XC_center_ptr,          // Mouse_UpArrow
       XC_boat                 // Mouse_Progress
      };

     SetFuncName("XcursorShapeLoadCursor");

     ret=XcursorShapeLoadCursor(display,Table[mshape]);

     CursorTable[mshape]=ret;
    }

  return ret;
 }

 // event mask

unsigned X11Host::EventMask(bool user_flag,bool leave_flag)
 {
  unsigned ret=ExposureMask|FocusChangeMask|StructureNotifyMask;

  if( user_flag )
    {
     ret|=KeyPressMask|KeyReleaseMask|ButtonPressMask|ButtonReleaseMask|PointerMotionMask;

     if( leave_flag ) ret|=LeaveWindowMask;
    }

  return ret;
 }

void X11Host::setEventMask()
 {
  if( window_ok )
    {
     SetFuncName("XSelectInput");

     XSelectInput(disp,window,EventMask(user_flag,leave_flag));
    }
 }

void X11Host::disableMotionNotify()
 {
  motion_flag=false;
 }

void X11Host::enableMotionNotify()
 {
  motion_flag=true;
 }

 // descendants

void X11Host::addDescendant(X11Host *host)
 {
  if( host->dparent==0 )
    {
     dlist.ins(host);

     host->dparent=this;

     host->parent_show = parent_show && show_flag ;
    }
 }

void X11Host::delAsDescendant()
 {
  if( dparent )
    {
     dparent->dlist.del(this);

     dparent=0;

     parent_show=true;
    }
 }

 // postDestroy()

void X11Host::postDestroy()
 {
  DelFromMap(this);
  delAsDescendant();

  clipboard.erase();
 }

 // message handle

MouseKey X11Host::GetMKey(unsigned state)
 {
  return DesktopObject.getMKey(state);
 }

KeyMod X11Host::GetKMod(unsigned state)
 {
  return DesktopObject.getKMod(state);
 }

auto X11Host::MapToVKey(unsigned state,unsigned keycode)
 {
  return DesktopObject.mapToVKey(state,keycode);
 }

auto X11Host::MapToChar(unsigned state,unsigned keycode)
 {
  return DesktopObject.mapToChar(state,keycode);
 }

void X11Host::mouseShape(VKey vkey,KeyMod kmod)
 {
  if( vkey==VKey_Shift || vkey==VKey_Ctrl || vkey==VKey_Alt )
    {
     frame->setMouseShape(getMousePos(),kmod);
    }
 }

void X11Host::handle(XEvent &event)
 {
  if( !is_alive )
    {
     is_alive=true;

     try { frame->alive(); } catch(...) {}

     XWindowAttributes attr{};

     if( window_ok )
       {
        SetFuncName("XGetWindowAttributes");

        XGetWindowAttributes(disp,window,&attr);
       }

     origin=Point_cast(attr.x,attr.y);
     size=Point_cast(attr.width,attr.height);

     frame->setSize(size,buf_dirty);
    }

  switch( event.type )
    {
     // user input

     case KeyPress :
      {
       XKeyPressedEvent &data=event.xkey;

       auto result=MapToChar(data.state,data.keycode);
       KeyMod kmod=GetKMod(data.state);

       if( result.ext ) kmod|=KeyMod_Ext;

       mouseShape(result.vkey,kmod);

       frame->put_Key(result.vkey,kmod);

       if( result.vkey==VKey_F12 ) DesktopObject.updateMap();

       if( char ch=result.ch )
         {
          if( kmod&KeyMod_Alt )
            frame->put_AltChar(ch);
          else
            frame->put_Char(ch);
         }
      }
     break;

     case KeyRelease :
      {
       XKeyReleasedEvent &data=event.xkey;

       auto result=MapToVKey(data.state,data.keycode);
       KeyMod kmod=GetKMod(data.state);

       if( result.ext ) kmod|=KeyMod_Ext;

       mouseShape(result.vkey,kmod);

       frame->put_KeyUp(result.vkey,kmod);
      }
     break;

     case ButtonPress :
      {
       if( window_ok )
         {
          SetFuncName("XSetInputFocus");

          XSetInputFocus(disp,window,RevertToPointerRoot,CurrentTime);
         }

       raiseAll();

       XButtonEvent &data=event.xbutton;

       Point point=Point_cast(data.x_root,data.y_root)-origin;
       MouseKey mkey=GetMKey(data.state);

       hover.stop();

       switch( data.button )
         {
          case Button1 :
           {
            bool dclick=left_dclick.detect(point,dclick_timeout);

            frame->put_LeftClick(point,mkey|MouseKey_Left);

            if( dclick ) frame->put_LeftDClick(point,mkey|MouseKey_Left);
           }
          break;

          case Button3 :
           {
            bool dclick=right_dclick.detect(point,dclick_timeout);

            frame->put_RightClick(point,mkey|MouseKey_Right);

            if( dclick ) frame->put_RightDClick(point,mkey|MouseKey_Right);
           }
          break;

          case Button4 : frame->put_Wheel(point,mkey,1); break;

          case Button5 : frame->put_Wheel(point,mkey,-1); break;
         }
      }
     break;

     case ButtonRelease :
      {
       XButtonEvent &data=event.xbutton;

       Point point=Point_cast(data.x_root,data.y_root)-origin;
       MouseKey mkey=GetMKey(data.state);

       switch( data.button )
         {
          case Button1 : frame->put_LeftUp(point,mkey); break;

          case Button3 : frame->put_RightUp(point,mkey); break;
         }
      }
     break;

     case MotionNotify :
      {
       XMotionEvent &data=event.xmotion;

       Point point=Point_cast(data.x_root,data.y_root)-origin;
       MouseKey mkey=GetMKey(data.state);

       if( (mkey&(MouseKey_Left|MouseKey_Right))==0 ) hover.start(point,mkey);

       frame->setMouseShape(point,GetKMod(data.state));

       if( motion_flag ) frame->put_Move(point,mkey);
      }
     break;

     case LeaveNotify :
      {
       XLeaveWindowEvent &data=event.xcrossing;

       if( data.mode==NotifyUngrab )
         {
          frame->looseCapture();
         }
       else
         {
          hover.stop();

          frame->put_Leave();
         }
      }
     break;

     case FocusIn :
      {
       frame->gainFocus();
      }
     break;

     case FocusOut :
      {
       frame->looseFocus();
      }
     break;

     // draw

     case Expose :
      {
       bool flag=Replace(expose_flag,false);

       XExposeEvent &data=event.xexpose;

       Pane pane=Pane_cast(data.x,data.y,data.width,data.height);

       if( !buf_dirty && window_ok ) buf.draw(disp,window,gc,pane);

       SetFuncName("XSync");

       XSync(disp,False);

       frame->paintDone(Replace_null(token));

       if( flag )
         {
          if( window_ok )
            {
             SetFuncName("XSetInputFocus");

             XSetInputFocus(disp,window,RevertToPointerRoot,CurrentTime);
            }
         }
      }
     break;

     // state

     case DestroyNotify :
      {
       try { frame->dead(); } catch(...) {}

       window=None;
       is_alive=false;

       postDestroy();

       if( is_main )
         {
          MainWindow=0;

          HiddenWindow.destroy();

          Stop();
         }
      }
     break;

     case ConfigureNotify :
      {
       stack_changed=true;
      }
     break;

     case ClientMessage :
      {
       clearStackChanged();
      }
     break;

     case SelectionRequest :
      {
       XSelectionRequestEvent &data=event.xselectionrequest;

       Atom notify_atom;

       if( data.selection==XA_PRIMARY && data.target==XA_STRING )
         {
          SetFuncName("XChangeProperty");

          unsigned char *ptr=(unsigned char *)clipboard.getPtr();
          int len=(int)Min<ulen>(clipboard.getLen(),SIntFunc<int>::MaxPositive);

          XChangeProperty(disp,data.requestor,data.property,data.target,8,PropModeReplace,ptr,len);

          notify_atom=data.property;
         }
       else
         {
          notify_atom=None;
         }

       SetFuncName("XSendEvent");

       XEvent notify{};

       XSelectionEvent &out=notify.xselection;

       out.type=SelectionNotify;
       out.requestor=data.requestor;
       out.selection=data.selection;
       out.target=data.target;
       out.property=notify_atom;
       out.time=data.time;

       XSendEvent(disp,data.requestor,False,0,&notify);
      }
     break;

     case SelectionClear :
      {
       clipboard.erase();
      }
     break;
    }
 }

void X11Host::ping()
 {
  enableMotionNotify();

  hover.test(frame);

  left_dclick.ping(dclick_timeout);

  right_dclick.ping(dclick_timeout);
 }

 // group actions

void X11Host::destroyAll()
 {
  for(auto cur=dlist.start(); +cur ;++cur)
    {
     cur->destroyAll();
    }

  if( window_ok )
    {
     SetFuncName("XFreeGC");

     XFreeGC(disp,gc);

     SetFuncName("XDestroyWindow");

     XDestroyWindow(disp,window);

     window_ok=false;
    }
 }

void X11Host::clearStackChanged()
 {
  stack_changed=false;

  for(auto cur=dlist.start(); +cur ;++cur) cur->clearStackChanged();
 }

void X11Host::raiseAll(bool force)
 {
  if( window_ok && ( stack_changed || force ) )
    {
     SetFuncName("XRaiseWindow");

     XRaiseWindow(disp,window);
    }

  if( stack_changed || force )
    for(auto cur=dlist.start(); +cur ;++cur) cur->raiseAll(true);

  if( window_ok && !force )
    {
     SetFuncName("XSendEvent");

     XEvent event{};

     event.xclient.type=ClientMessage;
     event.xclient.window=window;
     event.xclient.message_type=0;
     event.xclient.format=8;

     XSendEvent(disp,window,False,0,&event);
    }
 }

void X11Host::parentShowOn()
 {
  parent_show=true;

  if( window_ok && show_flag )
    {
     SetFuncName("XMapWindow");

     XMapWindow(disp,window);
    }

  if( show_flag )
    for(auto cur=dlist.start(); +cur ;++cur) cur->parentShowOn();
 }

void X11Host::parentShowOff()
 {
  parent_show=false;

  if( window_ok && show_flag )
    {
     SetFuncName("XUnmapWindow");

     XUnmapWindow(disp,window);
    }

  if( show_flag )
    for(auto cur=dlist.start(); +cur ;++cur) cur->parentShowOff();
 }

void X11Host::showAll()
 {
  if( window_ok && parent_show )
    {
     SetFuncName("XMapWindow");

     XMapWindow(disp,window);
    }

  if( parent_show )
    for(auto cur=dlist.start(); +cur ;++cur) cur->parentShowOn();
 }

void X11Host::hideAll()
 {
  if( window_ok && parent_show )
    {
     SetFuncName("XUnmapWindow");

     XUnmapWindow(disp,window);
    }

  if( parent_show )
    for(auto cur=dlist.start(); +cur ;++cur) cur->parentShowOff();
 }

void X11Host::do_move(Pane pane)
 {
  const char *format="CCore::Video::Private_Desktop::X11Host::do_move(...) : #;";

  guardAlive(format);

  GuardPane(format,pane,max_size);

  if( window_ok )
    {
     SetFuncName("XMoveResizeWindow");

     XMoveResizeWindow(disp,window,pane.x,pane.y,pane.dx,pane.dy);
    }

  disableMotionNotify();
  left_dclick.stop();
  right_dclick.stop();

  hover.stop();

  SetFuncName("XSync");

  XSync(disp,False);

  origin=pane.getBase();

  if( Change(size,pane.getSize()) )
    {
     frame->setSize(size,buf_dirty);
    }
 }

X11Host::X11Host(Display *display_,int screen_)
 : disp(display_),
   screen(screen_)
 {
 }

X11Host::~X11Host()
 {
  postDestroy();
 }

 // msg boxes

void X11Host::CloseApp()
 {
  if( MainWindow ) MainWindow->frame->askClose();
 }

void X11Host::RestoreApp()
 {
  if( MainWindow ) MainWindow->show();
 }

void X11Host::AbortMsgBox(StrLen text)
 {
  MsgBoxHost host;

  host.show("Abort",text);
 }

void X11Host::ErrorMsgBox(StrLen text,StrLen title)
 {
  MsgBoxHost host;

  host.show(title,text);
 }

 // WinControl
 // create/destroy

void X11Host::createMain(Point max_size)
 {
  Pane work=DesktopObject.getMaxPane();

  Point size;

  size.x=RandomLen(work.dx);
  size.y=RandomLen(work.dy);

  size=Inf(size,max_size);

  Point base;

  base.x=RandomPos(work.dx-size.x);
  base.y=RandomPos(work.dy-size.y);

  Pane pane=Pane(work.getBase()+base,size);

  createMain(pane,max_size);
 }

void X11Host::createMain(Pane pane,Point max_size_)
 {
  const char *format="CCore::Video::Private_Desktop::X11Host::createMain(...) : #;";

  guardCreate(format,pane,max_size_);

  if( MainWindow!=0 )
    {
     Printf(Exception,format,"main window is already created");
    }

  HiddenWindow.create();

  is_main=true;
  max_size=max_size_;

  reset();

  buf.setSize(max_size_);

  // create

  Window root=RootWindow(disp,screen);

  XSetWindowAttributes attr{};

  attr.event_mask=EventMask(user_flag,leave_flag);

  attr.override_redirect=True;

  SetFuncName("XCreateWindow");

  window=XCreateWindow(disp,root,pane.x,pane.y,pane.dx,pane.dy,0,CopyFromParent,InputOutput,CopyFromParent,CWEventMask|CWOverrideRedirect,&attr);

  if( window==None )
    {
     Printf(Exception,format,"cannot create window");
    }

  window_ok=true;

  // create gc

  XGCValues gcv{};

  SetFuncName("XCreateGC");

  gc=XCreateGC(disp,window,0,&gcv);

  if( gc==None )
    {
     SetFuncName("XDestroyWindow");

     XDestroyWindow(disp,window);

     window_ok=false;

     Printf(Exception,format,"cannot create GC");
    }

  // finish

  MainWindow=this;

  AddToMap(window,this);
 }

void X11Host::create(Pane pane,Point max_size_)
 {
  create(0,pane,max_size_);
 }

void X11Host::create(WindowHost *parent_,Pane pane,Point max_size_)
 {
  const char *format="CCore::Video::Private_Desktop::X11Host::create(...) : #;";

  guardCreate(format,pane,max_size_);

  X11Host *parent;

  if( parent_ )
    {
     parent=dynamic_cast<X11Host *>(parent_);

     if( !parent )
       {
        Printf(Exception,format,"bad parent");
       }

     if( !parent->window_ok )
       {
        Printf(Exception,format,"dead parent");
       }
    }
  else
    {
     parent=MainWindow;
    }

  is_main=false;
  max_size=max_size_;

  reset();

  buf.setSize(max_size_);

  // create

  Window root=RootWindow(disp,screen);

  XSetWindowAttributes attr{};

  attr.event_mask=EventMask(user_flag,leave_flag);

  attr.override_redirect=True;

  SetFuncName("XCreateWindow");

  window=XCreateWindow(disp,root,pane.x,pane.y,pane.dx,pane.dy,0,CopyFromParent,InputOutput,CopyFromParent,CWEventMask|CWOverrideRedirect,&attr);

  if( window==None )
    {
     Printf(Exception,format,"cannot create window");
    }

  window_ok=true;

  // create gc

  XGCValues gcv{};

  SetFuncName("XCreateGC");

  gc=XCreateGC(disp,window,0,&gcv);

  if( gc==None )
    {
     SetFuncName("XDestroyWindow");

     XDestroyWindow(disp,window);

     window_ok=false;

     Printf(Exception,format,"cannot create GC");
    }

  // finish

  AddToMap(window,this);

  if( parent ) parent->addDescendant(this);
 }

void X11Host::destroy()
 {
  const char *format="CCore::Video::Private_Desktop::X11Host::destroy() : #;";

  guardAlive(format);

  destroyAll();

  while( is_alive && !is_main )
    {
     if( !frame->desktop->pump() ) break;
    }
 }

 // operations

void X11Host::setTitle(StrLen title)
 {
  CapString<> cap(title);

  const char *format="CCore::Video::Private_Desktop::X11Host::setTitle(...) : #;";

  guardAlive(format);

  if( is_main ) HiddenWindow.setTitle(StrLen(cap));
 }

void X11Host::setMaxSize(Point max_size_)
 {
  const char *format="CCore::Video::Private_Desktop::X11Host::setMaxSize(...) : #;";

  GuardMaxSize(format,max_size_);

  buf.setSize(max_size_);

  max_size=max_size_;

  buf_dirty=true;
 }

bool X11Host::enableUserInput(bool en)
 {
  const char *format="CCore::Video::Private_Desktop::X11Host::enableUserInput(...) : #;";

  guardAlive(format);

  bool ret=user_flag;

  if( Change(user_flag,en) ) setEventMask();

  return ret;
 }

void X11Host::display(CmdDisplay cmd_display)
 {
  const char *format="CCore::Video::Private_Desktop::X11Host::display(...) : #;";

  guardAlive(format);

  switch( cmd_display )
    {
     default:
     case CmdDisplay_Normal :
      {
       show();
      }
     break;

     case CmdDisplay_Minimized :
      {
       if( is_main )
         {
          hide();

          HiddenWindow.iconify();
         }
      }
     break;

     case CmdDisplay_Maximized :
      {
       if( !max_flag )
         {
          max_flag=true;

          restore=getPlace();

          Pane pane=DesktopObject.getMaxPane();

          Replace_min(pane.dx,max_size.x);
          Replace_min(pane.dy,max_size.y);

          do_move(pane);

          if( window_ok )
            {
             SetFuncName("XClearArea");

             XClearArea(disp,window,0,0,0,0,True);
            }
         }

       show();
      }
     break;

     case CmdDisplay_Restore :
      {
       if( max_flag )
         {
          max_flag=false;

          do_move(restore);

          if( window_ok )
            {
             SetFuncName("XClearArea");

             XClearArea(disp,window,0,0,0,0,True);
            }
         }

       show();
      }
     break;
    }
 }

void X11Host::show()
 {
  const char *format="CCore::Video::Private_Desktop::X11Host::show() : #;";

  guardAlive(format);

  if( Change(show_flag,true) ) showAll();
 }

void X11Host::hide()
 {
  const char *format="CCore::Video::Private_Desktop::X11Host::hide() : #;";

  guardAlive(format);

  if( Change(show_flag,false) ) hideAll();
 }

 // drawing

void X11Host::update()
 {
  const char *format="CCore::Video::Private_Desktop::X11Host::update() : #;";

  guardAlive(format);

  Pane pane(Null,size);

  if( window_ok ) buf.draw(disp,window,gc,pane);

  buf_dirty=false;
 }

void X11Host::invalidate(Pane pane,unsigned token_)
 {
  const char *format="CCore::Video::Private_Desktop::X11Host::invalidate(...) : #;";

  guardAlive(format);

  if( !pane ) return;

  token|=token_;

  if( window_ok )
    {
     SetFuncName("XClearArea");

     XClearArea(disp,window,pane.x,pane.y,pane.dx,pane.dy,True);
    }

  buf_dirty=false;
 }

void X11Host::invalidate(unsigned token_)
 {
  const char *format="CCore::Video::Private_Desktop::X11Host::invalidate(...) : #;";

  guardAlive(format);

  token|=token_;

  if( window_ok )
    {
     SetFuncName("XClearArea");

     XClearArea(disp,window,0,0,0,0,True);
    }

  buf_dirty=false;
 }

ColorPlane X11Host::getDrawPlane()
 {
  return buf.getPlane();
 }

 // keyboard

void X11Host::setFocus()
 {
  const char *format="CCore::Video::Private_Desktop::X11Host::setFocus() : #;";

  guardAlive(format);

  if( window_ok )
    {
     SetFuncName("XSetInputFocus");

     XSetInputFocus(disp,window,RevertToPointerRoot,CurrentTime);
    }
 }

 // mouse

Point X11Host::getMousePos()
 {
  Window root;
  Window child;
  int root_x;
  int root_y;
  int win_x;
  int win_y;
  unsigned state;

  if( window_ok )
    {
     SetFuncName("XQueryPointer");

     if( XQueryPointer(disp,window,&root,&child,&root_x,&root_y,&win_x,&win_y,&state) )
       {
        Point point=Point_cast(root_x,root_y);

        return point-origin;
       }
    }

  return Null;
 }

void X11Host::captureMouse()
 {
  const char *format="CCore::Video::Private_Desktop::X11Host::captureMouse() : #;";

  guardAlive(format);

  if( window_ok )
    {
     SetFuncName("XGrabPointer");

     const unsigned AllEventMask=ButtonPressMask|ButtonReleaseMask|PointerMotionMask|LeaveWindowMask;

     XGrabPointer(disp,window,False,AllEventMask,GrabModeAsync,GrabModeAsync,None,GetCursor(disp,mouse_shape),CurrentTime);
    }
 }

void X11Host::releaseMouse()
 {
  const char *format="CCore::Video::Private_Desktop::X11Host::releaseMouse() : #;";

  guardAlive(format);

  SetFuncName("XUngrabPointer");

  XUngrabPointer(disp,CurrentTime);
 }

void X11Host::trackMouseHover()
 {
  trackMouseHover(400_msec);
 }

void X11Host::trackMouseHover(MSec time)
 {
  const char *format="CCore::Video::Private_Desktop::X11Host::trackMouseHover(...) : #;";

  guardAlive(format);

  hover.track(time);
 }

void X11Host::untrackMouseHover()
 {
  const char *format="CCore::Video::Private_Desktop::X11Host::untrackMouseHover() : #;";

  guardAlive(format);

  hover.untrack();
 }

void X11Host::trackMouseLeave()
 {
  const char *format="CCore::Video::Private_Desktop::X11Host::trackMouseLeave() : #;";

  guardAlive(format);

  if( Change(leave_flag,true) ) setEventMask();
 }

void X11Host::untrackMouseLeave()
 {
  const char *format="CCore::Video::Private_Desktop::X11Host::untrackMouseLeave() : #;";

  guardAlive(format);

  if( Change(leave_flag,false) ) setEventMask();
 }

void X11Host::setMouseShape(MouseShape mshape)
 {
  const char *format="CCore::Video::Private_Desktop::X11Host::setMouseShape(...) : #;";

  guardAlive(format);

  if( Change(mouse_shape,mshape) )
    {
     if( window_ok )
       {
        SetFuncName("XDefineCursor");

        XDefineCursor(disp,window,GetCursor(disp,mshape));
       }
    }
 }

 // place

Pane X11Host::getPlace()
 {
  const char *format="CCore::Video::Private_Desktop::X11Host::getPlace() : #;";

  guardAlive(format);

  return Pane(origin,size);
 }

void X11Host::setPlace(Pane pane)
 {
  max_flag=false;

  do_move(pane);
 }

 // clipboard

void X11Host::textToClipboard(StrLen text)
 {
  const char *format="CCore::Video::Private_Desktop::X11Host::textToClipboard(...) : #;";

  guardAlive(format);

  if( window_ok )
    {
     SetFuncName("XSetSelectionOwner");

     XSetSelectionOwner(disp,XA_PRIMARY,window,CurrentTime);

     clipboard.erase();

     clipboard.extend_copy(text);
    }
 }

void X11Host::textFromClipboard(Function<void (StrLen)> func)
 {
  const char *format="CCore::Video::Private_Desktop::X11Host::textFromClipboard(...) : #;";

  guardAlive(format);

  if( window_ok )
    {
     SetFuncName("XInternAtom");

     Atom prop=XInternAtom(disp,"STRING_FROM_CLIPBOARD",False);

     if( prop==Null )
       {
        func(Empty);

        return;
       }

     SetFuncName("XConvertSelection");

     XConvertSelection(disp,XA_PRIMARY,XA_STRING,prop,window,CurrentTime);

     for(MSecTimer timer; timer.less(1000) ;)
       {
        XEvent event;

        if( XCheckIfEvent(disp,&event,MatchSelection,0) )
          {
           if( event.type==SelectionNotify )
             {
              XSelectionEvent &data=event.xselection;

              if( data.property==prop )
                {
                 SetFuncName("XGetWindowProperty");

                 Atom type=None;
                 int format=0;
                 unsigned long ret_len=0;
                 unsigned long rest_len=0;
                 unsigned char *str=0;

                 XGetWindowProperty(disp,window,prop,0,SIntFunc<long>::MaxPositive/4,True,XA_STRING,&type,&format,&ret_len,&rest_len,&str);

                 if( format )
                   {
                    if( format==8 )
                      {
                       func(Range((char *)str,(ulen)ret_len));

                       XFree(str);

                       return;
                      }

                    XFree(str);
                   }
                }

              func(Empty);

              return;
             }
           else
             {
              DispatchEvent(event);
             }
          }
       }
    }

  func(Empty);
 }

} // namespace Internal
} // namespace Video
} // namespace CCore

