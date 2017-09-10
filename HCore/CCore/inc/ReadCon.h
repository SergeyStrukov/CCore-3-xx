/* ReadCon.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: HCore Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_ReadCon_h
#define CCore_inc_ReadCon_h

#include <CCore/inc/TimeScope.h>
#include <CCore/inc/ReadConType.h>

#include <CCore/inc/sys/SysCon.h>

#ifdef CCORE_UTF8
# include <CCore/inc/Utf8.h>
#endif

namespace CCore {

/* classes */

class ReadCon;

/* class ReadCon */

#ifdef CCORE_UTF8

class ReadCon : NoCopy
 {
   static constexpr ulen Len = 32 ;

   Sys::ConRead con;

   char buf[Len];
   ulen off;
   ulen len;

  private:

   void shift();

   static Utf8Code GetCode(char ch,const char *ptr,unsigned len);

  public:

   ReadCon();

   ~ReadCon();

   // get

   bool try_get(Utf8Code &ret);

   Utf8Code get();

   bool get(MSec timeout,Utf8Code &ret);

   bool get(TimeScope time_scope,Utf8Code &ret);

   // put

   void put(char ch) { put(&ch,1); }

   void put(const char *str,ulen len) { put(Range(str,len)); }

   void put(StrLen str) { Sys::ConWrite(str); }

   void put(Utf8Code code) { put(code.getRange()); }
 };

#else

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

#endif

} // namespace CCore

#endif


