/* ReadCon.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.01
//
//  Tag: XCore
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

#include <CCore/inc/sys/SysCon.h>

#include <CCore/inc/Task.h>
#include <CCore/inc/Fifo.h>

namespace CCore {

/* classes */

class ReadCon;

/* class ReadCon */

class ReadCon : public Funchor_nocopy , FastMutexBase
 {
   static constexpr ulen FifoLen = 128 ;

   MSec timeout;

   FifoBuf<ReadConCode,FifoLen> fifo;

   Sem sem;

   Sys::OwnConInput own;

  private:

   Sys::ConInputResult input_any(ReadConCode ch);

   Sys::ConInputFunction function_input() { return FunctionOf(this,&ReadCon::input_any); }

   bool do_get(ReadConCode &ret);

  public:

   explicit ReadCon(MSec timeout=DefaultTimeout);

   ~ReadCon();

   // get

   ReadConCode get();

   bool get(MSec timeout,ReadConCode &ret);

   bool get(TimeScope time_scope,ReadConCode &ret);

   // put

   void put(char ch) { put(Single(ch)); }

   void put(const char *str,ulen len) { put(Range(str,len)); }

   void put(StrLen str);

#ifdef CCORE_UTF8

   void put(ReadConCode ch) { put(SymbolRange(ch)); }

#endif
 };

} // namespace CCore

#endif


