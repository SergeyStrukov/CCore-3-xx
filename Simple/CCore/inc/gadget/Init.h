/* Init.h */
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

#ifndef CCore_inc_gadget_Init_h
#define CCore_inc_gadget_Init_h

#include <CCore/inc/gadget/Place.h>

namespace CCore {

/* functions */

void NoObjectAbort();

/* classes */

template <ulen Len> struct InitStorage;

template <class T> struct InitExitObject;

/* struct InitStorage<ulen Len> */

template <ulen Len>
struct InitStorage
 {
  // storage

  Meta::AlignedStorage<Len> storage;

  // methods

  void * getMem() { return &storage; }

  Place<void> getPlace() { return PlaceAt(getMem()); }

  const void * getMem() const { return &storage; }

  Place<const void> getPlace() const { return PlaceAt(getMem()); }
 };

/* struct InitExitObject<T> */

template <class T>
struct InitExitObject
 {
  // private data

  InitStorage<sizeof (T)> storage;

  T *obj;

  // init/exit

  void clean() { obj=0; }

   // prior value initialization is required or clean()

  template <class ... SS>
  void init(SS && ... ss) requires ( ConstructibleType<T,SS...> )
   {
    if( obj ) return;

    static_assert( Meta::IsPOD<InitExitObject<T> > ,"CCore::InitExitObject<T> must be POD");

    obj=new(storage.getPlace()) T( std::forward<SS>(ss)... );
   }

  void exit()
   {
    if( !obj ) return;

    Replace_null(obj)->~T();
   }

  // object ptr

  T * operator + () const { return obj; }

  bool operator ! () const { return !obj; }

  T * getPtr_unsafe() const { return obj; }

  T * getPtr() const
   {
    if( !obj ) NoObjectAbort();

    return obj;
   }

  T & operator * () const { return *getPtr(); }

  T * operator -> () const { return getPtr(); }
 };

} // namespace CCore

#endif


