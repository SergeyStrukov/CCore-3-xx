/* FrameWindow.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Desktop
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/video/FrameWindow.h>

#include <CCore/inc/StrToChar.h>

namespace CCore {
namespace Video {

/* enum CmdDisplay */

const char * GetTextDesc(CmdDisplay cmd_display)
 {
  switch( cmd_display )
    {
     case CmdDisplay_Normal    : return "Normal";
     case CmdDisplay_Minimized : return "Minimized";
     case CmdDisplay_Maximized : return "Maximized";
     case CmdDisplay_Restore   : return "Restore";

     default: return "???";
    }
 }

/* struct CopyFunction */

void CopyFunction::copy(PtrLen<const Char> text)
 {
  Replace_min(buf.len,text.len);

  buf.copy(text.ptr);
 }

void CopyFunction::cutEOL()
 {
  if( buf.len>=2 )
    {
     if( buf.back(2)=='\r' && buf.back(1)=='\n' )
       {
        buf.len-=2;

        return;
       }
    }

  if( +buf )
    {
     char ch=buf.back(1);

     if( ch=='\r' || ch=='\n' ) buf.len--;
    }
 }

/* class InterruptFunction */

void InterruptFunction::Call(Handle handle)
 {
  Desktop *desktop=(Desktop *)handle.ptr;

  desktop->interrupt();
 }

/* class WindowHost */

#ifdef CCORE_UTF8

void WindowHost::textToClipboard(StrLen text_)
 {
  StrToChar text(text_);

  textToClipboard(text);
 }

void WindowHost::textFromClipboard(Function<void (StrLen)> func)
 {
  auto proxy=ToFunction<void (PtrLen<const Char>)>( [func] (PtrLen<const Char> text_) { CharToStr text(text_); func(text); } );

  textFromClipboard( proxy.function() );
 }

#endif


} // namespace Video
} // namespace CCore


