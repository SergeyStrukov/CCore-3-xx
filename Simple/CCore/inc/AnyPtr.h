/* AnyPtr.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: Simple
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_AnyPtr_h
#define CCore_inc_AnyPtr_h

#include <CCore/inc/FunctorType.h>
#include <CCore/inc/Printf.h>

namespace CCore {

/* ApplyToPtr() */

template <class T,class FuncInit,class ... SS>
void ApplyToPtr(void *ptr,FuncInit func_init,SS && ... ss) requires ( FuncInitArgType<FuncInit,T *,SS...> )
 {
  FunctorTypeOf<FuncInit> func(func_init);

  func(static_cast<T *>(ptr), std::forward<SS>(ss)... );
 }

/* ApplyToPtr_const() */

template <class T,class FuncInit,class ... SS>
void ApplyToPtr_const(const void *ptr,FuncInit func_init,SS && ... ss) requires ( FuncInitArgType<FuncInit,const T *,SS...> )
 {
  FunctorTypeOf<FuncInit> func(func_init);

  func(static_cast<const T *>(ptr), std::forward<SS>(ss)... );
 }

/* ApplyToPtr2() */

template <class Ret,class T,class FuncInit>
Ret ApplyToPtr2(void *ptr1,void *ptr2,FuncInit func_init) requires ( FuncInitType<FuncInit,Ret,T *,T *> )
 {
  FunctorTypeOf<FuncInit> func(func_init);

  return func(static_cast<T *>(ptr1),static_cast<T *>(ptr2));
 }

/* ApplyToPtr2_const() */

template <class Ret,class T,class FuncInit>
Ret ApplyToPtr2_const(const void *ptr1,const void *ptr2,FuncInit func_init) requires ( FuncInitType<FuncInit,Ret,const T *,const T *> )
 {
  FunctorTypeOf<FuncInit> func(func_init);

  return func(static_cast<const T *>(ptr1),static_cast<const T *>(ptr2));
 }

/* concept BinaryRetType<Ret> */

template <class Ret>
concept bool BinaryRetType = requires(unsigned a,unsigned b)
 {
  Ret();

  Ret(a,b);
 } ;

/* classes */

template <PrinterType P> class PrintAnyObj;

template <class ... TT> class AnyPtr;

template <class ... TT> class AnyPtr_const;

template <class T,class S> struct ElaborateAnyPtrBind;

/* class PrintAnyObj<P> */

template <PrinterType P>
class PrintAnyObj
 {
   P &out;

  public:

   explicit PrintAnyObj(P &out_) : out(out_) {}

   void operator () (AnyType *obj)
    {
     Putobj(out,*obj);
    }
 };

/* class AnyPtr<TT> */

template <class ... TT>
class AnyPtr
 {
   void *ptr;
   unsigned type;

  public:

   // constructors

   AnyPtr() noexcept : ptr(0),type(0) {}

   AnyPtr(NothingType) : AnyPtr() {}

   AnyPtr(std::nullptr_t) : AnyPtr() {}

   template <class T>
   AnyPtr(T *ptr_) : ptr(ptr_),type(Meta::IndexOf<T,TT...>) {}

   // methods

   void * operator + () const { return ptr; }

   bool operator ! () const { return !ptr; }

   template <class T>
   bool hasType() const { return type==Meta::IndexOf<T,TT...>; }

   template <class T>
   T * castPtr() const { if( hasType<T>() ) return static_cast<T *>(ptr); return 0; }

   template <class FuncInit,class ... SS>
   void apply(FuncInit func_init,SS && ... ss) const requires ( ... && FuncInitArgType<FuncInit,TT *,SS...> )
    {
     using FuncType = void (*)(void *ptr,FuncInit func_init,SS && ...) ;

     static const FuncType Table[]={ ApplyToPtr<TT,FuncInit,SS...>... };

     if( type ) Table[type-1](ptr,func_init, std::forward<SS>(ss)... );
    }

   template <class T,class FuncInit>
   void applyFor(FuncInit func_init) const requires ( FuncInitArgType<FuncInit,T *> )
    {
     if( hasType<T>() ) ApplyToPtr<T>(ptr,func_init);
    }

   // Binary

   template <BinaryRetType Ret,class FuncInit>
   static Ret Binary(AnyPtr<TT...> a,AnyPtr<TT...> b,FuncInit func_init) requires ( ... && FuncInitType<FuncInit,Ret,TT *,TT *> )
    {
     if( a.type!=b.type ) return Ret(a.type,b.type);

     using FuncType = Ret (*)(void *,void *,FuncInit func_init) ;

     static const FuncType Table[]={ ApplyToPtr2<Ret,TT,FuncInit>... };

     if( a.type ) return Table[a.type-1](a.ptr,b.ptr,func_init);

     return Ret();
    }

   // print object

   template <PrinterType P>
   void print(P &out) const
    {
     if( ptr )
       apply(PrintAnyObj<P>(out));
     else
       Putobj(out,"(null)");
    }
 };

