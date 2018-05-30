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

#include <CCore/inc/Exception.h>

#include <CCore/inc/video/InternalUtils.h>
#include <CCore/inc/video/InternalDesktop.h>

#include <CCore/inc/sys/SysUtf8.h>

#include <cstdlib>

namespace CCore {
namespace Video {

CmdDisplay StartDisplay()
 {
  Win64::StartupInfo info;

  info.cb=sizeof (info);

  Win64::GetStartupInfoA(&info);

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
  MakeString<TextBufLen> verb;
  MakeString<MaxPathLen+1> file_name;

  verb.add(verb_,Null);
  file_name.add(file_name_,Null);

  if( !verb || !file_name )
    {
     Printf(Exception,"CCore::Video::ShellVerb(...) : too long arguments");
    }

  Win64::ShellExecuteA(0,verb.getZStr(),file_name.getZStr(),0,0,Win64::CmdShow_Show);
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
  if( const char *root=std::getenv("WINDIR") )
    {
     if( +buf.add(root,"/Fonts") )
       {
        dir=buf.get();
       }
     else
       {
        Printf(Exception,"CCore::Video::SystemFontDirs::SystemFontDirs() : too long file name");
       }
    }
  else
    {
     Printf(Exception,"CCore::Video::SystemFontDirs::SystemFontDirs() : no WINDIR");
    }
 }

/* class HomeDir */

HomeDir::HomeDir()
 {
  if( const char *data=std::getenv("LOCALAPPDATA") )
    {
     if( +buf.add(data) )
       {
        dir=buf.get();
       }
     else
       {
        Printf(Exception,"CCore::Video::HomeDir::HomeDir() : too long file name");
       }
    }
  else
    {
     Printf(Exception,"CCore::Video::HomeDir::HomeDir() : no LOCALAPPDATA");
    }
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


