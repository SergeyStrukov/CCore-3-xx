/* ArrayInsDel.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.60
//
//  Tag: Fundamental
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_array_ArrayInsDel_h
#define CCore_inc_array_ArrayInsDel_h

#include <CCore/inc/RangeDel.h>

#include <CCore/inc/algon/SimpleRotate.h>
#include <CCore/inc/algon/EuclidRotate.h>

#include <CCore/inc/array/ArrayBase.h>

namespace CCore {

/* guard functions */

void ArrayInsRangeGuardOutOfBorder(ulen ind,ulen len);

/* del functions */

template <class A>
bool ArrayCopyDel(A &array,ulen ind)
 {
  if( RangeCopyDel(Range(array),ind) )
    {
     array.shrink_one();

     return true;
    }

  return false;
 }

template <class A>
bool ArraySwapDel(A &array,ulen ind)
 {
  if( RangeSwapDel(Range(array),ind) )
    {
     array.shrink_one();

     return true;
    }

  return false;
 }

template <class A>
void ArrayCopyDel_guarded(A &array,ulen ind)
 {
  RangeCopyDel_guarded(Range(array),ind);

  array.shrink_one();
 }

template <class A>
void ArraySwapDel_guarded(A &array,ulen ind)
 {
  RangeSwapDel_guarded(Range(array),ind);

  array.shrink_one();
 }

/* del range functions */

template <class A>
ulen ArrayCopyDelRange(A &array,ulen ind,ulen count)
 {
  ulen delta=RangeCopyDel(Range(array),ind,count);

  array.shrink(delta);

  return delta;
 }

template <class A>
ulen ArraySwapDelRange(A &array,ulen ind,ulen count)
 {
  ulen delta=RangeSwapDel(Range(array),ind,count);

  array.shrink(delta);

  return delta;
 }

template <class A>
void ArrayCopyDelRange_guarded(A &array,ulen ind,ulen count)
 {
  RangeCopyDel_guarded(Range(array),ind,count);

  array.shrink(count);
 }

