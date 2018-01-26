/* AnyObjectPtr.h */
//----------------------------------------------------------------------------------------
//
//  Project: Book Convertor 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef App_AnyObjectPtr_h
#define App_AnyObjectPtr_h

#include <CCore/inc/MemAllocGuard.h>
#include <CCore/inc/Tuple.h>

namespace App {

/* using */

using namespace CCore;

/* classes */

template <class ... FF> struct ObjectFuncTable;

template <class T,class ... FF> class ObjectFuncTableOf;

template <class ... FF> class AnyObjectPtr;

/* struct ObjectFuncTable<FF> */

template <class ... FF>
struct ObjectFuncTable
 {
  void (*destroy)(void *obj) noexcept;

  using Methods = Tuple< void (*)(FF &,void *obj) ... > ;

  Methods methods;

  template <OneOfTypes<FF...> Func>
  void apply(Func &func,void *obj) const
   {
    methods.template ref< Meta::IndexOf<Func,FF...> >() (func,obj) ;
   }
 };

/* class ObjectFuncTableOf<T,FF> */

template <class T,class ... FF>
class ObjectFuncTableOf
 {
   static void Destroy(void *obj) noexcept
    {
     static_cast<T *>(obj)->~T();
    }

   template <class Func>
   static void Apply(Func &func,void *obj)
    {
     func( *static_cast<T *>(obj) );
    }

   using Methods = typename ObjectFuncTable<FF...>::Methods ;

   static const ObjectFuncTable<FF...> Table;

  public:

   static const ObjectFuncTable<FF...> * Get() { return &Table; }
 };

template <class T,class ... FF>
const ObjectFuncTable<FF...> ObjectFuncTableOf<T,FF...>::Table={Destroy,Methods{ Apply<FF> ... }};

/* class AnyObjectPtr<FF> */

template <class T>
concept bool AnyObjectType = NothrowDtorType<T> && MoveCtorType<T> ;

template <class ... FF>
class AnyObjectPtr
 {
   void *obj;
   const ObjectFuncTable<FF...> *func;

  private:

   void erase()
    {
     if( obj )
       {
        func->destroy(obj);

        MemFree(obj);
       }
    }

   template <AnyObjectType T>
   void create(T &&obj_)
    {
     MemAllocGuard guard(sizeof (T));

     obj=new(PlaceAt(guard)) T(std::move(obj_));

     guard.disarm();

     func=ObjectFuncTableOf<T,FF...>::Get();
    }

  public:

   template <class T>
   explicit AnyObjectPtr(T &&obj)
    {
     create(std::move(obj));
    }

   ~AnyObjectPtr()
    {
     erase();
    }

   AnyObjectPtr(AnyObjectPtr &&ptr)
    {
     obj=Replace_null(ptr.obj);
     func=ptr.func;
    }

   AnyObjectPtr & operator = (AnyObjectPtr &&ptr)
    {
     if( this!=&ptr )
       {
        erase();

        obj=Replace_null(ptr.obj);
        func=ptr.func;
       }

     return *this;
    }

   template <OneOfTypes<FF...> Func>
   void apply(Func f) const
    {
     if( obj ) func->apply(f,obj);
    }
 };

} // namespace App

#endif

