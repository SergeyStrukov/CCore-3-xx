/* Sort.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
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

#ifndef CCore_inc_Sort_h
#define CCore_inc_Sort_h

#include <CCore/inc/sort/ShortSort.h>
#include <CCore/inc/sort/HeapSort.h>
#include <CCore/inc/sort/QuickSort.h>
#include <CCore/inc/sort/ParaQuickSort.h>
#include <CCore/inc/sort/MergeSort.h>

namespace CCore {

/* concept ObjLessFuncType<Func,T> */

template <class Func,class T>
concept bool ObjLessFuncType = FuncType<Func,bool,Meta::ToConst<T> &,Meta::ToConst<T> &> ;

/* concept RanLessFuncType<Func,Ran> */

template <class Func,class Ran>
concept bool RanLessFuncType = ObjLessFuncType<Func,Meta::PtrObjType<Ran> > ;

/* classes */

template <RanType Ran,RanLessFuncType<Ran> Func> struct IncrSortCtx;

template <RanType Ran,RanLessFuncType<Ran> Func> struct DecrSortCtx;

/* struct IncrSortCtx<Ran,Func> */

template <RanType Ran,RanLessFuncType<Ran> Func>
struct IncrSortCtx
 {
  Func func;

  IncrSortCtx(const Func &func_) : func(func_) {} // implicit

  static void swap(Ran a,Ran b) { Swap(*a,*b); }

  bool less(Ran a,Ran b) { return func(*a,*b); }
 };

/* struct DecrSortCtx<Ran,Func> */

template <RanType Ran,RanLessFuncType<Ran> Func>
struct DecrSortCtx
 {
  Func func;

  DecrSortCtx(const Func &func_) : func(func_) {} // implicit

  static void swap(Ran a,Ran b) { Swap(*a,*b); }

  bool less(Ran a,Ran b) { return func(*b,*a); }
 };

/* functions */

template <SortRanType Ran,ULenType Len>
void Sort(Ran ptr,Len len) { QuickSort<Ran>::Sort(ptr,len); }

void Sort(PtrLen<OpLessType> range) { Sort(range.ptr,range.len); }

template <RanType Ran,ULenType Len,RanLessFuncType<Ran> Func>
void IncrSort(Ran ptr,Len len,Func less) { QuickSort<Ran,IncrSortCtx<Ran,Func> >::Sort(ptr,len,less); }

template <RanType Ran,ULenType Len,RanLessFuncType<Ran> Func>
void DecrSort(Ran ptr,Len len,Func less) { QuickSort<Ran,DecrSortCtx<Ran,Func> >::Sort(ptr,len,less); }

template <class T,ObjLessFuncType<T> Func>
void IncrSort(PtrLen<T> range,Func less) { IncrSort(range.ptr,range.len,less); }

template <class T,ObjLessFuncType<T> Func>
void DecrSort(PtrLen<T> range,Func less) { DecrSort(range.ptr,range.len,less); }

template <class T,ObjLessFuncType<T> Func>
void IncrSort(PtrLenReverse<T> range,Func less) { DecrSort(range.ptr-range.len,range.len,less); }

template <class T,ObjLessFuncType<T> Func>
void DecrSort(PtrLenReverse<T> range,Func less) { IncrSort(range.ptr-range.len,range.len,less); }

template <OpLessType T>
void Sort(PtrLenReverse<T> range) { IncrSort(range, [] (const T &a,const T &b) -> bool { return a<b; } ); }

} // namespace CCore

#endif


