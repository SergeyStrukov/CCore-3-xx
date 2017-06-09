/* ToMemBase.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Applied Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/ToMemBase.h>

#include <CCore/inc/MemBase.h>

namespace CCore {

/* class ToMemBase */

uint8 * ToMemBase::alloc(ulen len_)
 {
  ptr=static_cast<uint8 *>(MemAlloc(len_));
  len=len_;

  return ptr;
 }

ToMemBase::ToMemBase() noexcept
 {
  ptr=0;
  len=0;
 }

ToMemBase::~ToMemBase()
 {
  MemFree(ptr);
 }

ToMemBase & ToMemBase::operator = (ToMemBase &&obj) noexcept
 {
  if( this!=&obj )
    {
     uint8 *todel=Replace(ptr,Replace_null(obj.ptr));

     len=Replace_null(obj.len);

     MemFree(todel);
    }

  return *this;
 }

} // namespace CCore


