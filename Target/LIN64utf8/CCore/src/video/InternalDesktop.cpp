/* InternalDesktop.cpp */
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

#include <CCore/inc/video/InternalDesktop.h>

#include <CCore/inc/Exception.h>

#include <poll.h>
#include <sys/eventfd.h>
#include <unistd.h>

namespace CCore {
namespace Video {
namespace Internal {

/* class X11Desktop */

void X11Desktop::guardDisplay(const char *format)
 {
  if( !display )
    {
     Printf(Exception,format,"no display");
    }

  if( keymap.noMap() )
    {
     Printf(Exception,format,"no key map");
    }

  if( sem_fd==-1 )
    {
     Printf(Exception,format,"no interrupt semaphore");
    }
 }

Bool X11Desktop::MatchAll(Display *,XEvent *,XPointer)
 {
  return True;
 }

int X11Desktop::ErrorHandler(Display *display,XErrorEvent *err)
 {
  Printf(NoException,"#;> #;\n",GetFuncName(),PrintXStatus(display,err->error_code));

  return 0;
 }

int X11Desktop::IOErrorHandler(Display *)
 {
  Printf(NoException,"X11IOFault>\n");

  return 0;
 }

X11Desktop::X11Desktop()
 : display(XOpenDisplay(0)),
   keymap(display)
 {
  if( !display ) return;

  XSetErrorHandler(ErrorHandler);
  XSetIOErrorHandler(IOErrorHandler);

  screen=DefaultScreen(display);
  fd=ConnectionNumber(display);

  sem_fd=eventfd(0,EFD_SEMAPHORE);

  // XLib-xcb bug workaround

  SetFuncName("XKeysymToKeycode");

  XKeysymToKeycode(display,XK_F1);
 }

X11Desktop::~X11Desktop()
 {
  if( display )
    {
     SetFuncName("XCloseDisplay");

     XCloseDisplay(display);
    }

  if( sem_fd!=-1 ) close(sem_fd);
 }

WindowHost * X11Desktop::createHost()
 {
  guardDisplay("CCore::Video::Internal::X11Desktop::createHost() : #;");

  return new X11Host(display,screen);
 }

Point X11Desktop::getScreenSize()
 {
  guardDisplay("CCore::Video::Internal::X11Desktop::getScreenSize() : #;");

  return Point_cast(DisplayWidth(display,screen),DisplayHeight(display,screen));
 }

Pane X11Desktop::getMaxPane()
 {
  guardDisplay("CCore::Video::Internal::X11Desktop::getMaxPane() : #;");

  Window root=RootWindow(display,screen);

  SetFuncName("XInternAtom");

  Atom atom=XInternAtom(display,"_NET_WORKAREA",True);

  if( atom!=None )
    {
     Atom atom_type=None;
     int format=0;
     unsigned long ret_len=0;
     unsigned long rest_len=0;
     unsigned char *data=0;

     SetFuncName("XGetWindowProperty");

     XGetWindowProperty(display,root,atom,0,4,False,AnyPropertyType,&atom_type,&format,&ret_len,&rest_len,&data);

     if( format )
       {
        if( format==32 && ret_len==4 && rest_len==0 )
          {
           unsigned long *data32=(unsigned long *)data;

           Pane ret=Pane_cast(data32[0],data32[1],data32[2],data32[3]);

           XFree(data);

           return ret;
          }

        XFree(data);
       }
    }

  return Pane(Null,getScreenSize());
 }

bool X11Desktop::pump(unsigned lim)
 {
  guardDisplay("CCore::Video::Internal::X11Desktop::pump(...) : #;");

  for(XEvent event; lim && XCheckIfEvent(display,&event,MatchAll,0) ;lim--)
    {
     if( !WindowDispatcher::DispatchEvent(event) ) return false;
    }

  if( !WindowDispatcher::Ping() ) return false;

  return true;
 }

void X11Desktop::wait(TimeScope time_scope)
 {
  if( auto t=+time_scope.get() )
    {
     const char *format="CCore::Video::Internal::X11Desktop::wait(...) : #;";

     guardDisplay(format);

     pollfd list[2];

     list[0].fd=fd;
     list[0].events=POLLIN;

     list[1].fd=sem_fd;
     list[1].events=POLLIN;

     int result=poll(list,2,t);

     SysGuard(format, result!=-1 );

     if( result )
       {
        if( list[1].revents&POLLIN )
          {
           eventfd_t value;

           eventfd_read(sem_fd,&value);
          }
       }
    }
 }

void X11Desktop::interrupt()
 {
  const char *format="CCore::Video::Internal::X11Desktop::interrupt(...) : #;";

  guardDisplay(format);

  eventfd_write(sem_fd,1);
 }

/* global DesktopObject */

X11Desktop DesktopObject CCORE_INITPRI_3 ;

/* global HiddenWindow */

HiddenWindowHost HiddenWindow CCORE_INITPRI_3 ;

} // namespace Internal
} // namespace Video
} // namespace CCore

