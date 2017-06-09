/* ListCursor.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: Fundamental
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_ListCursor_h
#define CCore_inc_ListCursor_h

#include <CCore/inc/Gadget.h>

namespace CCore {

/* classes */

template <class Cur,class T> struct ListCursor;

template <class Cur,class T> struct ListCountCursor;

/* struct ListCursor<Cur,T> */

template <class Cur,class T>
struct ListCursor
 {
  Cur cur;

  ListCursor() noexcept {}

  ListCursor(const Cur &cur_) : cur(cur_) {}

  // object ptr

  void * operator + () const { return +cur; }

  bool operator ! () const { return !cur; }

  T * getPtr() const { return &cur->obj; }

  T & operator * () const { return cur->obj; }

  T * operator -> () const { return &cur->obj; }

  // cursor

  void operator ++ () { ++cur; }

  void operator -- () { --cur; }
 };

/* struct ListCountCursor<Cur,T> */

template <class Cur,class T>
struct ListCountCursor
 {
  Cur cur;
  ulen count;

  ListCountCursor() noexcept : count(0) {}

  ListCountCursor(const Cur &cur_,ulen count_) : cur(cur_),count(count_) {}

  // object ptr

  ulen operator + () const { return count; }

  bool operator ! () const { return !count; }

  T * getPtr() const { return &cur->obj; }

  T & operator * () const { return cur->obj; }

  T * operator -> () const { return &cur->obj; }

  // cursor

  void operator ++ () { ++cur; count--; }

  bool operator != (ulen end_count) const { return count!=end_count; }
 };

} // namespace CCore

#endif

