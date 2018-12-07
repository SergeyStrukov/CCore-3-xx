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

class NameCursor;

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

/* class NameCursor */

class NameCursor
 {
   StrLen path;
   StrLen name;
   bool ok;

  private:

   void set(StrLen text);

  public:

   explicit NameCursor(StrLen text) { set(text); }

   bool operator + () const { return ok; }

   bool operator ! () const { return !ok; }

   StrLen operator * () const { return name; }

   void operator ++ () { set(path); }
 };

/* class Linker */

class Linker : NoCopy
 {
   struct Base
    {
     StrKey name;
     PtrLen<StrKey> path;
     bool def = true ;
    };

   template <class T>
   struct Name : Base
    {
     IntObjPtr<T> ptr;
    };

   struct PtrBase : Base
    {
     PtrLen<StrKey> ext;
     bool abs = false ;

     PtrBase() { def=false; }
    };

   template <class T>
   struct Ptr : PtrBase
    {
     IntObjPtr<T> *ptr;
    };

   template <class ... TT>
   struct APtr : PtrBase
    {
     IntAnyObjPtr<TT...> *ptr;
    };

   PrintBase &eout;
   ElementPool pool;
   Collector<Base *> collector;

  private:

   bool assign(PtrBase *req,Base *def);

  private:

   void fillPath(Base *obj,IntAnyObjPtr<Scope,Doc> scope);

   void fill(Base *obj,IntAnyObjPtr<Scope,Doc> scope,StrLen name);

   void append(Base *obj,IntAnyObjPtr<Scope,Doc> scope,StrLen name);

   PtrLen<StrKey> makeExt(NameCursor cur,ulen count);

   void fillPtrRel(PtrBase *obj,IntAnyObjPtr<Scope,Doc> scope,NameCursor cur,ulen count);

   void fillPtrAbs(PtrBase *obj,NameCursor cur,ulen count);

   bool fillPtr(PtrBase *obj,IntAnyObjPtr<Scope,Doc> scope,StrLen name);

   void appendPtr(PtrBase *obj,IntAnyObjPtr<Scope,Doc> scope,StrLen name);

   bool link(PtrLen<Base *> list);

  private:

   struct PrintPath;

   struct NeqPath;

   static bool LessPrefix(Base *a,Base *b);

   bool linkNameAbs(PtrLen<Base *> list);

   bool linkName(PtrLen<Base *> list);

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
