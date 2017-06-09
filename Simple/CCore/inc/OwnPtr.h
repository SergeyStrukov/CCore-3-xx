/* OwnPtr.h */
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

#ifndef CCore_inc_OwnPtr_h
#define CCore_inc_OwnPtr_h

#include <CCore/inc/Move.h>

namespace CCore {

/* concept OwnPtrAlgo<Algo,T> */

template <class Algo,class T>
concept bool OwnPtrAlgo = requires(T *obj)
 {
  { Algo::Destroy(obj) } noexcept;
 } ;

/* classes */

template <class T> struct OwnAlgo;

template <class T,class Algo=OwnAlgo<T> > class OwnPtr;

/* struct OwnAlgo<T> */

template <class T>
struct OwnAlgo
 {
  static void Destroy(T *ptr) noexcept requires( NothrowDtorType<T> ) { delete ptr; }
 };

/* class OwnPtr<T,Algo> */

template <class T,class Algo>
class OwnPtr : NoCopy
 {
   T *ptr;

  private:

   static void SoftDestroy(OwnPtr<T,Algo> *obj)
    {
     obj->ptr=0;

     obj->~OwnPtr();
    }

   static void Destroy(T *ptr) requires ( OwnPtrAlgo<Algo,T> )
    {
     if( ptr ) Algo::Destroy(ptr);
    }

  public:

   // constructors

   OwnPtr() noexcept : ptr(0) {}

   explicit OwnPtr(T *ptr_) : ptr(ptr_) {}

   ~OwnPtr() { this->Destroy(ptr); }

   // std move

   OwnPtr(OwnPtr<T,Algo> &&obj) noexcept : ptr(Replace_null(obj.ptr)) {}

   OwnPtr<T,Algo> & operator = (OwnPtr<T,Algo> &&obj) noexcept
    {
     if( this!=&obj )
       {
        this->Destroy(Replace(ptr,Replace_null(obj.ptr)));
       }

     return *this;
    }

   // object ptr

   T * operator + () const { return ptr; }

   bool operator ! () const { return !ptr; }

   T * getPtr() const { return ptr; }

   T & operator * () const { return *ptr; }

   T * operator -> () const { return ptr; }

   // reset

   void set(T *new_ptr) { this->Destroy(Replace(ptr,new_ptr)); }

   T * detach(T *new_ptr=0) { return Replace(ptr,new_ptr); }

   // swap/move objects

   void objSwap(OwnPtr<T,Algo> &obj) { Swap(ptr,obj.ptr); }

   explicit OwnPtr(ToMoveCtor<OwnPtr<T,Algo> > obj) : ptr(Replace_null(obj->ptr)) {}

   OwnPtr<T,Algo> * objMove(Place<void> place)
    {
     OwnPtr<T,Algo> *ret=new(place) OwnPtr<T,Algo>(ptr);

     SoftDestroy(this);

     return ret;
    }
 };

} // namespace CCore

#endif


