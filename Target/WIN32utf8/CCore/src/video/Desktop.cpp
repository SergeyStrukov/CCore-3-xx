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

#include <CCore/inc/Exception.h>

#include <CCore/inc/video/InternalDesktop.h>

#include <cstdlib>

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
  return (unsigned char)(unsigned)Win32::CharLowerA((char *)(unsigned)(unsigned char)ch);
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

  Win32::ShellExecuteA(0,verb.getZStr(),file_name.getZStr(),0,0,Win32::CmdShow_Show);
 }

/* class CharMapTable */

CharMapTable::CharMapTable()
 {
  bool once=true;

  for(unsigned ind=0; ind<256u ;ind++)
    {
     char ch=char(ind);
     Win32::unicode_t out;

     int len=Win32::MultiByteToWideChar(Win32::CodePageActive,Win32::MultiBytePrecomposed|Win32::MultiByteUseGlyphChars,&ch,1,&out,1);

     if( len!=1 )
       {
        table[ind]=0;

        if( Replace_null(once) )
          Printf(NoException,"CCore::Video::CharMapTable::CharMapTable() : not a single byte code page");
       }
     else
       {
        table[ind]=out;
       }
    }
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


