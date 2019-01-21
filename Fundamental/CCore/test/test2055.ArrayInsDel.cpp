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

namespace App {

namespace Private_2055 {

/* --- */

ulen RangeCopyDel(NothrowCopyableType list[],ulen len,ulen ind,ulen count)
 {
  if( ind>=len || !count ) return 0;

  ulen rest=len-ind;

  if( count<rest )
    {
     for(rest-=count; rest ;rest--,ind++) list[ind]=list[ind+count];

     return count;
    }
  else
    {
     return rest;
    }
 }

ulen RangeCopyDel(PtrLen<NothrowCopyableType> range,ulen ind,ulen count)
 {
  return RangeCopyDel(range.ptr,range.len,ind,count);
 }

ulen RangeSwapDel(AnyType list[],ulen len,ulen ind,ulen count)
 {
  if( ind>=len || !count ) return 0;

  ulen rest=len-ind;

  if( count<rest )
    {
     for(rest-=count; rest ;rest--,ind++) Swap(list[ind],list[ind+count]);

     return count;
    }
  else
    {
     return rest;
    }
 }

ulen RangeSwapDel(PtrLen<AnyType> range,ulen ind,ulen count)
 {
  return RangeSwapDel(range.ptr,range.len,ind,count);
 }

/* del functions */

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

#if 0

template <class A>
void ArrayCopyDelRange_guarded(A &array,ulen ind,ulen count)
 {
  RangeCopyDel_guarded(Range(a),ind);

  a.shrink_one();
 }

template <class A>
void ArraySwapDelRange_guarded(A &array,ulen ind,ulen count)
 {
  RangeSwapDel_guarded(Range(a),ind);

  a.shrink_one();
 }

#endif

/* struct OddList */

struct OddList
 {
  int i,n;

  OddList(int i_,int n_) : i(i_),n(n_) {}

  ulen getLen() const { return n; }

  PtrLen<int> operator () (Place<void> place)
   {
    int *base=place;
    int *ptr=base;

    for(int v=i; v<i+n ;v++) if( v&1 ) *(ptr++)=v;

    return Range(base,ptr);
   }
 };

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

  ArrayInsRange(a,6,2, Creator_default<int,true>() );
  ArrayInsRange(a,2, OddList(5,5) );

  Printf(Con,"#;\n",PrintSet(Range(a)));
 }

/* test3() */

void test3()
 {
  DynArray<int> a{1,2,3,4,5};

  //ArrayInsRangeGuard(a,10);
  //ArrayInsRangeFill(a,10);
  ArrayInsRangeFill(a,10,5);

  ArrayInsRange_fill(a,10,5,100);

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
  //test2();
  test3();

  return true;
 }

} // namespace App

