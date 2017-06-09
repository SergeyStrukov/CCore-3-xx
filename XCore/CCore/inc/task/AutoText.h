/* AutoText.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: XCore
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_task_AutoText_h
#define CCore_inc_task_AutoText_h

#include <CCore/inc/TextLabel.h>
#include <CCore/inc/task/FastMutex.h>

namespace CCore {

/* types */

using AutoTextNameType = const char *const ;

/* classes */

class AutoTextNumber;

template <AutoTextNameType &Name> class AutoText;

/* class AutoTextNumber */

class AutoTextNumber : FastMutexBase
 {
   unsigned next = 0 ;

  public:

   AutoTextNumber() {}

   unsigned get();
 };

/* class AutoText<AutoTextNameType &Name> */

template <AutoTextNameType &Name>
class AutoText
 {
   static AutoTextNumber Next;

  public:

   static const char * GetText() { return Name; }

   static unsigned GetNumber() { return Next.get(); }
 };

template <AutoTextNameType &Name>
AutoTextNumber AutoText<Name>::Next CCORE_INITPRI_0 ;

/* GetAutoText() */

template <AutoTextNameType &Name>
TextLabel GetAutoText() { return NumTextLabel<AutoText<Name> >(); }

} // namespace CCore

#endif


