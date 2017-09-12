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

#include <CCore/inc/ReadConType.h>

namespace CCore {

/* functions */

#ifdef CCORE_UTF8

inline constexpr unsigned MaxSymbolLen = 4 ;

inline int ToChar(Utf8Code ch) { return (ch.getLen()==1)?ch[0]:(-1); }

inline ulen SymbolLen(Utf8Code ch) { return ch.getLen(); }

inline StrLen SymbolRange(const Utf8Code &ch) { return ch.getRange(); }

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

inline constexpr unsigned MaxSymbolLen = 1 ;

inline ulen PopSymbol(const char *ptr,ulen len) // len > 0
 {
  Used(ptr);

  return len-1;
 }

#endif

inline int ToChar(char ch) { return ch; }

inline ulen SymbolLen(char ch) { Used(ch); return 1; }

inline StrLen SymbolRange(const char &ch) { return Single(ch); }

inline ulen PutSymbol(char *ptr,ulen len,char ch)
 {
  ptr[len]=ch;

  return len+1;
 }

/* classes */

class ReadConBase;

class SymbolParser;

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

/* class SymbolParser */

#ifdef CCORE_UTF8

class SymbolParser : NoCopy
 {
   char buf[4];
   unsigned len;
   unsigned symlen = 0 ;

  public:

   SymbolParser() { reset(); }

   void reset() { len=0; }

   bool feed(StrLen &text);

   Utf8Code get()
    {
     len=0;

     return Utf8Code(buf,symlen);
    }
 };

#else

class SymbolParser : NoCopy
 {
   char buf;
   unsigned len;

  public:

   SymbolParser() { reset(); }

   void reset() { len=0; }

   bool feed(StrLen &text);

   char get()
    {
     len=0;

     return buf;
    }
 };

#endif

} // namespace CCore

#endif

