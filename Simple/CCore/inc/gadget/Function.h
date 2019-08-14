/* Function.h */
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

#ifndef CCore_inc_gadget_Function_h
#define CCore_inc_gadget_Function_h

#include <CCore/inc/base/PlatformBase.h>

#include <CCore/inc/gadget/Handle.h>
#include <CCore/inc/gadget/Nothing.h>
#include <CCore/inc/gadget/NoCopy.h>
#include <CCore/inc/gadget/Meta.h>

namespace CCore {

/* classes */

template <class FuncType> class Function;

struct Funchor; // Fu(nction) (A)nchor

template <class FuncType,class T> struct ToFunctionClass;

/* class Function<R,AA> */

template <class R,class ... AA>
class Function<R (AA...)>
 {
   Funchor *obj;

   struct CtxFunc
    {
     Handle ctx;
     R (*func)(Handle ctx,AA...);
    };

   union
    {
     CtxFunc ptr;
     R (Funchor::*method)(AA...);
    };

  private:

   static R EmptyFunction(AA ...)
    {
     if constexpr( !Meta::IsSame<R,void> ) return {};
    }

   static R FuncProxy(Handle ctx,AA ... aa)
    {
     auto func_ptr=(R (*)(AA...))ctx.func_ptr;

     return func_ptr(aa...);
    }

   void init(R (*func)(AA...))
    {
     obj=0;
     ptr.func=FuncProxy;
     ptr.ctx=(Handle::FuncPtr)func;
    }

  public:

   // constructors

   Function() noexcept
    {
     init(EmptyFunction);
    }

   Function(NothingType) : Function() {}

   Function(R (*func)(AA...))
    {
     init(func);
    }

   Function(R (*func)(Handle ctx,AA...),Handle ctx)
    {
     obj=0;
     ptr.func=func;
     ptr.ctx=ctx;
    }

   template <class T>
   Function(T *obj_,R (T::*method_)(AA...))
    {
     obj=obj_;
     method=static_cast<R (Funchor::*)(AA...)>(method_);
    }

   // methods

   bool operator + () const { return obj!=0 || ptr.func!=FuncProxy || ptr.ctx.func_ptr!=(Handle::FuncPtr)EmptyFunction; }

   bool operator ! () const { return obj==0 && ptr.func==FuncProxy && ptr.ctx.func_ptr==(Handle::FuncPtr)EmptyFunction; }

   template <class ... TT>
   R operator () (TT && ... tt) const
    {
     if( obj ) return (obj->*method)( std::forward<TT>(tt)... );

     return ptr.func(ptr.ctx, std::forward<TT>(tt)... );
    }
 };

/* struct Funchor */

struct Funchor
 {
  template <class T,class R,class ... AA>
  static Function<R (AA...)> FunctionOf(T *obj,R (T::*method)(AA...))
   {
    return Function<R (AA...)>(obj,method);
   }
 };

 //
 // class T : public Funchor
 //  {
 //   public:
 //
 //    void method();
 //
 //    Function<void (void)> function_method() { return FunctionOf(this,&T::method); }
 //  };
 //

/* type Funchor_nocopy */

using Funchor_nocopy = NoCopyBase<Funchor> ;

/* struct ToFunctionClass<FuncType,T> */

template <class T,class R,class ... AA>
struct ToFunctionClass<R (AA...),T> : Funchor
 {
  T obj;

  explicit ToFunctionClass(const T &obj_) : obj(obj_) {}

  R proxy(AA ... aa) { return obj( std::forward<AA>(aa)... ); }

  Function<R (AA...)> function() { return FunctionOf(this,&ToFunctionClass::proxy); }
 };

/* ToFunction() */

template <class FuncType,class T>
ToFunctionClass<FuncType,T> ToFunction(const T &obj) { return ToFunctionClass<FuncType,T>(obj); }

} // namespace CCore

#endif


