/* Desktop.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Target/WIN64
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_video_Desktop_h
#define CCore_inc_video_Desktop_h

#include <CCore/inc/video/FrameWindow.h>
#include <CCore/inc/GenFile.h>
#include <CCore/inc/MakeString.h>
#include <CCore/inc/Cmp.h>

namespace CCore {
namespace Video {

/* types */

using DesktopColor = RawColor32 ;

using unicode = uint32 ;

/* functions */

void TickEntryEvent();

void TickLeaveEvent();

void AbortMsgBox(StrLen text);

void ErrorMsgBox(StrLen text,StrLen title);

CmdDisplay StartDisplay();

char ToLowerCase(char ch);

CmpResult NativeCmp(char a,char b);

void ShellVerb(StrLen verb,StrLen file_name);

/* classes */

class CharMapTable;

class SystemFontDirs;

class HomeDir;

class DefaultDesktopPtr;

/* class CharMapTable */

class CharMapTable : NoCopy
 {
   unicode table[256];

  public:

   CharMapTable();

   unicode operator () (char ch) const { return table[(uint8)ch]; }

   unicode operator () (signed char ch) const { return table[(uint8)ch]; }

   unicode operator () (unsigned char ch) const { return table[(uint8)ch]; }
 };

/* class SystemFontDirs */

class SystemFontDirs : NoCopy
 {
   MakeString<MaxPathLen> buf;
   StrLen dir;

  public:

   SystemFontDirs();

   PtrLen<const StrLen> getList() const { return Range(&dir,1); }
 };

/* class HomeDir */

class HomeDir : NoCopy
 {
   MakeString<MaxPathLen> buf;
   StrLen dir;

  public:

   HomeDir();

   StrLen get() const { return dir; }
 };

/* class DefaultDesktopPtr */

class DefaultDesktopPtr : NoCopy
 {
   Desktop *ptr;

  public:

   DefaultDesktopPtr();

   operator Desktop * () const { return ptr; }

   Desktop * operator -> () const { return ptr; }
 };

/* global DefaultDesktop */

extern DefaultDesktopPtr DefaultDesktop;

} // namespace Video
} // namespace CCore

#endif


