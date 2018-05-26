/* Desktop.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Target/LIN64utf8
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

#include <CCore/inc/video/InternalDesktop.h>

#include <CCore/inc/Exception.h>

#include <cctype>
#include <cstring>
#include <cstdlib>
#include <clocale>
#include <cwctype>

namespace CCore {
namespace Video {

/* functions */

CmdDisplay StartDisplay()
 {
  return CmdDisplay_Normal;
 }

Char ToLowerCase(Char ch) // TODO
 {
  return std::towlower(ch);
 }

void ShellVerb(StrLen verb,StrLen file_name)
 {
  if( !verb.equal("open"_c) )
    {
     Printf(Exception,"CCore::Video::ShellVerb(#.q;,...) : unknown verb",verb);
    }

  char buf[MaxPathLen+20];
  PrintBuf out(Range(buf));

  Printf(out,"xdg-open #;",file_name);

  out.guardOverflow();

  std::system(out.closeZStr());
 }

/* class CharMapTable */

CharMapTable::CharMapTable() // TODO
 {
  AllChars( [this] (char ch)
                   {
                    char in[2]={ch,0};
                    wchar_t out[2];

                    auto len=std::mbstowcs(out,in,2);

                    if( len!=1 )
                      {
                       table[Index(ch)]=0;
                      }
                    else
                      {
                       table[Index(ch)]=out[0];
                      }

                   } );
 }

/* class SystemFontDirs */

SystemFontDirs::SystemFontDirs()
 {
  // 0

  buf[0].add("/usr/share/fonts");

  dir[0]=buf[0].get();

  // 1

  buf[1].add("/usr/local/share/fonts");

  dir[1]=buf[1].get();

  // 2

  if( const char *home=std::getenv("HOME") )
    {
     if( +buf[2].add(home,"/fonts") )
       {
        dir[2]=buf[2].get();
       }
     else
       {
        Printf(Exception,"CCore::Video::SystemFontDirs::SystemFontDirs() : too long file name");
       }
    }
  else
    {
     Printf(Exception,"CCore::Video::SystemFontDirs::SystemFontDirs() : no HOME");
    }
 }

/* class HomeDir */

HomeDir::HomeDir()
 {
  if( const char *home=std::getenv("HOME") )
    {
     if( +buf.add(home) )
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
     Printf(Exception,"CCore::Video::HomeDir::HomeDir() : no HOME");
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
  Internal::X11Host::AbortMsgBox(text);
 }

void ErrorMsgBox(StrLen text,StrLen title)
 {
  Internal::X11Host::ErrorMsgBox(text,title);
 }

void SetAppIcon(Picture pict)
 {
  Internal::HiddenWindow.setIcon(pict);
 }

/* global DefaultDesktop */

DefaultDesktopPtr::DefaultDesktopPtr()
 {
  ptr=&Internal::DesktopObject;
 }

DefaultDesktopPtr DefaultDesktop CCORE_INITPRI_3 ;

} // namespace Video
} // namespace CCore


