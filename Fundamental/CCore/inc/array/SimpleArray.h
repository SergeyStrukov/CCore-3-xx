/* SimpleArray.h */
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

#ifndef CCore_inc_array_SimpleArray_h
#define CCore_inc_array_SimpleArray_h

#include <CCore/inc/array/ArrayAlgo.h>

#include <CCore/inc/MemAllocGuard.h>

#include <CCore/inc/algon/ApplyToRange.h>

namespace CCore {

/* classes */

template <class T,class Algo=ArrayAlgo_mini<T> > class SimpleArray;

/* class SimpleArray<T,Algo> */

template <class T,class Algo>
class SimpleArray : NoCopy
 {
   T *ptr;
   ulen len;

  public:

   // constructors

   SimpleArray() noexcept
    {
     ptr=0;
     len=0;
    }

   explicit SimpleArray(ulen len);

   ~SimpleArray();

   // std move

   SimpleArray(SimpleArray<T,Algo> &&obj) noexcept
    {
     ptr=Replace_null(obj.ptr);
     len=Replace_null(obj.len);
    }

   SimpleArray<T,Algo> & operator = (SimpleArray<T,Algo> &&obj) noexcept
    {
     if( this!=&obj )
       {
        SimpleArray<T,Algo> todel;

        todel.ptr=Replace(ptr,Replace_null(obj.ptr));
        todel.len=Replace(len,Replace_null(obj.len));
       }

     return *this;
    }

   // methods

   void erase()
    {
     SimpleArray<T,Algo> temp;

     Swap(*this,temp);
    }

   // range access

   T * getPtr() { return ptr; }

   const T * getPtr() const { return ptr; }

   const T * getPtr_const() const { return ptr; }

   ulen getLen() const { return len; }

   // index access

   T & operator [] (ulen index)
    {
     return ptr[index];
    }

   const T & operator [] (ulen index) const
    {
     return ptr[index];
    }

   T & at(ulen index)
    {
     GuardIndex(index,len);

     return ptr[index];
    }

   const T & at(ulen index) const
    {
     GuardIndex(index,len);

     return ptr[index];
    }

   // apply

   auto apply(FuncInitArgType<T &> func_init) { return Algon::ApplyToRange(Range(*this),func_init); }

   auto apply(FuncInitArgType<const T &> func_init) const { return Algon::ApplyToRange(Range(*this),func_init); }

   auto apply_const(FuncInitArgType<const T &> func_init) const { return Algon::ApplyToRange(Range(*this),func_init); }

   auto applyReverse(FuncInitArgType<T &> func_init) { return Algon::ApplyToRange(RangeReverse(*this),func_init); }

   auto applyReverse(FuncInitArgType<const T &> func_init) const { return Algon::ApplyToRange(RangeReverse(*this),func_init); }

   auto applyReverse_const(FuncInitArgType<const T &> func_init) const { return Algon::ApplyToRange(RangeReverse(*this),func_init); }

   // swap/move objects

   void objSwap(SimpleArray<T,Algo> &obj)
    {
     Swap(ptr,obj.ptr);
     Swap(len,obj.len);
    }

   explicit SimpleArray(ToMoveCtor<SimpleArray<T,Algo> > obj)
    : ptr(obj->ptr),
      len(Replace_null(obj->len))
    {
    }
 };

template <class T,class Algo>
SimpleArray<T,Algo>::SimpleArray(ulen len_)
 {
  if( len_ )
    {
     MemAllocGuardOf<Algo> mem(len_,sizeof (T));

     ptr=Algo::Create_default(PlaceAt(mem),len_).ptr;
     len=len_;

     mem.disarm();
    }
  else
    {
     ptr=0;
     len=0;
    }
 }

template <class T,class Algo>
SimpleArray<T,Algo>::~SimpleArray()
 {
  if( len )
    {
     Algo::Destroy(ptr,len);

     Algo::MemFree(ptr);
    }
 }

} // namespace CCore

#endif


