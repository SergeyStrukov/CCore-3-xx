/* Desktop.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Target/WIN32utf8
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/video/Desktop.h>

#include <CCore/inc/TextTools.h>

#include <CCore/inc/sys/SysEnv.h>

#include <CCore/inc/video/InternalUtils.h>
#include <CCore/inc/video/InternalDesktop.h>

namespace CCore {
namespace Video {

/* functions */

CmdDisplay StartDisplay()
 {
  Win32::StartupInfo info;

  info.cb=sizeof (info);

  Win32::GetStartupInfoW(&info);

  if( info.flags&Win32::StartupInfo_show_window )
    {
     switch( info.show_window )
       {
        case Win32::CmdShow_Hide          : return CmdDisplay_Normal;
        default:
        case Win32::CmdShow_Normal        : return CmdDisplay_Normal;
        case Win32::CmdShow_Minimized     : return CmdDisplay_Minimized;
        case Win32::CmdShow_Maximized     : return CmdDisplay_Maximized;
        case Win32::CmdShow_NoActivate    : return CmdDisplay_Normal;
        case Win32::CmdShow_Show          : return CmdDisplay_Normal;
        case Win32::CmdShow_Minimize      : return CmdDisplay_Minimized;
        case Win32::CmdShow_MinNoActive   : return CmdDisplay_Minimized;
        case Win32::CmdShow_NA            : return CmdDisplay_Normal;
        case Win32::CmdShow_Restore       : return CmdDisplay_Restore;
        case Win32::CmdShow_Default       : return CmdDisplay_Normal;
        case Win32::CmdShow_ForceMinimize : return CmdDisplay_Minimized;
       }
    }

  return CmdDisplay_Normal;
 }

Char ToLowerCase(Char ch)
 {
  if( Sys::IsSurrogate(ch) )
    {
     Sys::SurrogateCouple couple(ch);
     Sys::WChar buf[3]={couple.hi,couple.lo,0};

     Win32::CharLowerW(buf);

     return Sys::Surrogate(buf[0],buf[1]);
    }
  else
    {
     Sys::WChar buf[2]={(Sys::WChar)ch,0};

     Win32::CharLowerW(buf);

     return buf[0];
    }
 }

void ShellVerb(StrLen verb_,StrLen file_name_)
 {
  Sys::WCharString<> verb(verb_);
  Sys::WCharString<MaxPathLen> file_name(file_name_);

  if( auto error=verb.getError() )
    {
     Printf(Exception,"CCore::Video::ShellVerb(verb,...) : #;",error);
    }

  if( auto error=file_name.getError() )
    {
     Printf(Exception,"CCore::Video::ShellVerb(...,file_name) : #;",error);
    }

  Win32::ShellExecuteW(0,verb,file_name,0,0,Win32::CmdShow_Show);
 }

/* class CharMapTable */

CharMapTable::CharMapTable()
 {
  AllChars( [this] (char ch)
                   {
                    Win32::wchar out;

                    int len=Win32::MultiByteToWideChar(Win32::CodePageActive,Win32::MultiBytePrecomposed|Win32::MultiByteUseGlyphChars,&ch,1,&out,1);

                    if( len!=1 )
                      {
                       table[Index(ch)]=0;
                      }
                    else
                      {
                       table[Index(ch)]=out;
                      }

                   } );
 }

/* class SystemFontDirs */

SystemFontDirs::SystemFontDirs()
 {
  Sys::GetEnv<32,MaxPathLen> data("WINDIR");

  if( auto error=data.getError() )
    {
     Printf(Exception,"CCore::Video::SystemFontDirs::SystemFontDirs() : #; , WINDIR",error);
    }

  ulen len=data.full(Range(buf));

  if( len==MaxULen )
    {
     Printf(Exception,"CCore::Video::SystemFontDirs::SystemFontDirs() : too long file name");
    }

  StrLen file="/Fonts"_c;

  if( file.len>DimOf(buf)-len )
    {
     Printf(Exception,"CCore::Video::SystemFontDirs::SystemFontDirs() : too long file name");
    }

  file.copyTo(buf+len);

  dir=Range(buf,len+file.len);
 }

/* class HomeDir */

HomeDir::HomeDir()
 {
  Sys::GetEnv<32,MaxPathLen> data("LOCALAPPDATA");

  if( auto error=data.getError() )
    {
     Printf(Exception,"CCore::Video::HomeDir::HomeDir() : #; , LOCALAPPDATA",error);
    }

  ulen len=data.full(Range(buf));

  if( len==MaxULen )
    {
     Printf(Exception,"CCore::Video::HomeDir::HomeDir() : too long file name");
    }

  dir=Range(buf,len);
 }

/* functions */

void TickEntryEvent()
 {
  TaskEventHost.add<Internal::TickEvent>(Internal::TickEvent::Entry);
 }

void TickLeaveEvent()
 {
  TaskEventHost.add<Internal::TickEvent>(Internal::TickEvent::Leave);
 }

void AbortMsgBox(StrLen text)
 {
  Internal::WindowsHost::AbortMsgBox(text);
 }

void ErrorMsgBox(StrLen text,StrLen title)
 {
  Internal::WindowsHost::ErrorMsgBox(text,title);
 }

void SetAppIcon(Picture pict)
 {
  Internal::WindowsHost::SetAppIcon(pict);
 }

/* global DefaultDesktop */

static Internal::WindowsDesktop DesktopObject CCORE_INITPRI_3 ;

DefaultDesktopPtr::DefaultDesktopPtr()
 {
  ptr=&DesktopObject;
 }

DefaultDesktopPtr DefaultDesktop CCORE_INITPRI_3 ;

} // namespace Video
} // namespace CCore


