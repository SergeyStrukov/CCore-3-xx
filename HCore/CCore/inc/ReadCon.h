/* ReadCon.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: HCore Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_ReadCon_h
#define CCore_inc_ReadCon_h

#include <CCore/inc/TimeScope.h>

#include <CCore/inc/sys/SysCon.h>

namespace CCore {

/* classes */

class ReadCon;

/* class ReadCon */

class ReadCon : NoCopy
 {
   static constexpr ulen Len = 32 ;

   Sys::ConRead con;

   char buf[Len];
   char *cur;
   char *lim;

  public:

   ReadCon();

   ~ReadCon();

   // get

   char get();

   bool get(MSec timeout,char &ret);

   bool get(TimeScope time_scope,char &ret);

   // put

   void put(char ch) { put(&ch,1); }

   void put(const char *str,ulen len) { put(Range(str,len)); }

   void put(StrLen str) { Sys::ConWrite(str); }
 };

} // namespace CCore

#endif


