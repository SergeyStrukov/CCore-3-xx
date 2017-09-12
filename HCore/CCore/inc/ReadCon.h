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

#include <CCore/inc/InputUtils.h>

#include <CCore/inc/sys/SysCon.h>

namespace CCore {

/* classes */

class ReadCon;

/* class ReadCon */

class ReadCon : public ReadConBase
 {
   Sys::ConRead con;

  private:

   virtual ulen read(char *ptr,ulen len);

   virtual ulen read(char *ptr,ulen len,MSec timeout);

   virtual ulen read(char *ptr,ulen len,TimeScope time_scope);

  public:

   ReadCon();

   ~ReadCon();

   // put

   void put(OneOfTypes<char,ReadConCode> ch) { put(SymbolRange(ch)); }

   void put(const char *str,ulen len) { put(Range(str,len)); }

   void put(StrLen str) { Sys::ConWrite(str); }
 };

} // namespace CCore

#endif


