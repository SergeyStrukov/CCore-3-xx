/* MemAllocGuard.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: Simple Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_MemAllocGuard_h
#define CCore_inc_MemAllocGuard_h

#include <CCore/inc/MemBase.h>

namespace CCore {

/* concept MemAllocAlgo<Algo> */

template <class Algo>
concept bool MemAllocAlgo = requires(ulen len,void *mem)
 {
  { Algo::MemAlloc(len) } -> void * ;

  Algo::MemFree(mem);
 } ;

/* classes */

class MemAllocGuard;

template <MemAllocAlgo Algo> class MemAllocGuardOf;

/* class MemAllocGuard */

class MemAllocGuard : NoCopy
 {
   void *mem;

  public:

   explicit MemAllocGuard(ulen len)
    {
     mem=MemAlloc(len);
    }

   MemAllocGuard(ulen count,ulen size_of,ulen extra=0)
    {
     mem=MemAlloc(LenOf(count,size_of,extra));
    }

   ~MemAllocGuard()
    {
     if( mem ) MemFree(mem);
    }

   operator void * () const { return mem; }

   void * disarm() { return Replace_null(mem); }
 };

/* class MemAllocGuardOf<Algo> */

template <MemAllocAlgo Algo>
class MemAllocGuardOf : NoCopy
 {
   void *mem;

  public:

   explicit MemAllocGuardOf(ulen len)
    {
     mem=Algo::MemAlloc(len);
    }

   MemAllocGuardOf(ulen count,ulen size_of,ulen extra=0)
    {
     mem=Algo::MemAlloc(LenOf(count,size_of,extra));
    }

   ~MemAllocGuardOf()
    {
     if( mem ) Algo::MemFree(mem);
    }

   operator void * () const { return mem; }

   void * disarm() { return Replace_null(mem); }
 };

} // namespace CCore

#endif