template <class A>
void ArraySwapDelRange_guarded(A &array,ulen ind,ulen count)
 {
  RangeSwapDel_guarded(Range(array),ind,count);

  array.shrink(count);
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
bool ArraySwapIns(A &array,ulen ind,SS && ... ss)
 {
  ulen len=array.getLen();
  bool ret=CapIndex(ind,len);

  array.append_fill( std::forward<SS>(ss)... );

  Algon::RangeRotateRight(Range(array).part(ind));

  return ret;
 }

template <class A,class ... SS>
bool ArrayCopyIns(A &array,ulen ind,SS && ... ss)
 {
  ulen len=array.getLen();
  bool ret=CapIndex(ind,len);

  array.append_fill( std::forward<SS>(ss)... );

  CopyRotateRight(Range(array).part(ind));

  return ret;
 }

template <class A,class ... SS>
auto ArraySwapIns_guarded(A &array,ulen ind,SS && ... ss)
 {
  ulen len=array.getLen();

  GuardIndex(ind,len+1);

  array.append_fill( std::forward<SS>(ss)... );

  auto r=Range(array).part(ind);

  Algon::RangeRotateRight(r);

  return r.ptr;
 }

template <class A,class ... SS>
auto ArrayCopyIns_guarded(A &array,ulen ind,SS && ... ss)
 {
  ulen len=array.getLen();

  GuardIndex(ind,len+1);

  array.append_fill( std::forward<SS>(ss)... );

  auto r=Range(array).part(ind);

  CopyRotateRight(r);

  return r.ptr;
 }

/* ins range prepare functions */

template <class A>
void ArrayInsRangeGuard(A &array,ulen ind)
 {
  ulen len=array.getLen();

  if( ind>len ) ArrayInsRangeGuardOutOfBorder(ind,len);
 }

template <class A>
void ArrayInsRangeFill(A &array,ulen ind)
 {
  ulen len=array.getLen();

  if( ind>len ) array.extend_default(ind-len);
 }

template <class A>
void ArrayInsRangeFill(A &array,ulen ind,ulen count)
 {
  ulen len=array.getLen();

  if( ind>len )
    {
     ind-=len;

     array.reserve(ind+count);
     array.extend_default(ind);
    }
 }

/* ins range functions */

template <class A>
auto ArrayInsRange_default(A &array,ulen ind,ulen count)
 {
  ulen len=array.getLen();

  if( ind<len )
    {
     array.extend_default(count);

     auto r=Range(array).part(ind);

     Algon::EuclidRotate_suffix(r,count);

     return r.prefix(count);
    }
  else
    {
     return array.extend_default(count);
    }
 }

template <class A,class ... SS>
auto ArrayInsRange_fill(A &array,ulen ind,ulen count,SS && ... ss)
 {
  ulen len=array.getLen();

  if( ind<len )
    {
     array.extend_fill(count, std::forward<SS>(ss)... );

     auto r=Range(array).part(ind);

     Algon::EuclidRotate_suffix(r,count);

     return r.prefix(count);
    }
  else
    {
     return array.extend_fill(count, std::forward<SS>(ss)... );
    }
 }

template <class A>
auto ArrayInsRange_copy(A &array,ulen ind,ulen count,decltype(array.getPtr_const()) src)
 {
  ulen len=array.getLen();

  if( ind<len )
    {
     array.extend_copy(count,src);

     auto r=Range(array).part(ind);

     Algon::EuclidRotate_suffix(r,count);

     return r.prefix(count);
    }
  else
    {
     return array.extend_copy(count,src);
    }
 }

template <class A>
auto ArrayInsRange_copy(A &array,ulen ind,PtrLen< Meta::PtrObjType<decltype(array.getPtr_const())> > src)
 {
  return ArrayInsRange_copy(array,ind,src.len,src.ptr);
 }

template <class A,class S>
auto ArrayInsRange_cast(A &array,ulen ind,ulen count,const S src[])
 {
  ulen len=array.getLen();

  if( ind<len )
    {
     array.extend_cast(count,src);

     auto r=Range(array).part(ind);

     Algon::EuclidRotate_suffix(r,count);

     return r.prefix(count);
    }
  else
    {
     return array.extend_cast(count,src);
    }
 }

template <class A,class S>
auto ArrayInsRange_cast(A &array,ulen ind,PtrLen<const S> src) { return ArrayInsRange_cast(array,ind,src.len,src.ptr); }

template <class A>
auto ArrayInsRange_swap(A &array,ulen ind,ulen count,decltype(array.getPtr()) objs)
 {
  ulen len=array.getLen();

  if( ind<len )
    {
     array.extend_swap(count,objs);

     auto r=Range(array).part(ind);

     Algon::EuclidRotate_suffix(r,count);

     return r.prefix(count);
    }
  else
    {
     return array.extend_swap(count,objs);
    }
 }

template <class A>
auto ArrayInsRange_swap(A &array,ulen ind,PtrLen< Meta::PtrObjType<decltype(array.getPtr())> > objs)
 {
  return ArrayInsRange_swap(array,ind,objs.len,objs.ptr);
 }

template <class A>
auto ArrayInsRange(A &array,ulen ind,ulen count,CreatorType< Meta::PtrObjType<decltype(array.getPtr())> > creator)
 {
  ulen len=array.getLen();

  if( ind<len )
    {
     array.extend(count,creator);

     auto r=Range(array).part(ind);

     Algon::EuclidRotate_suffix(r,count);

     return r.prefix(count);
    }
  else
    {
     return array.extend(count,creator);
    }
 }

template <class A>
auto ArrayInsRange(A &array,ulen ind,BuilderType< Meta::PtrObjType<decltype(array.getPtr())> > builder)
 {
  ulen len=array.getLen();

  if( ind<len )
    {
     ulen count=array.extend(builder).len;

     auto r=Range(array).part(ind);

     Algon::EuclidRotate_suffix(r,count);

     return r.prefix(count);
    }
  else
    {
     return array.extend(builder);
    }
 }

} // namespace CCore

#endif

