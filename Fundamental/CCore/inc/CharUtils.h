/* CharUtils.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Fundamental
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_CharUtils_h
#define CCore_inc_CharUtils_h

#include <CCore/inc/Printf.h>
#include <CCore/inc/Scanf.h>
#include <CCore/inc/Symbol.h>

namespace CCore {

/* classes */

struct FillCharBuf;

class PrintCharBuf;

#ifdef CCORE_UTF8

class ScanCharString;

#endif

/* struct FillCharBuf */

struct FillCharBuf
 {
  ulen len;
  bool overflow;

  FillCharBuf(PtrLen<Char> out,StrLen text);
 };

/* class PrintCharBuf */

#ifdef CCORE_UTF8

class PrintCharBuf : public PrintBase
 {
   PtrLen<Char> start;
   PtrLen<Char> out;
   bool overflow = false ;

   char buf[32];
   ulen off = 0 ;
   ulen len = 0 ;

  private:

   void shift();

   void push(Char ch);

   void push();

   virtual PtrLen<char> do_provide(ulen hint_len);

   virtual void do_flush(char *ptr,ulen len);

  public:

   explicit PrintCharBuf(PtrLen<Char> out);

   ~PrintCharBuf();

   PtrLen<const Char> close(bool guard_overflow=true);
 };

#else

class PrintCharBuf : public PrintBase
 {
   PtrLen<Char> start;
   PtrLen<Char> out;

  private:

   virtual PtrLen<char> do_provide(ulen hint_len);

   virtual void do_flush(char *ptr,ulen len);

  public:

   explicit PrintCharBuf(PtrLen<Char> out);

   ~PrintCharBuf();

   PtrLen<const Char> close(bool guard_overflow=true);
 };

#endif

/* class ScanCharString */

#ifdef CCORE_UTF8

class ScanCharString : public ScanBase
 {
   PtrLen<const Char> str;

   char buf[32];

  private:

   static ulen Put(PtrLen<char> out,PtrLen<const Char> &str);

   virtual PtrLen<const char> underflow();

  public:

   explicit ScanCharString(PtrLen<const Char> str);

   ~ScanCharString();
 };

#else

using ScanCharString = ScanString ;

#endif

} // namespace CCore

#endif

