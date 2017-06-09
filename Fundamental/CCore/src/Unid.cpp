/* Unid.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Fundamental Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/Unid.h>

#include <CCore/inc/Abort.h>

namespace CCore {

/* class UnidRegister */

ulen UnidRegister::find_or_add(const Unid &unid) noexcept
try
  {
   Mutex::Lock lock(mutex);

   auto result=map.find_or_add(unid,next);

   if( result.new_flag ) next++;

   return *result.obj;
  }
catch(...)
  {
   Abort("Fatal error: cannot allocate Unid mapping");

   return 0;
  }

UnidRegister::UnidRegister()
 : mutex("UnidRegister")
 {
 }

UnidRegister::~UnidRegister()
 {
 }

} // namespace CCore


