/* InternalDesktop.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Target/WIN64utf8
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/video/InternalDesktop.h>

namespace CCore {
namespace Video {
namespace Internal {

/* class WindowsDesktop */

bool WindowsDesktop::TestMsg()
 {
  Win64::Msg msg;

  return Win64::PeekMessageW(&msg,0,0,0,Win64::PeekMessage_NoRemove);
 }

WindowsDesktop::WindowsDesktop()
 {
  h_event=Win64::CreateEventW(0,false,false,0);
 }

WindowsDesktop::~WindowsDesktop()
 {
  if( h_event ) Win64::CloseHandle(h_event);
 }

 // Desktop

WindowHost * WindowsDesktop::createHost()
 {
  return new WindowsHost();
 }

Point WindowsDesktop::getScreenSize()
 {
  return Point((Coord)Win64::GetSystemMetrics(Win64::SysMetric_DXScreen),(Coord)Win64::GetSystemMetrics(Win64::SysMetric_DYScreen));
 }

Pane WindowsDesktop::getMaxPane()
 {
  return GetWorkPane();
 }

bool WindowsDesktop::pump(unsigned lim)
 {
  for(Win64::Msg msg; lim && Win64::PeekMessageW(&msg,0,0,0,Win64::PeekMessage_Remove) ;lim--)
    {
     if( msg.message==Win64::WM_Quit )
       {
        TaskEventHost.add<MsgEvent>(msg.message,MsgEvent::Stop);

        return false;
       }

     Win64::TranslateMessage(&msg);
     Win64::DispatchMessageW(&msg);
    }

  return true;
 }

void WindowsDesktop::wait(TimeScope time_scope)
 {
  if( auto t=+time_scope.get() )
    {
     if( TestMsg() ) return;

     if( h_event )
       Win64::MsgWaitForMultipleObjects(1,&h_event,false,t,Win64::Wake_AllInput);
     else
       Win64::MsgWaitForMultipleObjects(0,0,false,t,Win64::Wake_AllInput);
    }
 }

void WindowsDesktop::interrupt()
 {
  if( h_event ) Win64::SetEvent(h_event);
 }

} // namespace Internal
} // namespace Video
} // namespace CCore

