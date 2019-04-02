/* Desktop.cpp */
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

#include <CCore/inc/video/Desktop.h>

#include <CCore/inc/TextTools.h>

#include <CCore/inc/sys/SysEnv.h>

#include <CCore/inc/video/InternalUtils.h>
#include <CCore/inc/video/InternalDesktop.h>

namespace CCore {
namespace Video {

CmdDisplay StartDisplay()
 {
  Win64::StartupInfo info;

  info.cb=sizeof (info);

  Win64::GetStartupInfoW(&info);

  if( info.flags&Win64::StartupInfo_show_window )
    {
     switch( info.show_window )
       {
        case Win64::CmdShow_Hide          : return CmdDisplay_Normal;
        default:
        case Win64::CmdShow_Normal        : return CmdDisplay_Normal;
        case Win64::CmdShow_Minimized     : return CmdDisplay_Minimized;
        case Win64::CmdShow_Maximized     : return CmdDisplay_Maximized;
        case Win64::CmdShow_NoActivate    : return CmdDisplay_Normal;
        case Win64::CmdShow_Show          : return CmdDisplay_Normal;
        case Win64::CmdShow_Minimize      : return CmdDisplay_Minimized;
        case Win64::CmdShow_MinNoActive   : return CmdDisplay_Minimized;
        case Win64::CmdShow_NA            : return CmdDisplay_Normal;
        case Win64::CmdShow_Restore       : return CmdDisplay_Restore;
        case Win64::CmdShow_Default       : return CmdDisplay_Normal;
        case Win64::CmdShow_ForceMinimize : return CmdDisplay_Minimized;
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

     Win64::CharLowerW(buf);

     return Sys::Surrogate(buf[0],buf[1]);
    }
  else
    {
     Sys::WChar buf[2]={(Sys::WChar)ch,0};

     Win64::CharLowerW(buf);

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

  Win64::ShellExecuteW(0,verb,file_name,0,0,Win64::CmdShow_Show);
 }

/* class CharMapTable */

CharMapTable::CharMapTable()
 {
  AllChars( [this] (char ch)
                   {
                    Win64::wchar out;

                    int len=Win64::MultiByteToWideChar(Win64::CodePageActive,Win64::MultiBytePrecomposed|Win64::MultiByteUseGlyphChars,&ch,1,&out,1);

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


