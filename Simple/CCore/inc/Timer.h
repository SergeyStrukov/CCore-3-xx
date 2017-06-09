/* Timer.h */
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

#ifndef CCore_inc_Timer_h
#define CCore_inc_Timer_h

#include <CCore/inc/Gadget.h>

#include <CCore/inc/sys/SysTime.h>

namespace CCore {

/* classes */

template <UIntType T,T Time()> class Timer;

template <UIntType T,T Time()> class DiffTimer;

/* class Timer<T,T Time()> */

template <UIntType T,T Time()>
class Timer
 {
   T start;

  public:

   Timer() { reset(); }

   void reset() { start=Time(); }

   using ValueType = T ;

   T get() const { return Time()-start; }

   bool less(T lim) const { return get()<lim; }

   bool exceed(T lim) const { return get()>=lim; }

   void shift(T delta) { start+=delta; }

   static T Get() { return Time(); }
 };

/* class DiffTimer<T,T Time()> */

template <UIntType T,T Time()>
class DiffTimer
 {
   T prev;

  public:

   DiffTimer() { reset(); }

   void reset() { prev=Time(); }

   using ValueType = T ;

   T get() { return Diff(prev,Time()); }
 };

/* timer types */

using MSecTimer = Timer<Sys::MSecTimeType,Sys::GetMSecTime> ;

using SecTimer = Timer<Sys::SecTimeType,Sys::GetSecTime> ;

using ClockTimer = Timer<Sys::ClockTimeType,Sys::GetClockTime> ;

using MSecDiffTimer = DiffTimer<Sys::MSecTimeType,Sys::GetMSecTime> ;

using SecDiffTimer = DiffTimer<Sys::SecTimeType,Sys::GetSecTime> ;

using ClockDiffTimer = DiffTimer<Sys::ClockTimeType,Sys::GetClockTime> ;

} // namespace CCore

#endif


