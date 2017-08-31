/* InternalDesktop.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.01
//
//  Tag: Target/WIN32
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/video/InternalDesktop.h>

namespace CCore {
namespace Video {
namespace Internal {

/* class WindowsDesktop */

bool WindowsDesktop::TestMsg()
 {
  Win32::Msg msg;

  return Win32::PeekMessageA(&msg,0,0,0,Win32::PeekMessage_NoRemove);
 }

WindowsDesktop::WindowsDesktop()
 {
  h_event=Win32::CreateEventW(0,false,false,0);
 }

WindowsDesktop::~WindowsDesktop()
 {
  if( h_event ) Win32::CloseHandle(h_event);
 }

 // Desktop

WindowHost * WindowsDesktop::createHost()
 {
  return new WindowsHost();
 }

Point WindowsDesktop::getScreenSize()
 {
  return Point((Coord)Win32::GetSystemMetrics(Win32::SysMetric_DXScreen),(Coord)Win32::GetSystemMetrics(Win32::SysMetric_DYScreen));
 }

Pane WindowsDesktop::getMaxPane()
 {
  return GetWorkPane();
 }

bool WindowsDesktop::pump(unsigned lim)
 {
  for(Win32::Msg msg; lim && Win32::PeekMessageA(&msg,0,0,0,Win32::PeekMessage_Remove) ;lim--)
    {
     if( msg.message==Win32::WM_Quit )
       {
        TaskEventHost.add<MsgEvent>(msg.message,MsgEvent::Stop);

        return false;
       }

     Win32::TranslateMessage(&msg);
     Win32::DispatchMessageA(&msg);
    }

  return true;
 }

void WindowsDesktop::wait(TimeScope time_scope)
 {
  if( auto t=+time_scope.get() )
    {
     if( TestMsg() ) return;

     if( h_event )
       {
        Win32::MsgWaitForMultipleObjects(1,&h_event,false,t,Win32::Wake_AllInput);
       }
     else
       {
        Win32::MsgWaitForMultipleObjects(0,0,false,t,Win32::Wake_AllInput);
       }
    }
 }

void WindowsDesktop::interrupt()
 {
  if( h_event ) Win32::SetEvent(h_event);
 }

} // namespace Internal
} // namespace Video
} // namespace CCore

