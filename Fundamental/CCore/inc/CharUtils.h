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
#include <CCore/inc/Symbol.h>

namespace CCore {

#ifdef CCORE_UTF8

/* classes */

struct FillCharBuf;

class PrintCharBuf;

/* struct FillCharBuf */

struct FillCharBuf
 {
  ulen len;
  bool overflow;

  FillCharBuf(PtrLen<Char> out,StrLen text);
 };

/* class PrintCharBuf */

class PrintCharBuf : public PrintBase
 {
   PtrLen<Char> start;
   PtrLen<Char> out;
   bool overflow = false ;

   char buf[32];
   ulen off = 0 ;
   ulen len = 0 ;

  public:

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

#endif

} // namespace CCore

#endif

