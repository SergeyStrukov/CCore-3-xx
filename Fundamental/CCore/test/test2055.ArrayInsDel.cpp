/* test2055.ArrayInsDel.cpp */
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

#include <CCore/test/test.h>

#include <CCore/inc/Array.h>
#include <CCore/inc/PrintSet.h>

#include <CCore/inc/algon/EuclidRotate.h>

namespace App {

namespace Private_2055 {

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

#if 0

PtrLen<T> extend_copy(ulen delta_len,const T src[]);

PtrLen<T> extend_copy(PtrLen<const T> src);

template <class S>
PtrLen<T> extend_cast(ulen delta_len,const S src[]);

template <class S>
PtrLen<T> extend_cast(PtrLen<const S> src);

PtrLen<T> extend_swap(ulen delta_len,T objs[]);

PtrLen<T> extend_swap(PtrLen<T> objs);

PtrLen<T> extend(ulen delta_len,CreatorType<T> creator);

PtrLen<T> extend(BuilderType<T> builder);

#endif

/* test1() */

void test1()
 {
  DynArray<int> a;

  ArraySwapIns(a,0,1);
  ArraySwapIns(a,1,2);
  ArraySwapIns(a,2,3);
  ArraySwapIns(a,3,4);
  ArraySwapIns_guarded(a,4,5);

  ArrayCopyIns(a,0,100);
  ArrayCopyIns(a,1,101);
  ArrayCopyIns(a,2,102);
  ArrayCopyIns_guarded(a,3,103);

  Printf(Con,"#;\n",PrintSet(Range(a)));

  ArrayCopyDel(a,0);
  ArrayCopyDel_guarded(a,1);

  Printf(Con,"#;\n",PrintSet(Range(a)));

  ArraySwapDel(a,2);
  ArraySwapDel_guarded(a,3);

  Printf(Con,"#;\n",PrintSet(Range(a)));
 }

/* test2() */

void test2()
 {
  DynArray<int> a{1,2,3,4,5};

  ArrayInsRange_fill(a,6,3,100);
  ArrayInsRange_fill(a,2,5,200);

  Printf(Con,"#;\n",PrintSet(Range(a)));
 }

} // namespace Private_2055

using namespace Private_2055;

/* Testit<2055> */

template<>
const char *const Testit<2055>::Name="Test2055 ArrayInsDel";

template<>
bool Testit<2055>::Main()
 {
  //test1();
  test2();

  return true;
 }

} // namespace App

