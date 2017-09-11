/* InputUtils.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Applied
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_InputUtils_h
#define CCore_inc_InputUtils_h

#include <CCore/inc/TimeScope.h>
#include <CCore/inc/ReadConType.h>

namespace CCore {

/* functions */

#ifdef CCORE_UTF8

inline ulen SymbolLen(Utf8Code ch) { return ch.getLen(); }

inline ulen PutSymbol(char *ptr,ulen len,Utf8Code ch)
 {
  ch.getRange().copyTo(ptr+len);

  return len+ch.getLen();
 }

inline ulen PopSymbol(const char *ptr,ulen len) // len > 0
 {
  while( len && Utf8Ext(ptr[len-1]) ) len--;

  if( len ) len--;

  return len;
 }

#else

inline ulen SymbolLen(char ch) { Used(ch); return 1; }

inline ulen PutSymbol(char *ptr,ulen len,char ch)
 {
  ptr[len]=ch;

  return len+1;
 }

inline ulen PopSymbol(const char *ptr,ulen len) // len > 0
 {
  Used(ptr);

  return len-1;
 }

#endif

/* classes */

class ReadConBase;

/* class ReadConBase */

#ifdef CCORE_UTF8

class ReadConBase : NoCopy
 {
   static constexpr ulen Len = 32 ;

   char buf[Len];
   ulen off;
   ulen len;

  private:

   void shift();

   static Utf8Code GetCode(char ch,const char *ptr,unsigned len);

   virtual ulen read(char *ptr,ulen len,TimeScope time_scope)=0;

  public:

   ReadConBase();

   ~ReadConBase();

   // get

   bool try_get(Utf8Code &ret);

   Utf8Code get();

   bool get(MSec timeout,Utf8Code &ret);

   bool get(TimeScope time_scope,Utf8Code &ret);
 };

#else

class ReadConBase : NoCopy
 {
   static constexpr ulen Len = 32 ;

   char buf[Len];
   ulen off;
   ulen len;

  private:

   void shift();

   virtual ulen read(char *ptr,ulen len)=0;

   virtual ulen read(char *ptr,ulen len,MSec timeout)=0;

   virtual ulen read(char *ptr,ulen len,TimeScope time_scope)=0;

  public:

   ReadConBase();

   ~ReadConBase();

   // get

   bool try_get(char &ret);

   char get();

   bool get(MSec timeout,char &ret);

   bool get(TimeScope time_scope,char &ret);
 };

#endif

} // namespace CCore

#endif

