/* RefPtr.h */
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

#ifndef CCore_inc_RefPtr_h
#define CCore_inc_RefPtr_h

#include <CCore/inc/Move.h>

namespace CCore {

/* concept RefPtrAlgo<Algo,T> */

template <class Algo,class T>
concept bool RefPtrAlgo = requires(T *obj)
 {
  Algo::IncRef(obj);

  { Algo::DecRef(obj) } -> bool ;

  { Algo::Destroy(obj) } noexcept;
 } ;

/* concept RefCountType<T> */

template <class T>
concept bool RefCountType = requires(T &obj)
 {
  obj.incRef();

  { obj.decRef() } -> bool ;

  { obj.destroy() } noexcept ;
 } ;

/* classes */

template <class T> struct RefAlgo;

template <class T,class Algo=RefAlgo<T> > class RefPtr;

/* struct RefAlgo<T> */

template <class T>
struct RefAlgo
 {
  static void IncRef(T *ptr) requires ( RefCountType<T> ) { ptr->incRef(); }

  static bool DecRef(T *ptr) requires ( RefCountType<T> ) { return ptr->decRef(); }

  static void Destroy(T *ptr) noexcept requires ( RefCountType<T> ) { ptr->destroy(); }
 };

/* class RefPtr<T,Algo> */

template <class T,class Algo>
class RefPtr
 {
   T *ptr;

  private:

   static void SoftDestroy(RefPtr<T,Algo> *obj)
    {
     obj->ptr=0;

     obj->~RefPtr();
    }

   static void Hold(T *ptr) requires( RefPtrAlgo<Algo,T> )
    {
     Algo::IncRef(ptr);
    }

   static void Release(T *ptr) requires( RefPtrAlgo<Algo,T> )
    {
     if( Algo::DecRef(ptr) ) Algo::Destroy(ptr);
    }

  public:

   // constructors

   explicit RefPtr(T *ptr_) : ptr(ptr_) {} // ptr_!=0

   ~RefPtr() { if( ptr ) this->Release(ptr); }

   // copying

   RefPtr(const RefPtr<T,Algo> &obj) noexcept : ptr(obj.ptr) { this->Hold(ptr); }

   RefPtr<T,Algo> & operator = (const RefPtr<T,Algo> &obj) noexcept
    {
     T *new_ptr=obj.ptr;
     T *old_ptr=Replace(ptr,new_ptr);

     this->Hold(new_ptr);
     this->Release(old_ptr);

     return *this;
    }

   // object ptr

   T * getPtr() const { return ptr; }

   T & operator * () const { return *ptr; }

   T * operator -> () const { return ptr; }

   // reset

   void set(T *new_ptr) noexcept // new_ptr!=0
    {
     this->Release(Replace(ptr,new_ptr));
    }

   // update

   void update(FuncType<T *,T *> func) { ptr=func(ptr); }

   // swap/move objects

   void objSwap(RefPtr<T,Algo> &obj) { Swap(ptr,obj.ptr); }

   explicit RefPtr(ToMoveCtor<RefPtr<T,Algo> > obj) : ptr(Replace_null(obj->ptr)) {}

   RefPtr<T,Algo> * objMove(Place<void> place)
    {
     RefPtr<T,Algo> *ret=new(place) RefPtr<T,Algo>(ptr);

     SoftDestroy(this);

     return ret;
    }
 };

} // namespace CCore

#endif


