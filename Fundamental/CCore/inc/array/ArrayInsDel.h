/* ArrayInsDel.h */
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
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_array_ArrayInsDel_h
#define CCore_inc_array_ArrayInsDel_h

#include <CCore/inc/RangeDel.h>

#include <CCore/inc/algon/SimpleRotate.h>

namespace CCore {

/* del functions */

template <class A>
bool ArrayCopyDel(A &a,ulen ind)
 {
  if( RangeCopyDel(Range(a),ind) )
    {
     a.shrink_one();

     return true;
    }

  return false;
 }

template <class A>
bool ArraySwapDel(A &a,ulen ind)
 {
  if( RangeSwapDel(Range(a),ind) )
    {
     a.shrink_one();

     return true;
    }

  return false;
 }

template <class A>
void ArrayCopyDel_guarded(A &a,ulen ind)
 {
  RangeCopyDel_guarded(Range(a),ind);

  a.shrink_one();
 }

template <class A>
void ArraySwapDel_guarded(A &a,ulen ind)
 {
  RangeSwapDel_guarded(Range(a),ind);

  a.shrink_one();
 }

/* CopyRotateRight() */

template <NothrowCopyableType T>
void CopyRotateRight(PtrLen<T> range) // assume +range
 {
  auto r=RangeReverse(range);

  T temp=r[0];

  for(; r.len>1 ;++r) r[0]=r[1];

  r[0]=temp;
 }

/* CapIndex() */

inline bool CapIndex(ulen &ind,ulen cap)
 {
  if( ind>cap )
    {
     ind=cap;

     return false;
    }

  return true;
 }

/* ins functions */

template <class A,class ... SS>
bool ArraySwapIns(A &a,ulen ind,SS && ... ss)
 {
  ulen len=a.getLen();
  bool ret=CapIndex(ind,len);

  a.append_fill( std::forward<SS>(ss)... );

  Algon::RangeRotateRight(Range(a).part(ind));

  return ret;
 }

template <class A,class ... SS>
bool ArrayCopyIns(A &a,ulen ind,SS && ... ss)
 {
  ulen len=a.getLen();
  bool ret=CapIndex(ind,len);

  a.append_fill( std::forward<SS>(ss)... );

  CopyRotateRight(Range(a).part(ind));

  return ret;
 }

template <class A,class ... SS>
auto ArraySwapIns_guarded(A &a,ulen ind,SS && ... ss)
 {
  ulen len=a.getLen();

  GuardIndex(ind,len+1);

  a.append_fill( std::forward<SS>(ss)... );

  auto r=Range(a).part(ind);

  Algon::RangeRotateRight(r);

  return r.ptr;
 }

template <class A,class ... SS>
auto ArrayCopyIns_guarded(A &a,ulen ind,SS && ... ss)
 {
  ulen len=a.getLen();

  GuardIndex(ind,len+1);

  a.append_fill( std::forward<SS>(ss)... );

  auto r=Range(a).part(ind);

  CopyRotateRight(r);

  return r.ptr;
 }

} // namespace CCore

#endif