/* class AnyPtr_const<TT> */

template <class ... TT>
class AnyPtr_const
 {
   const void *ptr;
   unsigned type;

  public:

   // constructors

   AnyPtr_const() noexcept : ptr(0),type(0) {}

   AnyPtr_const(NothingType) : AnyPtr_const() {}

   AnyPtr_const(std::nullptr_t) : AnyPtr_const() {}

   template <class T>
   AnyPtr_const(const T *ptr_) : ptr(ptr_),type(Meta::IndexOf<T,TT...>) {}

   // methods

   const void * operator + () const { return ptr; }

   bool operator ! () const { return !ptr; }

   template <class T>
   bool hasType() const { return type==Meta::IndexOf<T,TT...>; }

   template <class T>
   const T * castPtr() const { if( hasType<T>() ) return static_cast<const T *>(ptr); return 0; }

   template <class FuncInit,class ... SS>
   void apply(FuncInit func_init,SS && ... ss) const requires ( ... && FuncInitArgType<FuncInit,const TT *,SS...> )
    {
     using FuncType = void (*)(const void *ptr,FuncInit func_init,SS && ...) ;

     static const FuncType Table[]={ ApplyToPtr_const<TT,FuncInit,SS...>... };

     if( type ) Table[type-1](ptr,func_init, std::forward<SS>(ss)... );
    }

   template <class T,class FuncInit>
   void applyFor(FuncInit func_init) const requires ( FuncInitArgType<FuncInit,const T *> )
    {
     if( hasType<T>() ) ApplyToPtr_const<T>(ptr,func_init);
    }

   // Binary

   template <BinaryRetType Ret,class FuncInit>
   static Ret Binary(AnyPtr_const<TT...> a,AnyPtr_const<TT...> b,FuncInit func_init) requires ( ... && FuncInitType<FuncInit,Ret,const TT *,const TT *> )
    {
     if( a.type!=b.type ) return Ret(a.type,b.type);

     using FuncType = Ret (*)(const void *,const void *,FuncInit func_init) ;

     static const FuncType Table[]={ ApplyToPtr2_const<Ret,TT,FuncInit>... };

     if( a.type ) return Table[a.type-1](a.ptr,b.ptr,func_init);

     return Ret();
    }

   // print object

   template <PrinterType P>
   void print(P &out) const
    {
     if( ptr )
       apply(PrintAnyObj<P>(out));
     else
       Putobj(out,"(null)");
    }
 };

/* concept ElaborateAnyPtrType<T> */

template <class T>
concept bool ElaborateAnyPtrType = requires (T &obj) { { obj } -> const AnyPtr<AnyType...> & ; } ||
                                   requires (T &obj) { { obj } -> const AnyPtr_const<AnyType...> & ; } ;

/* struct ElaborateAnyPtrBind<T,S> */

template <class T,class S>
struct ElaborateAnyPtrBind
 {
  T &obj;
  S &&arg;

  ElaborateAnyPtrBind(T &obj_,S &&arg_) : obj(obj_),arg( std::forward<S>(arg_) ) {}

  template <class ... SS>
  void operator () (SS && ... ss)
   {
    obj( std::forward<S>(arg) , std::forward<SS>(ss)... );
   }
 };

template <class T,ElaborateAnyPtrType S>
struct ElaborateAnyPtrBind<T,S>
 {
  T &obj;
  S &&arg;

  ElaborateAnyPtrBind(T &obj_,S &&arg_) : obj(obj_),arg( std::forward<S>(arg_) ) {}

  template <class ... SS>
  void operator () (SS && ... ss)
   {
    arg.apply( FunctorRef(obj) , std::forward<SS>(ss)... );
   }
 };

/* ElaborateAnyPtr() */

template <class T>
void ElaborateAnyPtr(T &obj)
 {
  obj();
 }

template <class T,class S,class ... SS>
void ElaborateAnyPtr(T &obj,S && s,SS && ... ss)
 {
  ElaborateAnyPtrBind<T,S> bind(obj, std::forward<S>(s) );

  ElaborateAnyPtr(bind, std::forward<SS>(ss)... );
 }

/* CastAnyPtr() */

template <class T,class S>
T CastAnyPtr(S obj)
 {
  T ret;

  obj.apply( [&ret] (auto *ptr) { ret=ptr; } );

  return ret;
 }

} // namespace CCore

#endif
