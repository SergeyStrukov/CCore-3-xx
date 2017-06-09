/* MSec.h */
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
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_gadget_MSec_h
#define CCore_inc_gadget_MSec_h

#include <CCore/inc/gadget/Replace.h>
#include <CCore/inc/gadget/Nothing.h>
#include <CCore/inc/gadget/Classification.h>

namespace CCore {

/* functions */

template <UIntType A,UIntType B>
constexpr unsigned MSecAdd(A a,B b)
 {
  return ( a <= unsigned(-1) && b <= unsigned(-1)-a ) ? unsigned(a+b) : unsigned(-1) ;
 }

template <UIntType A,UIntType B>
constexpr unsigned MSecMul(A a,B b)
 {
  return ( !b || a <= unsigned(-1)/b ) ? unsigned(a*b) : unsigned(-1) ;
 }

/* classes */

struct MSecUnit;

struct MSec;

/* struct MSecUnit */

struct MSecUnit
 {
  unsigned scale;

  // constructors

  explicit constexpr MSecUnit(unsigned scale_) : scale(scale_) {}

  // methods

  constexpr unsigned operator () (UIntType time) const { return MSecMul(time,scale); }
 };

/* consts */

inline constexpr MSecUnit tuMSec(1);

inline constexpr MSecUnit tuSec(1000);

inline constexpr MSecUnit tuMin(60*1000);

inline constexpr MSecUnit tuHour(60*60*1000);

/* struct MSec */

struct MSec
 {
  unsigned time;

  // constructors

  constexpr MSec(NothingType) : time(0) {}

  explicit constexpr MSec(unsigned time_) : time(time_) {}

  constexpr MSec(UIntType time_,MSecUnit unit) : time(unit(time_)) {}

  // methods

  constexpr unsigned operator + () const { return time; }

  constexpr bool operator ! () const { return !time; }

  MSec cap(MSec lim) { Replace_min(time,lim.time); return *this; }
 };

inline constexpr MSec operator + (MSec a,MSec b) { return MSec(MSecAdd(a.time,b.time)); }

inline constexpr MSec operator * (unsigned a,MSec b) { return MSec(MSecMul(b.time,a));  }

/* unit functions */

inline constexpr MSec operator "" _msec (unsigned long long time) { return MSec(time,tuMSec); }

inline constexpr MSec operator "" _sec  (unsigned long long time) { return MSec(time,tuSec); }

inline constexpr MSec operator "" _min  (unsigned long long time) { return MSec(time,tuMin); }

inline constexpr MSec operator "" _hour (unsigned long long time) { return MSec(time,tuHour); }

} // namespace CCore

#endif


