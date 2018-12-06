/* Linker.h */
//----------------------------------------------------------------------------------------
//
//  Project: BookLab 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef Linker_h
#define Linker_h

#include <inc/BookElements.h>

#include <CCore/inc/ElementPool.h>
#include <CCore/inc/StrKey.h>

namespace App {
namespace BookLab {

/* classes */

class ScopeCursor;

class Linker;

/* class ScopeCursor */

class ScopeCursor
 {
   Scope *ptr;

  private:

   void set(IntAnyObjPtr<Scope,Doc> scope) { ptr=scope.getPtr().castPtr<Scope>(); }

  public:

   explicit ScopeCursor(IntAnyObjPtr<Scope,Doc> scope) { set(scope); }

   Scope * operator + () const { return ptr; }

   StrLen operator * () const { return Range(ptr->name); }

   void operator ++ () { set(ptr->scope); }
 };

/* class Linker */

class Linker : NoCopy
 {
   struct Base
    {
     StrKey name;
     PtrLen<StrKey> path;
    };

   template <class T>
   struct Name : Base
    {
     IntObjPtr<T> ptr;
    };

   template <class T>
   struct Ptr : Base
    {
     IntObjPtr<T> *ptr;
    };

   template <class ... TT>
   struct APtr : Base
    {
     IntAnyObjPtr<TT...> *ptr;
    };

   PrintBase &eout;
   ElementPool pool;
   Collector<Base *> collector;

  private:

   void fill(Base *obj,IntAnyObjPtr<Scope,Doc> scope,StrLen name);

   void append(Base *obj,IntAnyObjPtr<Scope,Doc> scope,StrLen name);

   bool fillPtr(Base *obj,IntAnyObjPtr<Scope,Doc> scope,StrLen name);

   void appendPtr(Base *obj,IntAnyObjPtr<Scope,Doc> scope,StrLen name);

   bool linkName(PtrLen<Base *> list);

   bool link(PtrLen<Base *> list);

  public:

   explicit Linker(PrintBase &eout);

   ~Linker();

   template <class T>
   void addName(IntAnyObjPtr<Scope,Doc> scope,StrLen name,IntObjPtr<T> ptr)
    {
     Name<T> *obj=pool.create<Name<T> >();

     obj->ptr=ptr;

     append(obj,scope,name);
    }

   template <class T>
   void addPtr(IntAnyObjPtr<Scope,Doc> scope,StrLen name,IntObjPtr<T> &ptr)
    {
     Ptr<T> *obj=pool.create<Ptr<T> >();

     obj->ptr=&ptr;

     appendPtr(obj,scope,name);
    }

   template <class ... TT>
   void addPtr(IntAnyObjPtr<Scope,Doc> scope,StrLen name,IntAnyObjPtr<TT...> &ptr)
    {
     APtr<TT...> *obj=pool.create<APtr<TT...> >();

     obj->ptr=&ptr;

     appendPtr(obj,scope,name);
    }

   bool link();
 };

} // namespace BookLab
} // namespace App

#endif
