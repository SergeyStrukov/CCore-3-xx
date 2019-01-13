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
#include <CCore/inc/TypeSwitch.h>

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
     bool def;
    };

   struct NameBase : Base
    {
     using CaseList = Meta::CaseList< Meta::Case<int,1,Font> ,
                                      Meta::Case<int,2,Format> ,
                                      Meta::Case<int,3,SingleLine> ,
                                      Meta::Case<int,4,DoubleLine> ,
                                      Meta::Case<int,5,Page> ,
                                      Meta::Case<int,6,Scope> ,
                                      Meta::Case<int,7,Bitmap> ,
                                      Meta::Case<int,8,Collapse> ,
                                      Meta::Case<int,9,TextList> ,
                                      Meta::Case<int,10,Border> ,
                                      Meta::Case<int,11,Cell> ,
                                      Meta::Case<int,12,Table> ,
                                      Meta::Case<int,13,Link> ,
                                      Meta::Case<int,14,FixedText> ,
                                      Meta::Case<int,15,OneLine> ,
                                      Meta::Case<int,16,MultiLine> ,
                                      Meta::Case<int,17,Text> > ;

     int type;

     NameBase() { def=true; }

     template <class Arg>
     struct Ctx
      {
       NameBase *def;
       Arg arg;

       using RetType = bool ;

       template <class T>
       RetType call();

       RetType defcall(int) { return false; }
      };

     template <class Arg>
     bool setBy(Arg arg)
      {
       Ctx<Arg> ctx{this,arg};

       return Meta::TypeSwitch<CaseList>::Switch(type,ctx);
      }
    };

   template <class T>
   struct Name : NameBase
    {
     IntObjPtr<T> ptr;

     Name() { type=Meta::CaseVal<CaseList,T>; }

     template <class S>
     bool set(IntObjPtr<S> *) { return false; }

     bool set(IntObjPtr<T> *dst)
      {
       *dst=ptr;

       return true;
      }

     template <class ... TT>
     bool set(IntAnyObjPtr<TT...> *)
      {
       return false;
      }

     template <class ... TT>
     bool set(IntAnyObjPtr<TT...> *dst) requires( OneOfTypes<T,TT...> )
      {
       *dst=ptr;

       return true;
      }
    };

   struct PtrBase : Base
    {
     PtrLen<StrKey> ext;
     bool abs = false ;

     bool (*assign)(PtrBase *req,NameBase *def);

     PtrBase() { def=false; }
    };

   template <class T>
   struct Ptr : PtrBase
    {
     IntObjPtr<T> *ptr;

     static bool Assign(PtrBase *req,NameBase *def) { return static_cast<Ptr<T> *>(req)->set(def); }

     Ptr() { assign=Assign; }

     bool set(NameBase *def) { return def->setBy(ptr); }
    };

   template <class ... TT>
   struct APtr : PtrBase
    {
     IntAnyObjPtr<TT...> *ptr;

     static bool Assign(PtrBase *req,NameBase *def) { return static_cast<APtr<TT...> *>(req)->set(def); }

     APtr() { assign=Assign; }

     bool set(NameBase *def) { return def->setBy(ptr); }
    };

   PrintBase &eout;
   ElementPool pool;
   Collector<Base *> collector;

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

   struct PrintPathName;

   struct NeqPath;

   static bool LessPrefix(Base *a,Base *b);

   static bool LessSuffix(Base *a,Base *b);

   bool linkNameAbs(PtrLen<Base *> list);

   static PtrLen<Base *> ClipStep(PtrLen<Base *> list,ulen ind,StrKey key);

   static PtrLen<Base *> ClipSuffix(PtrLen<Base *> list,PtrLen<StrKey> ext);

   static Base * Find(PtrLen<Base *> list,ulen delta,PtrLen<StrKey> path);

   bool linkRel(PtrLen<Base *> def,Base *base);

   bool linkName(PtrLen<Base *> list);

   bool assign(PtrBase *req,Base *def);

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

     ptr=Null;

     appendPtr(obj,scope,name);
    }

   template <class ... TT>
   void addPtr(IntAnyObjPtr<Scope,Doc> scope,StrLen name,IntAnyObjPtr<TT...> &ptr)
    {
     APtr<TT...> *obj=pool.create<APtr<TT...> >();

     obj->ptr=&ptr;

     ptr=Null;

     appendPtr(obj,scope,name);
    }

   bool link();
 };

template <class Arg>
template <class T>
auto Linker::NameBase::Ctx<Arg>::call() -> RetType
 {
  return static_cast<Name<T> *>(def)->set(arg);
 }

} // namespace BookLab
} // namespace App

#endif
